#include <LogInFrame.h>
#include <Config.h>
#include <ImageUploadView.h>
#include <ImageView.h>
#include <MainFrame.h>

#include <wx/stdpaths.h>
#include <sqlite3.h>
extern wxColor* primaryColor;
extern wxString* smallLogo;
extern wxString* defaultUserImage;

ImageUploadView* logInImageUpload;
wxTextCtrl* fullnameText;

LogInFrame:: LogInFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
    this->SetBackgroundColour(*primaryColor);

    wxPanel *mainContainer = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(900, 600));

    wxPanel *leftInfoContainer = new wxPanel(mainContainer, wxID_ANY, wxDefaultPosition, wxSize(550, 350));

    ImageView *leftLogo = new ImageView(leftInfoContainer, wxDefaultPosition, wxSize(100, 100), *smallLogo, wxBITMAP_TYPE_PNG);
    leftLogo->SetBackgroundColor(*primaryColor);
    leftLogo->SetSizeCustom(wxSize(100, 100));


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

    wxPanel *logInContainer = new wxPanel(mainContainer, wxID_ANY, wxDefaultPosition, wxSize(350, 450));
    logInContainer->SetBackgroundColour(wxColor(255, 255, 255));

    // image uploader
    logInImageUpload = new ImageUploadView(logInContainer, wxString("Upload a Image"), wxPoint(0, 0), wxSize(100, 270/3), *defaultUserImage, wxBITMAP_TYPE_ANY, wxString("Click to upload a new image"));
    logInImageUpload->SetSizeCustom(wxSize(100, 270/3));

    // text entry
    wxStaticText *nameLabel = new wxStaticText(logInContainer, wxID_ANY, wxString("Your Name *"), wxDefaultPosition, wxSize(200, 30));
    nameLabel->SetForegroundColour(wxColor(0, 0, 0));
    nameLabel->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    fullnameText = new wxTextCtrl(logInContainer, wxID_ANY, wxString(""), wxDefaultPosition, wxSize(200, 30));
    fullnameText->SetForegroundColour(wxColor(0, 0, 0));
    fullnameText->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    // buttons
    wxButton *logInButton = new wxButton(logInContainer, 10, wxString("Log In"), wxDefaultPosition, wxDefaultSize);
    logInButton->SetBackgroundColour(wxColor(255, 255, 255));
    logInButton->SetForegroundColour(wxColor(0, 0, 0));
    logInButton->SetFont(wxFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    logInButton->SetCursor(wxCursor(wxCURSOR_HAND));
    logInButton->SetToolTip(wxString("Click to log in"));
    // bind click event to log in button
    logInButton->Bind(wxEVT_LEFT_DOWN, &LogInFrame::onLogInButtonClick, this);

    // sizer
    wxBoxSizer *logInContainerSizer = new wxBoxSizer(wxVERTICAL);
    logInImageUpload->setSizerCustom(logInContainerSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 20);
    logInContainerSizer->Add(nameLabel, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 2);
    logInContainerSizer->Add(fullnameText, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 10);
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

void LogInFrame::onLogInButtonClick(wxMouseEvent& event)
{
    wxString myDocRoot = wxStandardPaths::Get().GetDocumentsDir();
    wxString myDocRootPath = myDocRoot.Append(wxString("\\") + wxString(appName));
    wxString myDocRootPathConfig = myDocRootPath.Append(wxString("\\userdata.db"));
    // wxString myDocRootPathLogIn = myDocRootPath.Append(wxString("\\logindata.db"));
    std::cout << "Log In Button Clicked" << std::endl;
    // get the name from the text box
    wxString name = fullnameText->GetValue();
    wxString imageFullName = logInImageUpload->getImageFullPath();
    // check if the name is empty
    wxString imageName;
    if (!imageFullName.IsEmpty()){
        imageName = imageFullName.AfterLast('\\');
    }
    else{
        imageName = wxString("");
    }
    std::cout << "Image Name: " << imageName << std::endl;
    // check if the name is empty
    if (name.IsEmpty())
    {
        wxMessageBox(wxString("Please enter your name"), wxString("Error"), wxICON_ERROR);
    } else
    {
        // save the name to the database
        // get the database connection
        sqlite3 *db;
        int rc = sqlite3_open(myDocRootPathConfig.ToStdString().c_str(), &db);
        if (rc)
        {
            wxMessageBox(wxString("Cannot open database"), wxString("Error"), wxICON_ERROR);
        } else
        {
            // add the name to the database
            std::string sql;
            if (!imageName.IsEmpty()){
                sql = "INSERT INTO teacher (fullname, image) VALUES ('" + name.ToStdString() + "', '" + imageName.ToStdString() + "')";
            } else{
                sql = "INSERT INTO teacher (fullname) VALUES ('" + name.ToStdString() + "')";
            }
            rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
            if (rc)
            {
                wxMessageBox("Your Data wasn't saved, Query didn't execute successfully.", "Error", wxICON_ERROR);
            } else
            {
                if (!imageName.IsEmpty()){
                    // copy the image to myDocRootPath
                    wxString myDocRootPathImage = myDocRoot.Append(wxString("\\") + imageName);
                    std::cout << "Copying to " << myDocRootPathImage.ToStdString() << std::endl;
                    if (!wxCopyFile(imageFullName, myDocRootPathImage)) {
                        wxMessageBox("Your Image wasn't saved, Image didn't copy successfully.", "Error", wxICON_ERROR);
                    }
                }
                // get the id of the new teacher
                int id = sqlite3_last_insert_rowid(db);
                // close the database
                sqlite3_close(db);
                MainFrame *mainFrame = new MainFrame( appNameFull, wxDefaultPosition, wxDefaultSize );
                mainFrame->SetIcon( wxIcon(wxT("resources/images/ams-logo-small.png")) );
                mainFrame->Show( true );
                this->Hide();
            }
        }
    }
}