//.hpp file
#include "json.h"

valueType valueObj;

void JSON::read(std::fstream &file)
{
	char ch;
	if (file.is_open())
	{
		while (file >> std::noskipws >> ch)
        {
            inputString += ch;
		}
        //std::cout << inputString << std::endl;
	}
    //string seperated by space can create problem
	else
	{
		std::cout << "File cannot open." << std::endl;
	}
}

void JSON::read(std::string in)
{
	inputString = in;
}

bool JSON::tokenize()
{
    std::string tokenValue;
    for (int i = 0; i < inputString.length(); i++)
    {
        // check current char is terminating value or not !
        bool check = checkTerminate(inputString[i], terminatingChars);
        if (check)
        {
            if (!tokenValue.empty())
            {
                std::string tokenType = checkValueType(tokenValue);	  // check the TYPE of token
                if(tokenType == valueObj.INVALID)
                {
                    std::cout << "Invalid Token  : " << tokenValue << std::endl;
                    return false;
                }
                //std::cout << tokenValue << std::endl;
                input_JSON_Tokens.push_back({tokenValue, tokenType}); // store the token along with its TYPE
                tokenValue.clear();
            }
            std::string terminate_char(1, inputString[i]);
            if (!terminate_char.empty())
            {
                if (terminate_char == "{")
                    input_JSON_Tokens.push_back({terminate_char, valueObj.OPENING_CURLY_BRACE});
                else if (terminate_char == "}")
                    input_JSON_Tokens.push_back({terminate_char, valueObj.CLOSING_CURLY_BRACE});
                else if (terminate_char == "[")
                    input_JSON_Tokens.push_back({terminate_char, valueObj.OPENING_BOX_BRACE});
                else if (terminate_char == "]")
                    input_JSON_Tokens.push_back({terminate_char, valueObj.CLOSING_BOX_BRACE});
                else if (terminate_char == ",")
                    input_JSON_Tokens.push_back({terminate_char, valueObj.COMMA});
                else
                    input_JSON_Tokens.push_back({terminate_char, valueObj.COLON});
            }
            else
            {
                continue;
            }
        }
        else
        {
            if(inputString[i] == '"')
            {
                tokenValue += inputString[i];
                i++;
                while(i < inputString.length() && inputString[i] != '"')
                {
                    tokenValue += inputString[i];
                    i++;
                }
                tokenValue += inputString[i];
                //std::cout << tokenValue << std::endl;
                std::string tokenType = checkValueType(tokenValue);	  // check the TYPE of token
                if(tokenType == valueObj.INVALID)
                {
                    //std::cout << "Invalid Token  : " << tokenValue << std::endl;
                    return false;
                }
                //std::cout << tokenValue << std::endl;
                input_JSON_Tokens.push_back({tokenValue, tokenType}); // store the token along with its TYPE
                tokenValue.clear();
                continue;
            }
            check = checkEscape(inputString[i], escapeChars);
            if (check) {
                if (!tokenValue.empty())
                {
                    std::string tokenType = checkValueType(tokenValue);	  // check the TYPE of token
                    if(tokenType == valueObj.INVALID)
                    {
                        //std::cout << "Invalid Token  : " << tokenValue << std::endl;
                        return false;
                    }
                    input_JSON_Tokens.push_back({tokenValue, tokenType}); // store the token along with its TYPE
                    tokenValue.clear();
                }
                continue;
            }
            tokenValue += inputString[i];
        }
    }
    if(!tokenValue.empty())
    {
        std::string tokenType = checkValueType(tokenValue);	  // check the TYPE of token
        if(tokenType == valueObj.INVALID)
        {
            //std::cout << "Invalid Token  : " << tokenValue << std::endl;
            return false;
        }
        input_JSON_Tokens.push_back({tokenValue, tokenType}); // store the token along with its TYPE
        tokenValue.clear();
    }
    return true;
};

