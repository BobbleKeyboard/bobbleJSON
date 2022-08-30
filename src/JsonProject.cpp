//.hpp file
#include "jsonProject.hpp"
/*
      my idea to create a vector of pair of with {std::string,TokenType}
      so to do so we use pair data structure which consists of both these!
      so that when I am going to check the valid JSON or not so that it will be easy to do so!
*/

void JSON::read(std::string input_JSON_String){
    this->input_JSON_String=input_JSON_String;
}
//reading jsonObj from file
void JSON::read(std::ifstream& jsonFile){
    char ch;
    if(jsonFile.is_open()){
        while (jsonFile >> std::noskipws >> ch) {
//            if(!std::isspace(ch)){
//                input_JSON_String+=ch;
//            }
              input_JSON_String+=ch;
        }
    }else{
        std::cout<<"File Not Found"<<std::endl;
        exit(0);
    }
}

std::ostream& operator <<(std::ostream& os, const JSON& obj)
{
    //now here we need store everything in os
    os<<"JSON RAW DATA:";
    os<<std::endl;
    os<<"-------------\n";
    auto it=obj.input_JSON_Tokens.begin();
    while(it!=obj.input_JSON_Tokens.end()){
        os<<(it->first);
        it++;
        //checkType(it->second);
    }
    os<<std::endl;
    return os;
}

void JSON::doTokenize(){
    std::pair<std::string,TokenType> tokenValue;
    bool value_float = false;
    bool value_number = false;
    std::stack<std::pair<std::string,std::string>> stack;
    //here i am thinking we will consider two scenario 1.key.value pair 2.ordered list
    //if we are having an key value pair we will follow this path
    for (int i = 0; i < input_JSON_String.length(); i++) {
        //check current char is terminating value or not !
        std::pair<bool, TokenType> flag_present = checkTerminate(input_JSON_String[i], terminatingChars);

        //if after [:] we are going to check whether it is a string or number
//        if (input_JSON_String[i] == ':' && input_JSON_String[i + 1] == '"') {
//            value_string = true;
//        }

        //if we found that after :

        if(std::isdigit(input_JSON_String[i])){
            value_number = true;
        }
        if(input_JSON_String[0] == '[' &&  std::isdigit(input_JSON_String[i])){
            value_number = true;
        }
        if (input_JSON_String[i] == ':' && std::isdigit(input_JSON_String[i])) {
            value_number = true;
        }
        //if we are having at a current index as : && [(next) -> we can say it is an array type
//        if (input_JSON_String[i] == '[' && input_JSON_String[i - 1] == ':') {
//            value_array = true;
//        }
        //if we are having ] &&
//        if (input_JSON_String[i - 1] == ']' && (input_JSON_String[i] == ',' || input_JSON_String[i] == '}')) {
//            value_array = false;
//        }
        //resetting to default value
        if (input_JSON_String[i] == ',') {
            //value_string = false;
            value_float = false;
            value_number = false;
        }

        //if we found out that there is a dot in a non-string it must be a float value
        if (value_number && input_JSON_String[i] == '.') {
            value_float = true;
        }
        if (flag_present.first) {
            if (!tokenValue.first.empty()) {
                if (tokenValue.first == "TRUE" || tokenValue.first == "true") {
                    tokenValue.second = TokenType::TRUE_TOKEN;
                } else if (tokenValue.first == "FALSE" || tokenValue.first == "false") {
                    tokenValue.second = TokenType::FALSE_TOKEN;
                } else if (tokenValue.first == "NULL" || tokenValue.first == "null") {
                    tokenValue.second = TokenType::NULL_TOKEN;
                }
                input_JSON_Tokens.push_back(tokenValue);
                tokenValue.first.clear();
                tokenValue.second = TokenType::DEFAULT_VALUE;
            }
            std::pair<std::string, TokenType> terminate_char;
            std::string terminate_char1(1, input_JSON_String[i]);
            terminate_char.first = terminate_char1;
            terminate_char.second = flag_present.second;
            if (!terminate_char.first.empty()) {
//                if(terminate_char.second == TokenType::COMMA_TOKEN ) {
//                    terminate_char.first += "\n";
//                }
                if(terminate_char.second == TokenType::OPENING_BRACE_TOKEN ||terminate_char.second == TokenType::OPENING_SQUARE_TOKEN ){
                    if(stack.empty()){
                        stack.push({terminate_char.first,"\n\t"});
                        terminate_char.first += stack.top().second;
                    }else{
                        stack.push({terminate_char.first,stack.top().second+"\t"});
                        terminate_char.first += stack.top().second;
                    }
                }
                else if(terminate_char.second == TokenType::CLOSING_SQUARE_TOKEN || terminate_char.second == TokenType::CLOSING_BRACE_TOKEN){
                    if(!stack.empty()){
                        std::string top_string = stack.top().second;
                        stack.pop();
                        top_string.erase(top_string.size()-1,1);
                        terminate_char.first.insert(0,top_string);
                    }else{
                        break;
                    }
                }
                else if(terminate_char.second == TokenType::COMMA_TOKEN){
                    if(!stack.empty()) {
                        std::string top_string = stack.top().second;
                        terminate_char.first += top_string;
                    }else{
                        break;
                    }
                }
                input_JSON_Tokens.push_back(terminate_char);
            } else {
                continue;
            }
        } else {

            flag_present.first = checkEscape(input_JSON_String[i], escapeChars);
            if (flag_present.first) {
                continue;
            }
            if(input_JSON_String[i] == '"'){
                tokenValue.first+='"';
                i++;
                while(input_JSON_String[i] != '"'){
                    tokenValue.first+=input_JSON_String[i];
                    tokenValue.second=TokenType::STRING_TOKEN;
                    i++;
                }
                tokenValue.first+='"';
                continue;
            }
            else if (value_number) {
                tokenValue.first += input_JSON_String[i];
                if (value_float) {
                    tokenValue.second = TokenType::FLOAT_TOKEN;
                } else {
                    tokenValue.second = TokenType::INTEGER_TOKEN;
                    continue;
                }
            }
            else{
                tokenValue.second = TokenType::STRING_TOKEN;
                tokenValue.first += input_JSON_String[i];
            }
        }
    }
    if(!tokenValue.first.empty()){
        input_JSON_Tokens.push_back({tokenValue.first,tokenValue.second});
        tokenValue.first.clear();
        tokenValue.second=TokenType::DEFAULT_VALUE;
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
            break;
        case TokenType::FLOAT_TOKEN:
            std::cout<<"This is Float"<<std::endl;
            break;
    }
}

