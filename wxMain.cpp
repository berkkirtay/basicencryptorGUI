#include "wxMain.h"
#include <fstream>
#include "wx/filedlg.h"

//events
wxBEGIN_EVENT_TABLE(wxMain, wxFrame)
EVT_BUTTON(10001, onButtonClicked)
EVT_BUTTON(10002, onSecButtonClicked)

wxEND_EVENT_TABLE()

//definitions
wxMain::wxMain(): wxFrame(nullptr, wxID_ANY, "Basic Encryptor by trantor00",wxPoint(300,100),wxSize(350,200)){
    tx1 = new wxStaticText(this, wxID_ANY, "File Location: ", wxPoint(10, 10), wxSize(100, 50));
    tx2 = new wxStaticText(this, wxID_ANY, "Encrypt-Decrypt Key :", wxPoint(10, 60), wxSize(100, 50));
    txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(110, 10), wxSize(100, 20)); 
    txt2 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(110, 60), wxSize(100, 20));
    btn1 = new wxButton(this, 10001, "Encrypt!", wxPoint(110, 100), wxSize(100, 25));
    btn2 = new wxButton(this, 10002, "Find file", wxPoint(220, 10), wxSize(100, 25));
    path = wxT("C:/");
    Layout();  // setting appropriate size 
    this->SetMinSize(this->GetSize());
    this->SetMaxSize(this->GetSize());
    wxMessageBox("Please be careful while using this program when it comes to your important files. This program should be using only for text files!! ");
   
}
wxMain::~wxMain() {}

void wxMain::onButtonClicked(wxCommandEvent &event) {
    std::string* newFile =new std::string;
    *newFile = fileName;
    std::string* fileOut = new std::string;
    *fileOut = "EncryptedFILE";
    int x, y;
    int key=1;
    int opt = getOpt();
    if (opt == -1) *fileOut = "DecryptedFILE";
    std::string skey=txt2->GetValue().ToStdString();
   
 
    key = stoi(skey);
    wxString keymsg = wxString::Format(wxT("Your key is %d. Don't forget it!"), key);
    wxMessageBox(keymsg);   
   
    FILEO newEncryption(newFile, fileOut, opt);
    newEncryption.createKey(key);
    x = newEncryption.getX();
    y = newEncryption.getY();
    newEncryption.readingFile();
    newEncryption.encrypt(x, y, opt);  // enrypt-decrypt section!!
    newEncryption.writingFile();

    wxMessageBox("File Processed as "+*fileOut);

    
}
void wxMain::onSecButtonClicked(wxCommandEvent& event) {
    
    wxFileDialog* openFileDialog = new wxFileDialog(this, "Choose a file to open");
    if (openFileDialog->ShowModal() == wxID_OK){
         path = openFileDialog->GetPath();
         fileName = openFileDialog->GetPath().ToStdString();
         txt1->AppendText(path);
         bool opt =fileType();
         if (opt) option = -1;
         else option = 0;
    } 
    openFileDialog->Destroy();
    if (path=="") {
        wxMessageBox("FILE CAN'T BE OPENING!!"); 
    }
    else
     setfileLocation(txt1->GetValue().ToStdString()); 
      
}
void wxMain::setfileLocation(std::string fileLocation) {
    this->fileLocation = fileLocation;
}
bool wxMain::fileType() {
    if (fileName.find("EncryptedFILE") != std::string::npos) {
        btn1->SetLabelText("Decrypt!");
        return true;
    }
    return false;
}
int wxMain::getOpt() {
    return option;
}

