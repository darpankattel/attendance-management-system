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
        wxString name = sqlite3_column_text(stmt, 0);
        wxString id = sqlite3_column_text(stmt, 1);
        wxString roll_no = sqlite3_column_text(stmt, 2);
        wxString className = sqlite3_column_text(stmt, 3);
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
    }
    
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    for (int i = 0; i < noOfStudents; i++)
    {
        if (i == noOfStudents-1) 
            sizer->Add(studentViews[i], 0, wxALL | wxEXPAND, 5);    
        else
            sizer->Add(studentViews[i], 0, wxLEFT| wxRIGHT | wxTOP | wxEXPAND, 5);
    }
    this->SetSizer(sizer);    
}