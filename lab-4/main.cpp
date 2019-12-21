#include <utility>

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

namespace task_1 {
    int modular_pow(int base, int index_n, int modulus) {
        int c = 1;
        for (auto index_n_prime = 1; index_n_prime <= index_n; ++index_n_prime) {
            c = (c * base) % modulus;
        }
        return c;
    }

    void run() {
        std::cout << modular_pow(4, 13, 497) << std::endl;
    }
}

namespace task_2 {
    class Person {
    private:
        std::string name;
        long long private_key = 0;
        long long common_private_key = 0;

        void generate_private_key() {
            private_key = std::rand() % 100;
            std::cout << name << " private_key: " << private_key << std::endl;
        }

    public:
        static constexpr long long P = 23;
        static constexpr long long G = 9;

        explicit Person(std::string name): name(std::move(name)) {
            generate_private_key();
        }

        long long public_key = 0;
        long long other_public_key = 0;

        void calculate_public_key() {
            public_key = task_1::modular_pow(G, private_key, P);
        }

        long long get_public_key() {
            return public_key;
        }

        void set_other_public_key(long long key) {
            other_public_key = key;
        }

        void calculate_common_private_key() {
            common_private_key = task_1::modular_pow(other_public_key, private_key, P);
            std::cout << name << " common_private_key: " << common_private_key << std::endl;
        }

    };

    void run() {
        std::srand(unsigned(std::time(nullptr)));

        auto alice = Person("Alice");
        auto bob = Person("Bob");

        alice.calculate_public_key();
        bob.calculate_public_key();

        alice.set_other_public_key(bob.get_public_key());
        bob.set_other_public_key(alice.get_public_key());

        alice.calculate_common_private_key();
        bob.calculate_common_private_key();
    }
}

namespace task_3 {
    struct Key {
        long pkey;
        long ekey;
        long dkey;
    };

    class Rsa {
    public:
        Key produce_keys() {
            long prime1 = produce_prime();
            long prime2 = produce_prime();
            while (prime2 == prime1) {
                prime2 = produce_prime();
            }
            Key key{};
            long orla = produce_orla(prime1, prime2);
            key.pkey = produce_pkey(prime1, prime2);
            key.ekey = produce_ekey(orla);
            key.dkey = produce_dkey(key.ekey, orla);
            return key;
        }

        long endecrypt(const long msg, const long key, const long pkey) {
            long msg_des = 1;
            long root = msg;
            unsigned long index = key;
            while (index) {
                if (index & 1u) {
                    msg_des = (msg_des * root) % pkey;
                }
                index >>= 1u;
                root = (root * root) % pkey;
            }
            return msg_des;
        }

    private:
        long produce_pkey(const long prime1, const long prime2) {
            return prime1 * prime2;
        }

        long produce_ekey(const long orla) {
            long ekey;
            while (true) {
                ekey = std::rand() % orla;
                if (ekey >= 2 && produce_gcd(ekey, orla) == 1) {
                    break;
                }
            }
            return ekey;
        }

        long produce_dkey(const long ekey, const long orla) {
            long dkey = orla / ekey;
            while (true) {
                if (((dkey * ekey) % orla) == 1) {
                    break;
                } else ++dkey;
            }
            return dkey;
        }

        long produce_prime() {
            long prime = 0;
            std::srand(unsigned(std::time(nullptr)));
            while (true) {
                prime = std::rand() % 100 + 100;
                if (is_prime(prime)) {
                    break;
                }
            }
            return prime;
        }

        long produce_orla(const long prime1, const long prime2) {
            return (prime1 - 1) * (prime2 - 1);
        }

        long produce_gcd(const long a, const long b) {
            long dividend = a;
            long divisor = b;
            long residual = dividend % divisor;
            while (residual) {
                dividend = divisor;
                divisor = residual;
                residual = dividend % divisor;
            }
            return divisor;
        }

        bool is_prime(const long digit) {
            int tmp = 2;
            while (tmp < digit) {
                if (!(digit % tmp++)) {
                    break;
                }
            }
            return tmp == digit;
        }
    };

    void run() {
        Rsa rsa;
        Key key = rsa.produce_keys();
        std::cout << "p: " << key.pkey << std::endl;
        std::cout << "q: " << key.ekey << std::endl;
        std::cout << "n: " << key.dkey << std::endl;
        long msg;
        std::cout << "Write message: " << std::endl;
        std::cin >> msg;
        long msg_des = rsa.endecrypt(msg, key.ekey, key.pkey);
        std::cout << "encrypted: " << msg_des << std::endl;
        msg_des = rsa.endecrypt(msg_des, key.dkey, key.pkey);
        std::cout << "decrypted: " << msg_des << std::endl;
    }
}

int main() {
    task_1::run();
    task_2::run();
    task_3::run();
    return 0;
}