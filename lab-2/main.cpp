#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <string>
#include <cstdint>

#include "aes.h"

namespace task_1 {
    namespace {
        const size_t A = 11;
        const size_t B = 5;
        const size_t C = 64;

        const uint8_t K0 = 3;
    }

    uint8_t next_key(uint8_t prev_key) {
        return (A * prev_key + B) % C;
    }

    std::string lcg_encrypt(const std::string &s) {
        auto result_ss = std::stringstream();
        auto ss = std::stringstream(s);
        uint8_t xi;
        uint8_t ki = next_key(K0);
        while (ss >> xi) {
            result_ss << static_cast<char>(xi ^ ki);
            ki = next_key(ki);
        }
        return result_ss.str();
    }

    void check() {
        std::cout << "/////////////////TASK 1/////////////////" << std::endl;
        std::string s;
        std::getline(std::cin, s);

        auto s_encrypted = lcg_encrypt(s);
        auto s_decrypted = lcg_encrypt(s_encrypted);
        std::cout << "Encrypted: " << s_encrypted << std::endl;
        std::cout << "Decrypted: " << s_decrypted << std::endl;
        std::cout << "String encrypted and decrypted " << (s == s_decrypted ? "correctly" : "incorrectly") << std::endl;
    }
}

namespace task_2 {
    void check() {
        std::cout << "/////////////////TASK 2/////////////////" << std::endl;
        std::ifstream is("example.txt");
        std::istream_iterator<uint8_t> start(is), end;
        std::vector<uint8_t> bytes(start, end);
        auto aes = AESCipher();
        auto *out = new uint8_t[bytes.size()];

        std::cout << "Plaintext message:" << std::endl << bytes.data() << std::endl;
        auto *in = bytes.data();
        aes.cipher(in, out);
        std::cout << "Ciphered message:" << std::endl << out << std::endl;
        aes.inv_cipher(out, in);
        std::cout << "Original message (after inv cipher):" << std::endl << in << std::endl;

        delete[] out;
    }
}

namespace task_3 {
    uint16_t hash(uint8_t *data, size_t size) {
        uint16_t result = 0;
        for (auto i = 0; i < size; ++i) {
            result += *data;
            data++;
        }
        return result;
    }

    void check() {
        std::cout << "/////////////////TASK 3/////////////////" << std::endl;
        std::ifstream is("example.txt");
        std::istream_iterator<uint8_t> start(is), end;
        std::vector<uint8_t> bytes(start, end);
        auto aes = AESCipher();
        auto *out = new uint8_t[bytes.size()];

        std::cout << "Plaintext message:" << std::endl << bytes.data() << std::endl;
        auto *in = bytes.data();
        aes.cipher(in, out);
        std::cout << hash(out, bytes.size()) << std::endl;
    }
}

int main() {
    task_1::check();
    task_2::check();
    task_3::check();
    return 0;
}