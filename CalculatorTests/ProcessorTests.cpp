#include "pch.h"
#include "CppUnitTest.h"
#include "../SWE_App/Processor.h"
#include "wx/wx.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTests
{
	TEST_CLASS(ProcessorTests)
	{
	public:

		TEST_METHOD(SingletonWorking)
		{
			Assert::IsNotNull(Processor::GetInstance());
		}
		TEST_METHOD(ShuntingYardBasicAddition)
		{
			std::string converted = "2 2 +", toConvert = "2+2";
			Assert::AreEqual(converted, Processor::GetInstance()->ConvertToShuntingYard(toConvert));
		}
		TEST_METHOD(ShuntingYardBasicMultiplication)
		{
			std::string converted = "2 2 *", toConvert = "2*2";
			Assert::AreEqual(converted, Processor::GetInstance()->ConvertToShuntingYard(toConvert));
		}
		TEST_METHOD(ShuntingYardBasicDivision)
		{
			std::string converted = "2 2 /", toConvert = "2/2";
			Assert::AreEqual(converted, Processor::GetInstance()->ConvertToShuntingYard(toConvert));
		}
		TEST_METHOD(ShuntingYardBasicSubtraction)
		{
			std::string converted = "2 2 -", toConvert = "2-2";
			Assert::AreEqual(converted, Processor::GetInstance()->ConvertToShuntingYard(toConvert));
		}
		TEST_METHOD(ShuntingYardAdvanced1)
		{
			std::string converted = "2 2 / 3 8 * +", toConvert = "2/2+3*8";
			Assert::AreEqual(converted, Processor::GetInstance()->ConvertToShuntingYard(toConvert));
		}
		TEST_METHOD(ShuntingYardAdvanced2)
		{
			std::string converted = "-3 8 -9 * - 2 +", toConvert = "-3-8*-9+2";
			Assert::AreEqual(converted, Processor::GetInstance()->ConvertToShuntingYard(toConvert));
		}

		TEST_METHOD(CalculationBasic)
		{
			std::string toConvert = "2-2";
			float result = 2 - 2;
			Assert::AreEqual(result, Processor::GetInstance()->Calculate(toConvert));
		}
		TEST_METHOD(CalculationAdvanced1)
		{
			std::string toConvert = "2/2+3*8";
			float result = 2 / 2 + 3 * 8;
			Assert::AreEqual(result, Processor::GetInstance()->Calculate(toConvert));
		}
		TEST_METHOD(CalculationAdvanced2)
		{
			std::string toConvert = "-3-8*-9+2";
			float result = -3 - 8 * -9 + 2;
			Assert::AreEqual(result, Processor::GetInstance()->Calculate(toConvert));
		}
	};
}
