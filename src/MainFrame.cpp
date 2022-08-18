#include <MainFrame.h>
#include <Config.h>
#include <ImageView.h>
#include <sqlite3.h>
#include <Student.h>
#include <Query.h>
#include <Button.h>
extern wxColor *primaryBlack;
extern wxColor *primaryWhite;
extern wxColor *primaryGrey;
extern std::string appName;
extern wxString* defaultUserImage;

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
    wxPanel *mainContainer = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(900, 600));

    wxPanel *navPanel = new wxPanel(mainContainer, wxID_ANY, wxDefaultPosition, wxSize(200, 600));
    wxPanel *contentPanel = new wxPanel(mainContainer, wxID_ANY, wxDefaultPosition, wxSize(700, 600));

    wxPanel *topStatusBar = new wxPanel(contentPanel, wxID_ANY, wxDefaultPosition, wxSize(700, 60));
    topStatusBar->SetBackgroundColour(*primaryGrey);

    // wxPanel *mainContentPanel = new wxPanel(contentPanel, wxID_ANY, wxDefaultPosition, wxSize(700, 600));

    Query *query = new Query(myDocRootPathDb);
    wxString sql = "SELECT * FROM students";
    sqlite3_stmt* stmt = query->execute(sql);
    int rows = query->length(stmt);

    wxScrolledWindow *mainContentPanel = new wxScrolledWindow(contentPanel, wxID_ANY, wxDefaultPosition, wxSize(680, rows*85+20));
    mainContentPanel->SetScrollbars(10, 10, 1, 1);

    Student *studentPanel = new Student(mainContentPanel, wxID_ANY, wxDefaultPosition, wxSize(680, rows*85+20), query, stmt);


    //sizer
    wxBoxSizer* contentSizer = new wxBoxSizer(wxVERTICAL);
    contentSizer->Add(topStatusBar, 0, wxEXPAND);
    contentSizer->Add(mainContentPanel, 1, wxEXPAND);
    contentPanel->SetSizer(contentSizer);


    wxBoxSizer* mainContentSizer = new wxBoxSizer(wxVERTICAL);
    mainContentSizer->Add(studentPanel, 1, wxEXPAND);
    mainContentPanel->SetSizer(mainContentSizer);

    
    this->SetBackgroundColour(wxColour(255, 255, 255));
    navPanel->SetBackgroundColour(*primaryBlack);
    contentPanel->SetBackgroundColour(wxColour(255, 98, 29));

    wxStaticText *navAppText = new wxStaticText(navPanel, wxID_ANY, wxString(appName), wxDefaultPosition, wxSize(200, 40), wxALIGN_CENTER, wxString("Arial"));
    // navAppText->SetBackgroundColour(wxColour(0, 255, 255));
    navAppText->SetForegroundColour(wxColour(255, 255, 255));
    navAppText->SetFont(wxFont(16, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
    
    wxPanel *navButtonContainer = new wxPanel(navPanel, wxID_ANY, wxDefaultPosition, wxSize(200, 500));
    
    // nav buttons
    Button *homeButton = new Button(navButtonContainer, wxID_ANY, wxString("Home"), wxPoint(0, 0), wxSize(200, 40));
    Button *profileButton = new Button(navButtonContainer, wxID_ANY, wxString("Classes"), wxPoint(0, 40), wxSize(200, 40));
    Button *settingsButton = new Button(navButtonContainer, wxID_ANY, wxString("Settings"), wxPoint(0, 80), wxSize(200, 40));
    Button *logOutButton = new Button(navButtonContainer, wxID_ANY, wxString("About"), wxPoint(0, 120), wxSize(200, 40));
    


    // bottom
    wxPanel *navBottomContainer = new wxPanel(navPanel, wxID_ANY, wxDefaultPosition, wxSize(200, 60));
    navBottomContainer->SetBackgroundColour(*primaryGrey);


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
    navBottomLeftImageView->SetBackgroundColor(*primaryGrey);

    wxPanel *navBottomRightContainer = new wxPanel(navBottomContainer, wxID_ANY, wxPoint(0, 10), wxSize(150, 60));

    

    wxStaticText *navBottomTeacherName = new wxStaticText(navBottomRightContainer, wxID_ANY, wxString(teacherName), wxPoint(0, 0), wxSize(200, 20), wxALIGN_LEFT, wxString("Arial"));
    navBottomTeacherName->SetBackgroundColour(*primaryGrey);
    navBottomTeacherName->SetForegroundColour(*primaryBlack);
    navBottomTeacherName->SetFont(wxFont(14, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_SEMIBOLD));

    wxStaticText *navBottomTeacherPost = new wxStaticText(navBottomRightContainer, wxID_ANY, wxString("Teacher"), wxPoint(0, 20), wxSize(200, 20), wxALIGN_LEFT, wxString("Arial"));
    navBottomTeacherPost->SetBackgroundColour(*primaryGrey);
    navBottomTeacherPost->SetForegroundColour(*primaryBlack);
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
    navSizer->Add(navAppText, 0, wxEXPAND | wxTOP, 15);
    navSizer->Add(navButtonContainer, 1, wxEXPAND | wxBOTTOM, 10);
    navSizer->Add(navBottomContainer, 0, wxEXPAND);
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