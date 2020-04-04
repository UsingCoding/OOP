#include <iostream>
#include <fstream>
#include <stdexcept>
#include <exception>

const std::string CRYPT_MODE = "crypt";
const std::string DECRYPT_MODE = "decrypt";
const unsigned short int minKey = 0;
const unsigned short int maxKey = 255;

enum Mode
{
    CRYPT,
    DECRYPT
};

struct Arguments
{
    std::string finName;
    std::string foutName;
    Mode mode;
    int key;
};

struct Files
{
    std::ifstream fin;
    std::ofstream fout;
};


Arguments ParseArguments(int argc, char const *argv[]);

void Encrypt(char & byte, int key);
void Decrypt(char & byte, int key);

void Transform(std::istream & in, std::ostream & out, int key, void cryptionFunc(char & byte, int key));
void OpenFiles(std::ifstream & fin, std::ofstream & fout, const std::string & finName, const std::string & foutName);
void ProceedCryption(std::istream & in, std::ostream & out, Mode cryptMode, int key);

int main(int argc, char const *argv[])
{
    try
    {
        std::ifstream fin;
        std::ofstream fout;

        Arguments args = ParseArguments(argc, argv);

        OpenFiles(fin, fout, args.finName, args.foutName);

        ProceedCryption(fin, fout, args.mode, args.key);

        if (!fout.flush())
        {
            throw std::runtime_error("Failed to save data on disk");
        }
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;

        return 1;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << "Wrong char passed as key" << std::endl;
        return 1;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

Arguments ParseArguments(int argc, char const *argv[])
{
    if (argc != 5)
    {
        throw std::runtime_error("Incorrect count of arguments");
    }

    Arguments args;

    {
        bool modeInitialized = false;

        if (argv[1] == CRYPT_MODE)
        {
            args.mode = CRYPT;
            modeInitialized = true;
        }

        if (argv[1] == DECRYPT_MODE)
        {
            args.mode = DECRYPT;
            modeInitialized = true;
        }

        if (!modeInitialized)
        {
            throw std::runtime_error("Invalid cryption mode");
        }
    }

    args.key = std::stoi(argv[4]);

    if (args.key >= maxKey or args.key <= minKey)
    {
        throw std::runtime_error("Key less than 0 or greater than 255 is incorrect");
    }

    args.finName = argv[2];
    args.foutName = argv[3];

    return args;
}

void OpenFiles(std::ifstream & fin, std::ofstream & fout, const std::string & finName, const std::string & foutName)
{
    fin.open(finName, std::ios::binary);
    fout.open(foutName, std::ios::binary);

    if (!fin.is_open())
    {
        throw std::runtime_error("Failed to open input file");
    }

    if (!fout.is_open())
    {
        throw std::runtime_error("Failed to open output file");
    }
}

void ProceedCryption(std::istream & in, std::ostream & out, Mode cryptMode, int key)
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

    throw std::runtime_error("Invalid cryption mode");
}

void Transform(std::istream & in, std::ostream & out, int key, void  cryptionFunc(char & byte, int key))
{
    char byte;

    while (in.read(&byte, sizeof(char)))
    {
        cryptionFunc(byte, key);
        out.write(&byte, sizeof(char));
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
