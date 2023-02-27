#include "WidgetsApp.h"

wxIMPLEMENT_APP(WidgetsApp);

bool WidgetsApp::OnInit() {
	calculator = new Calculator();
	calculator->Show();

	return true;
}