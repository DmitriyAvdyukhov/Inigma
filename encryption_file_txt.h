#pragma once

#include "encryption.h"
#include <fstream>


namespace encryption
{
  class EncryptionFileTxt : public Encryption
  {
  public:
    EncryptionFileTxt();

    void DecryptionData() override;
    std::string DecryptionData(const std::string&) override;

    std::string EncryptionData(const std::string&) override;
    void EncryptionData() override;  

    inline std::string CutNameFile(const std::string& name_file) const;
  };

}// end namespace
