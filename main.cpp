#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <iterator>
#include <sstream>


class EncryptionBase
{
public:

    virtual std::string encrypt(const std::string& file, const std::string& password = {}) = 0;

    virtual std::string decrypt(const std::string& file, const std::string& password = {}) = 0;

    virtual ~EncryptionBase() = default;
};

class XOREncryption : public EncryptionBase
{
public:

    std::string encrypt(const std::string& file, const std::string& password) override
    {

        std::string result{ file };

        for (size_t i = 0; i < file.size(); i++)
        {
            result[i] = file[i] ^ password[i % password.size()];
        }

        return result;
    }


    std::string decrypt(const std::string& file, const std::string& password) override
    {
        return encrypt(file, password);
    }
};

class ZipEncryption : public EncryptionBase
{
public:
    std::string encrypt(const std::string& file, const std::string& password = {}) override
    {
        std::cout << " Some encrypt logic" << std::endl;
        return {};
    }

    std::string decrypt(const std::string& file, const std::string& password = {}) override
    {
        std::cout << " Some decrypt logic" << std::endl;
        return {};
    }

};

class FileEncryptHandler
{
public:
    FileEncryptHandler (std::unique_ptr<EncryptionBase> enc) : encryptor(std::move(enc))
    {}

    void encrypt(const std::string& filepathFrom, const std::string& filepathTo, const std::string& password = {})
    {

        std::ofstream output(filepathTo, std::ios::trunc);
        output << encryptor->encrypt(processTextFromFile(filepathFrom), password);

    }

    void decrypt(const std::string& filepathFrom, const std::string& filepathTo, const std::string& password = {})
    {
        std::ofstream output(filepathTo, std::ios::trunc);
        output << encryptor->decrypt(processTextFromFile(filepathFrom), password);
    }


private:
    std::unique_ptr<EncryptionBase> encryptor;


    std::string processTextFromFile(const std::string& file)
    {
        return std::string((std::istreambuf_iterator<char>(*(std::unique_ptr<std::ifstream>(new std::ifstream(file))).get())), std::istreambuf_iterator<char>());
    }
};

int main() {
    const std::string password{ "BLABLA" };
    FileEncryptHandler fileEncryptHandler(std::make_unique<XOREncryption>());

    fileEncryptHandler.encrypt("XOR_Original.txt", "XOR_Crypted.txt", password);
    fileEncryptHandler.decrypt("XOR_Crypted.txt", "XOR_Decrypted.txt", password);

    FileEncryptHandler fileEncryptHandlerZip(std::make_unique<ZipEncryption>());
    fileEncryptHandlerZip.encrypt("Zip_Original.txt", "Zip_Crypted.txt", password);
    fileEncryptHandlerZip.decrypt("Zip_Crypted.txt", "Zip_Decrypted.txt", password);
}