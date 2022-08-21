#include <MainFrame.h>
#include <Config.h>
#include <ImageView.h>
#include <sqlite3.h>
#include <Student.h>
#include <Query.h>
#include <Button.h>
#include <TopStatusBar.h>
#include <wx/treectrl.h>


extern wxColor *primaryBlack;
extern wxColor *primaryWhite;
extern wxColor *primaryGrey;
extern wxColor *tertiaryColor;

extern std::string appName;
extern wxString* defaultUserImage;
extern wxString* newLogo;

extern wxString myDocRoot;
extern wxString myDocRootPath;
extern wxString myDocRootPathConfig;
// extern wxString myDocRootPathLogIn;

MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    // file menu
    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(ID_ONE, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT);
    // help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT);
    // menubar
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");
    SetMenuBar(menuBar);
    // status bar
    CreateStatusBar();
    SetStatusText("This is a status bar");
    // create a panel
    wxPanel *mainContainer = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(900, 680));

    wxPanel *navPanel = new wxPanel(mainContainer, wxID_ANY, wxDefaultPosition, wxSize(200, 600));
    wxPanel *contentPanel = new wxPanel(mainContainer, wxID_ANY, wxDefaultPosition, wxSize(700, 600));

    TopStatusBar *topStatusBar = new TopStatusBar(contentPanel, wxID_ANY, wxDefaultPosition, wxSize(700, 80));
    topStatusBar->wxPanel::SetBackgroundColour(*primaryWhite);


    wxScrolledWindow *mainContentPanel = new wxScrolledWindow(contentPanel, wxID_ANY, wxDefaultPosition, wxSize(680, 600));
    mainContentPanel -> SetBackgroundColour(wxColor(240, 240, 240));
    //sizer
    wxBoxSizer* contentSizer = new wxBoxSizer(wxVERTICAL);
    contentSizer->Add(topStatusBar, 0, wxEXPAND);
    contentSizer->Add(mainContentPanel, 1, wxEXPAND | wxTOP, 10);
    contentPanel->SetSizer(contentSizer);

    
    this->SetBackgroundColour(wxColour(240, 240, 240));
    navPanel->SetBackgroundColour(*primaryColor);

    wxPanel *navAppTextPanel = new wxPanel(navPanel, wxID_ANY, wxPoint(0, 50), wxSize(200, 80));
    navAppTextPanel->SetBackgroundColour(*tertiaryColor);

    ImageView *navAppLogo = new ImageView(navAppTextPanel, wxPoint(0, 0), wxSize(40, 40), *newLogo, wxBITMAP_TYPE_PNG);

    wxStaticText *navAppText = new wxStaticText(navAppTextPanel, wxID_ANY, wxString(appName), wxPoint(10, 45), wxSize(200, 30), wxALIGN_CENTER, wxString("Arial"));
    navAppText->SetForegroundColour(*primaryWhite);
    navAppText->SetFont(wxFont(16, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));

    wxBoxSizer *navAppTextSizer = new wxBoxSizer(wxVERTICAL);
    navAppLogo->setSizerCustom(navAppTextSizer, 1, wxEXPAND | wxTOP, 5);
    navAppTextSizer->Add(navAppText, 1, wxEXPAND | wxTOP | wxBOTTOM, 5);
    navAppTextPanel->SetSizer(navAppTextSizer);

    
    wxPanel *navButtonContainer = new wxPanel(navPanel, wxID_ANY, wxDefaultPosition, wxSize(200, 500));
    
    // nav buttons
    Button *homeButton = new Button(navButtonContainer, wxWindowID(12), wxString("Home"), wxPoint(0, 0), wxSize(200, 40), wxALIGN_LEFT, wxString("resources/images/home-inverted.png"));
    homeButton->SetBackgroundColour(*primaryColor);
    homeButton->setControllingWindow(mainContentPanel);
    homeButton->setTopStatusBar(topStatusBar);
    homeButton->ShowYourWindow();

    Button *classButton = new Button(navButtonContainer, wxWindowID(13), wxString("Classes"), wxPoint(0, 40), wxSize(200, 40), wxALIGN_LEFT, wxString("resources/images/class-inverted.png"));
    classButton->setControllingWindow(mainContentPanel);
    classButton->setTopStatusBar(topStatusBar);

    Button *settingsButton = new Button(navButtonContainer, wxWindowID(14), wxString("Settings"), wxPoint(0, 80), wxSize(200, 40), wxALIGN_LEFT, wxString("resources/images/settings-inverted.png"));
    settingsButton->setControllingWindow(mainContentPanel);
    settingsButton->setTopStatusBar(topStatusBar);

    Button *aboutButton = new Button(navButtonContainer, wxWindowID(15), wxString("About"), wxPoint(0, 120), wxSize(200, 40), wxALIGN_LEFT, wxString("resources/images/about-inverted.png"));
    aboutButton->setControllingWindow(mainContentPanel);
    aboutButton->setTopStatusBar(topStatusBar);

    

    // bottom
    wxPanel *navPanelBottom = new wxPanel(navPanel, wxID_ANY, wxDefaultPosition, wxSize(200, 100));

    Button *logoutButton = new Button(navPanelBottom, wxWindowID(16), wxString("Logout"), wxPoint(0, 250), wxSize(200, 40), wxALIGN_LEFT, wxString("resources/images/logout-inverted.png"));

    wxPanel *navBottomContainer = new wxPanel(navPanelBottom, wxID_ANY, wxDefaultPosition, wxSize(200, 60));
    navBottomContainer->SetBackgroundColour(*tertiaryColor);

    wxBoxSizer *navPanelBottomSizer = new wxBoxSizer(wxVERTICAL);
    navPanelBottomSizer->Add(logoutButton, 0, wxEXPAND);
    navPanelBottomSizer->Add(navBottomContainer, 1, wxEXPAND);
    navPanelBottom->SetSizer(navPanelBottomSizer);

    wxPanel *navBottomLeftContainer = new wxPanel(navBottomContainer, wxID_ANY, wxPoint(0, 10), wxSize(50, 60));

    // get teacher name and image from .db file
    std::string teacherName;
    wxString teacherImage = *defaultUserImage;
    sqlite3 *db;
    int rc = sqlite3_open(myDocRootPathConfig.ToStdString().c_str(), &db);
    if (rc)
    {
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
    } else {
        std::cout << "Opened database successfully" << std::endl;
        std::string sql = "SELECT * FROM teacher";
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
        if (rc != SQLITE_OK)
        {
            std::cout << "Error: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
        } else {
            while (sqlite3_step(stmt) == SQLITE_ROW)
            {
                teacherName = (char*)sqlite3_column_text(stmt, 1);
                wxString teacherImagePath = wxString((char*)sqlite3_column_text(stmt, 2));
                teacherImage = wxString(myDocRootPath + "\\" + teacherImagePath);
                std::cout << "name: " << teacherName << std::endl;
                std::cout << "image: " << teacherImage << std::endl;
            }
            sqlite3_finalize(stmt);
            sqlite3_close(db);
        }
    }

    ImageView *navBottomLeftImageView = new ImageView(navBottomLeftContainer, wxDefaultPosition, wxSize(40, 40), teacherImage, wxBITMAP_TYPE_ANY);
    navBottomLeftImageView->SetBackgroundColor(*tertiaryColor);

    wxPanel *navBottomRightContainer = new wxPanel(navBottomContainer, wxID_ANY, wxPoint(0, 10), wxSize(150, 60));

    wxStaticText *navBottomTeacherName = new wxStaticText(navBottomRightContainer, wxID_ANY, wxString(teacherName), wxPoint(0, 0), wxSize(200, 20), wxALIGN_LEFT, wxString("Arial"));
    navBottomTeacherName->SetBackgroundColour(*tertiaryColor);
    navBottomTeacherName->SetForegroundColour(*primaryWhite);
    navBottomTeacherName->SetFont(wxFont(14, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_SEMIBOLD));

    wxStaticText *navBottomTeacherPost = new wxStaticText(navBottomRightContainer, wxID_ANY, wxString("Teacher"), wxPoint(0, 20), wxSize(200, 20), wxALIGN_LEFT, wxString("Arial"));
    navBottomTeacherPost->SetBackgroundColour(*tertiaryColor);
    navBottomTeacherPost->SetForegroundColour(*primaryWhite);
    navBottomTeacherPost->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_NORMAL));

    // sizer

    wxBoxSizer *bottomSizer = new wxBoxSizer(wxHORIZONTAL);
    bottomSizer->Add(navBottomLeftContainer, 1, wxLEFT | wxTOP | wxBOTTOM, 10);
    bottomSizer->Add(navBottomRightContainer, 6, wxEXPAND | wxTOP | wxBOTTOM, 10);
    navBottomContainer->SetSizer(bottomSizer);

    // create a sizer
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(mainContainer, 1, wxEXPAND);

    wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);
    mainSizer->Add(navPanel, 0, wxEXPAND);
    mainSizer->Add(contentPanel, 1, wxEXPAND);
    mainContainer->SetSizer(mainSizer);

    wxBoxSizer *navSizer = new wxBoxSizer(wxVERTICAL);
    navSizer->Add(navAppTextPanel, 0, wxEXPAND);
    navSizer->Add(navButtonContainer, 1, wxEXPAND | wxBOTTOM, 10);
    navSizer->Add(navPanelBottom, 0, wxEXPAND);
    // navSizer->Add(navBottomContainer, 0, wxEXPAND);
    navPanel->SetSizer(navSizer);
    // sizer->Add(navPanel, 1, wxEXPAND | wxALL, 10);
    this->SetSizerAndFit(sizer);
}
void MainFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}
void MainFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("This is a CPP project developed by team 3-QuBits, IOE Pulchowk Campus", "About", wxOK | wxICON_INFORMATION);
}
void MainFrame::OnHello(wxCommandEvent &event)
{
    wxLogMessage("Hello guys from 3-QuBits!");
}