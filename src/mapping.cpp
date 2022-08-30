#include<iostream>

class JSON_Value{
private:
    bool isNumber()
    {
        int count_digit = 0, count_decimals = 0;
        for (int i = 0; i < value.length(); i++)
        {
            if (isdigit(value[i]))
                count_digit++;
            else if (value[i] == '.')
                count_decimals++;
        }
        return (count_digit + count_decimals) == value.length() && count_decimals <= 1;
    }

    bool isBool()
    {
        return value == "true" || value == "false";
    }

    bool isNull()
    {
        return value == "NULL";
    }

    bool isJSON()
    {
        return value[0] == '{' && value[value.length() - 1] == '}';
    }

    bool isArray()
    {
        return value[0] == '[' && value[value.length() - 1] == ']';
    }

public:
    std::string value;
    std::string type;

    JSON_Value(std::string value){
        this -> value = value;
        getType();
        //store in map
    }

    void getType()
    {
        if (isNull())
            this -> type = "NULL";
        else if (isBool())
            this -> type = "BOOL";
        else if (isNumber())
            this -> type = "NUMBER";
        else if (isJSON())
            this -> type = "JSON";
        else if (isArray())
            this -> type = "ARRAY";
        else
            this -> type = "STRING";
    }
};