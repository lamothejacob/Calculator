#pragma once
#include "wx/wx.h"

class Calculator : public wxFrame
{
private:
	wxTextCtrl* outBox = nullptr;

	wxButton* add = nullptr;
	wxButton* subtract = nullptr;
	wxButton* divide = nullptr;
	wxButton* multiply = nullptr;
	wxButton* modulus = nullptr;

	wxButton* backspace = nullptr;
	wxButton* clear = nullptr;
	wxButton* negate = nullptr;
	wxButton* equals = nullptr;
	wxButton* dot = nullptr;

	wxButton* zero = nullptr;
	wxButton* one = nullptr;
	wxButton* two = nullptr;
	wxButton* three = nullptr;
	wxButton* four = nullptr;
	wxButton* five = nullptr;
	wxButton* six = nullptr;
	wxButton* seven = nullptr;
	wxButton* eight = nullptr;
	wxButton* nine = nullptr;

	wxButton* sin = nullptr;
	wxButton* cos = nullptr;
	wxButton* tan = nullptr;
public:
	Calculator();
	~Calculator();
	void OnButtonClick(wxCommandEvent& e);
	wxDECLARE_EVENT_TABLE();
	bool CanAddSymbol(wxString& s);
	void SetText(wxString& s);
	void SetText(const char* s);
	void SetText(char c);
};

