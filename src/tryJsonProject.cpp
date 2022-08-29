#include<string>
#include<iostream>
#include<vector>
#include<map>
#include<unordered_map>
//.hpp file
#include "jsonProject.hpp"
/*
      my idea to create a vector of pair of with {std::string,TokenType}
      so to do so we use pair data structure which consists of both these!
      so that when i am going to check the valid JSON or not so that it will be easy to do so!
*/

class JSON{
private:
    std::string input_JSON_String;
    //here we are storing {string,TokenType}
    std::vector<std::pair<std::string,TokenType>> input_JSON_Tokens;
    //here we will combine the string value with TokenType
    std::vector<std::pair<char,TokenType>> terminatingChars{
        {'{',TokenType::OPENING_BRACE_TOKEN},
        {'}',TokenType::CLOSING_BRACE_TOKEN},
        {':',TokenType::COLON_TOKEN},
        {',',TokenType::COMMA_TOKEN}
    };
    //here we are not requried any TokenType because here we are escaping so not required!

    std::vector<char> escapeChars{' ','\t','\n','"'};

    std::vector<TokenType> json_Obj_State{
            TokenType::OPENING_BRACE_TOKEN,
            TokenType::STRING_TOKEN,//here it should be always a String (Key)
            TokenType::COLON_TOKEN,
            TokenType::STRING_TOKEN,//here it may be String or Number or Boolean or Null (Value)
            TokenType::INTEGER_TOKEN,
            TokenType::FLOAT_TOKEN,
            TokenType::COMMA_TOKEN,//we are going to upper STRING_TOKEN
            TokenType::CLOSING_BRACE_TOKEN,
    };
    //using map data structure i am going to its key-value pair in map<string,string> format
    std::unordered_map<std::string,std::string> jsonObject;//jsonObject['Name']->
public:
    JSON(){
        std::cout<<"Stop Please pass json string to JSON obj"<<std::endl;
    }

    JSON(std::string input_JSON_String){
        this->input_JSON_String=input_JSON_String;
    }
    //all methods
    void doTokenize();
    bool isValidJSON();
    void displayTokens();
    void checkType(TokenType);
    void parseJSON();//Tokens->JSON
    void displayMap();

    std::pair<bool,TokenType> checkTerminate(char,std::vector<std::pair<char,TokenType>>);
    bool checkEscape(char,std::vector<char>);
};

void JSON::doTokenize(){
    std::pair<std::string,TokenType> tokenValue;
    bool value_string=false;
    bool value_float=false;
    for(int i=0;i<input_JSON_String.length();i++){
        //check current char is terminating value or not !
        std::pair<bool,TokenType> flag_present = checkTerminate(input_JSON_String[i],terminatingChars);

        //if after [:] we are going to check whether it is a string or number
        if(input_JSON_String[i] == ':' && input_JSON_String[i+1] == '"'){
            value_string = true;
        }
        //resetting to default value
        if(input_JSON_String[i] == ','){
            value_string = false;
            value_float = false;
        }

        //if we found out that there is a dot in a non-string it must be a float value
        if(!value_string && input_JSON_String[i]=='.'){
            value_float = true;
        }
        if(flag_present.first){
            if(!tokenValue.first.empty()){
                input_JSON_Tokens.push_back(tokenValue);
                tokenValue.first.clear();
                tokenValue.second = TokenType::DEFAULT_VALUE;
            }
            std::pair<std::string,TokenType> terminate_char;
            std::string terminate_char1(1,input_JSON_String[i]);
            terminate_char.first = terminate_char1;
            terminate_char.second = flag_present.second;
            if(!terminate_char.first.empty()){
                input_JSON_Tokens.push_back(terminate_char);
            }else{
                continue;
            }
        }else{
            flag_present.first = checkEscape(input_JSON_String[i],escapeChars);
            if(flag_present.first){
                continue;
            }

            if(std::isdigit(input_JSON_String[i])  && !value_string){
                tokenValue.first += input_JSON_String[i];
                if(value_float){
                    tokenValue.second = TokenType::FLOAT_TOKEN;
                }else {
                    tokenValue.second = TokenType::INTEGER_TOKEN;
                    continue;
                }
            }else {

                tokenValue.first += input_JSON_String[i];
                tokenValue.second = TokenType::STRING_TOKEN;
            }
        }
    }
};


