#pragma once
#include "wx/wx.h"
#include "BasicEncryptor.h"
#include <wx/progdlg.h>


class wxMain : public wxFrame{
private:
	std::string fileLocation;
	wxString path;
	std::string fileName;
	int option = 0;
	int operations = 0;
	int encryptionType = 0;  // 0 for RSA_Algorithm - 1 for BASICXOR_Algorithm
	wxArrayString* choices = nullptr;
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
	wxStaticText* tx3 = nullptr;
	wxStaticText* tx4 = nullptr;
	wxFileDialog* file = nullptr;
	wxListBox* listbox = nullptr;
	void onButtonClicked(wxCommandEvent& event);
	void onSecButtonClicked(wxCommandEvent& event);
	void onListBox(wxCommandEvent& event);
	void onClose(wxCloseEvent& event);
	void setfileLocation(std::string fileLocation);
	static void progressBar(int progress);
	bool fileType();
	int getOpt();
	int getencryptionType();
	wxDECLARE_EVENT_TABLE();
	

};

