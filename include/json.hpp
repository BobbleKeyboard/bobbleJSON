//Add guard
#ifndef JSON_H
#define JSON_H

//include libraries
#include <map>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>

namespace json
{
//Classes along with function declaration
/*
                                         i/p                      o/p
Functions:  1. lex: Tokenistion       string                      tokens
            2. parse:                   token                      json object
            3. deparse                  json object                string
            4. print                    string or json object       outstream

Assumptions: Array have atleast one value inside it
*/


    enum class TokenType{
        OPENING_BRACE_TOKEN,
        CLOSING_BRACE_TOKEN,
        OPENING_SQUARE_BRACE_TOKEN,
        CLOSING_SQUARE_BRACE_TOKEN,
        COMMA_TOKEN,
        COLON_TOKEN,
        OPENING_QUOTE_TOKEN,
        CLOSING_QUOTE_TOKEN,
        STRING_TOKEN,
        INTEGER_TOKEN,
        FLOAT_TOKEN,
        ARRAY_TOKEN, 
        OBJECT_TOKEN,                                   
        DEFAULT_VALUE,
        OPTIONAL_COMMA_TOKEN
    };

    class JsonToken{
        private:
            std::string json_string;
            std::vector<std::pair<std::string, TokenType>> allTokens;           //change into vector<pair>

            std::vector<std::pair<char,TokenType>> terminating_char{
                {'{',TokenType::OPENING_BRACE_TOKEN},
                {'}',TokenType::CLOSING_BRACE_TOKEN},
                {'[',TokenType::OPENING_SQUARE_BRACE_TOKEN},
                {']',TokenType::CLOSING_SQUARE_BRACE_TOKEN},
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
                TokenType::OPENING_SQUARE_BRACE_TOKEN,
                TokenType::CLOSING_SQUARE_BRACE_TOKEN,
                TokenType::COMMA_TOKEN,
                TokenType::CLOSING_BRACE_TOKEN,
            };

            std::unordered_map<std::string, std::string> JSONobject;

            //methods
            void tokenize();
            void displayTokens();
            
            
            std::string showType(TokenType);
            TokenType findType(std::string);
            TokenType isIntFloatString(std::string);
            
            std::string makeNestedJSONasString(std::vector<std::pair<std::string, json::TokenType>>::iterator&, int);
            std::string makeArrayasString(std::vector<std::pair<std::string, json::TokenType>>::iterator&, int);

            std::pair<bool,TokenType> checkTerminatingChar(char);
            bool checkEscapeChar(char);
            void displayJSON();
        
        public:
            
            JsonToken(){
                //std::cout << "Can not pass empty JSON" << std::endl;
            }

            JsonToken(std::unordered_map<std::string,std::string> JSONob){
                JSONobject = JSONob;
            }

            //getter methong for JSON map
            std::unordered_map<std::string, std::string> getJSON(){
                return JSONobject;
            }

            void read(std::string);
            void read(std::ifstream&);

            bool isValidJSON();
            void parseJSON();

            friend std::ostream& operator<<(std::ostream& os, const JsonToken& ob);     //overloading output operator

            std::string operator[](std::string);                //overloading subscript operator
            
    };


    class JSON_Value{
        std::string value_type;
        std::string string_value;


        //methods
        std::string getType();
        std::string toString();
        JSON_Value getObject();

        JSON_Value(std::string val, std::string type){
            string_value = val;
            value_type = type;
        }

    };

    

}       //end of namespace json

#endif
