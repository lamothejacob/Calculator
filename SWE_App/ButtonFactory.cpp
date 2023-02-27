#include "ButtonFactory.h"

/// <summary>
/// Instantiates the button factory with values necessary for creating the buttons
/// </summary>
/// <param name="parent">The window that the buttons will be children of</param>
/// <param name="windowHeight">The window's height</param>
/// <param name="windowWidth">The window's width</param>
ButtonFactory::ButtonFactory(wxWindow* parent, int windowHeight, int windowWidth)
{
	this->parent = parent;
	this->windowHeight = windowHeight;
	this->windowWidth = windowWidth;
}

/// <summary>
/// A generic function for creating a button
/// </summary>
/// <param name="gridX">The x position trapped to a grid based on button width</param>
/// <param name="gridY">The y position trapped to a grid based on button height</param>
/// <param name="ID">The buttons ID</param>
/// <param name="text">The buttons text/label</param>
/// <param name="doubleWidth">Whether or not the button should have double the typical width</param>
/// <returns>A pointer to the button created</returns>
wxButton* ButtonFactory::CreateButton(int gridX, int gridY, int ID, const char* text, bool doubleWidth = false) {
	return new wxButton(parent, ID, text, wxPoint(buttonWidth * gridX, windowHeight - buttonHeight * gridY), wxSize(doubleWidth ? 2 * buttonWidth : buttonWidth, buttonHeight));
}

/// <summary>
/// Creates a button for numbers
/// </summary>
/// <param name="num">The ID for which number the button will represent</param>
/// <returns>A pointer to the button created</returns>
wxButton* ButtonFactory::CreateNumericButton(NUMERICS num)
{
	/**
	* X position yields 1 if zero, 0->2 if one through nine
	* Y position yields 2 if Zero, 3 if 1->3, 4 if 4->6, 5 if 7->9
	* 
	* These algorithms allow for one semi-clean definition of all numerical buttons
	*/
	return CreateButton(num == ZERO ? 1 : (num - 1) % 3, ((num - 1) / 3.0 + 3.0), num, std::to_string(num).c_str());
}

ButtonFactory::~ButtonFactory()
{
	delete[] functionLabels;
}

/// <summary>
/// Creates a button for functions
/// </summary>
/// <param name="function">The ID for the function button to be made</param>
/// <returns>A pointer to the button created</returns>
wxButton* ButtonFactory::CreateFunctionButton(FUNCTIONS function)
{
	switch (function) {
	case EQUALS:
	case ADD:
	case SUBTRACT:
	case MULTIPLY:
	case DIVIDE:
	case MOD:
		return CreateButton(3, function - 100 + 2, function, functionLabels[function - 100].c_str());
		break;
	case DOT:
		return CreateButton(2, 2, function, functionLabels[function - 100].c_str());
		break;
	case NEGATE:
		return CreateButton(0, 2, function, functionLabels[function - 100].c_str());
		break;
	case BACKSPACE:
		return CreateButton(2, 7, function, functionLabels[function - 100].c_str());
		break;
	case CLEAR:
		return CreateButton(0, 7, function, functionLabels[function - 100].c_str(), true);
		break;
	case SIN:
	case COS:
	case TAN:
		return CreateButton(function-SIN, 6, function, functionLabels[function - 100].c_str());
		break;
	}
}
