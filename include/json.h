#ifndef JSON_H
#define JSON_H

#include <optional>
#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <unordered_map>

struct valueType
{
	const std::string Null = "Null";
	const std::string STRING = "String";
	const std::string NUMBER = "Number";
	const std::string BOOL = "Boolean";
	const std::string OPENING_CURLY_BRACE = "OpenCurlyBrace";
	const std::string CLOSING_CURLY_BRACE = "CloseCurlyBrace";
    const std::string OPENING_BOX_BRACE = "OpenBoxBrace";
    const std::string CLOSING_BOX_BRACE = "CloseBoxBrace";
	const std::string COMMA = "Comma";
	const std::string COLON = "Colon";
    const std::string INVALID = "InvalidToken";
};

class JSON
{
private:
    std::vector<char> terminatingChars{'{', '}', '[', ']', ':', ','};
    std::vector<char> escapeChars{' ', '\t', '\n'};
    std::string inputString;
    std::unordered_map<std::string, std::string> kv_pair; //std::unordered_map<std::string, std::pair<std::string, std::string>> kv_pair;
    std::string error = "Key not Found";


    bool isNull(std::string);
    std::string checkValueType(std::string);
    bool checkTerminate(char, std::vector<char>);
    bool isNumber(std::string str);
    bool isBool(std::string str);
    bool isString(std::string str);
    bool checkEscape(char, std::vector<char>);

public:
    std::vector<std::pair<std::string, std::string>> input_JSON_Tokens; // pair stands for {token, tokenType}
    friend std::ostream& operator <<(std::ostream&, const JSON&);

    //fxn return TYPE of token using input_JSON_Tokens

    JSON()
    {
        this->inputString = "";
    }

    JSON(std::string input_JSON_String)
    {
        this->inputString = input_JSON_String;
    }

    // all methods
    bool tokenize();
    void read(std::string);
    void read(std::fstream &);
    void parseJSON();
    bool validSyntax();

    std::string& operator [](std::string key){
        //now we will get a string value now we should check
        //exceptional handled!!
        try{
            std::string key_token = '"' + key + '"';
            //std::cout << key_token;
            return kv_pair.at(key_token);
        }
        catch (std::exception out_of_range){
            return error;
        }
    }
};

#endif