# 🔐 **Proyecto de Cifrado: Salsa20, ChaCha20 y RC4**

Este proyecto implementa los algoritmos de cifrado **Salsa20**, **ChaCha20**, y **RC4** en C++. Además, te permite visualizar el proceso de cifrado y descifrado, almacenando los resultados de los rounds intermedios en archivos de texto para un análisis detallado.

## 🛠 **Requisitos del sistema**

### Dependencias
- **Compilador compatible con C++17 o superior**:
  - GCC 7.1 o superior
  - Clang 6.0 o superior
  - Visual Studio 2019 o superior
- **Bibliotecas**:
  - `<iostream>`: Para la interacción básica de entrada/salida.
  - `<iomanip>`: Para el formato de salida de texto (en hexadecimal).
  - `<cstdlib>`: Para la limpieza de pantalla según el sistema.
  - `<fstream>`: Para escribir los resultados en archivos de texto.
  - `<unistd.h>` (Linux/macOS): Para obtener la ruta del directorio actual.
  - `<windows.h>` (Windows): Para obtener la ruta del directorio actual en Windows.

## 🔧 **Compilación**

### En **Windows** (Visual Studio o g++):

```bash
g++ -std=c++17 -o cifrado main.cpp salsa20.cpp chacha20.cpp rc4.cpp commons.cpp
```

### En Linux/macOS:

```bash
g++ -std=c++17 -o cifrado main.cpp salsa20.cpp chacha20.cpp rc4.cpp commons.cpp
```

## 🚀 **Uso**

Al ejecutar el programa, se te mostrará un menú para seleccionar qué algoritmo de cifrado deseas utilizar. Puedes elegir entre Salsa20, ChaCha20, una combinación de ambos, o RC4.

```bash
./cifrado
=== Cifrados de Flujo I ===
1. Cifrar y descifrar con Salsa20
2. Cifrar y descifrar con ChaCha20
3. Cifrar y descifrar con Salsa20 y ChaCha20 (ambos)
4. Cifrar y descifrar con RC4
0. Salir

```
El programa pedirá una clave, un nonce (para Salsa20 y ChaCha20), y un texto plano para cifrar.

Ejemplo de uso:
Ingresa la clave (32 bytes para Salsa20/ChaCha20, variable para RC4).
Ingresa el nonce (8 bytes para Salsa20/ChaCha20).
Ingresa el texto plano a cifrar.

## 📄 Archivos generados
Durante el proceso de cifrado, los resultados intermedios de los rounds se guardan en archivos de texto en la misma ruta donde se ejecuta el programa:

salsa20.txt: Rondas intermedias del cifrado Salsa20.
chacha20.txt: Rondas intermedias del cifrado ChaCha20.
rc4.txt: Estado del algoritmo RC4 después de cada paso.

El programa te mostrará la ruta exacta donde se guardarán los archivos:
```bash
Los archivos de los rounds se guardarán en la siguiente ruta:
<ruta_aquí>
```
## 📂 Estructura del Proyecto
```bash
/Cifrados de flujo
│
├── commons.h         # Funciones comunes (hex, XOR, etc.)
├── commons.cpp
│
├── salsa20.h         # Definiciones de Salsa20
├── salsa20.cpp       # Implementación de Salsa20
│
├── chacha20.h        # Definiciones de ChaCha20
├── chacha20.cpp      # Implementación de ChaCha20
│
├── rc4.h             # Definiciones de RC4
├── rc4.cpp           # Implementación de RC4
│
└── main.cpp          # Lógica principal del menú y ejecución

```
## 📝 Descripción de los Algoritmos

### Salsa20
Salsa20 es un algoritmo de cifrado de flujo que trabaja sobre bloques de 64 bytes. Se utiliza un nonce y una clave de 32 bytes para generar un flujo de claves, que se combina con el texto plano usando operaciones XOR.

### ChaCha20
ChaCha20 es una variante de Salsa20 que mejora la difusión por medio de más rotaciones y una estructura de diseño optimizada. También trabaja sobre bloques de 64 bytes, usando un nonce y una clave.

### RC4
RC4 es un algoritmo de cifrado de flujo más antiguo. Utiliza una permutación interna de 256 bytes y genera un flujo pseudoaleatorio que se combina con el texto plano. No requiere un nonce, solo una clave de longitud variable.