#include <MainFrame.h>

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
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
    menuBar->Append( fileMenu, "&File" );
    menuBar->Append( helpMenu, "&Help" );
    SetMenuBar( menuBar );
    // status bar
    CreateStatusBar();
    SetStatusText( "This is a status bar" );
    // create a panel
    wxPanel *mainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(400, 300));

    wxPanel *newPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(300, 100));

    mainPanel->SetBackgroundColour(wxColour(255, 205, 255));
    newPanel->SetBackgroundColour(wxColour(255, 5, 255));
    // create a sizer
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(mainPanel, 1, wxEXPAND | wxALL, 5);
    vbox->Add(newPanel, 1, wxEXPAND | wxALL, 10);
    this->SetSizerAndFit(vbox);
}
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "This is a wxWidgets' Hello world sample",
                  "About Hello World", wxOK | wxICON_INFORMATION );
}
void MainFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}