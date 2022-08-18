#include <CreateForm.h>
#include <ImageView.h>
#include <Config.h>
#include <Query.h>
extern wxString myDocRootPathDb;

wxTextCtrl* FormNameText;
wxTextCtrl* FormClassText;
wxTextCtrl* FormRollNoText;
CreateForm::CreateForm(wxWindow *parent, wxPoint pos, wxSize size, wxString &title, wxString &defaultImage, wxBitmapType type)
: wxFrame(parent, wxID_ANY, title, pos, size)
{
    this->pos = pos;
    this->size = size;
    this->defaultImage = defaultImage;
    this->imagePath = defaultImage;
    this->type = type;
    this->SetBackgroundColour(wxColor(255, 255, 255));
    wxPanel* FormPanel = new wxPanel(this, wxID_ANY, wxPoint(0,0), wxSize(400, 500));
    ImageView* studentImage = new ImageView(FormPanel, wxPoint(0,0), wxSize(100, 100), defaultImage, type);
    studentImage->SetBackgroundColor(wxColor(255, 255, 255));
    wxStaticText* FormTitle = new wxStaticText(FormPanel, wxID_ANY, wxString("Create a Student"), wxPoint(0,0), wxSize(400, 30));
    FormTitle->SetFont(wxFont(22, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    wxStaticText* FormName = new wxStaticText(FormPanel, wxID_ANY, wxString("Name"), wxPoint(0,30), wxSize(400, 30));
    FormNameText = new wxTextCtrl(FormPanel, wxID_ANY, wxString(""), wxPoint(0,60), wxSize(400, 30));
    wxStaticText* FormClass = new wxStaticText(FormPanel, wxID_ANY, wxString("Class"), wxPoint(0,90), wxSize(400, 30));
    FormClassText = new wxTextCtrl(FormPanel, wxID_ANY, wxString(""), wxPoint(0,120), wxSize(400, 30));
    wxStaticText* FormRollNo = new wxStaticText(FormPanel, wxID_ANY, wxString("Roll No.:"), wxPoint(0,150), wxSize(400, 30));
    FormRollNoText = new wxTextCtrl(FormPanel, wxID_ANY, wxString(""), wxPoint(0,180), wxSize(400, 30));

    wxButton* FormSubmit = new wxButton(FormPanel, wxID_ANY, wxString("Create"), wxPoint(0,210), wxSize(400, 30));
    FormSubmit->SetCursor(wxCURSOR_HAND);
    wxButton* FormCancel = new wxButton(FormPanel, wxID_ANY, wxString("Cancel"), wxPoint(0,240), wxSize(400, 30));
    FormSubmit->SetCursor(wxCURSOR_HAND);
    FormSubmit->Bind(wxEVT_BUTTON, &CreateForm::OnSubmit, this);
    FormCancel->Bind(wxEVT_BUTTON, &CreateForm::OnCancel, this);

    wxBoxSizer* FormSizer = new wxBoxSizer(wxVERTICAL);
    FormSizer->Add(FormTitle, 1, wxALL | wxEXPAND | wxALIGN_CENTER, 5);
    studentImage->setSizerCustom(FormSizer, 0, wxALL, 5);
    FormSizer->Add(FormName, 0, wxALL, 1);
    FormSizer->Add(FormNameText, 0, wxALL, 1);
    FormSizer->Add(FormClass, 0, wxALL, 1);
    FormSizer->Add(FormClassText, 0, wxALL, 1);
    FormSizer->Add(FormRollNo, 0, wxALL, 1);
    FormSizer->Add(FormRollNoText, 0, wxALL, 1);
    FormSizer->Add(FormSubmit, 0, wxALL, 2);
    FormSizer->Add(FormCancel, 0, wxALL, 2);
    FormPanel->SetSizer(FormSizer);
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(FormPanel, 1, wxALL | wxEXPAND, 15);
    this->SetSizer(mainSizer);
}

void CreateForm::OnSubmit(wxCommandEvent& event)
{
    wxString name = FormNameText->GetValue();
    wxString className = FormClassText->GetValue();
    wxString rollNo = FormRollNoText->GetValue();
    if(name.IsEmpty() || className.IsEmpty() || rollNo.IsEmpty())
    {
        wxMessageBox("Please fill all the fields");
        return;
    }
    wxString sql = "INSERT INTO students (name, class, roll_no) VALUES ('" + name + "', '" + className + "', '" + rollNo + "')";
    Query *query = new Query(myDocRootPathDb);
    query->query(sql);
    wxMessageBox("Student Created");
    query->close();
    this->Close();
}

void CreateForm::OnSubmitScript(wxCommandEvent& event)
{
    wxString names[12] = {"Ashreem Pandey", "Bishnu Datt Badu", "Vivek Sunar", "Darshan Koirala", "Javed Ansari", "Manish Kunwar", "Mandeep Thapa", "Lokesh Pandey", "Madhav Pd. Parajuli", "Mr. Madhu", "Divya Shankat Karki", "Bibek Niraula"};
    wxString classNames[12] = {"077BCT", "077BCT", "077BCT", "077BCT", "077BCT", "077BCT", "077BCT", "077BCT", "077BCT","077BCT", "077BCT", "077BCT"};
    wxString rollNos[12] = {"077BCT001", "077BCT002", "077BCT003", "077BCT004", "077BCT005", "077BCT006", "077BCT007", "077BCT008", "077BCT009", "077BCT010", "077BCT011", "077BCT012"};
    for(int i = 0; i < 12; i++)
    {
        wxString sql = "INSERT INTO students (name, class, roll_no) VALUES ('" + names[i] + "', '" + classNames[i] + "', '" + rollNos[i] + "')";
        Query *query = new Query(myDocRootPathDb);
        query->query(sql);
        query->close();
    }
    wxMessageBox("Student Created");
}

void CreateForm::OnCancel(wxCommandEvent& event)
{
    this->Close();
}


