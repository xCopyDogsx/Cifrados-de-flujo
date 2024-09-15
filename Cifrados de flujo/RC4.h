#ifndef RC4_H
#define RC4_H

#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <bitset>
#include <iostream>

// Función para inicializar el estado de RC4
void inicializar_rc4(std::vector<uint8_t>& S, const std::string& clave);

// Función para cifrar/descifrar usando RC4
std::string rc4(const std::string& datos, const std::string& clave);

// Función para convertir un byte a su representación en binario
std::string byte_a_binario(uint8_t byte);

// Función para covnertir un carácter a su representación de 5 bits basado en el diccionario
std::string caracter_a_5bits(char c);

// Función para realizar fuerza bruta en RC4
std::string fuerza_bruta_rc4(const std::string& texto_cifrado, const std::string& palabra_original);
#endif // RC4_H
