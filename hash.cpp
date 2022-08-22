#include "hash.h"

namespace hasher
{

  Hash::Hash(std::string str):str_(str){}

  uint64_t Hash::operator()()
  {
    return std::hash<std::string>{}(str_);
  }
}
