#pragma once
#include "wx/wx.h"
#include "BasicEncryptor.h"

class wxMain : public wxFrame{
private:
	std::string fileLocation;
	wxString path;
	std::string fileName;
	int option = 0;
public:
	wxMain();
	~wxMain();
public:
	wxButton* btn1 = nullptr;
	wxButton* btn2 = nullptr;
	wxTextCtrl* txt1 = nullptr;
	wxTextCtrl* txt2 = nullptr;
	wxStaticText* tx1=nullptr;
	wxStaticText* tx2 = nullptr;
	wxFileDialog* file= nullptr;
	void onButtonClicked(wxCommandEvent &event);
	void onSecButtonClicked(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();

	void setfileLocation(std::string fileLocation);
	bool fileType();
	int getOpt();
	

};

