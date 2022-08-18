#include <StudentView.h>
#include <ImageView.h>
#include <wx/tglbtn.h>
#include <StudentObject.h>

StudentView::StudentView(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, StudentObject* studentObject) : wxPanel(parent, id, pos, size)
{
    wxString defaultImage = "resources/images/student-circled.png";
    this->wxPanel::SetBackgroundColour(wxColor(255, 255, 225));

    wxPanel* buttonContainer = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 100));
    // buttonContainer->SetBackgroundColour(wxColor(0, 0, 255));

    ImageView *studentImageView = new ImageView(this, wxDefaultPosition, wxSize(60, 60), defaultImage, wxBITMAP_TYPE_ANY);

    wxPanel* studentInfoPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(250, 100));
    wxStaticText* studentNameLabel = new wxStaticText(studentInfoPanel, wxID_ANY, "Student Name: ", wxPoint(0, 0), wxSize(100, 20));
    wxStaticText* studentName = new wxStaticText(studentInfoPanel, wxID_ANY, studentObject->getName().ToStdString(), wxPoint(100, 0), wxSize(150, 20));

    wxStaticText* studentIdLabel = new wxStaticText(studentInfoPanel, wxID_ANY, "Roll No.: ", wxPoint(0, 20), wxSize(100, 20));
    wxStaticText* studentId = new wxStaticText(studentInfoPanel, wxID_ANY, studentObject->getRollNo(), wxPoint(100, 20), wxSize(150, 20));
    // wxStaticText* studentId = new wxStaticText(studentInfoPanel, wxID_ANY, studentObject->getRollNo().ToStdString(), wxPoint(100, 20), wxSize(100, 20));

    wxStaticText* studentClassLabel = new wxStaticText(studentInfoPanel, wxID_ANY, "Class: ", wxPoint(0, 40), wxSize(100, 20));
    wxStaticText* studentClass = new wxStaticText(studentInfoPanel, wxID_ANY, studentObject->getClassName(), wxPoint(100, 40), wxSize(150, 20));
    // wxStaticText* studentClass = new wxStaticText(studentInfoPanel, wxID_ANY, studentObject->getClassName().ToStdString(), wxPoint(100, 40), wxSize(100, 20));

    // wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    // sizer->Add(studentNameLabel, 0, wxALL, 5);
    // sizer->Add(studentIdLabel, 0, wxALL, 5);
    // sizer->Add(studentClassLabel, 0, wxALL, 5);
    // studentInfoPanel->SetSizer(sizer);

    wxPanel* rightPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(300, 100));
    // rightPanel->SetBackgroundColour(wxColor(255, 255, 255));

    wxStaticText* presencePercentageLabel = new wxStaticText(rightPanel, wxID_ANY, "Presence Percentage: ", wxPoint(30, 10), wxSize(120, 20));
    wxStaticText* presencePercentage = new wxStaticText(rightPanel, wxID_ANY, "100%", wxPoint(30, 30), wxSize(120, 20));
    presencePercentage->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxStaticText* presenceNumberLabel = new wxStaticText(rightPanel, wxID_ANY, "Presence: ", wxPoint(160, 10), wxSize(120, 20));
    wxStaticText* presenceNumber = new wxStaticText(rightPanel, wxID_ANY, "10", wxPoint(160, 30), wxSize(120, 70));
    presenceNumber->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    // toggle button
    wxToggleButton *toggleButton = new wxToggleButton(buttonContainer, wxID_ANY, "Mark Present", wxPoint(0, 25), wxSize(100, 30));
    toggleButton->SetValue(false);
    toggleButton->SetBackgroundColour(wxColor(0, 255, 0));
    toggleButton->SetCursor(wxCURSOR_HAND);
    toggleButton->Bind(wxEVT_TOGGLEBUTTON, &StudentView::onToggleButtonClick, this);


    //sizer
    wxBoxSizer* studentViewSizer = new wxBoxSizer(wxHORIZONTAL);
    studentImageView->setSizerCustom(studentViewSizer, 0, wxEXPAND, 5);
    studentViewSizer->Add(studentInfoPanel, 0, wxALL, 5);
    studentViewSizer->Add(buttonContainer, 0, wxEXPAND, 5);
    // studentViewSizer->Add(studentImageView, 0);
    studentViewSizer->Add(rightPanel, 0, wxEXPAND, 5);
    this->SetSizer(studentViewSizer);

}

void StudentView::OnPaint(wxPaintEvent& event)
{
    // draw rounded border
    wxPaintDC dc(this);
    dc.SetBrush(wxBrush(wxColor(255, 255, 225)));
    dc.SetPen(wxPen(wxColor(255, 255, 225), 1));
    dc.DrawRoundedRectangle(0, 0, this->GetSize().GetWidth(), this->GetSize().GetHeight(), 5);
    
}

void StudentView::onToggleButtonClick(wxCommandEvent& event)
{
    wxToggleButton *toggleButton = (wxToggleButton*)event.GetEventObject();
    if (toggleButton->GetValue())
    {
        toggleButton->SetBackgroundColour(wxColor(255, 0, 0));
        toggleButton->SetLabel("Mark Absent");
        toggleButton->SetForegroundColour(wxColor(255, 255, 255));
    }
    else
    {
        toggleButton->SetBackgroundColour(wxColor(0, 255, 0));
        toggleButton->SetLabel("Mark Present");
        toggleButton->SetForegroundColour(wxColor(0, 0, 0));
    }
}