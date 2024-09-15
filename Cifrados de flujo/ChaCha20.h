#ifndef CHACHA20_H
#define CHACHA20_H

#include "commons.h"
#include <fstream>

// Función de quarter round para ChaCha20
#define QR_CHACHA20(a, b, c, d) (  \
        a += b, d ^= a, d = ROTL(d, 16), \
        c += d, b ^= c, b = ROTL(b, 12), \
        a += b, d ^= a, d = ROTL(d,  8), \
        c += d, b ^= c, b = ROTL(b,  7))

// Ejecuta las 20 rondas del cifrado ChaCha20
void bloque_chacha20(uint32_t salida[16], const uint32_t entrada[16]);

// Función para cifrar usando ChaCha20
std::string cifrar_chacha20(const std::string& texto_plano, const std::string& clave, const std::string& nonce);

// Función para descifrar usando ChaCha20
std::string descifrar_chacha20(const std::string& texto_cifrado, const std::string& clave, const std::string& nonce);

#endif
