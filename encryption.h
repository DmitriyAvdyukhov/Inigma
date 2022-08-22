#pragma once
#include <string>
#include "array_secret_chars.h"
#include "hash.h"
#include <ctime>

namespace encryption
{
  struct Header
  {
    Header(uint64_t hash, uint64_t date);
    Header();
    uint64_t hash{};
    uint64_t date{};
  };

  enum class Type
  {
    MESSAGE,
    FILE
  };

  class Encryption
  {
  public:
    Encryption();
    Encryption(Type type);
    Encryption(const std::string& char_encryption, const std::string& container_action);

    virtual ~Encryption();

    virtual std::string DecryptionData(const std::string&)= 0;
    virtual void DecryptionData() = 0;

    virtual std::string EncryptionData(const std::string&)= 0;
    virtual void EncryptionData() = 0;    

    void CreateArraySecretChar(encryption::Header header);
    void AddHeader(std::stringstream& result);
    void SetKey(const std::string&);
    void SetContainerChar(const std::string&);
    void SetData(const std::string&);
    std::string GetData();
    const std::string& GetCharEncryption() const;
    void Clear();

    Type GetType() const;
  protected:
    std::string data_{};
    std::string char_encryption_{};
    std::string container_action_{};

    const size_t MAX = 256;
    char SetChar(char action, char str, char shift);
    char GetChar(char action, char str, char shift);
  private:
    Type type_;
  };
}


