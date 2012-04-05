#include "libCrypt.h"

using namespace std;

static const string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";


static inline bool is_base64(unsigned char c)
{
  return (isalnum(c) || (c == '+') || (c == '/'));
}

string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len)
{
  string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--)
  {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3)
    {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;

}

string base64_decode(std::string const& encoded_string)
{
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_]))
  {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4)
    {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i)
  {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}


string _ver_encode_(string& inpStr, string& inpKey)
{
        string::iterator iter;
        string::iterator keyIter = inpKey.begin();
        string retStr;

        retStr.clear(); // clear the string in case any garbage values exist

        for(iter = inpStr.begin(); iter != inpStr.end(); iter++, keyIter++)
        {
                // now the sizes are the same
                retStr.push_back((int)(*iter) ^ (int)(*keyIter));
        }

        if(retStr.empty())
                return NULL;
        else
                return retStr;
}

string _ver_decode_(string& encStr, string& inpKey)
{
        string::iterator iter;
        string::iterator keyIter = inpKey.begin();
        string retStr;

        retStr.clear(); // clear the string in case any garbage values exist

        for(iter = encStr.begin(); iter != encStr.end(); iter++, keyIter++)
        {
                // now the sizes are the same
                retStr.push_back((int)(*iter) ^ (int)(*keyIter));
        }

        if(retStr.empty())
                return NULL;
        else
                return retStr;
}

long _ver_encode_(long& inpLongVar, long& inpVerKey)
{
    if(inpLongVar != 0)
        return (inpLongVar ^ inpVerKey);
    else
    {
        inpLongVar = 1000;
        return (inpLongVar ^ inpVerKey);
    }
}

long _ver_decode_(long& inpEncVal, long& inpKey)
{
    long decVar = (inpEncVal ^ inpKey);
    if(decVar == 1000)
        return 0;
    else
        return decVar;  // hope this one works out
}

int _ver_encode_(int& inpUsrLvl, int& inpKey)
{
    if(inpUsrLvl != 0)
        return(inpUsrLvl ^ inpKey);
    else
    {
        inpUsrLvl = 64;
        return (inpUsrLvl ^ inpKey);
    }
}

int _ver_decode_(int& encVal, int& inpKey)
{
    int decVar = (encVal ^ inpKey);
    if(decVar == 64)
        return 0;
    else
        return decVar;  // hope this one also works out
}

void _pad_string_(string& inpStr, unsigned int targetSize)
{
        while(inpStr.size() != targetSize)
                inpStr.push_back('=');  // keep on padding until the size matches
}

void _unpad_string_(std::string& inpStr)
{
    size_t found = inpStr.find('=');    // search for the first occurence of the padded character
    int curLength = inpStr.length();
    inpStr.erase(found, curLength);
}
