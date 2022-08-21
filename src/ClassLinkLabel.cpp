#include <ClassLinkLabel.h>
#include <Config.h>
#include <Query.h>
#include <Student.h>
#include <TopStatusBar.h>
extern wxColor* primaryColor;
extern wxColor* primaryWhite;

ClassLinkLabel::ClassLinkLabel(wxWindow *parent, wxWindowID id, wxString className, const wxPoint& pos, const wxSize& size, wxString classId)
: wxButton(parent, id, className, pos, size)
{
    this->className = className;
    this->classId = classId;

    wxButton::SetWindowStyle(wxBORDER_NONE);
    wxButton::SetBackgroundColour(*primaryColor);
    wxButton::SetForegroundColour(*primaryWhite);
    wxButton::SetCursor(wxCURSOR_HAND);
    // border
    wxButton::SetWindowStyle(wxBORDER_NONE);
    // change font size only
    wxFont font = wxButton::GetFont();
    font.SetPointSize(font.GetPointSize() + 2);
    wxButton::SetFont(font);
    // on click
    wxButton::Bind(wxEVT_BUTTON, &ClassLinkLabel::OnClick, this);

}

// void giveControl(){}

void ClassLinkLabel::OnClick(wxCommandEvent& event)
{
    wxString newClassName = this->className;
    wxString newClassId = this->classId;
    std::cout<<"received class id: "<<newClassId<< " received class name: "<< newClassName <<std::endl;
    controllingWindow->DestroyChildren();
    std::cout<<"show student window"<<std::endl;
    wxScrolledWindow *window = controllingWindow;
    Query *query = new Query(myDocRootPathDb);
    wxString sql = "SELECT * FROM student WHERE class_id = " + newClassId.ToStdString();
    std::cout<<"sql: "<<sql<<std::endl;
    sqlite3_stmt* stmt = query->execute(sql);
    int rows = query->length(stmt);
    std::cout<<"returned rows: "<<rows<<std::endl;
    window->SetSize(wxSize(680, rows*85+40));
    std::cout<<"set size [past], configuring topStatusBar"<<std::endl;
    std::cout<<newClassId<<newClassName<<std::endl;
    
    topStatusBar->setTitle(newClassName);
    topStatusBar->setFirstLabelTitle(wxString("No. of Students"));
    topStatusBar->setFirstLabelValue(wxString(std::to_string(rows)));
    topStatusBar->setSecondLabelTitle(wxString("Below 70%"));
    topStatusBar->setSecondLabelValue(wxString("0"));
    std::cout<<"If else approached"<<std::endl;
    if (rows > 0)
    {
        window->SetScrollbars(10, 10, 1, 1);
        Student *studentPanel = new Student(window, wxID_ANY, wxDefaultPosition, wxSize(680, rows*85+20), query, stmt);
        studentPanel->SetBackgroundColour(wxColor(240, 240, 240));
        wxBoxSizer* mainContentSizer = new wxBoxSizer(wxVERTICAL);
        mainContentSizer->Add(studentPanel, 1, wxEXPAND);
        window->SetSizer(mainContentSizer);
    }
    else
    {
        wxStaticText *noStudentLabel = new wxStaticText(window, wxID_ANY, "No Students Found", wxDefaultPosition, wxSize(680, 50));
        noStudentLabel->SetForegroundColour(wxColor(255, 0, 0));
        // font only set
        wxFont font = noStudentLabel->GetFont();
        font.SetPointSize(font.GetPointSize() + 2);
        noStudentLabel->SetFont(font);
        wxBoxSizer* mainContentSizer = new wxBoxSizer(wxVERTICAL);
        mainContentSizer->Add(noStudentLabel, 1, wxEXPAND | wxALL, 10);
        window->SetSizer(mainContentSizer);
    }
    // update window
    topStatusBar->wxPanel::Update();
    topStatusBar->wxPanel::Refresh();
    window->Layout();
    window->Refresh();
    window->Update();
    wxWindow *mainAppWindow = window->GetParent();
    mainAppWindow->Layout();
    mainAppWindow->Refresh();
    mainAppWindow->Update();
}

void ClassLinkLabel::setControllingWindow(wxScrolledWindow *window)
{
    this->controllingWindow = window;
}

void ClassLinkLabel::setTopStatusBar(TopStatusBar *statusBar)
{
    this->topStatusBar = statusBar;
}