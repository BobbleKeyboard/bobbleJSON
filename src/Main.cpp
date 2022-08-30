#include "json.h"
#include <iostream>

using namespace std;

int main()
{
    //JSON jsonObj("{\n\t\"xyz\":\"10.9\",\n\t\"happy\": \"{""xyz\":\"123\"}\"}");
    JSON jsonObj;
    //jsonObj.read("{\n\t\"xyz\":\"10.9\",\n\t\"happy\": \"{""xyz\":\"123\"}\"}");
    std::fstream file;
    file.open("../testcase/input13.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.parseJSON();
    std::cout << jsonObj << endl;
    std::cout << jsonObj["quiz"] << std::endl;
    return 0;
}