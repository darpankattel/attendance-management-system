#include <LogInFrame.h>
#include <Config.h>
#include <ImageUploadView.h>
#include <ImageView.h>
extern wxColor* primaryColor;
extern wxString* smallLogo;
extern wxString* defaultUserImage;

LogInFrame:: LogInFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
    this->SetBackgroundColour(*primaryColor);

    wxPanel *mainContainer = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(900, 600));

    wxPanel *leftInfoContainer = new wxPanel(mainContainer, wxID_ANY, wxDefaultPosition, wxSize(550, 350));
    // leftInfoContainer->SetBackgroundColour(wxColor(0, 0, 0));

    // wxImage *leftImage = new wxImage(*smallLogo, wxBITMAP_TYPE_PNG);
    // wxBitmap *leftBitmap = new wxBitmap(*leftImage);
    // leftBitmap->Rescale(*leftBitmap, wxSize(100, 100));
    // wxStaticBitmap *leftLogo = new wxStaticBitmap(leftInfoContainer, wxID_ANY, *leftBitmap, wxDefaultPosition, wxSize(300, 200));
    // leftLogo->SetBackgroundColour(*primaryColor);

    ImageView *leftLogo = new ImageView(leftInfoContainer, wxDefaultPosition, wxSize(300, 200), *smallLogo, wxBITMAP_TYPE_PNG);
    leftLogo->SetBackgroundColor(*primaryColor);


    wxStaticText *leftAppText = new wxStaticText(leftInfoContainer, wxID_ANY, wxString(appName), wxDefaultPosition, wxSize(300, 40), wxALIGN_CENTER);
    // leftAppText->SetBackgroundColour(wxColor(0, 0, 255));

    leftAppText->SetForegroundColour(wxColor(255, 255, 255));
    leftAppText->SetFont(wxFont(20, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));

    wxStaticText *leftStaticText = new wxStaticText(leftInfoContainer, wxID_ANY, *logInContainerLeftText, wxDefaultPosition, wxSize(400, 90), wxALIGN_CENTER);
    // leftStaticText->SetBackgroundColour(wxColor(0, 255, 0));

    leftStaticText->SetForegroundColour(wxColor(255, 255, 255));
    leftStaticText->SetFont(wxFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxBoxSizer *leftInfoContainerSizer = new wxBoxSizer(wxVERTICAL);
    leftLogo->setSizerCustom(leftInfoContainerSizer, 1, wxALIGN_CENTER_HORIZONTAL, 0);
    // leftInfoContainerSizer->Add(leftLogo, 1, wxALIGN_CENTER_HORIZONTAL);
    leftInfoContainerSizer->Add(leftAppText, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    leftInfoContainerSizer->Add(leftStaticText, 0, wxEXPAND | wxTOP, 10);
    leftInfoContainer->SetSizerAndFit(leftInfoContainerSizer);

    wxPanel *logInContainer = new wxPanel(mainContainer, wxID_ANY, wxDefaultPosition, wxSize(350, 400));
    logInContainer->SetBackgroundColour(wxColor(255, 255, 255));

    // image uploader
    ImageUploadView* logInImageUpload = new ImageUploadView(logInContainer, wxString("Upload a Image"), wxPoint(0, 0), wxSize(120, 150), *defaultUserImage, wxBITMAP_TYPE_PNG, wxString("Click to upload a new image"));

    // text entry
    wxStaticText *nameLabel = new wxStaticText(logInContainer, wxID_ANY, wxString("Your Name *"), wxDefaultPosition, wxSize(200, 30));
    nameLabel->SetForegroundColour(wxColor(0, 0, 0));
    nameLabel->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxTextCtrl *usernameText = new wxTextCtrl(logInContainer, wxID_ANY, wxString(""), wxDefaultPosition, wxSize(200, 30));
    usernameText->SetForegroundColour(wxColor(0, 0, 0));
    usernameText->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    // buttons
    wxButton *logInButton = new wxButton(logInContainer, wxID_ANY, wxString("Log In"), wxDefaultPosition, wxDefaultSize);
    logInButton->SetBackgroundColour(wxColor(255, 255, 255));
    logInButton->SetForegroundColour(wxColor(0, 0, 0));
    logInButton->SetFont(wxFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    logInButton->SetCursor(wxCursor(wxCURSOR_HAND));

    // sizer
    wxBoxSizer *logInContainerSizer = new wxBoxSizer(wxVERTICAL);
    logInImageUpload->setSizerCustom(logInContainerSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);
    logInContainerSizer->Add(logInImageUpload, 0, wxALIGN_CENTER_HORIZONTAL);
    logInContainerSizer->Add(nameLabel, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 2);
    logInContainerSizer->Add(usernameText, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 10);
    logInContainerSizer->Add(logInButton, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 10);
    logInContainer->SetSizerAndFit(logInContainerSizer);
    
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(mainContainer, 1, wxEXPAND | wxALL, 0);
    this->SetSizerAndFit(sizer);

    wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *centeringSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(leftInfoContainer, 10, wxALIGN_CENTER | wxRIGHT, 40);
    mainSizer->Add(logInContainer, 7, wxALIGN_CENTER | wxLEFT, 40);
    centeringSizer->Add(mainSizer, 1, wxALIGN_CENTER);
    mainContainer->SetSizerAndFit(centeringSizer);

    this->Layout();
}