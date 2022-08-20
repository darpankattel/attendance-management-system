#include <CreateStudentForm.h>
#include <ImageView.h>
#include <Config.h>
#include <Query.h>
#include <cstring>
extern wxString myDocRootPathDb;

wxTextCtrl* FormNameText;
wxChoice* FormClassChoice;
wxTextCtrl* FormRollNoText;
CreateStudentForm::CreateStudentForm(wxWindow *parent, wxPoint pos, wxSize size, wxString &title, wxString &defaultImage, wxBitmapType type)
: wxFrame(parent, wxID_ANY, title, pos, size)
{
    this->pos = pos;
    this->size = size;
    this->defaultImage = defaultImage;
    this->imagePath = defaultImage;
    this->type = type;
    this->SetBackgroundColour(wxColor(255, 255, 255));

    Query* query = new Query(myDocRootPathDb);
    sqlite3_stmt* stmt = query->execute("SELECT * FROM class");
    int length = query->length(stmt);


    wxString choices[length];

    int i = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        wxString name = wxString((const char*)sqlite3_column_text(stmt, 1));
        *(choices+i) = name;
        i++;
    }

    wxPanel* FormPanel = new wxPanel(this, wxID_ANY, wxPoint(0,0), wxSize(400, 500));
    wxPanel* imageContainer = new wxPanel(FormPanel, wxID_ANY, wxPoint(0, 0), wxSize(400, 110));
    ImageView* studentImage = new ImageView(imageContainer, wxPoint(150-30,5), wxSize(100, 100), defaultImage, type);
    studentImage->SetBackgroundColor(wxColor(255, 255, 255));
    wxStaticText* FormTitle = new wxStaticText(FormPanel, wxID_ANY, wxString("Create a Student"), wxPoint(0,0), wxSize(400, 30), wxALIGN_CENTER);
    FormTitle->SetFont(wxFont(22, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    wxStaticText* FormName = new wxStaticText(FormPanel, wxID_ANY, wxString("Name"), wxPoint(0,30), wxSize(400, 30));
    FormNameText = new wxTextCtrl(FormPanel, wxID_ANY, wxString(""), wxPoint(0,60), wxSize(400, 30));

    wxStaticText* FormClass = new wxStaticText(FormPanel, wxID_ANY, wxString("Class"), wxPoint(0,90), wxSize(400, 30));
    FormClassChoice = new wxChoice(FormPanel, wxID_ANY, wxPoint(0,120), wxSize(400, 30), length, choices);

    wxStaticText* FormRollNo = new wxStaticText(FormPanel, wxID_ANY, wxString("Roll No.:"), wxPoint(0,150), wxSize(400, 30));
    FormRollNoText = new wxTextCtrl(FormPanel, wxID_ANY, wxString(""), wxPoint(0,180), wxSize(400, 30));

    wxButton* FormSubmit = new wxButton(FormPanel, wxID_ANY, wxString("Create"), wxPoint(0,210), wxSize(400, 30));
    FormSubmit->SetCursor(wxCURSOR_HAND);
    wxButton* FormCancel = new wxButton(FormPanel, wxID_ANY, wxString("Cancel"), wxPoint(0,240), wxSize(400, 30));
    FormCancel->SetCursor(wxCURSOR_HAND);
    FormSubmit->Bind(wxEVT_BUTTON, &CreateStudentForm::OnSubmit, this);
    FormCancel->Bind(wxEVT_BUTTON, &CreateStudentForm::OnCancel, this);

    wxBoxSizer* FormSizer = new wxBoxSizer(wxVERTICAL);
    FormSizer->Add(FormTitle, 0, wxALL | wxALIGN_CENTER, 5);
    FormSizer->Add(imageContainer, 0, wxALL | wxALIGN_CENTER, 5);
    FormSizer->Add(FormName, 0, wxALL, 1);
    FormSizer->Add(FormNameText, 0, wxALL, 1);
    FormSizer->Add(FormClass, 0, wxALL, 1);
    FormSizer->Add(FormClassChoice, 0, wxALL, 1);
    FormSizer->Add(FormRollNo, 0, wxALL, 1);
    FormSizer->Add(FormRollNoText, 0, wxALL, 1);
    FormSizer->Add(FormSubmit, 0, wxALL, 2);
    FormSizer->Add(FormCancel, 0, wxALL, 2);
    FormPanel->SetSizer(FormSizer);
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(FormPanel, 1, wxALL | wxEXPAND, 15);
    this->SetSizer(mainSizer);
}

void CreateStudentForm::OnSubmit(wxCommandEvent& event)
{
    wxString name = FormNameText->GetValue();
    wxString className = FormClassChoice->GetStringSelection();
    std::cout<<className<<std::endl;
    wxString rollNo = FormRollNoText->GetValue();
    if(name.IsEmpty() || className.IsEmpty() || rollNo.IsEmpty())
    {
        wxMessageBox("Please fill all the fields");
        return;
    }
    Query *query = new Query(myDocRootPathDb);
    sqlite3_stmt* stmtClass = query->execute("Select * from class where name = '"+className+"'");
    int classId;
    while (sqlite3_step(stmtClass) == SQLITE_ROW)
    {
        classId = sqlite3_column_int(stmtClass, 0);
    }
    std::cout<<classId<<std::endl;
    wxString sql = "INSERT INTO student (name, class_id, roll_no) VALUES ('" + name + "', " + std::to_string(classId) + ", '" + rollNo + "')";
    query->query(sql);
    wxMessageBox("Student Created");
    query->close();
    this->Close();
}

void CreateStudentForm::OnSubmitScript(wxCommandEvent& event)
{
    const int no = 15;
    wxString names[no] = {"Darpan Kattel", "Ashreem Pandey", "Bishnu Datt Badu", "Vivek Sunar", "Darshan Koirala", "Javed Ansari", "Manish Kunwar", "Mandeep Thapa", "Lokesh Pandey", "Madhav Pd. Parajuli", "Mr. Madhu", "Divya Shankat Karki", "Bibek Niraula", "Biraj Kumar Karanjit", "Biraj Khatiwada"};
    wxString classNames[no] = {"1", "1", "1", "1", "1", "1", "1", "1", "1","1", "1", "1", "1", "1", "1"};
    wxString rollNos[no] = {"077BCT001", "077BCT002", "077BCT003", "077BCT004", "077BCT005", "077BCT006", "077BCT007", "077BCT008", "077BCT009", "077BCT010", "077BCT011", "077BCT012", "077BCT013", "077BCT014", "077BCT015"};
    for(int i = 0; i < no; i++)
    {
        wxString sql = "INSERT INTO student (name, class_id, roll_no) VALUES ('" + names[i] + "', " + classNames[i] + ", '" + rollNos[i] + "')";
        Query *query = new Query(myDocRootPathDb);
        query->query(sql);
        query->close();
    }
    wxMessageBox("Student Created");
}

void CreateStudentForm::OnCancel(wxCommandEvent& event)
{
    this->Close();
}