bool JSON::isValidJSON() {
    //edge conditions
    if (input_JSON_Tokens.size() == 0) {
        return true;
    } else if (input_JSON_Tokens.size() == 1) {
        return false;
    }
        //here we checking our JSON Obj is Valid or Not
        //to do it we should first the sequence to do we will have a
        //we are having json_obj_state["{","Key",":","Value",",","}"]
        //                                   |                |
        //                                   |<-----<---------|

        //
    else {
        auto itA = input_JSON_Tokens.begin();
        //at starting it must be a { or [ else if we find any thing else we will return false from here
        if (itA->second != TokenType::OPENING_BRACE_TOKEN && itA->second != TokenType::OPENING_SQUARE_TOKEN) {
            return false;
        }

        std::stack<char> stack;
        while (itA != input_JSON_Tokens.end()) {
            if (itA->second == TokenType::OPENING_BRACE_TOKEN) {
                stack.push('{');
                if ((itA + 1) != input_JSON_Tokens.end() && (itA + 1)->second != TokenType::STRING_TOKEN && (itA + 1)->second != TokenType::CLOSING_BRACE_TOKEN) {
                    if (!((itA + 1)->second != TokenType::OPENING_SQUARE_TOKEN && itA->second != TokenType::OPENING_BRACE_TOKEN)) {
                        return false;
                    }
                }
                itA++;
            } else if (itA->second == TokenType::COLON_TOKEN) {
                if ((itA + 1) != input_JSON_Tokens.end() && (itA + 1)->second == TokenType::OPENING_BRACE_TOKEN ||
                    (itA + 1)->second == TokenType::OPENING_SQUARE_TOKEN) {
                    itA++;
                    continue;
                } else if ((itA + 1) != input_JSON_Tokens.end() && (itA + 1)->second != TokenType::TRUE_TOKEN &&
                           (itA + 1)->second != TokenType::FALSE_TOKEN && (itA + 1)->second != TokenType::NULL_TOKEN &&
                           (itA + 1)->second != TokenType::INTEGER_TOKEN &&
                           (itA + 1)->second != TokenType::FLOAT_TOKEN &&
                           (itA + 1)->second != TokenType::STRING_TOKEN) {
                    return false;
                }
                itA++;
            } else if (itA->second == TokenType::COMMA_TOKEN) {
                if ((itA + 1) != input_JSON_Tokens.end() && (itA + 1)->second != TokenType::STRING_TOKEN) {
                    if (!(((itA + 1)->second == TokenType::OPENING_BRACE_TOKEN && stack.top() == '[') ||
                          ((itA + 1)->second == TokenType::OPENING_SQUARE_TOKEN && stack.top() == '['))) {
                        return false;
                    }
                }
                itA++;
            } else if (itA->second == TokenType::CLOSING_BRACE_TOKEN) {
                if (stack.empty() || stack.top() == '[') {
                    return false;
                }
                stack.pop();
                itA++;
            } else if (itA->second == TokenType::OPENING_SQUARE_TOKEN) {
                stack.push('[');
                itA++;
                bool skip = false;
                while (itA != input_JSON_Tokens.end() && (itA->second != TokenType::OPENING_BRACE_TOKEN || itA->second != TokenType::OPENING_SQUARE_TOKEN)) {
                    if ((itA + 1) != input_JSON_Tokens.end()
                        && (itA->second == TokenType::STRING_TOKEN || itA->second == TokenType::INTEGER_TOKEN || itA->second == TokenType::FLOAT_TOKEN || itA->second == TokenType::NULL_TOKEN || itA->second == TokenType::TRUE_TOKEN || itA->second == TokenType::FALSE_TOKEN)
                        && ((itA + 1)->second == TokenType::STRING_TOKEN ||  (itA + 1)->second == TokenType::INTEGER_TOKEN || (itA+1)->second == TokenType::FLOAT_TOKEN || (itA + 1)->second == TokenType::NULL_TOKEN || (itA+1)->second == TokenType::TRUE_TOKEN ||(itA+1)->second == TokenType::FALSE_TOKEN || (itA + 1)->second == TokenType::COLON_TOKEN)) {
                        return false;
                    } else if ((itA + 1) != input_JSON_Tokens.end()
                               && (itA->second == TokenType::COMMA_TOKEN || itA->second == TokenType::COLON_TOKEN)
                               && ((itA + 1)->second == TokenType::COMMA_TOKEN ||
                                   (itA + 1)->second == TokenType::COLON_TOKEN ||
                                   (itA + 1)->second == TokenType::CLOSING_BRACE_TOKEN ||
                                   (itA + 1)->second == TokenType::CLOSING_SQUARE_TOKEN)) {
                        return false;
                    } else if (itA->second == TokenType::OPENING_BRACE_TOKEN ||
                               itA->second == TokenType::OPENING_SQUARE_TOKEN ||
                               itA->second == TokenType::CLOSING_BRACE_TOKEN ||
                               itA->second == TokenType::CLOSING_SQUARE_TOKEN) {
                        skip = true;
                        break;
                    }
                    itA++;
                }
                if (skip == true) {
                    continue;
                }
            } else if (itA->second == TokenType::CLOSING_SQUARE_TOKEN) {
                if (stack.empty() || stack.top() == '{') {
                    return false;
                }
                stack.pop();
                itA++;
            } else {
                if ((itA + 1) != input_JSON_Tokens.end()
                    && ((itA + 1)->second == TokenType::TRUE_TOKEN ||
                        (itA + 1)->second == TokenType::FALSE_TOKEN || (itA + 1)->second == TokenType::NULL_TOKEN ||
                         (itA + 1)->second == TokenType::INTEGER_TOKEN || (itA + 1)->second == TokenType::FLOAT_TOKEN ||
                         (itA + 1)->second == TokenType::STRING_TOKEN)){
                    return false;
                } else if (!(((itA + 1)->second == TokenType::COLON_TOKEN
                              && ((itA - 1)->second == TokenType::OPENING_BRACE_TOKEN ||(itA - 1)->second == TokenType::COMMA_TOKEN))
                             || ((itA - 1)->second == TokenType::COLON_TOKEN && ((itA + 1)->second == TokenType::CLOSING_BRACE_TOKEN || (itA + 1)->second == TokenType::COMMA_TOKEN)))) {
                    //std::cout << itA->first << " KV" << std::endl;
                    return false;
                }
                itA++;
            }
        }
        return stack.empty();
    }
};

