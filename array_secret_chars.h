#pragma once

#include <string>
#include <sstream>

namespace secret_chars
{
  class ArraySecretChars
  {
  public:
    ArraySecretChars(uint64_t cash);

    const std::string operator()() const;

    const std::string GetSecretChars() const;

  private:
    std::string secret_chars_;

    char SetChar(char ch);
  };

}// end namespace