void JSON::parseJSON() {
    //we will use map structure
    if(!JSON::tokenize())
    {
        std::cout << "Invalid JSON Token Found";
        exit(0);
    }

    if(JSON::validSyntax()) {
        std::cout << "Valid JSON" << std::endl;
//        auto itr = input_JSON_Tokens.begin() + 1;
//        //std::cout << itr -> first << std::endl;
//        bool jsonObj_value = false;
//        while (itr != input_JSON_Tokens.end()) {
//            std::string key;
//            key = itr -> first;
//            //std::cout << key << "\t";
//            itr++;
//            itr++;
//            if (itr -> second == valueObj.OPENING_CURLY_BRACE) {
//                itr++;
//                std::string json_value_obj;
//                while (itr -> second != valueObj.CLOSING_CURLY_BRACE) {
//                    json_value_obj += itr -> first;
//                    json_value_obj += " ";
//                    itr++;
//                }
//                itr++;
//                itr++;
//                auto temp = itr;
//                if ((++temp)->second == valueObj.CLOSING_CURLY_BRACE) {
//                    itr++;
//                }
//                kv_pair[key] = json_value_obj;
//                //test json_value_obj is JSON object
//                continue;
//            }
//
//            std::string value = itr -> first;
//            //std::cout<<"Value :"<< value <<std::endl;
//            itr++;
//            itr++;
//            kv_pair[key] = value;
//        }
//        std::stack<char> stack;
//        std::cout << "VALID JSON:!!!" << std::endl;
//        auto itr = input_JSON_Tokens.begin() + 1;
//        //std::string inside_key;
//        bool jsonObj_value = false;
//        while (itr != input_JSON_Tokens.end()) {
//            std::string key = itr->first;
//            ++itr;
//            ++itr;
//            if(itr->second == valueObj.OPENING_CURLY_BRACE) {
//                std::string json_value_obj;
//                stack.push('{');
//                json_value_obj+='{';
//                ++itr;
//                std::string inside_key;
//                std::string inside_value;
//                while(!stack.empty()){
//                    if(itr->second == valueObj.OPENING_CURLY_BRACE){
//                        //inside_key = (itr+1)->first;
//                        stack.push('{');
//                    }
//                    else if(itr->second == valueObj.OPENING_BOX_BRACE){
//                        //inside_key=(itr-1)->first;
//                        stack.push('[');
//                    }
//                    else if(itr->second == valueObj.CLOSING_CURLY_BRACE|| itr->second == valueObj.CLOSING_BOX_BRACE){
//                        stack.pop();
//                        //  jsonObject[inside_key] = inside_value;
//                    }
//                    json_value_obj += itr->first;
//                    // inside_value += itr->first;
//                    itr++;
//                }
//                ++itr;
//                kv_pair[key] = json_value_obj;
//                continue;
//            }
//            std::string value = itr->first;
//            //std::cout<<"Value :"<<itr->first<<std::endl;
//            ++itr;
//            ++itr;
//            kv_pair[key] = value;
//        }
    }else{
        std::cout<<"INVALID JSON INPUT"<<std::endl;
        exit(0);
    }
}

bool JSON::checkTerminate(char current_char, std::vector<char> terminatingChars)
{
	for (auto it = terminatingChars.begin(); it != terminatingChars.end(); it++)
	{
		if ((*it) == current_char)
		{
			return true;
		}
	}
	return false;
};

bool JSON::checkEscape(char current_char, std::vector<char> escapeChars)
{
	for(auto it = escapeChars.begin(); it != escapeChars.end(); it++)
	{
		if ((*it) == current_char)
		{
			return true;
		}
	}
	return false;
};

