#include "cApp.h"


wxIMPLEMENT_APP(cApp);

cApp::cApp()
{

}

cApp::~cApp()
{

}

bool cApp::OnInit()
{

	cMain* frame1 = new cMain();
	frame1->Show(true);

	
	return true;
}

