#include "rc4.h"

std::string diccionario = "EAOLSNDRUITCPMYQ";

void inicializar_rc4(std::vector<uint8_t>& S, const std::string& clave) {
    int clave_len = clave.size();
    for (int i = 0; i < 256; ++i) {
        S[i] = static_cast<uint8_t>(i);
    }

    int j = 0;
    for (int i = 0; i < 256; ++i) {
        j = (j + S[i] + clave[i % clave_len]) % 256;
        std::swap(S[i], S[j]);
    }
}

std::string byte_a_binario(uint8_t byte) {
    return std::bitset<8>(byte).to_string();
}

std::string caracter_a_5bits(char c) {
    auto pos = diccionario.find(c);
    if (pos != std::string::npos) {
        return std::bitset<5>(pos).to_string(); 
    }
    else {
        return "ERROR"; 
    }
}

std::string rc4(const std::string& datos, const std::string& clave) {
    std::vector<uint8_t> S(256);
    inicializar_rc4(S, clave);
    int i = 0, j = 0;
    std::string salida;
    salida.reserve(datos.size());

    std::ofstream archivo_keystream("rc4_keystream.txt");
    std::ofstream archivo_xor("rc4_xor.txt");
    std::ofstream archivo_cifrado("rc4_cifrado.txt");

    if (!archivo_keystream.is_open() || !archivo_xor.is_open() || !archivo_cifrado.is_open()) {
        std::cerr << "Error al abrir los archivos de salida." << std::endl;
        return "";
    }

    for (size_t n = 0; n < datos.size(); ++n) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        std::swap(S[i], S[j]);
        uint8_t keystream_byte = S[(S[i] + S[j]) % 256];

        archivo_keystream << "Paso " << n + 1 << ": " << byte_a_binario(keystream_byte) << std::endl;

        char mensaje_byte = datos[n];
        std::string mensaje_binario_5bits = caracter_a_5bits(mensaje_byte);
        std::string keystream_binario_5bits = byte_a_binario(keystream_byte & 0x1F);
        if (mensaje_binario_5bits != "ERROR") {
            std::string xor_resultado;
            for (int k = 0; k < 5; ++k) {
                xor_resultado += (mensaje_binario_5bits[k] == keystream_binario_5bits[k]) ? '0' : '1';
            }

            int valor_xor = std::bitset<5>(xor_resultado).to_ulong();
            if (valor_xor < diccionario.size()) {  
                archivo_xor << "Paso " << n + 1 << " - Mensaje: " << mensaje_binario_5bits
                    << " XOR KeyStream: " << keystream_binario_5bits
                    << " = " << xor_resultado << std::endl;

                archivo_cifrado << diccionario[valor_xor];
            }
            else {
                std::cerr << "Error: valor fuera del rango del diccionario en el paso " << n + 1 << std::endl;
                return "";  
            }
        }
        else {
            archivo_xor << "Paso " << n + 1 << ": ERROR en el carácter del mensaje no válido" << std::endl;
        }

        salida.push_back(datos[n] ^ keystream_byte);
    }

    archivo_keystream.close();
    archivo_xor.close();
    archivo_cifrado.close();

    return salida;
}

std::string fuerza_bruta_rc4(const std::string& texto_cifrado, const std::string& palabra_original) {
    int contador = 0;
    for (char c1 : diccionario) {
        for (char c2 : diccionario) {
            for (char c3 : diccionario) {
                for (char c4 : diccionario) {
                    std::string clave_prueba = { c1, c2, c3, c4 };
                    std::string descifrado = rc4(texto_cifrado, clave_prueba);

                    contador++;
                    std::cout << "Probando clave: " << clave_prueba << " resultado obtenido "<< descifrado <<" Intento numero : " << contador  << std::endl;  

                    if (descifrado == palabra_original) {
						std::cout << "Clave encontrada tras " << contador << " intentos." << std::endl;
                        return clave_prueba;
                    }
                }
            }
        }
    }
    std::cout << "Clave no encontrada tras " << contador << " intentos." << std::endl;  
    return "";
}
