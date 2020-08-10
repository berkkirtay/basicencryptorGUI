#include "wxAppLaunch.h"




wxIMPLEMENT_APP(wxAppLaunch);


wxAppLaunch::wxAppLaunch() {


}
wxAppLaunch::~wxAppLaunch() {


}

bool wxAppLaunch::OnInit() {
	frame = new wxMain();
	frame->SetIcon(wxIcon(wxT("encrypt.ico"), wxBITMAP_TYPE_ICO));  // setting ico 
	wxFont myFont(16, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	frame->SetFont(myFont);
	frame->Show();
	return true;
}