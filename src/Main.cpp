#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <sqlite3.h>

#include <MainFrame.h>
#include <LogInFrame.h>
#include <Config.h>
#include <fstream>
#include <wx/stdpaths.h>
#include <CreateForm.h>
extern std::string appNameFull;
extern std::string appName;
extern wxString* teacherFullname;
extern wxString* teacherImage;
extern wxString* defaultStudentImage;

extern wxString myDocRoot;
extern wxString myDocRootPath;
extern wxString myDocRootPathConfig;
extern wxString myDocRootPathDb;


class App: public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(App);
bool App::OnInit()
{
    wxImage::AddHandler(new wxPNGHandler);
    wxImage::AddHandler(new wxJPEGHandler);
    
    myDocRoot = wxStandardPaths::Get().GetDocumentsDir();
    myDocRootPath = myDocRoot + "\\" + wxString(appName);
    myDocRootPathConfig = myDocRootPath + "\\userdata.db";
    myDocRootPathDb = myDocRootPath + "\\studentdata.db";

    // connect to sqlite database
    sqlite3 *db;
    int rc = sqlite3_open(myDocRootPathConfig.ToStdString().c_str(), &db);
    if (rc)
    {
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        try{
            // create the database file
            std::ofstream {myDocRootPathConfig.ToStdString()};
            // connect to database
            std::cout << "Created database..." << std::endl;
            rc = sqlite3_open(myDocRootPathConfig.ToStdString().c_str(), &db);
            if (rc)
            {
                std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
                wxMessageBox("Error creating/opening database, tried 2 times.", "Error", wxICON_ERROR);
                sqlite3_close(db);
                return false;
            }
        } catch (...) {
            wxMessageBox("Unknown error while creating database.", "Error", wxICON_ERROR);
            return false;
        }
    }
    // create table if it doesn't exist
    std::string sql = "CREATE TABLE IF NOT EXISTS teacher (id INTEGER PRIMARY KEY AUTOINCREMENT, fullname TEXT, image TEXT)";
    rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
    if (rc != SQLITE_OK)
    {
        std::cout << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        wxMessageBox("Error creating table.", "Error", wxICON_ERROR);
        sqlite3_close(db);
        return false;
    }

    // get the teacher's full name and image
    sql = "SELECT fullname, image FROM teacher";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        std::cout << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        wxMessageBox("Error preparing 'SELECT teacher' statement.", "Error", wxICON_ERROR);
        sqlite3_close(db);
        return false;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        // teacherFullname = new wxString(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        // teacherImage = new wxString(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));

        std::string fullname = (char*)sqlite3_column_text(stmt, 0);
        std::string image = (char*)sqlite3_column_text(stmt, 1);
        teacherFullname = new wxString(fullname.c_str());
        teacherImage = new wxString(image.c_str());

        std::cout << "Teacher: " << fullname << " " << image << std::endl;

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        MainFrame *mainFrame = new MainFrame( appNameFull, wxDefaultPosition, wxDefaultSize );
        mainFrame->SetIcon( wxIcon(wxT("resources/images/ams-logo-small.png")) );
        mainFrame->Show( true );
        
        // wxString StudentTitle = appName+" - Create Student";
        // CreateForm *CreateStudentForm = new CreateForm(NULL, wxDefaultPosition, wxSize(400, 500), StudentTitle, *defaultStudentImage, wxBITMAP_TYPE_PNG);
        // // disable maximize button
        // CreateStudentForm->Maximize(false);
        // CreateStudentForm->Show(true);

        return true;
    }
    

    LogInFrame *logInFrame = new LogInFrame( appNameFull, wxDefaultPosition, wxDefaultSize );
    logInFrame->SetIcon( wxIcon(wxT("resources/images/ams-logo-small.png")) );
    logInFrame->Show( true );

    return true;
}

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(ID_ONE,   MainFrame::OnHello)
    EVT_MENU(wxID_EXIT,  MainFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
wxEND_EVENT_TABLE()