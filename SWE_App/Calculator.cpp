#include "Calculator.h"
#include "ButtonFactory.h"
#include "Processor.h"


/**
* Creates an event table for the buttons
*/
wxBEGIN_EVENT_TABLE(Calculator, wxFrame)
	EVT_BUTTON(EQUALS, OnButtonClick)
	EVT_BUTTON(ADD, OnButtonClick)
	EVT_BUTTON(SUBTRACT, OnButtonClick)
	EVT_BUTTON(MULTIPLY, OnButtonClick)
	EVT_BUTTON(DIVIDE, OnButtonClick)
	EVT_BUTTON(BACKSPACE, OnButtonClick)
	EVT_BUTTON(CLEAR, OnButtonClick)
	EVT_BUTTON(SIN, OnButtonClick)
	EVT_BUTTON(COS, OnButtonClick)
	EVT_BUTTON(TAN, OnButtonClick)
	EVT_BUTTON(MOD, OnButtonClick)
	EVT_BUTTON(NEGATE, OnButtonClick)
	EVT_BUTTON(DOT, OnButtonClick)

	EVT_BUTTON(ZERO, OnButtonClick)
	EVT_BUTTON(ONE, OnButtonClick)
	EVT_BUTTON(TWO, OnButtonClick)
	EVT_BUTTON(THREE, OnButtonClick)
	EVT_BUTTON(FOUR, OnButtonClick)
	EVT_BUTTON(FIVE, OnButtonClick)
	EVT_BUTTON(SIX, OnButtonClick)
	EVT_BUTTON(SEVEN, OnButtonClick)
	EVT_BUTTON(EIGHT, OnButtonClick)
	EVT_BUTTON(NINE, OnButtonClick)
wxEND_EVENT_TABLE()

//Defines window width and height as constants
const int windowWidth = 315, windowHeight = 400;

