#include "json.hpp"

#include <iostream>

int main(){
    std::string in;
    //example input considering key as string & values as either string or json object.
    in = "{\n\t\"pi\": \"3.141\",\n\t\"happy\": \"true\"\n, \"a\"}";

    std::cout << in << std::endl;                    //using this line to print string in as it is
    
    //Call parse function and store the json object in a variable
    //Call print function

    json::JsonToken obj;
    obj.json_string = in;               //stores input string in json_string

    obj.inputTokens = obj.tokenize(obj.json_string);            //stores claculated tokens in inputTokens
    
    
    if(obj.isValidJSON(obj.inputTokens)){                      //checking validity of JSON
        std::cout << "JSON is valid" << std::endl;
    }
    else{
        std::cout << "JSON is invalid" << std::endl;
    }
    
    return 0;


}