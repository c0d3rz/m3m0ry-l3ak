#include "libClParser.h"

using namespace std;

void nxClParser::nxClParserLoad(const string &inpLine)
{
    string strToken;    // current token
    tType tokenType = TOKEN_UNKNOWN;

    unsigned int idx = 0x00;

    // while we are inside the string and within the BUF_SIZE
    for(; (idx < inpLine.length()) && (idx < BUFFER_SIZE); idx++)
    {
        if(tokenType == TOKEN_UNKNOWN)
            tokenType = nxParserGetTokenType(inpLine.at(idx));

        //cout<<int(tokenType)<<" "<<inpLine.at(idx)<<endl; // enable print tokenType
        cout<<nxParserPrintTokenType(tokenType);
        tokenType = TOKEN_UNKNOWN;

        // Now the token type has been known, find the tokens now
        //idx = 0x00;
    }
}

int nxClParser::nxParserGetTokenType(tType inpChar)
{
    if(isdigit(inpChar))
        return TOKEN_NUMBER;
    else if(isalpha(inpChar) || (inpChar == '_'))
        return TOKEN_LITERAL;
    else if(isspace(inpChar))
        return TOKEN_DELIM;
    else
        return TOKEN_UNKNOWN;
}

string nxClParser::nxParserPrintTokenType(tType tokenType)
{
    switch(tokenType)
    {
        case TOKEN_DELIM:
            return "DELIMITER\n";
        break;

        case TOKEN_LITERAL:
            return "LITERAL\n";
        break;

        case TOKEN_NUMBER:
            return "NUMBER\n";
        break;

        default:
            return "UNKNOWN TOKEN\n";
        break;
    }
}
