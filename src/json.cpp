#include "json.hpp"

#include <set>
#include <stack>

namespace json {
//All functions here


    /*
    function to read file content and save in json_string
    */

    void JsonToken::read(std::string str){
        json_string = str;
    }


    void JsonToken::read(std::ifstream& file){
        //appending a blank line in the end of txt file is solving the issue of 2 closing braces, but why?
        std::string myline;
        if(file.is_open()){
            while(!file.eof()){
                std::getline(file, myline);
                json_string += myline;        //append
                //std::cout << json_string << std::endl;
            }
        }
        else {
            std::cerr << "Could not open the file" << std::endl;
            exit(EXIT_FAILURE);
        }
    }



    /*
    checkTerminatingChar function returns true, tokenType if the token is a terminating char 
    otherwise false, default_value tokenType
    */
    std::pair<bool,TokenType> JsonToken::checkTerminatingChar(char curr_char){
        for(auto i = terminating_char.begin(); i != terminating_char.end(); i++){
            if((i->first) == curr_char){
                //std::cout << curr_char << std::endl;
                return {true, i->second};
            }
        } 
        //std::cout << curr_char << std::endl;
        return {false, TokenType::DEFAULT_VALUE};
    }



    /*
    returns true if curr_char is an escape char
    otherwise false
    */
    bool JsonToken::checkEscapeChar(char curr_char){
        for(auto i = escape_char.begin(); i != escape_char.end(); i++){
            if((*i) == curr_char){
                //std::cout << curr_char << std::endl;
                return true;
            }
        }
        //std::cout << curr_char << std::endl;
        return false;
    }



    /*
    checks if a given string(more than 1 char) is an int or float
    otherwise string
    */
    TokenType JsonToken::isIntFloatString(std::string token){
        int cnt = 0;                        //counts no. of '.' in token
        for(int itr = 0; itr < token.length() && cnt < 2; itr++){

            if(token[itr] == '.')
                cnt++;
        }
        if(cnt == 0)
            return TokenType::INTEGER_TOKEN;
        else if(cnt == 1)
            return TokenType::FLOAT_TOKEN;
        else 
            return TokenType::STRING_TOKEN;
    }



    /*
    showType function to show the type of token as string
    */
    std::string JsonToken::showType(TokenType currType){
        switch (currType) {
            case TokenType::OPENING_BRACE_TOKEN:
                return "{";
                break;
            case TokenType::CLOSING_BRACE_TOKEN:
                return "}";
                break;
            case TokenType::OPENING_SQUARE_BRACE_TOKEN:
                return "[";
                break;
            case TokenType::CLOSING_SQUARE_BRACE_TOKEN:
                return "]";
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
            case TokenType::ARRAY_TOKEN:
                return "Array";
                break;
            default:
                return "";
                break;
        }
        return "";              //control does not reach till here. Added to avoid warning.
    }



