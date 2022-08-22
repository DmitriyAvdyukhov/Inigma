#pragma once
#include <string>

namespace hasher
{
  struct Hash
  {
    Hash(std::string str);

    uint64_t operator()();

    std::string str_;
  };
}