bool JSON::validSyntax()
{
	if (input_JSON_Tokens.size() == 0)
		return true;
	else if (input_JSON_Tokens.size() == 1) // JSON of size 1 is not possible
		return false;
	else
	{
		auto itr = input_JSON_Tokens.begin();
		if (itr->second != valueObj.OPENING_CURLY_BRACE && itr->second != valueObj.OPENING_BOX_BRACE) // First token has to be an Opening Brace
        {
            //std::cout << "Begining" << std::endl;
            return false;
        }
        if ((input_JSON_Tokens.end() - 1) -> second != valueObj.CLOSING_CURLY_BRACE && (input_JSON_Tokens.end() - 1) -> second != valueObj.CLOSING_BOX_BRACE) // Last token has to be a Closing Brace
        {
            //std::cout << "Ending" << std::endl;
            return false;
        }

		std::stack<char> stk;
		while (itr != input_JSON_Tokens.end())
		{
			if (itr->second == valueObj.OPENING_CURLY_BRACE)
            {
				stk.push('{');
				if ((itr + 1) != input_JSON_Tokens.end() && (itr + 1)->second != valueObj.STRING && (itr + 1)->second != valueObj.CLOSING_CURLY_BRACE)
				{
                    if(!((itr + 1)->second != valueObj.OPENING_BOX_BRACE && itr->second != valueObj.OPENING_CURLY_BRACE))
                    {
                        //std::cout << "Opening" << std::endl;
                        return false;
                    }
				}
				itr++;
			}
			else if (itr->second == valueObj.COLON)
			{
				if ((itr + 1) != input_JSON_Tokens.end() && (itr + 1)->second == valueObj.OPENING_CURLY_BRACE || (itr + 1)->second == valueObj.OPENING_BOX_BRACE)
				{
					itr++;
					continue;
				}
				else if ((itr + 1) != input_JSON_Tokens.end() && (itr + 1)->second != valueObj.BOOL && (itr + 1)->second != valueObj.Null && (itr + 1)->second != valueObj.NUMBER && (itr + 1)->second != valueObj.STRING)
				{
					//std::cout << "Colon" << std::endl;
					return false;
				}
				itr++;
			}
			else if (itr->second == valueObj.COMMA)
			{
				if ((itr + 1) != input_JSON_Tokens.end() && (itr + 1)->second != valueObj.STRING)
                {
					if(!(((itr + 1)->second == valueObj.OPENING_CURLY_BRACE && stk.top() == '[')
                        || ((itr + 1)->second == valueObj.OPENING_BOX_BRACE && stk.top() == '[')))
                    {
                        //std::cout << "Comma" << std::endl;
                        return false;
                    }
				}
				itr++;
			}
			else if (itr->second == valueObj.CLOSING_CURLY_BRACE)
			{
				if(stk.empty() || stk.top() == '[')
                {
                    //std::cout << "Closing }" << std::endl;
                    return false;
                }
                stk.pop();
				itr++;
			}
            else if(itr->second == valueObj.OPENING_BOX_BRACE)
            {
                stk.push('[');
                itr++;
                bool skip = false;
                while(itr != input_JSON_Tokens.end() && (itr->second != valueObj.OPENING_CURLY_BRACE || itr->second != valueObj.OPENING_BOX_BRACE))
                {
                    if((itr + 1) != input_JSON_Tokens.end()
                        && (itr->second == valueObj.STRING || itr->second == valueObj.NUMBER || itr->second == valueObj.Null || itr->second == valueObj.BOOL)
                        && ((itr + 1)->second == valueObj.STRING || (itr + 1)->second == valueObj.NUMBER || (itr + 1)->second == valueObj.Null || (itr + 1)->second == valueObj.BOOL || (itr + 1)->second == valueObj.COLON))
                    {
                        //std::cout << "Array S:S" << std::endl;
                        return false;
                    }
                    else if((itr + 1) != input_JSON_Tokens.end()
                        && (itr->second == valueObj.COMMA || itr->second == valueObj.COLON)
                        && ((itr + 1)->second == valueObj.COMMA || (itr + 1)->second == valueObj.COLON || (itr + 1)->second == valueObj.CLOSING_CURLY_BRACE || (itr + 1)->second == valueObj.CLOSING_BOX_BRACE))
                    {
                        //std::cout << "Array C:C" << std::endl;
                        return false;
                    }
                    else if(itr->second == valueObj.OPENING_CURLY_BRACE || itr->second == valueObj.OPENING_BOX_BRACE || itr->second == valueObj.CLOSING_CURLY_BRACE || itr->second == valueObj.CLOSING_BOX_BRACE)
                    {
                        skip = true;
                        break;
                    }
                    itr++;
                }
                if(skip == true)
                {
                    continue;
                }
            }
            else if(itr->second == valueObj.CLOSING_BOX_BRACE)
            {
                if(stk.empty() || stk.top() == '{')
                {
                    //std::cout << "Closing ]" << std::endl;
                    return false;
                }
                stk.pop();
                itr++;
            }
			else
			{
				// In this case we have either encountered a KEY or a VALUE
				if ((itr + 1) != input_JSON_Tokens.end()
                    && ((itr + 1)->second == valueObj.BOOL || (itr + 1)->second == valueObj.Null || (itr + 1)->second == valueObj.NUMBER || (itr + 1)->second == valueObj.STRING))
				{
					//std::cout << "KV" << std::endl;
					return false;
				}
				else if (!(((itr + 1)->second == valueObj.COLON
                    && ((itr - 1)->second == valueObj.OPENING_CURLY_BRACE || (itr - 1)->second == valueObj.COMMA))
                    || ((itr - 1)->second == valueObj.COLON && ((itr + 1)->second == valueObj.CLOSING_CURLY_BRACE || (itr + 1)->second == valueObj.COMMA))))
				{
					//std::cout << itr->first << " KV" << std::endl;
					return false;
				}
				itr++;
			}
            if(stk.empty() && itr != input_JSON_Tokens.end())
            {
                //std::cout << "STK" << std::endl;
                return false;
            }
		}
        //if(!stk.empty()) std::cout << "Stack" << std::endl;
		return stk.empty();
	}
};

