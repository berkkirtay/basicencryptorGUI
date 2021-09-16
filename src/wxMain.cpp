#include "wxMain.h"
#include <fstream>
#include <thread>
#include "wx/filedlg.h"
#include "PrimeNumberContainer.cpp"

//events
wxBEGIN_EVENT_TABLE(wxMain, wxFrame)
EVT_BUTTON(10001, onButtonClicked)
EVT_BUTTON(10002, onSecButtonClicked)
EVT_CLOSE(wxMain::onClose)
wxEND_EVENT_TABLE()

//definitions
wxMain::wxMain(): wxFrame(nullptr, wxID_ANY, "Basic RSA File Encryptor",wxPoint(300,100),wxSize(350,200)){
    tx1 = new wxStaticText(this, wxID_ANY, "File Location : ", wxPoint(10, 10), wxSize(100, 50));
    tx2 = new wxStaticText(this, wxID_ANY, "Encrypt-Decrypt Key :", wxPoint(10, 60), wxSize(100, 50));
    tx3 = new wxStaticText(this, wxID_ANY, wxString::Format(wxT("File Processed: %d"), operations), wxPoint(230, 140), wxSize(100, 50));
    txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(110, 10), wxSize(100, 20)); 
    txt2 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(110, 60), wxSize(100, 20));
    btn1 = new wxButton(this, 10001, "Encrypt!", wxPoint(220, 100), wxSize(100, 25));
    btn2 = new wxButton(this, 10002, "Find file", wxPoint(220, 10), wxSize(100, 25));
    path = wxT("C:/");
    Layout();  // setting appropriate size 
    this->SetMinSize(this->GetSize());
    this->SetMaxSize(this->GetSize());
}
wxMain::~wxMain() {}
 
void wxMain::onClose(wxCloseEvent &event) {
    Destroy();
}

void wxMain::onButtonClicked(wxCommandEvent& event) {
    if (txt2->GetValue() == "") {
        wxMessageBox("Please enter your key!", "Error!");
    }
    else {
        std::string skey = txt2->GetValue().ToStdString();
        int key = stoi(skey);

        PrimeNumberContainer primeContainer;
        std::pair<long, long> primes = primeContainer.getPrimes(key);
        long prime1 = primes.first;
        long prime2 = primes.second;

        if (option == ENCRYPTION) {
            wxString keymsg = wxString::Format(wxT("Chosen prime numbers for this encryption are %d and %d"), prime1, prime2);
            wxMessageBox(keymsg, "Hey!");
        }

        startEncryption(prime1, prime2);
        operations++;
        tx3->SetLabelText(wxString::Format(wxT("File Processed: %d"), operations));
    }
}

void wxMain::startEncryption(int prime1, int prime2) {
    std::string newFile = fileName;
    std::string fileOut = "EncryptedFILE";
    if (option == DECRYPTION) {
        fileOut = "DecryptedFILE";
    }

    std::unique_ptr<FileHandler> newEncryption(new FileHandler(newFile, fileOut));
    newEncryption->initializeEncryptor(prime1, prime2);

    if (option == DECRYPTION) {
        newEncryption->readAndDecrypt();
    }
    else {
        newEncryption->readAndEncrypt();
    }
    wxMessageBox("File Processed as " + fileOut);
}

void wxMain::onSecButtonClicked(wxCommandEvent& event) {
    wxFileDialog* openFileDialog = new wxFileDialog(this, "Choose a file to open");
    if (openFileDialog->ShowModal() == wxID_OK){
         path = openFileDialog->GetPath();
         fileName = openFileDialog->GetPath().ToStdString();
         txt1->AppendText(path);
         option = getFileType();
    } 
    openFileDialog->Destroy();
    if (path=="") {
        wxMessageBox("File cannot be opened!","Error!"); 
    }
    else
    setfileLocation(txt1->GetValue().ToStdString()); 
}

void wxMain::setfileLocation(std::string fileLocation) {
    this->fileLocation = fileLocation;
}

int wxMain::getFileType() {
    if (fileName.find("EncryptedFILE") != std::string::npos) {
        btn1->SetLabelText("Decrypt!");
        return DECRYPTION;
    }
    else
        btn1->SetLabelText("Encrypt!");
    return ENCRYPTION;
}
