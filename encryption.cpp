#include "encryption.h"

namespace encryption
{
  Header::Header() = default;
  Header::Header(uint64_t hash, uint64_t date)
    : hash(hash), date(date)
  {}

  Encryption::Encryption() = default;


  Encryption::Encryption(Type type) : type_(type)
  {}

  Encryption::Encryption(const std::string &char_encriptor, const std::string &container_action)
    : char_encryption_(char_encriptor)
    , container_action_(container_action)
  {}

  Encryption::~Encryption(){}
  char Encryption::SetChar(char action, char str, char shift)
  {
    char ch = ' ';
    int pos = 0;
    switch (action)
      {
      case '0':
        ch = str + shift;
        break;
      case '1':
        ch = str ^ shift;
        break;
      case '2':
        ch = str - shift;
        break;
      case '3':
        ch = shift ^ str;
        break;     
      }
    return ch;
  }

  char Encryption::GetChar(char action, char str, char shift)
  {
    char ch = ' ';
    switch (action)
      {
      case '0':
        ch = str - shift;
        break;
      case '1':
        ch = shift ^ str;
        break;
      case '2':
        ch = str + shift;
        break;
      case '3':
        ch = str ^ shift;
        break;      
      }
    return ch;
  }

  void Encryption::SetKey(const std::string& char_encriptor)
  {
    char_encryption_ = char_encriptor;
  }

  void Encryption::SetContainerChar(const std::string& container_action)
  {
    container_action_ = container_action;
  }

  void Encryption::SetData(const std::string& data)
  {
    data_ = data;
  }

  std::string Encryption::GetData()
  {
    return data_;
  }

  const std::string& Encryption::GetCharEncryption() const
  {
    return char_encryption_;
  }

  void Encryption::Clear()
  {
    char_encryption_.clear();
  }

  Type Encryption::GetType() const
  {
    return type_;
  }

  void Encryption::CreateArraySecretChar(encryption::Header header)
  {
    if(header.date % 2)
      {
        secret_chars::ArraySecretChars s_ch(header.hash + header.date);
        container_action_ = s_ch.GetSecretChars();
      }
    else
      {
        secret_chars::ArraySecretChars s_ch(header.hash * header.date);
        container_action_ = s_ch.GetSecretChars();
      }
  }

  void Encryption::AddHeader(std::stringstream& result)
  {
    std::stringstream hash;
    encryption::Header header(hasher::Hash(char_encryption_)(), static_cast<uint64_t>(std::time(nullptr)));
    result << header.hash << " " << header.date;
    CreateArraySecretChar(header);
  }

}// end namespace

