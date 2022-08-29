//Add guard
#ifndef JSON_H
#define JSON_H

//include libraries
#include <map>
#include <string>
#include <vector>

namespace json
{
//Classes along with function declaration
/*
                                         i/p                      o/p
Functions:  1. lex: Tokenistion       string                      tokens
            2. parse:                   token                      json object
            3. deparse                  json object                string
            4. print                    string or json object       outstream
*/


enum class TokenType{
    OPENING_BRACE_TOKEN,
    CLOSING_BRACE_TOKEN,
    COMMA_TOKEN,
    COLON_TOKEN,
    OPENING_QUOTE_TOKEN,
    CLOSING_QUOTE_TOKEN,
    NUMBER_TOKEN,
    STRING_TOKEN,
    OPTIONAL_COMMA_TOKEN
};

class JsonToken{
    public:
        std::string json_string;
        std::map<std::string, TokenType> inputTokens;

        //std::vector<TokenType> json_states {TokenType::OPENING_BRACE_TOKEN, TokenType::STRING_TOKEN, TokenType::COLON_TOKEN, TokenType::STRING_TOKEN, TokenType::OPTIONAL_COMMA_TOKEN, TokenType::CLOSING_BRACE_TOKEN};
        
        //std::string TokenTypeString[9] = {"{", "}", ",", ":", "\"", "\""};
        //NUMBER_TOKEN, STRING_TOKEN, OPTIONAL_COMMA_TOKEN not added yet to TokenTypeString
        
        std::map<std::string, TokenType> tokenize(std::string); 
        bool isValidJSON(std::map<std::string, TokenType>);
        TokenType findType(std::string);
};




}

#endif
