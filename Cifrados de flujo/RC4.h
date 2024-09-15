#ifndef RC4_H
#define RC4_H

#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

// Función para inicializar el estado de RC4
void inicializar_rc4(std::vector<uint8_t>& S, const std::string& clave);

// Función para cifrar/descifrar usando RC4
std::string rc4(const std::string& datos, const std::string& clave);

#endif // RC4_H
