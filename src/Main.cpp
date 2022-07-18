#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <MainFrame.h>
#include <LogInFrame.h>
#include <Config.h>
extern std::string appNameFull;

class App: public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(App);
bool App::OnInit()
{
    wxImage::AddHandler(new wxPNGHandler);

    MainFrame *mainFrame = new MainFrame( appNameFull, wxDefaultPosition, wxDefaultSize );
    mainFrame->SetIcon( wxIcon(wxT("resources/images/ams-logo-small.png")) );
    mainFrame->Show( true );

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