void JSON::Push_Into_Map(bool flag){
    std::stack<char> stack;
    auto itr = input_JSON_Tokens.begin() ;
    itr++;
    //std::string inside_key;
    std::string json_value_obj;
    TokenType value=TokenType::DEFAULT_VALUE;
    while (itr != input_JSON_Tokens.end() && flag) {
        std::string key = itr->first;
        ++itr;
        ++itr;
        if(itr->second == TokenType::OPENING_BRACE_TOKEN || itr->second==TokenType::OPENING_SQUARE_TOKEN) {
            if(itr->second==TokenType::OPENING_BRACE_TOKEN){
                value=TokenType::OPENING_BRACE_TOKEN;
                json_value_obj="";
                stack.push('{');
                json_value_obj+='{';
                ++itr;
            }
            else if(itr->second==TokenType::OPENING_SQUARE_TOKEN){
                value=TokenType::OPENING_SQUARE_TOKEN;
                json_value_obj="";
                stack.push('[');
                json_value_obj+='[';
                ++itr;
            }

            while(!stack.empty()){
                if(itr->second == TokenType::OPENING_BRACE_TOKEN ){
                    //inside_key = (itr+1)->first;
                    stack.push('{');
                }
                else if(itr->second == TokenType::OPENING_SQUARE_TOKEN){
                    //inside_key=(itr-1)->first;
                    stack.push('[');
                }
                else if(itr->second == TokenType::CLOSING_BRACE_TOKEN || itr->second == TokenType::CLOSING_SQUARE_TOKEN){
                    stack.pop();
                    //  jsonObject[inside_key] = inside_value;
                }
                json_value_obj += itr->first;
                // inside_value += itr->first;
                itr++;
            }


            ++itr;
            JSON_Value object(value,json_value_obj);
            key_value[key] = object;
            continue;
        }

        else if(itr->second == TokenType::INTEGER_TOKEN){
            value = TokenType::INTEGER_TOKEN;
            JSON_Value object(value,itr->first);
            ++itr;
            ++itr;
            key_value[key] = object;
        }
        else if(itr->second == TokenType::FLOAT_TOKEN){
            value = TokenType::FLOAT_TOKEN;
            JSON_Value object(value,itr->first);
            ++itr;
            ++itr;
            key_value[key] = object;
        }
        else if(itr->second == TokenType::STRING_TOKEN){
            value = TokenType::STRING_TOKEN;
            JSON_Value object(value,itr->first);
            ++itr;
            ++itr;
            key_value[key] = object;
        }
        else if(itr->second == TokenType::TRUE_TOKEN){
            value = TokenType::TRUE_TOKEN;
            JSON_Value object(value,itr->first);
            ++itr;
            ++itr;
            key_value[key] = object;
        }
        else if(itr->second == TokenType::FALSE_TOKEN){
            value = TokenType::FALSE_TOKEN;
            JSON_Value object(value,itr->first);
            ++itr;
            ++itr;
            key_value[key] = object;
        }
        else if(itr->second == TokenType::NULL_TOKEN){
            value = TokenType::NULL_TOKEN;
            JSON_Value object(value,itr->first);
            ++itr;
            ++itr;
            key_value[key] = object;
        }

    }
}


void JSON::parseJSON() {
    //we will use map structure
    JSON::doTokenize();
    if (JSON::isValidJSON()) {
        std::cout << "VALID JSON:!!!";
        auto itr = input_JSON_Tokens.begin() ;
        bool flag=false;
        if(itr->second == TokenType::OPENING_BRACE_TOKEN && (itr+1)->second==TokenType::CLOSING_BRACE_TOKEN){
            std::cout<<"Can't Be Push to Map\n";
        }
        else if(itr->second == TokenType::OPENING_SQUARE_TOKEN && (itr+1)->second==TokenType::CLOSING_SQUARE_TOKEN){
            std::cout<<"Can't Be Push to Map\n";
        }
        else if(itr->second == TokenType::OPENING_BRACE_TOKEN){
            flag=true;
            JSON::Push_Into_Map(flag);
        }else if(itr->second == TokenType::OPENING_SQUARE_TOKEN){
            //iterator
        }
    }
    else{
        std::cout<<"INVALID JSON INPUT"<<std::endl;
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


