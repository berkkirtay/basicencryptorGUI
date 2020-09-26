#include "wxMain.h"
#include <fstream>
#include "wx/filedlg.h"

//events
wxBEGIN_EVENT_TABLE(wxMain, wxFrame)
EVT_BUTTON(10001, onButtonClicked)
EVT_BUTTON(10002, onSecButtonClicked)
EVT_LISTBOX(10003, onListBox)
EVT_CLOSE(wxMain::onClose)
wxEND_EVENT_TABLE()

//definitions
wxMain::wxMain(): wxFrame(nullptr, wxID_ANY, "Basic Encryptor by trantor00",wxPoint(300,100),wxSize(350,200)){
    tx1 = new wxStaticText(this, wxID_ANY, "File Location : ", wxPoint(10, 10), wxSize(100, 50));
    tx2 = new wxStaticText(this, wxID_ANY, "Encrypt-Decrypt Key :", wxPoint(10, 60), wxSize(100, 50));
    tx3 = new wxStaticText(this, wxID_ANY, wxString::Format(wxT("File Processed: %d"), operations), wxPoint(230, 140), wxSize(100, 50));
    txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(110, 10), wxSize(100, 20)); 
    txt2 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(110, 60), wxSize(100, 20));
    btn1 = new wxButton(this, 10001, "Encrypt!", wxPoint(220, 100), wxSize(100, 25));
    btn2 = new wxButton(this, 10002, "Find file", wxPoint(220, 10), wxSize(100, 25));
    path = wxT("C:/");
    choices = new wxArrayString();
    choices->Add("RSA_Algorithm");
    choices->Add("BASICXOR_Algorithm");  
    listbox = new wxListBox(this, 10003, wxPoint(85, 110), wxSize(120, 35),*choices,0L,wxDefaultValidator);
    tx4= new wxStaticText(this, wxID_ANY, "Algorithm Type :", wxPoint(10, 110), wxSize(60, 50));
    Layout();  // setting appropriate size 
    this->SetMinSize(this->GetSize());
    this->SetMaxSize(this->GetSize());
}
wxMain::~wxMain() {}

void wxMain::onClose(wxCloseEvent &event) {
    Destroy();
}

void wxMain::onListBox(wxCommandEvent& event) {
    std::string algorithmchoice;
    algorithmchoice = listbox->GetStringSelection().ToStdString();
    if (algorithmchoice == "RSA_Algorithm") {
        encryptionType = 0;
    }
    else if (algorithmchoice == "BASICXOR_Algorithm") {
        encryptionType = 1;
    }
    else {
        wxMessageBox("Choose a proper algorithm!");
    }
}

void wxMain::onButtonClicked(wxCommandEvent &event) {
    std::string newFile = fileName;
    std::string fileOut = "EncryptedFILE";
    int x, y;
    int key=1;
    int opt = getOpt();
    if (opt == -1) fileOut = "DecryptedFILE";
    if (txt2->GetValue() == "")
        wxMessageBox("Please enter your key!", "Error!");
    else if (txt2->GetValue().length()<2)
        wxMessageBox("Please enter a key which has more than 1 value!", "Error!");
    else {
        std::string skey = txt2->GetValue().ToStdString();

        key = stoi(skey);
        std::unique_ptr<FILEO> newEncryption(new FILEO(newFile, fileOut, opt));
        newEncryption->createKey(key);
        x = newEncryption->getX();
        y = newEncryption->getY();
        if (opt != -1) {
            wxString keymsg = wxString::Format(wxT("Your key is %d. Generated prime numbers are %d and %d"), key, x, y);
            wxMessageBox(keymsg, "Hey!");
 }
        newEncryption->setopt(opt);
        newEncryption->setencry(encryptionType);
        newEncryption->readingFile(opt);
        newEncryption->encrypt(x, y, opt);  // enrypt-decrypt section!!
        int progress=newEncryption->getProgress();
        progressBar(progress);
        newEncryption->writingFile(opt);
        wxMessageBox("File Processed as " + fileOut);
        operations++;
        tx3->SetLabelText(wxString::Format(wxT("File Processed: %d"), operations));
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

int wxMain::getencryptionType() {
    return encryptionType;
}

void wxMain::progressBar(int progress) {
    wxFrame* frame = new wxFrame(NULL, wxID_ANY, "progressbar");
    wxPoint* points = new wxPoint(400, 400);
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

