#include "s_json.hpp"

//#include <sstream>
#include <iostream>
#include <set>
#include <string>

namespace json
{
    // All functions here

    //checking if it is a terminating char
    std::pair<bool,TokenType> JsonToken::checkTerminatingChar(char curr_char, std::vector<std::pair<char,TokenType>> terminating_char){
        for(auto i = terminating_char.begin(); i != terminating_char.end(); i++){
            if((i->first) == curr_char){
                return {true,i->second};
            }
        } 
        return {false, TokenType::DEFAULT_VALUE};
    }

    //checking if it is an escape char
    bool JsonToken::checkEscapeChar(char curr_char, std::vector<char> escape_char){
        for(auto i = escape_char.begin(); i != escape_char.end(); i++){
            if((*i) == curr_char){
                return true;
            }
        }
        return false;
    }

    //to show the type of token as string
    std::string JsonToken::showType(TokenType currType){
        switch (currType) {
            case TokenType::OPENING_BRACE_TOKEN:
                return "{";
                break;
            case TokenType::CLOSING_BRACE_TOKEN:
                return "}";
                break;
            case TokenType::COMMA_TOKEN:
                return ",";
                break;
            case TokenType::COLON_TOKEN:
                return ":";
                break;
            case TokenType::STRING_TOKEN:
                return "String";
                break;
            case TokenType::INTEGER_TOKEN:
                return "Integer";
                break;
            case TokenType::FLOAT_TOKEN:
                return "Float";
                break;
            default:
                break;
        }
        return "";              //control does not reach till here. Added to avoid warning.
    }

    //displaying all tokens and its type
    void JsonToken::displayTokens(){
        for(auto it = inputTokens.begin(); it != inputTokens.end(); it++){
            std::cout << (it->first) << " => " << showType(it->second) << std::endl;
        }
        std::cout << std::endl;
    };

    void JsonToken::displayJSON() {
        std::cout << "\n\nJSON Content is:" << std::endl;
        for(auto itr = JSONobject.begin(); itr != JSONobject.end(); itr++){
            std::cout << itr->first << " : " << itr->second << std::endl;
        }
    }



    /*
    function to find the type of token from a precalculated token
    This assumes NUMBER_TOKEN as all strings containing only digits. Other than such string each token is considered as a STRING_TOKEN
    */
    /*
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
                default: char temp = token[0];
                        if(temp == '0' || temp == '1' || temp == '2' || temp == '3' || temp == '4' || temp == '5' || temp == '6' || temp == '7' || temp == '8' || temp == '9')
                            return TokenType::INTEGER_TOKEN;
                        else return TokenType::STRING_TOKEN;
                        break;
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
            return TokenType::INTEGER_TOKEN;
        }
        return TokenType::STRING_TOKEN;         // control will not reach here but return statement is added to remove warning
    }
    */

    //function to make tokens from given json string and store them in a map
    void JsonToken::tokenize()
    {
        std::pair<std::string,TokenType> tokenValue;
        bool value_string=false;
        bool value_float=false;
        for(int i = 0; i < json_string.length(); i++){
            //check current char is terminating value or not !
            std::pair<bool,TokenType> flag_present = checkTerminatingChar(json_string[i], terminating_char);

            //if after [:] we are going to check whether it is a string or number
            if(json_string[i] == ':' && json_string[i+1] == '"'){
                value_string = true;
            }
            //resetting to default value
            if(json_string[i] == ','){
                value_string = false;
                value_float = false;
            }

            //if we found out that there is a dot in a non-string it must be a float value (considers 1.1.22 as float also)
            if(!value_string && json_string[i]=='.'){
                value_float = true;
            }
            if(flag_present.first){
                if(!tokenValue.first.empty()){
                    inputTokens.push_back(tokenValue);
                    tokenValue.first.clear();
                    tokenValue.second = TokenType::DEFAULT_VALUE;
                }
                std::pair<std::string,TokenType> terminate_char;
                std::string terminate_char1(1,json_string[i]);
                terminate_char.first = terminate_char1;
                terminate_char.second = flag_present.second;
                if(!terminate_char.first.empty()){
                    inputTokens.push_back(terminate_char);
                }else{
                    continue;
                }
            }else{
                flag_present.first = checkEscapeChar(json_string[i], escape_char);
                if(flag_present.first){
                    continue;
                }

                if(std::isdigit(json_string[i])  && !value_string){
                    tokenValue.first += json_string[i];
                    if(value_float){
                        tokenValue.second = TokenType::FLOAT_TOKEN;
                    }else {
                        tokenValue.second = TokenType::INTEGER_TOKEN;
                        continue;
                    }
                }else {

                    tokenValue.first += json_string[i];
                    tokenValue.second = TokenType::STRING_TOKEN;
                }
            }
        }

        /* my function
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

        */
    }

