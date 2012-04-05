#ifndef LIBCRYPT_H_INCLUDED
#define LIBCRYPT_H_INCLUDED

// libCrypt -- handle all encryption functions

#include <iostream>
#include <cstdlib>
#include <string>

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
std::string base64_decode(std::string const& encoded_string);

// string vernam crypt functions
// std::string enc_dec -- I also need the enc_dec functions for the long, int and double variables
void _pad_string_(std::string& inpStr, unsigned int targetSize); // pad string
void _unpad_string_(std::string& inpStr);   // unpad string
std::string _ver_encode_(std::string& inpStr, std::string& inpKey);
std::string _ver_decode_(std::string& encStr, std::string& inpKey);

// long, int && bool enc_dec
long _ver_encode_(long& inpLongVar, long& inpVerKey);
long _ver_decode_(long& inpEncVal, long& inpKey);
int _ver_encode_(int& inpUsrLvl, int& inpKey);
int _ver_decode_(int& encVal, int& inpKey);

#endif // LIBCRYPT_H_INCLUDED
