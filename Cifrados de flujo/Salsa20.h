#ifndef SALSA20_H
#define SALSA20_H

#include "commons.h"
#include <fstream>

// Función de quarter round para Salsa20
#define QR_SALSA20(a, b, c, d) (   \
        b ^= ROTL(a + d, 7),       \
        c ^= ROTL(b + a, 9),       \
        d ^= ROTL(c + b, 13),      \
        a ^= ROTL(d + c, 18))

// Ejecuta las 20 rondas del cifrado Salsa20
void bloque_salsa20(uint32_t salida[16], const uint32_t entrada[16]);

// Función para cifrar usando Salsa20
std::string cifrar_salsa20(const std::string& texto_plano, const std::string& clave, const std::string& nonce);

// Función para descifrar usando Salsa20
std::string descifrar_salsa20(const std::string& texto_cifrado, const std::string& clave, const std::string& nonce);

#endif
