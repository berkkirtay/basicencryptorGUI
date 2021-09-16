#pragma once
#include "wx/wx.h"
#include <wx/progdlg.h>
#include "FileHandler.h"

class wxMain : public wxFrame {
private:
	const int ENCRYPTION = 0;
	const int DECRYPTION = -1;

private:
	std::string fileLocation;
	wxString path;
	std::string fileName;
	int operations = 0;
	int option = 0;

private:
	wxButton* btn1 = nullptr;
	wxButton* btn2 = nullptr;
	wxTextCtrl* txt1 = nullptr;
	wxTextCtrl* txt2 = nullptr;
	wxStaticText* tx1 = nullptr;
	wxStaticText* tx2 = nullptr;
	wxStaticText* tx3 = nullptr;
	wxStaticText* tx4 = nullptr;
	wxFileDialog* file = nullptr;
	wxListBox* listbox = nullptr;
	void onButtonClicked(wxCommandEvent& event);
	void onSecButtonClicked(wxCommandEvent& event);
	void onClose(wxCloseEvent& event);
	void setfileLocation(std::string fileLocation);
	int getFileType();
	void startEncryption(int prime1, int prime2);
	wxDECLARE_EVENT_TABLE();

public:
	wxMain();
	~wxMain();
};