bool JSON::isNull(std::string str)
{
	return str == "NULL";
}

bool JSON::isBool(std::string str)
{
	return str == "true" || str == "false";
}

bool JSON::isString(std::string str)
{
    if(str.length() <= 1)
        return false;
    return str[0] == '"' && str[str.length() - 1] == '"';
}

bool JSON::isNumber(std::string str)
{
	int count_digit = 0, count_decimals = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (isdigit(str[i]))
			count_digit++;
		else if (str[i] == '.')
			count_decimals++;
	}
	return (count_digit + count_decimals) == str.length() && count_decimals <= 1;
}

std::string JSON::checkValueType(std::string str)
{
	if (isNull(str))
		return valueObj.Null;
	else if (isBool(str))
		return valueObj.BOOL;
	else if (isNumber(str))
		return valueObj.NUMBER;
	else if(isString(str))
		return valueObj.STRING;
    else
        return valueObj.INVALID;
}

std::ostream& operator <<(std::ostream& os, const JSON& obj)
{
    //now here we need store everything in os
    bool flag = false;
    os << "JSON RAW DATA : ";
    os << std::endl;
    os << "-------------\n";
    auto it= obj.input_JSON_Tokens.begin();
    if(it != obj.input_JSON_Tokens.end()){
        os << (it -> first) << "\n \t\t";
        it++;
    }
    while(it != obj.input_JSON_Tokens.end()){
        if(it -> first == "{"){
            flag = true;
            os << (it -> first) << "\n \t\t\t\t";
        }
        else if(it -> first == "," && flag)
        {
            os << (it -> first) << "\n \t\t\t\t";
        }
        else if(it -> first == ",")
        {
            os << (it -> first)<<"\n \t\t";
        }
        else if(it -> first == "}" && flag)
        {
            os << "\n\t\t\t\t" << (it->first);
        }
        else if(it -> first == "}")
        {
            os << "\n" << (it->first);
        }
        else
        {
            os << (it->first) << " ";
        }
        if(it -> first == "}"){
            flag = false;
        }
        it++;
        // checkType(it->second);
    }
    os << std::endl;
    return os;
}