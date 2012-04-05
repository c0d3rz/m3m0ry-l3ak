#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

#define TOKEN_UNKNOWN 99
#define TOKEN_NUMBER 0
#define TOKEN_LITERAL 1
#define TOKEN_DELIM 2

#define BUFFER_SIZE 0xFF

typedef unsigned char tType;

class nxClParser
{
    public:
        void nxClParserLoad(const std::string &inpLine);

    private:
        bool isDelimiter(tType inpChar);
        int nxParserGetTokenType(tType inpChar);
        std::string nxParserPrintTokenType(tType tokenType);
};
