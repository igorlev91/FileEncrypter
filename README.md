# FileEncrypter in C++.

## Implementation:

A basic virtual class for std::string encryption:

```cpp
class EncryptionBase
{
public:
    virtual std::string encrypt(const std::string& file, const std::string& password = {}) = 0;
    virtual std::string decrypt(const std::string& file, const std::string& password = {}) = 0;
    virtual ~EncryptionBase() = default;
};
```

Encryption logic using XOR:

```cpp
class XOREncryption : public EncryptionBase ...
```

Interface for file encryption using encryption:

```cpp
class FileEncryptHandler ...
```