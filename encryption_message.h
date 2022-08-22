#pragma once
#include "encryption.h"
#include <string>


namespace encryption
{
  class EncryptionMessage : public Encryption
  {
  public:   

    EncryptionMessage();

    explicit EncryptionMessage(const std::string& char_encriptor, const std::string& container_action);

    std::string EncryptionData(const std::string& str) override;

    void EncryptionData() override;

    std::string DecryptionData(const std::string& str_encription) override;

    void DecryptionData() override;    

  };

}


