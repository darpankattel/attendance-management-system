#include <Student.h>
#include <StudentView.h>
#include <Config.h>
#include <fstream>
#include <Query.h>
#include <StudentObject.h>
extern wxColor* primaryGrey;
extern wxString myDocRootPathDb;

Student::Student(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, Query* query, sqlite3_stmt* stmt) : wxPanel(parent, id, pos, size)
{
    int rows = query->length(stmt);
    if (stmt == NULL)
    {
        wxMessageBox("Error executing query.", "Error", wxICON_ERROR);
        return;
    }
    StudentObject *studentObject = new StudentObject[rows];
    int i = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        wxString id = sqlite3_column_text(stmt, 0);
        wxString name = sqlite3_column_text(stmt, 1);

        wxString classId = sqlite3_column_text(stmt, 2);
        wxString sql = "SELECT name FROM class WHERE id = " + classId.ToStdString();
        std::cout << sql << std::endl;
        sqlite3_stmt *stmt2 = query->execute(sql);
        if (stmt2 == NULL)
        {
            wxMessageBox("Error executing query.", "Error", wxICON_ERROR);
            return;
        }
        wxString className;
        while (sqlite3_step(stmt2) == SQLITE_ROW)
        {
            className = sqlite3_column_text(stmt2, 0);
        }
        std::cout << className << std::endl;
        sqlite3_finalize(stmt2);

        wxString roll_no = sqlite3_column_text(stmt, 3);
        studentObject[i].setName(name);
        studentObject[i].setId(id);
        studentObject[i].setRollNo(roll_no);
        studentObject[i].setClassName(className);
        i++;
    }
    query->close();

    const int noOfStudents = rows;
    this->wxPanel::SetBackgroundColour(wxColor(255, 255, 255));
    // parent->SetSize(wxSize(680, noOfStudents * 85));
    // this->wxPanel::SetSize(wxSize(680, noOfStudents * 85));
    // update parent
    parent->Layout();
    parent->Update();
    StudentView *studentViews[noOfStudents];
    for (int i = 0; i < noOfStudents; i++)
    {
        studentViews[i] = new StudentView(this, wxID_ANY, wxDefaultPosition, wxSize(700, 75), &studentObject[i]);
        this->Refresh();
        this->Update();
        this->GetParent()->Refresh();
        this->GetParent()->Update();
        this->GetParent()->GetParent()->Refresh();
        this->GetParent()->GetParent()->Update();
    }
    
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    for (int i = 0; i < noOfStudents; i++)
    {
        if (i == noOfStudents-1) 
            sizer->Add(studentViews[i], 0, wxALL | wxEXPAND, 10);    
        else
            sizer->Add(studentViews[i], 0, wxLEFT| wxRIGHT | wxTOP | wxEXPAND, 10);
    }
    this->SetSizer(sizer);    
}