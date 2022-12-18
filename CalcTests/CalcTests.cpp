#include <iostream>
#include <sstream>
#include <cmath>
#include <stack>

#include "pch.h"
#include "CppUnitTest.h"
#include "../KursovayaCalc/KursovayaCalc.cpp"
#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_METHOD(TestMethod1)
        {
            std::string str = "5-(5-4)";
            double expected = 4;
            double res = calculate(str);
            Assert::AreEqual(expected, res);
        }
        TEST_METHOD(TestMethod4)
        {
            std::string str = "1/8";
            double expected = 0.125;
            double res = calculate(str);
            Assert::AreEqual(expected, res);
        }
        TEST_METHOD(TestMethod6)
        {
            std::string str = "4^(1/2)";
            double expected = 2;
            double res = calculate(str);
            Assert::AreEqual(expected, res);
        }
    };
}
