#ifndef STUDENT_H
#define STUDENT_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <sqlite3.h>
#include <Query.h>
class Student: public wxPanel
{
    public:
        Student(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, Query* query, sqlite3_stmt* stmt);
    private:
        // void OnPaint(wxPaintEvent& event);
        // void OnSize(wxSizeEvent& event);
        // void OnEraseBackground(wxEraseEvent& event);
        // wxDECLARE_EVENT_TABLE();
};

#endif