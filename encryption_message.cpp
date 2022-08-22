#include "encryption_message.h"
#include <sstream>
#include <fstream>

namespace encryption
{

  EncryptionMessage::EncryptionMessage() : Encryption(Type::MESSAGE)
  {}

  EncryptionMessage::EncryptionMessage(const std::string& char_incryptor,
                                       const std::string& container_action)
    : Encryption(char_incryptor, container_action)
  {}

  std::string EncryptionMessage::EncryptionData(const std::string& data)
  {
    std::stringstream str;
    AddHeader(str);
    std::string result;
    std::getline(str, result);
    int pos_in_container = 0;
    int pos_in_char_incript = 0;
    size_t size_incryption_message = data.size();
    for (size_t i = 0; i < size_incryption_message; ++i)
      {
        if (pos_in_container >= container_action_.size())
          {
            pos_in_container = 0;
          }
        if (pos_in_char_incript >= char_encryption_.size())
          {
            pos_in_char_incript = 0;
          }
        result += (SetChar(container_action_[pos_in_container++], data[i],
            char_encryption_[pos_in_char_incript++]));
      }
    return result;
  }

  void EncryptionMessage::EncryptionData() {}

  std::string EncryptionMessage::DecryptionData(const std::string& data)
  {
    std::string result;
    std::stringstream str(data);
    encryption::Header header;
    str >> header.hash >> header.date;
    CreateArraySecretChar(header);
    int pos_in_container = 0;
    int pos_in_char_incript = 0;    
    while(!str.eof())
      {
        char ch;
        str >> ch;
        if (pos_in_container >= container_action_.size())
          {
            pos_in_container = 0;
          }
        if (pos_in_char_incript >= char_encryption_.size())
          {
            pos_in_char_incript = 0;
          }
        result += GetChar(container_action_[pos_in_container++], ch, char_encryption_[pos_in_char_incript++]);
      }
    result.erase(result.size() - 1);
    return result;
  }

  void EncryptionMessage::DecryptionData() {}

}//end namespace incryption
