#include "encryption_file_txt.h"
#include <vector>


namespace encryption
{
  EncryptionFileTxt::EncryptionFileTxt() : Encryption(Type::FILE)
  {}

  std::string EncryptionFileTxt::DecryptionData(const std::string&)
  {
    return {};
  }

   inline std::string EncryptionFileTxt::CutNameFile(const std::string& name_file) const
  {
    std::string result{ name_file };
    auto pos_insert = result.find_last_of('.');
    result.insert(pos_insert, ".copy");
    return result.erase(result.size() - 1);
  }

  void EncryptionFileTxt::DecryptionData()
  {
    std::ifstream in(data_, std::ios::binary);
    std::ofstream of(CutNameFile(data_));
    if (in && of)
      {
        int pos_in_container = 0;
        int pos_in_char_incript = 0;

        in.seekg(0, std::ios::end);
        auto size = in.tellg() / sizeof(uint8_t);
        int count_char = MAX;
        in.seekg(0);

        while (in)
          {
            std::vector<char>result;
            result.reserve(MAX);
            uint8_t buff[MAX];
            if (size < MAX)
              {
                count_char = size;
              }
            in.read(reinterpret_cast<char*>(buff), MAX * sizeof(uint8_t));
            for (int i = 0; i < count_char; ++i)
              {
                if (pos_in_container >= MAX)
                  {
                    pos_in_container = 0;
                  }
                if (pos_in_char_incript >= MAX)
                  {
                    pos_in_char_incript = 0;
                  }
                result.push_back(GetChar(container_action_[pos_in_container++],
                                 static_cast<char>(buff[i]),
                                 char_encryption_[pos_in_char_incript++]));
              }
            size -= MAX;
            of.write(result.data(), result.size());
          }
      }
  }

  std::string EncryptionFileTxt::EncryptionData(const std::string&)
  {
    return {};
  }

  void EncryptionFileTxt::EncryptionData()
  {
    std::ifstream in(data_, std::ios::binary);
    std::ofstream file;
    file.open(data_ + 'i', std::ios::binary);
    if (in && file)
      {
        int pos_in_container = 0;
        int pos_in_char_incript = 0;
        char ch;
        char ch_last;
        uint8_t buff[MAX];
        int count_char = 0;
        while (in.get(ch))
          {
            if (pos_in_container >= MAX)
              {
                pos_in_container = 0;
              }
            if (pos_in_char_incript >= MAX)
              {
                pos_in_char_incript = 0;
              }

            if(ch_last == '\r' && ch == '\n')
              {
                ch_last = {};
                continue;
              }

            buff[count_char++] = static_cast<uint8_t>(SetChar(container_action_[pos_in_container++],
                                                 ch, char_encryption_[pos_in_char_incript++])
                );
            if (count_char == MAX)
              {
                file.write(reinterpret_cast<char*>(buff), MAX * sizeof(uint8_t));
                for (int j = 0; j < MAX; j++)
                  {
                    buff[j] = 0;
                  }
                count_char = 0;
              }
            ch_last = ch;
          }
        file.write(reinterpret_cast<char*>(buff), count_char * sizeof(uint8_t));
        file.close();
      }
  }
}// end namespace
