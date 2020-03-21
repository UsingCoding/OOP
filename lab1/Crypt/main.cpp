#include <iostream>
#include <fstream>
#include <stdexcept>
#include <exception>

const std::string CRYPT = "crypt";
const std::string DECRYPT = "decrypt";

void Encrypt(char & byte, int key);
void Decrypt(char & byte, int key);
void Transform(std::istream * in, std::ostream * out, int key, void cryptionFunc(char & byte, int key));
void OpenFiles(std::ifstream* fin, std::ofstream* fout, const std::string & finName, const std::string & foutName);
void ProceedCryption(std::istream * in, std::ostream * out, const std::string & cryptMode, int key);

int main(int argc, char const *argv[])
{
    if (argc != 5)
    {
        std::cout << "Incorrect count of arguments" << std::endl;
        return 1;
    }

    std::ifstream fin;
    std::ofstream fout;

    try
    {
        OpenFiles(&fin, &fout, argv[2], argv[3]);

        int key = std::stoi(argv[4]);

        ProceedCryption(&fin, &fout, argv[1], key);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

void OpenFiles(std::ifstream* fin, std::ofstream* fout, const std::string & finName, const std::string & foutName)
{
    (*fin).open(finName, std::ios::binary);
    (*fout).open(foutName, std::ios::binary);

    if (!(*fin).is_open())
    {
        throw std::runtime_error("Failed to open input file");
    }

    if (!(*fout).is_open())
    {
        throw std::runtime_error("Failed to open output file");
    }
}

void ProceedCryption(std::istream * in, std::ostream * out, const std::string & cryptMode, int key)
{
    if (cryptMode == CRYPT)
    {
        Transform(in, out, key, Encrypt);
        return;
    }

    if (cryptMode == DECRYPT)
    {
        Transform(in, out, key, Decrypt);
        return;
    }

    throw std::invalid_argument("Invalid cryption mode");
}

void Transform(std::istream * in, std::ostream * out, int key, void cryptionFunc(char & byte, int key))
{
    char byte;

    while ((*in).read(&byte, sizeof(char)))
    {
        cryptionFunc(byte, key);
        (*out).write(&byte, sizeof(char));
    }
}

void Encrypt(char & byte, int key)
{
    byte ^= key;

    byte = ((byte & 0b00000111) << 2)
        | ((byte & 0b00011000) << 3)
        | ((byte & 0b01100000) >> 5)
        | ((byte & 0b10000000) >> 2);
}

void Decrypt(char & byte, int key)
{
    byte = ((byte & 0b00000011) << 5)
        | ((byte & 0b00011100) >> 2)
        | ((byte & 0b00100000) << 2)
        | ((byte & 0b11000000) >> 3);

    byte ^= key;
}
