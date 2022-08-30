#ifndef DAD7EA70_78F3_411F_8339_64F4047AEFD1
#define DAD7EA70_78F3_411F_8339_64F4047AEFD1

#include<string>
#include<iostream>
#include<vector>
#include<map>
#include<sstream>
#include<stack>
#include<fstream>
#include<unordered_map>

enum class TokenType{
      OPENING_BRACE_TOKEN,
      CLOSING_BRACE_TOKEN,
      STRING_TOKEN,
      INTEGER_TOKEN,
      FLOAT_TOKEN,
      COMMA_TOKEN,
      COLON_TOKEN,
      TRUE_TOKEN,
      FALSE_TOKEN,
      ARRAY_TOKEN,
      OPENING_SQUARE_TOKEN,
      CLOSING_SQUARE_TOKEN,
      NULL_TOKEN,
      DEFAULT_VALUE
};

class JSON_Value{
private:
    //here we store which token type
    TokenType value_type;
    //here we store the key value
    std::string string_value;



public:

    // actual_obj;
    JSON_Value(){
        value_type = TokenType::DEFAULT_VALUE;
        string_value = " ";
    }
    JSON_Value(TokenType type,std::string value){
        value_type = type;
        string_value = value;
    }

    TokenType getType() {
        return value_type;
    }

    std::string toString() {
        return string_value;
    }

};


class JSON:public JSON_Value{
private:
    std::string input_JSON_String;
    //here we are storing {string,TokenType}
    std::vector<std::pair<std::string,TokenType>> input_JSON_Tokens;
    //here we will combine the string value with TokenType
    std::vector<std::pair<char,TokenType>> terminatingChars{
            {'{',TokenType::OPENING_BRACE_TOKEN},
            {'}',TokenType::CLOSING_BRACE_TOKEN},
            {'[',TokenType::OPENING_SQUARE_TOKEN},
            {']',TokenType::CLOSING_SQUARE_TOKEN},
            {':',TokenType::COLON_TOKEN},
            {',',TokenType::COMMA_TOKEN}
    };
    //here we are not required any TokenType because here we are escaping so not required!

    std::vector<char> escapeChars{' ','\t','\n'};

    std::vector<TokenType> json_Obj_State{
            TokenType::OPENING_BRACE_TOKEN,
            TokenType::STRING_TOKEN,//here it should be always a String (Key)
            TokenType::COLON_TOKEN,
            TokenType::STRING_TOKEN,//here it may be String or Number or Boolean or Null (Value)
            TokenType::INTEGER_TOKEN,
            TokenType::FLOAT_TOKEN,
            TokenType::OPENING_BRACE_TOKEN,
            TokenType::OPENING_SQUARE_TOKEN,
            TokenType::TRUE_TOKEN,
            TokenType::FALSE_TOKEN,
            TokenType::NULL_TOKEN,
            TokenType::COMMA_TOKEN,//we are going to upper STRING_TOKEN
            TokenType::CLOSING_BRACE_TOKEN,
    };

    //here in this there will be a continuous order of values[value,value,...]->value may be string , jsonObj , integer, float
    std::vector<TokenType> json_Obj_State_Ordered{
            TokenType::OPENING_SQUARE_TOKEN,
            //this is for json Value
            TokenType::OPENING_BRACE_TOKEN,
            //we should jump to json_Obj_State to second token itr
            //upto here json value
            TokenType::OPENING_SQUARE_TOKEN,
            TokenType::STRING_TOKEN,
            TokenType::INTEGER_TOKEN,
            TokenType::FLOAT_TOKEN,
            TokenType::TRUE_TOKEN,
            TokenType::FALSE_TOKEN,
            TokenType::NULL_TOKEN,
            TokenType::COMMA_TOKEN,//if we are having comma then we will change iterator to string_token
            TokenType::CLOSING_SQUARE_TOKEN
    };

    //using map data structure I am going to its key-value pair in map<string,string> format
    //value class json array bool
    std::unordered_map<std::string,std::string> jsonObject;
    std::unordered_map<std::string,JSON_Value> key_value;

    bool validate_JSON_structure();
    bool validate_Array();
    bool valdiate_Value();
    void checkType(TokenType);
    void displayMap();
    //validation part exceptions
    bool checkEscape(char,std::vector<char>);
    std::pair<bool,TokenType> checkTerminate(char,std::vector<std::pair<char,TokenType>>);
    void Push_Into_Map(bool);
public:
    void doTokenize();
    bool isValidJSON();
    //reading jsonObj from string
    void read(std::string input_JSON_String);
    //reading jsonObj from file
    void read(std::ifstream& jsonFile);

    /*
         doTokenize()->isValidJSON()->if yes then it will parseJSON()
                                    else then it will display error message and exit from that line!
     */

    friend std::ostream& operator<<(std::ostream& os, const JSON& obj);

    //here I am going to do the subscripting overloading concept ->here when I pass the key value i should get its respective value
    //unordered map->std::unordered_map<std::string,std::string> jsonObject;
    std::string operator [](std::string key){
        //now we will get a string value now we should check
        //exceptional handled!!
        std::string json_obj_placeholder("JSON_OBJ");
        std::string json_array_placeholder("JSON_ARRAY");
        try{
            std::string key_string = '"'+key+'"';
             std::string return_val = "";
             JSON_Value val_obj = key_value.at(key_string);
             //get address of val_obj in hexa decimal format and stringfy it and store it in a string variable
             auto val_obj_addr = getHexAddressString(val_obj);
            // ?long int obj_address!!
             auto type = val_obj.getType();
             if(type == TokenType::STRING_TOKEN  || type == TokenType::INTEGER_TOKEN || type == TokenType::NULL_TOKEN || type == TokenType::TRUE_TOKEN || type == TokenType::FALSE_TOKEN || type == TokenType::FLOAT_TOKEN ){
                return_val = val_obj.toString();
             }else if(type == TokenType::OPENING_BRACE_TOKEN){
                  return_val = json_obj_placeholder+"@  "+val_obj_addr;
             }else if(type == TokenType::OPENING_SQUARE_TOKEN){
                return_val = json_array_placeholder+"@  "+val_obj_addr;
             }
             return return_val;
        }
        catch (std::exception out_of_range){
            std::cout<<"ERROR!!!\nWhat you are Searching for a Key Value is :NOT PRESENT:!"<<std::endl;
        }
    }

    std::string getHexAddressString(JSON_Value obj){
        const JSON_Value * address = static_cast<const JSON_Value*>(&obj);
        std::stringstream ss;
        ss << address;
        std::string name = ss.str();
        return name;
    }

//    std::string& operator [](int index){
//
//    }
    void parseJSON();
};




#endif /* DAD7EA70_78F3_411F_8339_64F4047AEFD1 */
