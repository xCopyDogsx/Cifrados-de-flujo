#include "chacha20.h"

void bloque_chacha20(uint32_t salida[16], const uint32_t entrada[16]) {
    uint32_t x[16];
    std::memcpy(x, entrada, 16 * sizeof(uint32_t));

    std::ofstream archivo("chacha20.txt"); 

    for (int i = 0; i < 20; i += 2) {
        QR_CHACHA20(x[0], x[4], x[8], x[12]);
        QR_CHACHA20(x[1], x[5], x[9], x[13]);
        QR_CHACHA20(x[2], x[6], x[10], x[14]);
        QR_CHACHA20(x[3], x[7], x[11], x[15]);

        imprimir_estado_en_archivo(x, i + 1, false, archivo);

        QR_CHACHA20(x[0], x[5], x[10], x[15]);
        QR_CHACHA20(x[1], x[6], x[11], x[12]);
        QR_CHACHA20(x[2], x[7], x[8], x[13]);
        QR_CHACHA20(x[3], x[4], x[9], x[14]);

        imprimir_estado_en_archivo(x, i + 2, false, archivo);
    }

    archivo.close();  

    for (int i = 0; i < 16; ++i)
        salida[i] = x[i] + entrada[i];
}

std::string cifrar_chacha20(const std::string& texto_plano, const std::string& clave, const std::string& nonce) {
    std::vector<uint32_t> estado = cadena_a_u32vector(clave + nonce);
    std::string salida;
    uint32_t contador = 0;

    for (size_t i = 0; i < texto_plano.size(); i += 64) {
        estado[12] = contador++;
        uint32_t bloque[16];
        bloque_chacha20(bloque, estado.data());

        std::string keystream = u32vector_a_cadena(std::vector<uint32_t>(bloque, bloque + 16));
        std::string chunk = texto_plano.substr(i, 64);
        salida += xor_cadenas(chunk, keystream.substr(0, chunk.size()));
    }

    return salida;
}

std::string descifrar_chacha20(const std::string& texto_cifrado, const std::string& clave, const std::string& nonce) {
    return cifrar_chacha20(texto_cifrado, clave, nonce);
}
