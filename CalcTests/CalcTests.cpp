#include <iostream>
#include <sstream>
#include <cmath>
#include <stack>

#include "pch.h"
#include "CppUnitTest.h"
#include "../KursovayaCalc/KursovayaCalc.cpp"
#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestCalc
{
    TEST_CLASS(UnitTestCalc)
    {
    public:
        TEST_METHOD(Plus_minus_test)
        {
            std::string str = "5-(5-4)";
            double expected = 4;
            double res = calculate(str);
            Assert::AreEqual(expected, res);
        }
        TEST_METHOD(Devide_tests)
        {
            std::string str = "1/8";
            double expected = 0.125;
            double res = calculate(str);
            Assert::AreEqual(expected, res);
        }
        TEST_METHOD(Multiply_test)
        {
            std::string str = "5*2";
            double expected = 10;
            double res = calculate(str);
            Assert::AreEqual(expected, res);
        }
        TEST_METHOD(Breckets_test)
        {
            std::string str = "5*(1-6)";
            double expected = -25;
            double res = calculate(str);
            Assert::AreEqual(expected, res);
        }
    };
}
