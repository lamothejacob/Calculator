#include "pch.h"
#include "CppUnitTest.h"
#include "../SWE_App/ButtonFactory.h"
#include "../SWE_App/Calculator.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTests
{
	TEST_CLASS(ButtonFactoryTests)
	{
	public:
		TEST_METHOD(CreatingButton)
		{
			ButtonFactory bf(new wxFrame(nullptr, 1010, "Calculator", wxPoint(100, 100), wxSize(100, 100)), 100, 100);
			wxButton* b = bf.CreateButton(1, 1, 1, "test", false);
			Assert::IsNotNull(b);
		}
		TEST_METHOD(LabelingButton)
		{
			ButtonFactory bf (new wxFrame(nullptr, 1010, "Calculator", wxPoint(100, 100), wxSize(100, 100)), 100, 100);
			std::string label = "Testing Labels";
			wxButton* b = bf.CreateButton(1, 1, 1, label.c_str(), false);
			Assert::AreEqual(label.c_str(), b->GetLabel().c_str());
		}
		TEST_METHOD(IDButton)
		{
			ButtonFactory bf(new wxFrame(nullptr, 1010, "Calculator", wxPoint(100, 100), wxSize(100, 100)), 100, 100);
			int ID = 500;
			wxButton* b = bf.CreateButton(1, 1, ID, "", false);
			Assert::AreEqual(ID, b->GetId());
		}
		TEST_METHOD(TestXPosition)
		{
			ButtonFactory bf(new wxFrame(nullptr, 1010, "Calculator", wxPoint(100, 100), wxSize(100, 100)), 100, 100);
			int x = 5, expectedX = x * 75;
			wxButton* b = bf.CreateButton(x, 1, 1, "", false);
			Assert::AreEqual(expectedX, b->GetPosition().x);
		}
		TEST_METHOD(TestYPosition)
		{
			ButtonFactory bf(new wxFrame(nullptr, 1010, "Calculator", wxPoint(100, 100), wxSize(100, 100)), 100, 100);
			int y = 2, expectedY = 100 - (75 / 2) * y;
			wxButton* b = bf.CreateButton(1, y, 1, "", false);
			Assert::AreEqual(expectedY, b->GetPosition().y);
		}
		TEST_METHOD(NumericsPositionTest)
		{
			ButtonFactory bf(new wxFrame(nullptr, 1010, "Calculator", wxPoint(100, 100), wxSize(100, 100)), 100, 100);
			for (int n = 1; n < 10; n++) {
				wxButton* b = bf.CreateNumericButton((NUMERICS)n);
				Assert::AreEqual((n - 1) % 3, b->GetPosition().x / 75);
			}
		}
		TEST_METHOD(ZeroPositionTest)
		{
			ButtonFactory bf(new wxFrame(nullptr, 1010, "Calculator", wxPoint(100, 100), wxSize(100, 100)), 100, 100);
			wxButton* b = bf.CreateNumericButton(ZERO);
			Assert::AreEqual(1, b->GetPosition().x / 75);
		}
		TEST_METHOD(TestFunctionMultiply)
		{
			ButtonFactory bf(new wxFrame(nullptr, 1010, "Calculator", wxPoint(100, 100), wxSize(100, 100)), 100, 100);
			wxButton* b = bf.CreateFunctionButton(MULTIPLY);
			Assert::AreEqual("*", b->GetLabel().c_str());
		}
		TEST_METHOD(TestFunctionSin)
		{
			ButtonFactory bf(new wxFrame(nullptr, 1010, "Calculator", wxPoint(100, 100), wxSize(100, 100)), 100, 100);
			wxButton* b = bf.CreateFunctionButton(SIN);
			Assert::AreEqual("SIN", b->GetLabel().c_str());
		}
		TEST_METHOD(TestFunctionNegate)
		{
			ButtonFactory bf(new wxFrame(nullptr, 1010, "Calculator", wxPoint(100, 100), wxSize(100, 100)), 100, 100);
			wxButton* b = bf.CreateFunctionButton(NEGATE);
			Assert::AreEqual("+/-", b->GetLabel().c_str());
		}
	};
}
