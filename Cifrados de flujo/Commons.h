#ifndef COMMONS_H
#define COMMONS_H

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <fstream> 
#include <sstream>


#define ROTL(a,b) (((a) << (b)) | ((a) >> (32 - (b))))

// Convierte una cadena binaria a su representación en hexadecimal
std::string a_hex(const std::string& entrada);

// Convierte una cadena hexadecimal a su representación binaria
std::string de_hex(const std::string& entrada);

// Convierte una cadena en un vector de enteros de 32 bits (para usar como estado)
std::vector<uint32_t> cadena_a_u32vector(const std::string& entrada);

// Convierte un vector de enteros de 32 bits a una cadena
std::string u32vector_a_cadena(const std::vector<uint32_t>& entrada);

// Realiza una operación XOR entre dos cadenas
std::string xor_cadenas(const std::string& s1, const std::string& s2);

// Imprime una cadena escapando los caracteres no imprimibles
void imprimir_escapado(const std::string& s);

// Imprime el estado actual del bloque en un archivo
void imprimir_estado_en_archivo(const uint32_t estado[16], int ronda, bool es_salsa20, std::ofstream& archivo);

#endif
