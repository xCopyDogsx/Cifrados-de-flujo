#include "rc4.h"


void inicializar_rc4(std::vector<uint8_t>& S, const std::string& clave) {
    int clave_len = clave.size();
    for (int i = 0; i < 256; ++i) {
        S[i] = static_cast<uint8_t>(i);
    }

    int j = 0;
    for (int i = 0; i < 256; ++i) {
        j = (j + S[i] + clave[i % clave_len]) % 256;
        std::swap(S[i], S[j]);
    }
}

std::string rc4(const std::string& datos, const std::string& clave) {
    std::vector<uint8_t> S(256);
    inicializar_rc4(S, clave);

    int i = 0, j = 0;
    std::string salida;
    salida.reserve(datos.size());

    std::ofstream archivo("rc4.txt");

    for (size_t n = 0; n < datos.size(); ++n) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        std::swap(S[i], S[j]);
        uint8_t keystream_byte = S[(S[i] + S[j]) % 256];
        salida.push_back(datos[n] ^ keystream_byte);
        archivo << "RC4 Estado en el paso " << n + 1 << ":\n";
        for (int k = 0; k < 256; ++k) {
            archivo << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(S[k]) << " ";
            if ((k + 1) % 16 == 0) archivo << std::endl;
        }
        archivo << std::endl;
    }

    archivo.close();  

    return salida;
}
