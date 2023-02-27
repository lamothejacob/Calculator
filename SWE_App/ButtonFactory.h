#pragma once
#include "wx/wx.h"

/**
* Stores IDs for function buttons
*/
enum FUNCTIONS {
	EQUALS = 100,
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVIDE,
	MOD,
	DOT,
	NEGATE,
	BACKSPACE,
	CLEAR,
	SIN,
	COS,
	TAN
};

/**
* Stores IDs for number buttons
*/
enum NUMERICS {
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE
};

class ButtonFactory
{
private:
	const int buttonWidth = 75, buttonHeight = buttonWidth / 2;
	int windowHeight, windowWidth;
	wxWindow* parent = nullptr;

	const std::string* functionLabels = new std::string[13]{"=","+","-","*","/","%",".","+/-","DELETE","CLEAR","SIN","COS","TAN"};
public:
	ButtonFactory(wxWindow* parent, int windowHeight, int windowWidth);
	~ButtonFactory();

	wxButton* CreateButton(int gridX, int gridY, int ID, const char* text, bool doubleWidth);
	
	wxButton* CreateNumericButton(NUMERICS num);

	wxButton* CreateFunctionButton(FUNCTIONS function);
};