    /*
    function to find the type of token from a precalculated token
    */
    TokenType JsonToken::findType(std::string token){      
        if(token.size() == 1){
            switch(token[0]){               //it will only have 1 char
                case '{': return TokenType::OPENING_BRACE_TOKEN;
                            break;
                case '}': return TokenType::CLOSING_BRACE_TOKEN;
                            break;
                case '[': return TokenType::OPENING_SQUARE_BRACE_TOKEN;
                            break;
                case ']': return TokenType::CLOSING_SQUARE_BRACE_TOKEN;
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
                    case '.':
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
                            return TokenType::STRING_TOKEN;             //any char other than digits or dot -> string
                            break;

                }
            }

            return isIntFloatString(token);                             //cases: 123, 12.3, 123.4.56.7
                                                                        //       int  float  string
        }
        return TokenType::STRING_TOKEN;         // control will not reach here but return statement is added to remove warning
    }



    /*
    displays all token and their type
    */
    void JsonToken::displayTokens(){
        std::cout << "Tokens are:\n\n";
        for(auto it = allTokens.begin(); it != allTokens.end(); it++){
            std::cout << (it->first) << " => " << showType(it->second) << std::endl;
        }
        std::cout << std::endl;
    }


    /*
    displays json which is stored in a map
    */
    void JsonToken::displayJSON() {
        std::cout << "\n\nJSON Content is:" << std::endl;
        for(auto itr = JSONobject.begin(); itr != JSONobject.end(); itr++){
            std::cout << itr->first << " : " << itr->second << std::endl;
        }
    }


    /*
    uses string and makes a vector<pair<string, tokenType>> which stores all tokens in order
    */
    void JsonToken::tokenize(){
        /*
            we have vector<pair<char, TokenType>> terminating_char;
                    vector<char> escape_char;
                    input string in json_string;

            functions used: findType
                            checkTerminatingChar
                            checkEscapeChar

        */

        std::pair<std::string, TokenType> token;             //stores token value before pushing into allTokens
        std::string tokenValue;                              //stores token value in between
        std::pair<bool, TokenType> tempTerCh;                //stores result of checkTerminatingChar
        bool tempEscCh;                                      //stores result of checkEscapeChar

        //std::cout << json_string << std::endl;

        for(int i = 0; i < json_string.length(); i++){
            //std::cout << json_string[i] << std::endl;
            tempTerCh = checkTerminatingChar(json_string[i]);
            
            if(tempTerCh.first){                                                //it is a terminating char
                if(!tokenValue.empty()){                                        //previously stored tokenValue
                    token = std::make_pair(tokenValue, findType(tokenValue));   
                    allTokens.push_back(token);                                 //push that old value
                    tokenValue.clear();
                }
                token = std::make_pair(json_string[i], tempTerCh.second);      //push the found terminating char as token
                allTokens.push_back(token); 
            }
            else{                                           //not a terminating char
                tempEscCh = checkEscapeChar(json_string[i]);
                if(tempEscCh){                          
                    continue;                                //ignore escape char
                }
                else{
                    tokenValue += json_string[i];              //keep storing in tokenValue
                }

            }
        }
        
        return;

    }


    /*
        used to make a string of nested json value
    */
    std::string JsonToken::makeNestedJSONasString(std::vector<std::pair<std::string, json::TokenType>>::iterator &itr, int nest_cnt){
        itr++;
        int internal_nest_cnt = nest_cnt + 1;           //if we arrive at this function means one more level of nesting
        int i;                                          //i for giving tabs
        std::string ans = "";
        while(internal_nest_cnt != nest_cnt){
            
            for(i = 0; i < internal_nest_cnt; i++){         //add no. of tabs = internal_nest_cnt before key
                ans += "\t";
            }

            ans += itr->first + " : ";                      //adding key and :

            itr+=2;                                         //points to value corresponding to above key

            if(itr->second == TokenType::OPENING_BRACE_TOKEN){                      //another nesting     
               
                ans += "{\n" + makeNestedJSONasString(itr, internal_nest_cnt) + "\n";           //a function used recursively to get the right string
                
                //add again no. of tabs
                for(i = 0; i < internal_nest_cnt; i++){         //add no. of tabs = internal_nest_cnt before key
                    ans += "\t";
                }

                ans += "}";   
            }
            else if(itr->second == TokenType::OPENING_SQUARE_BRACE_TOKEN){          //array encountered
                ans += "[" + makeArrayasString(itr, internal_nest_cnt) + "]";
            }
            else{                       //no nesting then string float or int value (normal)
                ans += itr->first;
            }

            itr++;              //expects comma or closing braces

            if(itr->second == TokenType::COMMA_TOKEN){      //more ahead
                ans += ",\n";
                itr++;
                continue;
            }
            else{                                           //closing brace came
                internal_nest_cnt--;
                
            }


        }

        //std::cout << itr->first << std::endl;
        return ans;
    }


    /*
    converts array into string to be saved in map as value
    */
    std::string JsonToken::makeArrayasString(std::vector<std::pair<std::string, json::TokenType>>::iterator& itr, int nest_cnt){
        int i;
        int internal_nest_cnt = nest_cnt;           //same because not increasing tabs for sq brackets
        itr++;                  //now points to first element
        std::string ans = "";

        while(true){
            if(itr->second == TokenType::OPENING_BRACE_TOKEN){                  //if an opening brace or opening sq brace encountered, call those functions
                ans += "{\n" + makeNestedJSONasString(itr, internal_nest_cnt) + "\n";           //a function used recursively to get the right string
                
                //add again no. of tabs
                for(i = 0; i < internal_nest_cnt; i++){         //add no. of tabs = internal_nest_cnt before key
                    ans += "\t";
                }

                ans += "}";
            }
            else if(itr->second == TokenType::OPENING_SQUARE_BRACE_TOKEN){
                ans += "[" + makeArrayasString(itr, internal_nest_cnt) + "]";
            }
            else{
                ans += itr->first;
            }
                              
            itr++;                              //expects comma or closing square brace
            if(itr->second == TokenType::COMMA_TOKEN){
                ans+= ", ";
                itr++;                          //expects another element of array
            }
            else{
                return ans;
            }

        }

    }


    /*
    store tokens into map as a json object
    */
    void JsonToken::parseJSON(){
        /*
        we have unordered map std::unordered_map<std::string,std::string> JSONobject;
        */

        tokenize();
        displayTokens();

        if(isValidJSON()){                      //checking validity of JSON
            std::cout << "JSON is valid" << std::endl;
        }
        else{
            std::cout << "JSON is invalid" << std::endl;
            return;
        }
        
        std::string key, value;
        int i;
        int nest_cnt = 1;
        auto itr = allTokens.begin();       //on opening brace
        itr++;                              //on first key

        if(itr->second == TokenType::CLOSING_BRACE_TOKEN){          //here json is {}
            return;
        }

        while(itr < allTokens.end()){
            key = itr->first;
            itr+=2;                       //skipped :
            
            if(itr->second == TokenType::OPENING_BRACE_TOKEN){                  // if itr->second == tt opening brace -> nested json object
                //calc nested value as string

                value = "{\n" + makeNestedJSONasString(itr, nest_cnt) + "\n";
                for(i = 0; i < nest_cnt; i++){         //for indentation, add no. of tabs = nest_cnt before key
                    value += "\t";
                }
                value += "}";
            }
            else if(itr->second == TokenType::OPENING_SQUARE_BRACE_TOKEN){          //array encountered
                value = "[" + makeArrayasString(itr, nest_cnt) + "]";
            }
            else{
                value = itr->first;
            }
            
            /*

            auto value_type = getType(value);
            

            */

            JSONobject[key] = value;
            itr+=2; 
        }

        
    }


    /*
    checks validity of json object before it is parsed
    */
    bool JsonToken::isValidJSON(){
        auto j = 0;         //iterator for json_states

        std::stack<TokenType> stk;

        if(allTokens.begin()->second == TokenType::OPENING_BRACE_TOKEN){                //if first token opeining brace encountered then insert object_token in stack
            stk.push(TokenType::OBJECT_TOKEN);
        }

        if(allTokens.size() > 1 && (allTokens.begin() + 1) -> second == TokenType::CLOSING_BRACE_TOKEN){
            return true;                    // {} is also a valid json
        }
        
        //traverse allTokens
        for(auto i = allTokens.begin(); i != allTokens.end(); i++, j++){         
            
            if(stk.empty()){                    //stack is empty but there are tokens left -> invalid
                return false;   
            }
           
            if(j == 3){
                if(i->second == json_states[j] || i->second == json_states[j+1] || i->second == json_states[j+2]){             // after colon either int, float or string
                    j = 7;               //all value token crosses, now expecting comma when j becomes 6
                    continue;           //value token came here
                }
                else if(i->second == TokenType::OPENING_BRACE_TOKEN){                   //if not the above 3 then check for opening brace token -> denotes nested json
                    stk.push(TokenType::OBJECT_TOKEN);                                          //object_token shows that a jsonobject is in process
                    
                    j = 0;
                    continue;
                }
                else if(i->second == TokenType::OPENING_SQUARE_BRACE_TOKEN){           //opening square brace token encountered
                    stk.push(TokenType::ARRAY_TOKEN);

                    j = 2;                                      //next expecting string or int or float
                    continue;
                }
                else return false;                              //anything except str, int, float, {, [ -> invalid
                    
            }

            if(j == 8){
                if(i->second == TokenType::COMMA_TOKEN){        //comma encountered
                    if(stk.empty()){
                        return false;
                    }

                    if(stk.top() == TokenType::ARRAY_TOKEN){        //expects a value after comma
                        j = 2;
                        continue;
                    }
                    else if(stk.top() == TokenType::OBJECT_TOKEN){              //expects a key after comma
                        j = 0;
                        continue;
                    }
                    
                
                }
                else{
                    if(i->second == TokenType::CLOSING_SQUARE_BRACE_TOKEN && stk.top() == TokenType::ARRAY_TOKEN){
                        stk.pop();
                        
                        if(stk.empty()){                                //after ending array if stack is empty -> invalid
                            return false;
                        }

                        //Expects a comma in both conditions(top array_token, top object_token)
                        j = 7;
                        continue;
                        
                        
                    }
                    else if(i->second == TokenType::CLOSING_BRACE_TOKEN && stk.top() == TokenType::OBJECT_TOKEN){          //not comma. closing bracket came
                        stk.pop();

                        //Expects a comma in both conditions(top array_token, top object_token)
                        j = 7;
                        continue;
                        
                    }
                    else return false;                          //no comma, no closing brace -> something else -> invalid

                }
            }


            if(i->second != json_states[j]){                     //for all j = 0, 1, 2
                return false;                                   //tt not matched in middle states
            }

        }
        if(stk.empty()){                                        //allTokens ended and stack is empty
            return true; 
        }
        else return false;                                      //allTokens ended but stack is not empty -> invalid
        
    }


    /*
    overloaded operator <<
    */
    std::ostream& operator<<(std::ostream& os, const JsonToken& ob){
        os << "\n\nJSON Content is:\n\n" << "{\n";
        
        for(auto itr = ob.JSONobject.begin(); itr != ob.JSONobject.end(); itr++){
            os << "\t" << itr->first << " : " << itr->second << ",\n";
        }
        os << "}" << std::endl;

        return os;
    }


    /*
    overloading array subscript operator
    */
    std::string JsonToken::operator[](std::string key){
        for(auto i = JSONobject.begin(); i != JSONobject.end(); i++){
            if(key.compare(i->first) == 0){         //key matched
                return i->second;
            }
        }
        return "Not Found!";
    }





}       //end of namespace json



/*
Todo:
Nested json                                         done
read from a file                                    done
restructure class                                   done
overload << operator for pretty printing            done
subscript operator overloading                      done
array as a json object literal                      done
debugger                                            done
minify                                              done
last blank line                                     done

refactor

json object, nested array inside array              done
array in json (json object w/o key)
{} is also a valid json                             done


handle "my name is bob" string type key/value during tokenization (spaces are getting removed)
strings without "" and uneven " are also getting tokenised
subscript operator only works on level 1 and not inside because we stored values as string
*/