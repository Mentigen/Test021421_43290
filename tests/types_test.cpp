#include <lib/interpreter.h>
#include <gtest/gtest.h>


TEST(TypesTestSuite, IntTest) {
    std::string code = R"(
        x = 1
        y = 2
        z = 3 * x + y
        print(z)
    )";

    std::string expected = "5";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(TypesTestSuite, StringTest) {
    std::string code = R"(
        s1 = "Hello"
        s2 = "World"
        s3 = s1 + " " + s2
        print(s3)
    )";

    std::string expected = "Hello World";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(TypesTestSuite, ListTest) {
    std::string code = R"(
        lst = [1, 2, 3, 4, 5]
        sum = 0
        for i in lst
            sum = sum + i
        end for
        print(sum)
    )";

    std::string expected = "15";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(TypesTestSuite, FunctionTest) {
    std::string code = R"(
        add = function(a, b)
            return a + b
        end function

        result = add(2, 3)
        print(result)
    )";

    std::string expected = "5";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}

TEST(TypesTestSuite, NilTest) {
    std::string code = R"(
        x = nil
        if x == nil then
            print("nil")
        else
            print("not nil")
        end if
    )";

    std::string expected = "nil";

    std::istringstream input(code);
    std::ostringstream output;

    ASSERT_TRUE(interpret(input, output));
    ASSERT_EQ(output.str(), expected);
}
