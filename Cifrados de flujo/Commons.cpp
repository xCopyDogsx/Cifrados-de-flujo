#include "commons.h"

std::string a_hex(const std::string& entrada) {
    static const char hex_digitos[] = "0123456789ABCDEF";
    std::string salida;
    salida.reserve(entrada.size() * 2);
    for (unsigned char c : entrada) {
        salida.push_back(hex_digitos[c >> 4]);
        salida.push_back(hex_digitos[c & 0x0F]);
    }
    return salida;
}

std::string de_hex(const std::string& entrada) {
    std::string salida;
    salida.reserve(entrada.size() / 2);
    for (size_t i = 0; i < entrada.size(); i += 2) {
        unsigned char alto = (entrada[i] > '9') ? (entrada[i] - 'A' + 10) : (entrada[i] - '0');
        unsigned char bajo = (entrada[i + 1] > '9') ? (entrada[i + 1] - 'A' + 10) : (entrada[i + 1] - '0');
        salida.push_back((alto << 4) | bajo);
    }
    return salida;
}

std::vector<uint32_t> cadena_a_u32vector(const std::string& entrada) {
    std::vector<uint32_t> salida(16, 0);
    for (size_t i = 0; i < entrada.size() && i < 64; i++) {
        salida[i / 4] |= (static_cast<uint32_t>(static_cast<unsigned char>(entrada[i])) << ((i % 4) * 8));
    }
    return salida;
}

std::string u32vector_a_cadena(const std::vector<uint32_t>& entrada) {
    std::string salida;
    for (size_t i = 0; i < 16; i++) {
        for (int j = 0; j < 4; j++) {
            char ch = (entrada[i] >> (j * 8)) & 0xFF;
            salida += ch;
        }
    }
    return salida;
}

std::string xor_cadenas(const std::string& s1, const std::string& s2) {
    std::string resultado;
    resultado.reserve(s1.size());
    for (size_t i = 0; i < s1.size(); ++i) {
        resultado.push_back(s1[i] ^ s2[i]);
    }
    return resultado;
}

void imprimir_escapado(const std::string& s) {
    std::stringstream ss;
    for (unsigned char c : s) {
        if (c >= 32 && c <= 126) {
            ss << c;
        }
        else {
            ss << "\\x" << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(c);
        }
    }
    std::cout << ss.str() << std::endl;
}

void imprimir_estado_en_archivo(const uint32_t estado[16], int ronda, bool es_salsa20, std::ofstream& archivo) {
    std::string algoritmo = es_salsa20 ? "Salsa20" : "ChaCha20";
    archivo << algoritmo << " Ronda " << ronda << ":\n";
    for (int i = 0; i < 16; i++) {
        archivo << std::hex << std::setw(8) << std::setfill('0') << estado[i] << " ";
        if ((i + 1) % 4 == 0) archivo << std::endl;
    }
    archivo << std::dec << std::endl;
}