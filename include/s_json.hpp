//Add guard
#ifndef JSON_H
#define JSON_H

//include libraries
#include <map>
#include <string>
#include <vector>
#include <unordered_map>
#include <ostream>
#include <iostream>

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
    STRING_TOKEN,
    INTEGER_TOKEN,
    FLOAT_TOKEN,
    DEFAULT_VALUE,
    OPTIONAL_COMMA_TOKEN
};

class JsonToken{
    private:
        std::string json_string;
        std::vector<std::pair<std::string, TokenType>> inputTokens;           //change into vector<pair>

        std::vector<std::pair<char,TokenType>> terminating_char{
            {'{',TokenType::OPENING_BRACE_TOKEN},
            {'}',TokenType::CLOSING_BRACE_TOKEN},
            {':',TokenType::COLON_TOKEN},
            {',',TokenType::COMMA_TOKEN}
        };

        std::vector<char> escape_char{' ','\t','\n','"'};

        std::vector<TokenType> json_states{
            TokenType::OPENING_BRACE_TOKEN,
            TokenType::STRING_TOKEN,
            TokenType::COLON_TOKEN,
            TokenType::STRING_TOKEN,
            TokenType::INTEGER_TOKEN,
            TokenType::FLOAT_TOKEN,
            TokenType::COMMA_TOKEN,
            TokenType::CLOSING_BRACE_TOKEN,
        };

        std::unordered_map<std::string,std::string> JSONobject;
    
    public:

        JsonToken(){
            std::cout << "Can not pass empty JSON" << std::endl;
        }

        JsonToken(std::string input){
            this->json_string = input;
        }

        void tokenize();
        bool isValidJSON();
        void displayTokens();
        std::string showType(TokenType);
        void parseJSON();
        void displayJSON();

        std::pair<bool,TokenType> checkTerminatingChar(char,std::vector<std::pair<char,TokenType>>);
        bool checkEscapeChar(char,std::vector<char>);
        
        /*
        std::map<std::string, TokenType> tokenize(std::string); 
        bool isValidJSON(std::map<std::string, TokenType>);
        TokenType findType(std::string);
        */
};




}

#endif