    void JsonToken::parseJSON(){
        // auto i = inputTokens.begin() + 1;       //first token is opening brace, skip.
        // //we have JSONobject (unordered map)
        // while(i < inputTokens.end() - 1){

        // }


        auto itr = inputTokens.begin();
        bool jsonObj_value = false;
        while(itr!=inputTokens.end()){
            std::string key = itr->first;
            //std::cout<<"Key :"<<itr->first<<std::endl;
            ++itr;
            ++itr;
            if(itr->second == TokenType::OPENING_BRACE_TOKEN){
                ++itr;
                std::string json_value_obj;
                while(itr->second != TokenType::CLOSING_BRACE_TOKEN){
                    json_value_obj += itr->first;
                    json_value_obj += " ";
                    ++itr;
                }
           
                ++itr;
                ++itr;
                auto temp=itr;
                if((++temp)->second == TokenType::CLOSING_BRACE_TOKEN){
                    ++itr;
                }
                JSONobject[key] = json_value_obj;
                continue;
            }

            std::string value = itr->first;
            //std::cout<<"Value :"<<itr->first<<std::endl;
            ++itr;
            ++itr;
            JSONobject[key] = value;
        }

    }


    //fuction to check if json object is valid or not
    void JsonToken::isValidJSON(){
        //write here
        auto itA = inputTokens.begin();
        auto itB = json_states.begin();
        bool flag = true;
        while(itA != inputTokens.end() || itB != json_states.end())
        {

            //if we are getting closing token we can say it is a valid json object and we will return true;
            if(itA->second == TokenType::CLOSING_BRACE_TOKEN){
                return true;
            }

            //to verify it is correct pattern what we are finding
            if(itA->second!=(*itB)){
                flag= false;
            }

            //this is jump from this token to upper key token state
            if(itA->second==TokenType::COMMA_TOKEN){
                itB=json_states.begin()+1;
                ++itA;
                continue;
            }

            //when ever I found to be COLON(:) so that for value it may contain string or number

            if(itA->second == TokenType::COLON_TOKEN){
                    //now we should check that value must be a string or number
                    auto temp=itA;
                    auto temp_jsonObj=itA;
                    if((++temp)->second == TokenType::STRING_TOKEN){
                        itA++;
                        itA++;
                        itB=json_states.begin()+6;//it will directly jump to
                        continue;
                    }
                    else if((++temp_jsonObj)->second==TokenType::OPENING_BRACE_TOKEN){
                        itA++;
                        itA++;
                        itB=json_states.begin()+1;
                        continue;
                    }
                    else{
                        itA++;
                        itA++;
                        itB=json_states.begin()+6;
                        continue;
                    }
            }

            if(flag == false){
                return false;
            }



            if(itA != inputTokens.end())
            {
                ++itA;
            }
            if(itB != json_states.end())
            {
                if(itA->second == TokenType::CLOSING_BRACE_TOKEN){
                    ++itB;
                }
                ++itB;
            }


        }
        return true;
            
            
    
        /*
        My version

        
        traverse map & json_states simultaneously
            compare each tt with json_states 
            if(not matching) 
                return false => json is not valid

        return true => json is valid
        


        //add NUMBER_TOKEN here as well
        std::vector<TokenType> json_states {TokenType::OPENING_BRACE_TOKEN, TokenType::STRING_TOKEN, TokenType::COLON_TOKEN, TokenType::STRING_TOKEN, TokenType::COMMA_TOKEN, TokenType::CLOSING_BRACE_TOKEN};

        auto j = 0;         //iterator for json_states
        //std::map<std::string, TokenType>::iterator i = token_map.begin();
        for(auto i = token_map.begin(); i != token_map.end(); i++, j++){         //i is iterator for token_map
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
            std::cout << "type: " << i->second << " state: " << json_states[j] << std::endl;
            if(i->second != json_states[j]){
                return false;                                   //tt not matched in middle states
            }

        }
        return true;                    //control will not reach to this point but to avoid warning this line is added

        */
    }



}

/*
try to print map in isValidJson. not working.
Number type & float type
subscript operator
nested object
gTest
*/