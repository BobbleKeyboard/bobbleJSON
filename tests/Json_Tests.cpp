#include "jsonProject.hpp"

#include "gtest/gtest.h"

using namespace std;

//TEST(JSON_test, input1)
//{
//    JSON jsonObj;
//    std::ifstream file;
//    file.open("../test_case_demo/input1.json", std::ios::in);
//    jsonObj.read(file);
//    jsonObj.parseJSON();
//    ASSERT_TRUE(jsonObj.isValidJSON());
//}

TEST(JSON_test, input2)
{
    JSON jsonObj;
    std::ifstream file;
    file.open("../test_cases/input2.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.parseJSON();
    ASSERT_TRUE(jsonObj.isValidJSON());
}

TEST(JSON_test, input3)
{
    JSON jsonObj;
    std::ifstream file;
    file.open("../test_cases/input3.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.parseJSON();
    ASSERT_TRUE(jsonObj.isValidJSON());
}

TEST(JSON_test, input4)
{
    JSON jsonObj;
    std::ifstream file;
    file.open("../test_cases/input4.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.parseJSON();
ASSERT_TRUE(jsonObj.isValidJSON());
}

TEST(JSON_test, input5)
{
    JSON jsonObj;
    std::ifstream file;
    file.open("../test_cases/input5.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.parseJSON();
    ASSERT_TRUE(jsonObj.isValidJSON());
}

TEST(JSON_test, input6)
{
    JSON jsonObj;
    std::ifstream file;
    file.open("../test_cases/input6.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.parseJSON();
    ASSERT_TRUE(jsonObj.isValidJSON());
}

TEST(JSON_test, input7)
{
    JSON jsonObj;
    std::ifstream file;
    file.open("../test_cases/input7.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.parseJSON();
    std::cout<<jsonObj["Address"];
    ASSERT_TRUE(jsonObj.isValidJSON());
}

TEST(JSON_test, input8)
{
    JSON jsonObj;
    std::ifstream file;
    file.open("../test_cases/input8.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.parseJSON();
    ASSERT_TRUE(jsonObj.isValidJSON());
}

TEST(JSON_test, input9)
{
    JSON jsonObj;
    std::ifstream file;
    file.open("../test_cases/input9.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.parseJSON();
    ASSERT_FALSE(jsonObj.isValidJSON());
}

TEST(JSON_test, input10)
{
    JSON jsonObj;
    std::ifstream file;
    file.open("../test_cases/input10.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.parseJSON();
    ASSERT_FALSE(jsonObj.isValidJSON());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}