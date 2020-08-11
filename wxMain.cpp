#include "wxMain.h"
#include <fstream>
#include "wx/filedlg.h"

//events
wxBEGIN_EVENT_TABLE(wxMain, wxFrame)
EVT_BUTTON(10001, onButtonClicked)
EVT_BUTTON(10002, onSecButtonClicked)
EVT_CLOSE(wxMain::onClose)
wxEND_EVENT_TABLE()

//definitions
wxMain::wxMain(): wxFrame(nullptr, wxID_ANY, "Basic Encryptor by trantor00",wxPoint(300,100),wxSize(350,200)){
    tx1 = new wxStaticText(this, wxID_ANY, "File Location: ", wxPoint(10, 10), wxSize(100, 50));
    tx2 = new wxStaticText(this, wxID_ANY, "Encrypt-Decrypt Key :", wxPoint(10, 60), wxSize(100, 50));
    tx3 = new wxStaticText(this, wxID_ANY, wxString::Format(wxT("Operations: %d"), operations), wxPoint(250, 140), wxSize(100, 50));
    txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(110, 10), wxSize(100, 20)); 
    txt2 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(110, 60), wxSize(100, 20));
    btn1 = new wxButton(this, 10001, "Encrypt!", wxPoint(110, 100), wxSize(100, 25));
    btn2 = new wxButton(this, 10002, "Find file", wxPoint(220, 10), wxSize(100, 25));
    path = wxT("C:/");
    Layout();  // setting appropriate size 
    this->SetMinSize(this->GetSize());
    this->SetMaxSize(this->GetSize());
    wxMessageBox("Please be careful while using this program when it comes to your important files. This program should be using only for text files!! ","Hey!");
}
wxMain::~wxMain() {}
void wxMain::onClose(wxCloseEvent &event) {
    Destroy();
}
void wxMain::onButtonClicked(wxCommandEvent &event) {
    std::string* newFile =new std::string;
    *newFile = fileName;
    std::string* fileOut = new std::string;
    *fileOut = "EncryptedFILE";
    int x, y;
    int key=1;
    int opt = getOpt();
    if (opt == -1) *fileOut = "DecryptedFILE";
    if (txt2->GetValue() == "")
        wxMessageBox("Please enter your key!", "Error!");
    else {
        std::string skey = txt2->GetValue().ToStdString();


        key = stoi(skey);
        if (opt != -1) {
            wxString keymsg = wxString::Format(wxT("Your key is %d. Don't forget it!"), key);
            wxMessageBox(keymsg, "Hey!");
      }

        FILEO newEncryption(newFile, fileOut, opt);
        newEncryption.createKey(key);
        x = newEncryption.getX();
        y = newEncryption.getY();
        newEncryption.readingFile();
        newEncryption.encrypt(x, y, opt);  // enrypt-decrypt section!!
        int progress=newEncryption.getProgress();
        newEncryption.writingFile();
        progressBar(progress);
        wxMessageBox("File Processed as " + *fileOut);
        operations++;
        tx3->SetLabelText(wxString::Format(wxT("Operations: %d"), operations));
    }
   
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
        wxMessageBox("FILE CAN'T BE OPENING!!","Error!"); 
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
    else
        btn1->SetLabelText("Encrypt!");
    return false;
}
int wxMain::getOpt() {
    return option;
}

void wxMain::progressBar(int progress) {
    wxFrame* frame = new wxFrame(NULL, wxID_ANY, "progressbar");
    wxPoint *points = new wxPoint(400, 400);
    frame->SetPosition(*points);
    wxProgressDialog* progressBar = new wxProgressDialog(wxT("File Processing"), wxT("Please wait"), progress, frame, wxPD_AUTO_HIDE | wxPD_APP_MODAL);
    progressBar->SetIcon(wxIcon(wxT("encrypt.ico"), wxBITMAP_TYPE_ICO));  // setting ico 
 
        for (int i = 0; i < progress; i++) {
             wxMilliSleep(0.0005); 
            if (i % 31) progressBar->Update(i);
        }
    
    progressBar->Update(progress);
    delete progressBar;
    delete frame;

}