/// <summary>
/// Default Constructor initializes buttons and text box for Calculator functionality
/// </summary>
Calculator::Calculator() : 
	wxFrame(nullptr, 1010, "Calculator", wxPoint(windowWidth, windowHeight), wxSize(windowWidth, windowHeight))
{
	ButtonFactory factory = ButtonFactory(this, windowHeight, windowWidth);

	//Makes the calculator app slightly transparent and have a gray background
	this->SetBackgroundColour(wxColour(75, 75, 75, 50));
	this->SetTransparent(240);

	//Defines the text box which is used for input / output
	outBox = new wxTextCtrl(this, 1000, "", wxPoint(0,0), wxSize(windowWidth*.95, windowHeight/3));
	outBox->SetBackgroundColour(wxColour(75, 75, 75, 255));
	outBox->SetForegroundColour(wxColour(255, 255, 255, 255));
	outBox->SetFont(wxFont(30, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	//Disallow user input
	outBox->SetEditable(false);
	
	//Defines operation buttons
	divide = factory.CreateFunctionButton(DIVIDE);
	multiply = factory.CreateFunctionButton(MULTIPLY);
	modulus = factory.CreateFunctionButton(MOD);
	subtract = factory.CreateFunctionButton(SUBTRACT);
	add = factory.CreateFunctionButton(ADD);
	equals = factory.CreateFunctionButton(EQUALS);
	
	//Defines delete and clear buttons
	backspace = factory.CreateFunctionButton(BACKSPACE);
	clear = factory.CreateFunctionButton(CLEAR);

	//Defines special operation buttons
	negate = factory.CreateFunctionButton(NEGATE);
	dot = factory.CreateFunctionButton(DOT);

	//Defines numerical buttons 0-9
	zero = factory.CreateNumericButton(ZERO);
	one = factory.CreateNumericButton(ONE);
	two = factory.CreateNumericButton(TWO);
	three = factory.CreateNumericButton(THREE);
	four = factory.CreateNumericButton(FOUR);
	five = factory.CreateNumericButton(FIVE);
	six = factory.CreateNumericButton(SIX);
	seven = factory.CreateNumericButton(SEVEN);
	eight = factory.CreateNumericButton(EIGHT);
	nine = factory.CreateNumericButton(NINE);

	//Un-implemented trig functions
	sin = factory.CreateFunctionButton(SIN);
	cos = factory.CreateFunctionButton(COS);
	tan = factory.CreateFunctionButton(TAN);
}

Calculator::~Calculator()
{
	delete Processor::GetInstance();
}

/// <summary>
/// Given the current text in the calculators text box,
/// determines whether or not a symbol (+,-,/,*) can be added
/// </summary>
/// <param name="s">
/// The text in the Calculators text box
/// </param>
/// <returns>
/// True if a symbol can be added.
/// False if not
/// </returns>
bool Calculator::CanAddSymbol(wxString& s) {
	if (s.length() == 0) {
		return true;
	}

	if ((s[s.length() - 1] < 48 || s[s.length() - 1] > 57)) {
		return false;
	}

	return true;
}

/// <summary>
/// Sets the Calculator's Text Box's text to the string input
/// </summary>
/// <param name="s">
/// The wxString input
/// </param>
void Calculator::SetText(wxString& s) {
	outBox->Clear();
	outBox->AppendText(s);
}

/// <summary>
/// Sets the Calculator's Text Box's text to the string input
/// </summary>
/// <param name="s">
/// The string input
/// </param>
void Calculator::SetText(const char* s) {
	outBox->Clear();
	outBox->AppendText(s);
}

/// <summary>
/// Sets the Calculator's Text Box's text to the char input
/// </summary>
/// <param name="c">
/// The character input
/// </param>
void Calculator::SetText(char c) {
	outBox->Clear();
	outBox->AppendText(c);
}

//Stores whether a decimal point can be added or not
bool decimal = false;

/// <summary>
/// Performs a function based on which Calculator button was clicked
/// </summary>
/// <param name="e">
/// The button clicked
/// </param>
void Calculator::OnButtonClick(wxCommandEvent& e) {
	int id = e.GetId(); //The Button's ID
	wxString s = outBox->GetRange(0, outBox->GetLineLength(0)); //The Text Box's Text
	std::string convS = s.ToStdString();
	int index = s.length(); //The Current Pointer Index

	switch (id) {
	case EQUALS:
		//Checks if the last character is numeric, and if so calls the calculate function
		if (CanAddSymbol(s)) {
			//Converts the float to a string
			s = std::to_string(Processor::GetInstance()->Calculate(convS));
			//Displays the returned value
			SetText(s);
			//Prevents extra decimal point from being placed
			//Because the output is a float that will always have a decimal
			decimal = true;
		}
		break;
	case ADD:
		//Places a 0 if the text box is empty
		if (index == 0) {
			SetText('0');
		}
		
		//Checks if the last character is numeric, and if so places the symbol
		if (CanAddSymbol(s)) {
			outBox->AppendText('+');
			decimal = false;
		}
		else {
			//Checks if symbol can be replaced, only not true if it is a negate symbol
			//And if so, replaces the symbol
			s = outBox->GetRange(0, outBox->GetLineLength(0) - 1);
			if (CanAddSymbol(s)) {
				SetText(outBox->GetRange(0, outBox->GetLineLength(0) - 1) + '+');
				decimal = false;
			}
		}

		decimal = false;
		break;
	case SUBTRACT:
		//Places a 0 if the text box is empty
		if (index == 0) {
			SetText('0');
		}

		//Checks if the last character is numeric, and if so places the symbol
		if (CanAddSymbol(s)) {
			outBox->AppendText('-');
			decimal = false;
		}
		else {
			//Checks if symbol can be replaced, only not true if it is a negate symbol
			//And if so, replaces the symbol
			s = outBox->GetRange(0, outBox->GetLineLength(0) - 1);
			if (CanAddSymbol(s)) {
				SetText(outBox->GetRange(0, outBox->GetLineLength(0) - 1) + '-');
				decimal = false;
			}
		}
		break;
	case MULTIPLY:
		//Places a 0 if the text box is empty
		if (index == 0) {
			SetText('1');
		}

		//Checks if the last character is numeric, and if so places the symbol
		if (CanAddSymbol(s)) {
			outBox->AppendText('*');
			decimal = false;
		}
		else {
			//Checks if symbol can be replaced, only not true if it is a negate symbol
			//And if so, replaces the symbol
			s = outBox->GetRange(0, outBox->GetLineLength(0) - 1);
			if (CanAddSymbol(s)) {
				SetText(outBox->GetRange(0, outBox->GetLineLength(0) - 1) + '*');
				decimal = false;
			}
		}
		break;
	case DIVIDE:
		//Places a 0 if the text box is empty
		if (index == 0) {
			SetText('0');
		}

		//Checks if the last character is numeric, and if so places the symbol
		if (CanAddSymbol(s)) {
			outBox->AppendText('/');
			decimal = false;
		}
		else {
			//Checks if symbol can be replaced, only not true if it is a negate symbol
			//And if so, replaces the symbol
			s = outBox->GetRange(0, outBox->GetLineLength(0) - 1);
			if (CanAddSymbol(s)) {
				SetText(outBox->GetRange(0, outBox->GetLineLength(0) - 1) + '/');
				decimal = false;
			}
		}
		break;
	case BACKSPACE:
		if (s.length() == 0) {
			break;
		}

		if (s[s.length() - 1] == '.') {
			decimal = false;
		}

		if (s[s.length() - 1] == 'S' || s[s.length() - 1] == 'N') {
			SetText(outBox->GetRange(0, outBox->GetLineLength(0) - 3));
		}
		else {
			SetText(outBox->GetRange(0, outBox->GetLineLength(0) - 1));
		}
		
		break;
	case CLEAR:
		outBox->Clear();
		decimal = false;
		break;
	case SIN://Calculates the sine of the calculated result
		//Checks if the last character is numeric, and if so calls the calculate function
		if (CanAddSymbol(s)) {
			//Converts the float to a string
			s = std::to_string(Processor::GetInstance()->SIN(Processor::GetInstance()->Calculate(convS)));
			//Displays the returned value
			SetText(s);
			//Prevents extra decimal point from being placed
			//Because the output is a float that will always have a decimal
			decimal = true;
		}
		break;
	case COS://Calculates the cosine of the calculated result
		//Checks if the last character is numeric, and if so calls the calculate function
		if (CanAddSymbol(s)) {
			//Converts the float to a string
			s = std::to_string(Processor::GetInstance()->COS(Processor::GetInstance()->Calculate(convS)));
			//Displays the returned value
			SetText(s);
			//Prevents extra decimal point from being placed
			//Because the output is a float that will always have a decimal
			decimal = true;
		}
		break;
	case TAN://Calculates the tangent of the calculated result
		//Checks if the last character is numeric, and if so calls the calculate function
		if (CanAddSymbol(s)) {
			//Converts the float to a string
			s = std::to_string(Processor::GetInstance()->TAN(Processor::GetInstance()->Calculate(convS)));
			//Displays the returned value
			SetText(s);
			//Prevents extra decimal point from being placed
			//Because the output is a float that will always have a decimal
			decimal = true;
		}
		break;
	case MOD:
		//Places a 0 if the text box is empty
		if (index == 0) {
			SetText('0');
		}

		//Checks if the last character is numeric, and if so places the symbol
		if (CanAddSymbol(s)) {
			outBox->AppendText('%');
			decimal = false;
		}
		else {
			//Checks if symbol can be replaced, only not true if it is a negate symbol
			//And if so, replaces the symbol
			s = outBox->GetRange(0, outBox->GetLineLength(0) - 1);
			if (CanAddSymbol(s)) {
				SetText(outBox->GetRange(0, outBox->GetLineLength(0) - 1) + '%');
				decimal = false;
			}
		}
		break;
	case NEGATE:
		//If text box is empty, nothing to negate
		if (index == 0) {
			break;
		}

		//Finds the start of the float, where the negate symbol will be placed
		index = 0;
		for (int i = outBox->GetLineLength(0) - 1; i > 0; i--) {
			//If not numeric, then the start of the float has been found
			if (!((s[i] >= 48 && s[i] <= 57) || s[i]=='.')) {
				//The index of where to insert the negate symbol
				index = i;
				break;
			}
		}

		//If the index is already a negate or subtract symbol
		if (s[index] == '-') {
			//If the negate symbol is not at the beginning of the text box
			if (index != 0) {
				//If there is a symbol to the left of the negate symbol, toggle the negate symbol
				if (index >= 1 && (s[index - 1] == '+' || s[index - 1] == '*' || s[index - 1] == '/' || s[index - 1] == '%' || s[index - 1] == 'S' || s[index - 1] == 'N')) {
					s = outBox->GetRange(0, index) + outBox->GetRange(index + 1, outBox->GetLineLength(0));
				}
				else { //If that symbol is a subtract sybol, two negatives make a positive, replace with a '+' symbol
					s = outBox->GetRange(0, index) + '+' + outBox->GetRange(index + 1, outBox->GetLineLength(0));
				}
			}
			else { //The negate symbol is at the start of the text box, just toggle it
					s = outBox->GetRange(0, index) + outBox->GetRange(index + 1, outBox->GetLineLength(0));
			}
		}else if (index != 0) { //Insert the negate symbol within the text box
			s = outBox->GetRange(0, index + 1) + '-' + outBox->GetRange(index + 1, outBox->GetLineLength(0));
		}
		else { //Set the negate symbol at the beginning of the text box
			s = '-' + s;
		}

		SetText(s);
		break;
	case DOT:
		//If the text box is empty or the previous character is non-numeric, insert a 0 before the decimal point
		if (!decimal && (s.length() == 0 || !CanAddSymbol(s))) {
			outBox->AppendText("0.");
			decimal = true;
		}
		else if(!decimal) { //Make sure a decimal point hasn't already been inserted into the float
			outBox->AppendText(".");
			decimal = true;
		}
		break;
	default:
		//Otherwise just print the numerical buttons to the text box
		outBox->AppendText((char)(id + 48));
		break;
	}

	//Adjust the text box's font size based on text length
	outBox->SetFont(wxFont(s.length() > 18 ? 12 : 30 - s.length(), wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
}