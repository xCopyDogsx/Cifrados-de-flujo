#ifdef _WIN32
#include <windows.h>  
#include <cstdlib>    
#define PATH_MAX MAX_PATH  
#else
#include <unistd.h>   
#include <limits.h>   
#include <cstdlib>    
#endif

#include <iostream>
#include "commons.h"
#include "salsa20.h"
#include "chacha20.h"
#include "rc4.h"

void limpiar_pantalla() {
#ifdef _WIN32
    system("cls");  
#else
    system("clear");  
#endif
}

void esperar_enter() {
    std::cout << "Presione Enter para continuar...";
    std::cin.ignore(); 
    std::cin.get();
}


void mostrar_ruta_archivos() {
    char buffer[PATH_MAX];
    #ifdef _WIN32
        GetCurrentDirectoryA(MAX_PATH, buffer);  
    #else
        getcwd(buffer, sizeof(buffer));  
    #endif
    std::cout << "Los archivos de los rounds se guardaran en la siguiente ruta:\n";
    std::cout << buffer << std::endl << std::endl;
}

void mostrar_menu() {
    std::cout << "\n=== Cifrados de flujo I ===\n";
    std::cout << "1. Cifrar y descifrar con Salsa20\n";
    std::cout << "2. Cifrar y descifrar con ChaCha20\n";
    std::cout << "3. Cifrar y descifrar con Salsa20 y ChaCha20 (ambos)\n";
    std::cout << "4. Cifrar y descifrar con RC4\n";
	std::cout << "5. Creditos\n";
    std::cout << "0. Salir\n";
    std::cout << "Seleccione una Opcion: ";
}

int main() {
    mostrar_ruta_archivos();
    std::string clave, nonce, texto_plano;

    std::cout << "Ingrese la clave (32 bytes para Salsa/ChaCha, variable para RC4): ";
    std::getline(std::cin, clave);

    std::cout << "Ingrese el nonce (8 bytes, solo para Salsa/ChaCha): ";
    std::getline(std::cin, nonce);

    std::cout << "Ingrese el texto plano a cifrar: ";
    std::getline(std::cin, texto_plano);

    int opcion;
    do {
        limpiar_pantalla();  
        mostrar_menu();
        std::cin >> opcion;
        std::cin.ignore();  

        switch (opcion) {
        case 1: {
            limpiar_pantalla();
            if (clave.size() != 32 || nonce.size() != 8) {
                std::cerr << "Clave o nonce incorrectos para Salsa20.\n";
                break;
            }
            std::cout << "Cifrando con Salsa20...\n";
            std::string texto_cifrado_salsa20 = cifrar_salsa20(texto_plano, clave, nonce);
            std::string texto_descifrado_salsa20 = descifrar_salsa20(texto_cifrado_salsa20, clave, nonce);

            std::cout << "Texto cifrado Salsa20 (Hex): " << a_hex(texto_cifrado_salsa20) << std::endl;
            std::cout << "Texto descifrado Salsa20: ";
            imprimir_escapado(texto_descifrado_salsa20);
            esperar_enter(); 
            break;
        }
        case 2: {
            limpiar_pantalla();
            if (clave.size() != 32 || nonce.size() != 8) {
                std::cerr << "Clave o nonce incorrectos para ChaCha20.\n";
                break;
            }
            std::cout << "Cifrando con ChaCha20...\n";
            std::string texto_cifrado_chacha20 = cifrar_chacha20(texto_plano, clave, nonce);
            std::string texto_descifrado_chacha20 = descifrar_chacha20(texto_cifrado_chacha20, clave, nonce);

            std::cout << "Texto cifrado ChaCha20 (Hex): " << a_hex(texto_cifrado_chacha20) << std::endl;
            std::cout << "Texto descifrado ChaCha20: ";
            imprimir_escapado(texto_descifrado_chacha20);
            esperar_enter();
            break;
        }
        case 3: {
            limpiar_pantalla();
            if (clave.size() != 32 || nonce.size() != 8) {
                std::cerr << "Clave o nonce incorrectos para Salsa20 y ChaCha20.\n";
                break;
            }

            std::cout << "Cifrando con ChaCha20...\n";
            std::string texto_cifrado_chacha20 = cifrar_chacha20(texto_plano, clave, nonce);
            std::string texto_descifrado_chacha20 = descifrar_chacha20(texto_cifrado_chacha20, clave, nonce);

            std::cout << "Texto cifrado ChaCha20 (Hex): " << a_hex(texto_cifrado_chacha20) << std::endl;
            std::cout << "Texto descifrado ChaCha20: ";
            imprimir_escapado(texto_descifrado_chacha20);

            std::cout << "Cifrando con Salsa20...\n";
            std::string texto_cifrado_salsa20 = cifrar_salsa20(texto_plano, clave, nonce);
            std::string texto_descifrado_salsa20 = descifrar_salsa20(texto_cifrado_salsa20, clave, nonce);

            std::cout << "Texto cifrado Salsa20 (Hex): " << a_hex(texto_cifrado_salsa20) << std::endl;
            std::cout << "Texto descifrado Salsa20: ";
            imprimir_escapado(texto_descifrado_salsa20);

            esperar_enter();
            break;
        }
        case 4: {
            limpiar_pantalla();
            std::cout << "Cifrando con RC4...\n";
            std::string texto_cifrado_rc4 = rc4(texto_plano, clave);
            std::string texto_descifrado_rc4 = rc4(texto_cifrado_rc4, clave);

            std::cout << "Texto cifrado RC4 (Hex): " << a_hex(texto_cifrado_rc4) << std::endl;
            std::cout << "Texto descifrado RC4: ";
            imprimir_escapado(texto_descifrado_rc4);
            esperar_enter();
            break;
        }
        case 5: {
			limpiar_pantalla();
            std::cout << "Creditos\n";
            std::cout << "Brian Steven Canon Rojas - 20231678025\n";
            std::cout << "Marlon Stevan Castano Merida - 20231678037\n";
            std::cout << "Alejandro Bernal Bernal - 20231678019\n";
			esperar_enter();
        }
        case 0: {
            std::cout << "Saliendo...\n";
            break;
        }
        default: {
            std::cout << "Opción no válida. Intente de nuevo.\n";
            esperar_enter();
            break;
        }
        }
    } while (opcion != 0);

    return 0;
}
