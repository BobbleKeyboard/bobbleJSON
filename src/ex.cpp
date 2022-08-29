enum class TokenType{
    OPENING_BRACE_TOKEN,
    CLOSING_BRACE_TOKEN,
    STRING_TOKEN,
    COMMA_TOKEN,
    COLON_TOKEN,
    OPENING_QUOTE_TOKEN,
    CLOSING_QUOTE_TOKEN,
    NUMBER_TOKEN,
    OPTIONAL_COMMA_TOKEN
}



class JSON{
    public:
        string json_string;
        std::vector<std::string> inputTokens;
        std::vector<TokenType> json_states {TokenType::OPENING_BRACE_TOKEN, TokenType::STRING_TOKEN, TokenType::COLON_TOKEN, TokenType::STRING_TOKEN, TokenType::OPTIONAL_COMMA_TOKEN, TokenType::CLOSING_BRACE_TOKEN}

        //inputTokens ["{", "pi", ":", "3.141"...]

        void read(string);
        void tokenize();       
        bool isValidJson();

        /*
        iterate over the json string character by character
        json_string = "{\n\t\"pi\": \"3.141\",\n\t\"happy\": \"true\"\n}";

        space, comma, colon, opening brace, closing brace => list of string terminating characters => list
        terminating_char = [" "...]
        escape_char = ["/"]

        string token;

        while(auto x : json_string){
            if(x is in terminating_char){
                if(!token.empty()){
                    InputTokens.push_back(token);
                    make token empty
                
                }
                string temp_token = x;

                if(!temp_token.empty())
                    inputTokens.push_back(temp_token);
                else continue;

            }
            else{
                if(x is in escpae_char){
                    continue;
                }
                token += x;
            }
            
        }

        token = pi
        temp_token = 
        x = :
        inputTokens ["{", "pi", ":", "3.141"...]


        
        /* 
};



