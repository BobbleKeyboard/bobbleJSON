#include "json.hpp"

//#include <sstream>
#include <iostream>
#include <set>
#include <string>

namespace json
{
    // All functions here

    /*
    function to find the type of token from a precalculated token
    This assumes NUMBER_TOKEN as all strings containing only digits. Other than such string each token is considered as a STRING_TOKEN
    */
    TokenType JsonToken::findType(std::string token){
        if(token.size() == 1){
            switch(token[0]){               //it will only have 1 char
                case '{': return TokenType::OPENING_BRACE_TOKEN;
                            break;
                case '}': return TokenType::CLOSING_BRACE_TOKEN;
                            break;
                case ',': return TokenType::COMMA_TOKEN;
                            break;
                case ':': return TokenType::COLON_TOKEN;
                            break;
                default: break;
            }
        }
        else{
            bool isNum = true;                  // not using this variable anywhere
            for(auto &i : token){
                switch(i){
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9': break;
                    default: isNum = false; 
                            return TokenType::STRING_TOKEN;
                            break;

                }
            }
            return TokenType::NUMBER_TOKEN;
        }
        return TokenType::STRING_TOKEN;         // control will not reach here but return statement is added to remove warning
    }

    //function to make tokens from given json string and store them in a map
    std::map<std::string, TokenType> JsonToken::tokenize(std::string json_str)
    {
         std::map<std::string, TokenType> InputTokens;          //stores final tokens

        std::set<TokenType> terminating_char_TT_set = {TokenType::OPENING_BRACE_TOKEN, TokenType::CLOSING_BRACE_TOKEN, TokenType::COMMA_TOKEN, TokenType::COLON_TOKEN};
        std::set<char> terminating_char_set = {'{', '}', ',', ':'};
        std::set<char> escape_char_set = {'\\'};

        std::string token;
        TokenType tt;
        

        for(auto &x: json_str)
        {
            if (auto index1 = terminating_char_set.find(x); (*index1 >= 0 && *index1 < terminating_char_set.size()))
            {
                if (!token.empty())
                {
                    //find token ka type then make a pair and push it in map InputTokens
                    tt = findType(token);               //make a function which finds type of token


                    InputTokens.insert(std::pair<std::string, TokenType>(token, tt));       //insert in map
                    token.clear();
                }
                std::string temp_token = &x;

                if (!temp_token.empty()){
                    //find token ka type then make a pair and push it in map InputTokens
                    tt = findType(temp_token);


                    InputTokens.insert(std::pair<std::string, TokenType>(temp_token, tt));          //insert in map
                }   
                else
                    continue;
            }
            else
            {
                if (auto index2 = escape_char_set.find(x); (*index2 >= 0 && *index2 < escape_char_set.size()))
                {
                    continue;
                }
                token += x;
            }
        }

        return InputTokens;
    }


    //fuction to check if json object is valid or not
    bool JsonToken::isValidJSON(std::map<std::string, TokenType> token_map){
        //write here
        
        /*
        traverse map & json_states simultaneously
            compare each tt with json_states 
            if(not matching) 
                return false => json is not valid

        return true => json is valid
        */


        //add NUMBER_TOKEN here as well
        std::vector<TokenType> json_states {TokenType::OPENING_BRACE_TOKEN, TokenType::STRING_TOKEN, TokenType::COLON_TOKEN, TokenType::STRING_TOKEN, TokenType::COMMA_TOKEN, TokenType::CLOSING_BRACE_TOKEN};

        auto j = 0;         //iterator for json_states
        std::map<std::string, TokenType>::iterator i = token_map.begin();
        for(; i != token_map.end(); i++, j++){         //i is iterator for token_map
            //TokenType tt;
            //tt = TokenType::i->second;

            if(j == 4){
                //handle comma
                if(i->second == json_states[j]){            //optional comma matched
                    j = 0;
                    continue;
                }
                else{
                    if(i->second != json_states[j+1]){          //optional comma not matched and no closing brace
                        return false;
                    }
                    return true;                                //optional comma not matched but closing brace matched i.e. JSON end and valid
                        
                }
            }
            //std::cout << tt;
            //std::cout << "type: " << i->second << " state: " << json_states[j] << std::endl;
            if(i->second != json_states[j]){
                return false;                                   //tt not matched in middle states
            }

        }
        return true;                    //control will not reach to this point but to avoid warning this line is added

    }

    //make a function to display json

}

/*
try to print map in isValidJson. not working.
Number type & float type
subscript operator
nested object
gTest
*/