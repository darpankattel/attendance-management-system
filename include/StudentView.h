#ifndef STUDENTVIEW_H
#define STUDENTVIEW_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <StudentObject.h>

class StudentView: public wxPanel
{
    public:
        StudentView(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, StudentObject* student);
    private:
        void OnPaint(wxPaintEvent& event);
        void onToggleButtonClick(wxCommandEvent& event);
        // void OnSize(wxSizeEvent& event);
        // void OnEraseBackground(wxEraseEvent& event);
        // wxDECLARE_EVENT_TABLE();
};

#endif