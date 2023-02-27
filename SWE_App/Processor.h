#pragma once
#include <string>
#include <map>

class Processor
{
private:
	enum FUNCTIONS {
		ADD = '+',
		SUBTRACT = '-',
		MULTIPLY = '*',
		DIVIDE = '/',
		MOD = '%'
	};

	std::map<char, int> priority = {{(char)ADD,0},
									{(char)SUBTRACT,0}, 
									{(char)MULTIPLY,1}, 
									{(char)DIVIDE,1}, 
									{(char)MOD,1}};
	static Processor* _processor;

	Processor();
	void operator=(Processor& v) = delete;
	Processor(Processor& v) = delete;
public:
	static Processor* GetInstance();
	std::string ConvertToShuntingYard(std::string& s);
	float Calculate(std::string s);
	float SIN(float f);
	float COS(float f);
	float TAN(float f);
};

