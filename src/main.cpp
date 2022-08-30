#include<iostream>
#include<string>
#include "jsonProject.hpp"

int main(){

    //creating a JSON class Obj -> inputJsonObjFile
    JSON inputJsonObjFile;//this will read through the file

    //creating a JSON class Obj -> inputJsonObj
//    JSON inputJsonObj;


    //now by I am reading the file
    std::ifstream jsonFile;
    jsonFile.open("../test_cases/input2.json",std::ios::in);
    inputJsonObjFile.read(jsonFile);

    //now we are reading by string
    // inputJsonObj.read("{\n\t\"Name\":\"Surya\",\"Age\":\"NULL\",\"Address\":{\"Pin code\":\"532459\",\"Country\":\"Indian\"},\"Group\":\"CSE\"}");

    //here i am parsing for jsonFile
    inputJsonObjFile.parseJSON();

    //displaying the content using extraction operator
     std::cout << inputJsonObjFile;
     //Using Sub script operator
     std::cout<<"\n\nUsing SubScript Operator:\n------------------"<<std::endl;
     std::cout<<"xyz :"<<inputJsonObjFile["xyz"]<<std::endl;
     std::cout<<"def :"<<inputJsonObjFile["def"];


    return 0;
}