std::pair<bool,TokenType> JSON::checkTerminate(char current_char,std::vector<std::pair<char,TokenType>> termintingChars){
    for(auto it = termintingChars.begin();it!=termintingChars.end();it++){
        if((it->first) == current_char){
            return {true,it->second};
        }
    }
    return {false,TokenType::DEFAULT_VALUE};
};

bool JSON::checkEscape(char current_char,std::vector<char> escapeChars){
    for(auto it = escapeChars.begin();it != escapeChars.end();it++){
        if((*it) == current_char){
            return true;
        }
    }
    return false;
};

void JSON::displayTokens(){
    for(auto it = input_JSON_Tokens.begin();it != input_JSON_Tokens.end();++it){
        std::cout<<(it->first)<<" ";
       // checkType(it->second);
    }
    std::cout<<std::endl;
};

//switch case to see the type of token
void JSON::checkType(TokenType currType){
    switch (currType) {
        case TokenType::OPENING_BRACE_TOKEN:
            std::cout<<"This is {"<<std::endl;
            break;
        case TokenType::CLOSING_BRACE_TOKEN:
            std::cout<<"This is }"<<std::endl;
            break;
        case TokenType::COMMA_TOKEN:
            std::cout<<"This is ,"<<std::endl;
            break;
        case TokenType::COLON_TOKEN:
            std::cout<<"This is :"<<std::endl;
            break;
        case TokenType::STRING_TOKEN:
            std::cout<<"This is String"<<std::endl;
            break;
        case TokenType::INTEGER_TOKEN:
            std::cout<<"This is Integer"<<std::endl;
        case TokenType::FLOAT_TOKEN:
            std::cout<<"This is FLoat"<<std::endl;
    }
}


bool JSON::isValidJSON(){
    //here we checking our JSON Obj is Valid or Not
    //to do it we should first the sequence to do we will have a
    //we are having json_obj_state["{","Key",":","Value",",","}"]
    //                                   |                |
    //                                   |<-----<---------|

    //
    auto itA = input_JSON_Tokens.begin();
    auto itB = json_Obj_State.begin();
    bool flag = true;
    while(itA != input_JSON_Tokens.end() || itB != json_Obj_State.end())
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
            itB=json_Obj_State.begin()+1;
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
                    itB=json_Obj_State.begin()+6;//it will directly jump to
                    continue;
                }
                else if((++temp_jsonObj)->second==TokenType::OPENING_BRACE_TOKEN){
                    itA++;
                    itA++;
                    itB=json_Obj_State.begin()+1;
                    continue;
                }
                else{
                    itA++;
                    itA++;
                    itB=json_Obj_State.begin()+6;
                    continue;
                }
        }

        if(flag == false){
            return false;
        }



        if(itA != input_JSON_Tokens.end())
        {
            ++itA;
        }
        if(itB != json_Obj_State.end())
        {
            if(itA->second == TokenType::CLOSING_BRACE_TOKEN){
                ++itB;
            }
            ++itB;
        }


    }
    return true;
};

void JSON::parseJSON() {
    //we will use map structure

    auto itr = input_JSON_Tokens.begin()+1;
    bool jsonObj_value = false;
    while(itr!=input_JSON_Tokens.end()){

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
           // std::cout<<json_value_obj;
            ++itr;
            ++itr;
            auto temp=itr;
            if((++temp)->second == TokenType::CLOSING_BRACE_TOKEN){
                ++itr;
            }
            jsonObject[key] = json_value_obj;
            continue;
        }

        std::string value = itr->first;
        //std::cout<<"Value :"<<itr->first<<std::endl;
        ++itr;
        ++itr;
        jsonObject[key] = value;
    }
}

void JSON::displayMap() {
    auto itr=jsonObject.begin();
    std::cout<<"\n\nDisplay Map Content:"<<std::endl;
    while(itr!=jsonObject.end()){
        std::cout<<itr->first<<": "<<itr->second;
        std::cout<<std::endl;
        itr++;
    }
}

int main(){
    JSON jsonObj("{\n\t\"Name\":\"Surya\",\"Age\":20.0,\"Address\":{\"Pin code\":\"532459\",\"Country\":\"Indian\"},\"Group\":\"CSE\"}");
    jsonObj.doTokenize();

    if(jsonObj.isValidJSON()){
        std::cout<<"VALID JSON"<<std::endl;
        jsonObj.displayTokens();
        //now we are going to parse it to jsonObject using those tokens
        jsonObj.parseJSON();

        //display JSONObj content in map
        jsonObj.displayMap();
    }

    else{
        std::cout<<"INVALID JSON"<<std::endl;
    }

    return 0;
}
