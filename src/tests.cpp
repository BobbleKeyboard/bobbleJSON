#include "json.hpp"
#include "gtest/gtest.h"

using namespace std;



    TEST(JSON_test, input0)
    {
        json::JsonToken jsonObj;
        std::ifstream file;
        file.open("../tests/input0.json", std::ios::in);
        jsonObj.read(file);
        jsonObj.parseJSON();
        ASSERT_TRUE(jsonObj.isValidJSON());
    }

    TEST(JSON_test, input1)
    {
        json::JsonToken jsonObj;
        std::ifstream file;
        file.open("../tests/input1.json", std::ios::in);
        jsonObj.read(file);
        jsonObj.parseJSON();
        ASSERT_TRUE(jsonObj.isValidJSON());
    }

    TEST(JSON_test, input2)
    {
        json::JsonToken jsonObj;
        std::ifstream file;
        file.open("../tests/input2.json", std::ios::in);
        jsonObj.read(file);
        jsonObj.parseJSON();
        ASSERT_FALSE(jsonObj.isValidJSON());
    }

    TEST(JSON_test, input3)
    {
        json::JsonToken jsonObj;
        std::ifstream file;
        file.open("../tests/input3.json", std::ios::in);
        jsonObj.read(file);
        jsonObj.parseJSON();
        ASSERT_TRUE(jsonObj.isValidJSON());
    }

    TEST(JSON_test, input4)
    {
        json::JsonToken jsonObj;
        std::ifstream file;
        file.open("../tests/input4.json", std::ios::in);
        jsonObj.read(file);
        jsonObj.parseJSON();
        ASSERT_FALSE(jsonObj.isValidJSON());
    }

    TEST(JSON_test, input5)
    {
        json::JsonToken jsonObj;
        std::ifstream file;
        file.open("../tests/input5.json", std::ios::in);
        jsonObj.read(file);
        jsonObj.parseJSON();
        ASSERT_TRUE(jsonObj.isValidJSON());
    }

    TEST(JSON_test, input6)
    {
        json::JsonToken jsonObj;
        std::ifstream file;
        file.open("../tests/input6.json", std::ios::in);
        jsonObj.read(file);
        jsonObj.parseJSON();
        ASSERT_TRUE(jsonObj.isValidJSON());
    }

    TEST(JSON_test, input7)
    {
        json::JsonToken jsonObj;
        std::ifstream file;
        file.open("../tests/input7.json", std::ios::in);
        jsonObj.read(file);
        jsonObj.parseJSON();
        ASSERT_TRUE(jsonObj.isValidJSON());
    }

    TEST(JSON_test, input8)
    {
        json::JsonToken jsonObj;
        std::ifstream file;
        file.open("../tests/input8.json", std::ios::in);
        jsonObj.read(file);
        jsonObj.parseJSON();
        ASSERT_TRUE(jsonObj.isValidJSON());
    }

    TEST(JSON_test, input9)
    {
        json::JsonToken jsonObj;
        std::ifstream file;
        file.open("../tests/input9.json", std::ios::in);
        jsonObj.read(file);
        jsonObj.parseJSON();
        ASSERT_TRUE(jsonObj.isValidJSON());
    }

    TEST(JSON_test, input10)
    {
        json::JsonToken jsonObj;
        std::ifstream file;
        file.open("../tests/input10.json", std::ios::in);
        jsonObj.read(file);
        jsonObj.parseJSON();
        ASSERT_TRUE(jsonObj.isValidJSON());
    }

    TEST(JSON_test, input11)
    {
        json::JsonToken jsonObj;
        std::ifstream file;
        file.open("../tests/input11.json", std::ios::in);
        jsonObj.read(file);
        jsonObj.parseJSON();
        ASSERT_TRUE(jsonObj.isValidJSON());
    }

    TEST(JSON_test, input12)
    {
        json::JsonToken jsonObj;
        std::ifstream file;
        file.open("../tests/input12.json", std::ios::in);
        jsonObj.read(file);
        jsonObj.parseJSON();
        ASSERT_TRUE(jsonObj.isValidJSON());
    }

    TEST(JSON_test, input13)
    {
        json::JsonToken jsonObj;
        std::ifstream file;
        file.open("../tests/input13.json", std::ios::in);
        jsonObj.read(file);
        jsonObj.parseJSON();
        ASSERT_TRUE(jsonObj.isValidJSON());
    }

    TEST(JSON_test, input14)
    {
        json::JsonToken jsonObj;
        std::ifstream file;
        file.open("../tests/input14.json", std::ios::in);
        jsonObj.read(file);
        jsonObj.parseJSON();
        ASSERT_TRUE(jsonObj.isValidJSON());
    }

    int main(int argc, char** argv)
    {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }

