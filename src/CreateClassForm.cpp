#include <CreateClassForm.h>
#include <ImageView.h>
#include <Config.h>
#include <Query.h>
extern wxString myDocRootPathDb;

wxTextCtrl* FormClassNameText;
CreateClassForm::CreateClassForm(wxWindow *parent, wxPoint pos, wxSize size, wxString &title, wxString &defaultImage, wxBitmapType type)
: wxFrame(parent, wxID_ANY, title, pos, size)
{
    this->pos = pos;
    this->size = size;
    this->defaultImage = defaultImage;
    this->imagePath = defaultImage;
    this->type = type;
    this->SetBackgroundColour(wxColor(255, 255, 255));
    wxPanel* FormPanel = new wxPanel(this, wxID_ANY, wxPoint(0,0), wxSize(400, 300));
    wxPanel* imageContainer = new wxPanel(FormPanel, wxID_ANY, wxPoint(0, 0), wxSize(400, 110));
    ImageView* studentImage = new ImageView(imageContainer, wxPoint(150-30,5), wxSize(100, 100), defaultImage, type);
    studentImage->SetBackgroundColor(wxColor(255, 255, 255));
    wxStaticText* FormTitle = new wxStaticText(FormPanel, wxID_ANY, wxString("Create a Class"), wxPoint(0,0), wxSize(400, 30), wxALIGN_CENTER);
    FormTitle->SetFont(wxFont(22, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    wxStaticText* FormName = new wxStaticText(FormPanel, wxID_ANY, wxString("Classname"), wxPoint(0,30), wxSize(400, 30));
    FormClassNameText = new wxTextCtrl(FormPanel, wxID_ANY, wxString(""), wxPoint(0,60), wxSize(400, 30));

    wxButton* FormSubmit = new wxButton(FormPanel, wxID_ANY, wxString("Create"), wxPoint(0,210), wxSize(400, 30));
    FormSubmit->SetCursor(wxCURSOR_HAND);
    wxButton* FormCancel = new wxButton(FormPanel, wxID_ANY, wxString("Cancel"), wxPoint(0,240), wxSize(400, 30));
    FormCancel->SetCursor(wxCURSOR_HAND);
    FormSubmit->Bind(wxEVT_BUTTON, &CreateClassForm::OnSubmit, this);
    FormCancel->Bind(wxEVT_BUTTON, &CreateClassForm::OnCancel, this);

    wxBoxSizer* FormSizer = new wxBoxSizer(wxVERTICAL);
    FormSizer->Add(FormTitle, 0, wxALL | wxALIGN_CENTER, 5);
    FormSizer->Add(imageContainer, 0, wxALL | wxALIGN_CENTER, 5);
    FormSizer->Add(FormName, 0, wxALL, 1);
    FormSizer->Add(FormClassNameText, 0, wxALL, 1);
    FormSizer->Add(FormSubmit, 0, wxTOP, 40);
    FormSizer->Add(FormCancel, 0, wxTOP, 2);
    FormPanel->SetSizer(FormSizer);
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(FormPanel, 1, wxALL | wxEXPAND, 15);
    this->SetSizer(mainSizer);
}

void CreateClassForm::OnSubmit(wxCommandEvent& event)
{
    wxString name = FormClassNameText->GetValue();
    if(name.IsEmpty())
    {
        wxMessageBox("Please fill all the fields");
        return;
    }
    wxString sql = "INSERT INTO class (name) VALUES ('" + name + "')";
    Query *query = new Query(myDocRootPathDb);
    query->query(sql);
    wxMessageBox("Class Created");
    query->close();
    this->Close();
}

void CreateClassForm::OnSubmitScript(wxCommandEvent& event)
{
    const int no = 15;
    wxString names[no] = {"077BEIAB", "077BEICD", "076BCTAB", "076BCTCD", "075BCTAB", "075BCTCD", "074BCTAB", "074BCTCD", "073BCTAB", "073BCTCD", "072BCTAB", "072BCTCD", "071BCTAB", "071BCTCD"};
    for(int i = 0; i < no; i++)
    {
        wxString sql = "INSERT INTO class (name) VALUES ('" + names[i] + "')";
        Query *query = new Query(myDocRootPathDb);
        query->query(sql);
        query->close();
    }
    wxMessageBox("Classes Created");
}

void CreateClassForm::OnCancel(wxCommandEvent& event)
{
    this->Close();
}