#include "CppUnitTest.h"
#include "Formula.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FormulaTest
{		
	TEST_CLASS(FormulaUnitTests)
	{
	public:

		//epsilon value since float values are not precise
		float EPSILON = 0.001;
		
		TEST_METHOD(TestBasicAdditionFormula)
		{
			map<string, float> valueMap = {
				{"Cuka", 1.0}
			};
			string testString = "2.1 + Cuka";
			Formula testFormula = fromString(testString);
			float x = testFormula.calculate(valueMap);
			Assert::IsTrue(abs(testFormula.calculate(valueMap) - 3.1) < EPSILON);
		}

		TEST_METHOD(TestBasicSubtractionFormula)
		{
			map<string, float> valueMap = {
				{"Cuka", 1.0}
			};
			string testString = "2.1 - Cuka";
			Formula testFormula = fromString(testString);
			float x = testFormula.calculate(valueMap);
			Assert::IsTrue(abs(testFormula.calculate(valueMap) - 1.1) < EPSILON);
		}

		TEST_METHOD(TestBasicMultiplicationFormula)
		{
			map<string, float> valueMap = {
				{"Cuka", 1.0},
			};
			string testString = "2.1 * Cuka";
			Formula testFormula = fromString(testString);
			float x = testFormula.calculate(valueMap);
			Assert::IsTrue(abs(testFormula.calculate(valueMap) - 2.1) < EPSILON);
		}

		TEST_METHOD(TestBasicDivisionFormula)
		{
			map<string, float> valueMap = {
				{"Cuka", 1.1}
			};
			string testString = "2.1 / Cuka";
			Formula testFormula = fromString(testString);
			float x = testFormula.calculate(valueMap);
			Assert::IsTrue(abs(testFormula.calculate(valueMap) - 2.1/1.1) < EPSILON);
		}

		TEST_METHOD(TestBasicPowerFormula)
		{
			map<string, float> valueMap = {
				{"Cuka", 3}
			};
			string testString = "2 ^ Cuka";
			Formula testFormula = fromString(testString);
			float x = testFormula.calculate(valueMap);
			Assert::IsTrue(abs(testFormula.calculate(valueMap) - 8) < EPSILON);
		}

		TEST_METHOD(TestBasicFormula)
		{
			map<string, float> valueMap = {
				{"Cuka", 1.0},
				{"Moka", 2.0},
			};
			string testString = "2.1 * Cuka - 0.1 * Moka  ";
			Formula testFormula = fromString(testString);
			float x = testFormula.calculate(valueMap);
			Assert::IsTrue(abs(testFormula.calculate(valueMap) - 1.9) < EPSILON);
		}

		TEST_METHOD(TestBasicFormula2)
		{
			map<string, float> valueMap = {
				{"Cuka", 1.0},
				{"Moka", 2.0},
			};
			string testString = "2.1 * Cuka + 0.1 * Moka  ";
			Formula testFormula = fromString(testString);

			Assert::IsTrue(abs(testFormula.calculate(valueMap) - 2.3) < EPSILON);

		}
		TEST_METHOD(TestBasicFormulaWithDifferentValues)
		{
			map<string, float> valueMap = {
				{"Cuka", 2.0},
				{"Moka", 1.0},
			};
			string testString = "2.1 * Cuka - 0.1 * Moka";
			Formula testFormula = fromString(testString);

			Assert::IsTrue(abs(testFormula.calculate(valueMap) - 4.1) < EPSILON);
		}

		TEST_METHOD(TestBasicFormulaWithAllValues)
		{
			map<string, float> valueMap = {
			};
			string testString = "1 * 2 - 3 * 4";
			Formula testFormula = fromString(testString);

			Assert::IsTrue(abs(testFormula.calculate(valueMap) - (-10)) < EPSILON);
		}

		TEST_METHOD(TestBasicFormulaWithAllTags)
		{
			map<string, float> valueMap = {
				{"Cuka", 1.0},
				{"Moka", 2.0},
				{"a", 5},
				{"b", 10}
			};
			string testString = "a * Cuka - b * Moka";
			Formula testFormula = fromString(testString);

			Assert::IsTrue(abs(testFormula.calculate(valueMap) - (-15)) < EPSILON);
		}

		TEST_METHOD(TestDifficultFormula)
		{
			map<string, float> valueMap = {
				{"Cuka", -18.0},
				{"Moka", 19.2},
				{"X", -12.54}
			};
			string testString = "2.1 * Cuka ^ 3 - 0.1 * Moka / 16 + X";
			Formula testFormula = fromString(testString);
			Assert::IsTrue(abs(testFormula.calculate(valueMap) - (-12259.86)) < EPSILON);
		}

		TEST_METHOD(TestDifficultFormula2)
		{
			map<string, float> valueMap = {
				{"Cuka", 0},
				{"Moka", 19.2},
				{"X", 0}
			};
			string testString = "0 * Cuka ^ 3 - 0.1 * Moka / 16 - X";
			Formula testFormula = fromString(testString);

			Assert::IsTrue(abs(testFormula.calculate(valueMap) - (-0.12)) < EPSILON);
		}


		TEST_METHOD(TestBasicFormulaWithBrackets)
		{
			map<string, float> valueMap = {
				{"Cuka", 1.0},
				{"Moka", 2.0},
			};
			string testString = "2.1 * ( Cuka - 0.1 ) * Moka";
			Formula testFormula = fromString(testString);
			float x = testFormula.calculate(valueMap);
			Assert::IsTrue(abs(testFormula.calculate(valueMap) - 3.78) < EPSILON);
		}

		TEST_METHOD(TestBasicFormulaWithMultipleBrackets)
		{
			map<string, float> valueMap = {
				{"Cuka", 1.0},
				{"Moka", 2.0},
			};
			string testString = "( ( ( 2.1 * ( Cuka - 0.1 ) * Moka ) ) )";
			Formula testFormula = fromString(testString);
			float x = testFormula.calculate(valueMap);
			Assert::IsTrue(abs(testFormula.calculate(valueMap) - 3.78) < EPSILON);

		}
		TEST_METHOD(TestDifficultFormulaWithMultipleBrackets)
		{
			map<string, float> valueMap = {
				{"Cuka", -18.0},
				{"Moka", 19.2},
				{"X", -12.54}
			};
			string testString = "2.1 * ( Cuka ^ 3 - 0.1 ) * Moka / ( 16 + X )";
			Formula testFormula = fromString(testString);
			float x = testFormula.calculate(valueMap);
			Assert::IsTrue(abs(x - (-67962.50)) < EPSILON);
		}

		TEST_METHOD(TestDifficultFormulaWithNestedBrackets)
		{
			map<string, float> valueMap = {
				{"Cuka", -18.0},
				{"Moka", 19.2},
				{"X", -12.54}
			};
			string testString = "2.1 * ( Cuka ^ ( 3 - 2 ) ) * Moka / ( 16 + X )";
			Formula testFormula = fromString(testString);
			Assert::IsTrue(abs(testFormula.calculate(valueMap) - (-209.7572)) < EPSILON);
		}
	};
}