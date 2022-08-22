#include "array_secret_chars.h"

namespace secret_chars
{
  ArraySecretChars::ArraySecretChars(uint64_t cash)
  {
    int n = 1;
    while (true)
      {
        std::stringstream str;
        str << cash * n;
        while (str)
          {
            char ch = 0;
            str.get(ch);
            secret_chars_ += SetChar(ch);
          }
        if (secret_chars_.size() > 256)
          {
            secret_chars_.erase(256);
            break;
          }
        ++n;
      }
  }

  const std::string ArraySecretChars::operator()() const
  {
    return secret_chars_;
  }

  const std::string ArraySecretChars::GetSecretChars() const
  {
    return secret_chars_;
  }

  char ArraySecretChars::SetChar(char ch)
  {
    char result = ' ';
    if (static_cast<size_t>(ch) % 4 == 0)
      {
        result = '0';
      }
    else if (static_cast<size_t>(ch) % 4 == 1)
      {
        result = '1';
      }
    else if (static_cast<size_t>(ch) % 4 == 2)
      {
        result = '2';
      }
    else if (static_cast<size_t>(ch) % 4 == 3)
      {
        result = '3';
      }
    return result;
//    char result = static_cast<size_t>(static_cast<size_t>(ch) % 6);
//    return result == '\0' ? '0' : result;
  }

}// end namespace
