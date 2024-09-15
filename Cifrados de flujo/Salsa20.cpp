#include "salsa20.h"

void bloque_salsa20(uint32_t salida[16], const uint32_t entrada[16]) {
    uint32_t x[16];
    std::memcpy(x, entrada, 16 * sizeof(uint32_t));

    std::ofstream archivo("salsa20.txt");  

    for (int i = 0; i < 20; i += 2) {
        QR_SALSA20(x[0], x[4], x[8], x[12]);
        QR_SALSA20(x[5], x[9], x[13], x[1]);
        QR_SALSA20(x[10], x[14], x[2], x[6]);
        QR_SALSA20(x[15], x[3], x[7], x[11]);

        imprimir_estado_en_archivo(x, i + 1, true, archivo);

        QR_SALSA20(x[0], x[1], x[2], x[3]);
        QR_SALSA20(x[5], x[6], x[7], x[4]);
        QR_SALSA20(x[10], x[11], x[8], x[9]);
        QR_SALSA20(x[15], x[12], x[13], x[14]);

        imprimir_estado_en_archivo(x, i + 2, true, archivo);
    }

    archivo.close(); 

    for (int i = 0; i < 16; ++i)
        salida[i] = x[i] + entrada[i];
}

std::string cifrar_salsa20(const std::string& texto_plano, const std::string& clave, const std::string& nonce) {
    std::vector<uint32_t> estado = cadena_a_u32vector(clave + nonce);
    std::string salida;
    uint32_t contador = 0;

    for (size_t i = 0; i < texto_plano.size(); i += 64) {
        estado[12] = contador++;
        uint32_t bloque[16];
        bloque_salsa20(bloque, estado.data());

        std::string keystream = u32vector_a_cadena(std::vector<uint32_t>(bloque, bloque + 16));
        std::string chunk = texto_plano.substr(i, 64);
        salida += xor_cadenas(chunk, keystream.substr(0, chunk.size()));
    }

    return salida;
}

std::string descifrar_salsa20(const std::string& texto_cifrado, const std::string& clave, const std::string& nonce) {
    return cifrar_salsa20(texto_cifrado, clave, nonce);
}
