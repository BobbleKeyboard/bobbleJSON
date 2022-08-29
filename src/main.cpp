#include "json.hpp"



int main(){
    //std::string in = "{\n\t\"pi\": \"3.141\",\n\t\"happy\": \"2345\"\n}";
    

    json::JsonToken obj;
    std::ifstream myfile("../files/test10.json");
    obj.read(myfile);
    
    //obj.json_string = in;               //stores input string in json_string

    obj.parseJSON();

    std::cout << obj;

    // std::cout << "\nUsing subscript overloading:\n";
    // std::cout << "obj[\"color\"] : " << obj["color"] << std::endl;
    // std::cout << "obj[\"korean\"] : " << obj["korean"] << std::endl;
    // std::cout << "obj[\"greetings\"] : " << obj["greetings"] << std::endl;
    
    
    return 0;

}