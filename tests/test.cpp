#include "json.h"
#include <gtest/gtest.h>

using namespace std;

TEST(JSON_test, input1)
{
    JSON jsonObj;
    std::fstream file;
    file.open("../testcase/input1.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.tokenize();
    ASSERT_TRUE(jsonObj.validSyntax());
}

TEST(JSON_test, input2)
{
    JSON jsonObj;
    std::fstream file;
    file.open("../testcase/input2.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.tokenize();
    ASSERT_FALSE(jsonObj.validSyntax());
}

TEST(JSON_test, input3)
{
    JSON jsonObj;
    std::fstream file;
    file.open("../testcase/input3.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.tokenize();
    ASSERT_TRUE(jsonObj.validSyntax());
}

TEST(JSON_test, input4)
{
    JSON jsonObj;
    std::fstream file;
    file.open("../testcase/input4.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.tokenize();
    ASSERT_TRUE(jsonObj.validSyntax());
}

TEST(JSON_test, input5)
{
    JSON jsonObj;
    std::fstream file;
    file.open("../testcase/input5.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.tokenize();
    ASSERT_TRUE(jsonObj.validSyntax());
}

TEST(JSON_test, input6)
{
    JSON jsonObj;
    std::fstream file;
    file.open("../testcase/input6.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.tokenize();
    ASSERT_TRUE(jsonObj.validSyntax());
}

TEST(JSON_test, input7)
{
    JSON jsonObj;
    std::fstream file;
    file.open("../testcase/input7.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.tokenize();
    ASSERT_FALSE(jsonObj.validSyntax());
}

TEST(JSON_test, input8)
{
    JSON jsonObj;
    std::fstream file;
    file.open("../testcase/input8.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.tokenize();
    ASSERT_TRUE(jsonObj.validSyntax());
}

TEST(JSON_test, input9)
{
    JSON jsonObj;
    std::fstream file;
    file.open("../testcase/input9.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.tokenize();
    ASSERT_TRUE(jsonObj.validSyntax());
}

TEST(JSON_test, input10)
{
    JSON jsonObj;
    std::fstream file;
    file.open("../testcase/input10.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.tokenize();
    ASSERT_TRUE(jsonObj.validSyntax());
}

TEST(JSON_test, input11)
{
    JSON jsonObj;
    std::fstream file;
    file.open("../testcase/input11.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.tokenize();
    ASSERT_TRUE(jsonObj.validSyntax());
}

TEST(JSON_test, input12)
{
    JSON jsonObj;
    std::fstream file;
    file.open("../testcase/input12.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.tokenize();
    ASSERT_TRUE(jsonObj.validSyntax());
}

TEST(JSON_test, input13)
{
    JSON jsonObj;
    std::fstream file;
    file.open("../testcase/input13.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.tokenize();
    ASSERT_TRUE(jsonObj.validSyntax());
}

TEST(JSON_test, input14)
{
    JSON jsonObj;
    std::fstream file;
    file.open("../testcase/input14.json", std::ios::in);
    jsonObj.read(file);
    jsonObj.tokenize();
    ASSERT_TRUE(jsonObj.validSyntax());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
