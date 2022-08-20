#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class HomeWidget: public wxPanel
{
    private:
    wxString typeOfWidget;
    wxString title;
    public:
        HomeWidget(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, wxString bgPath, wxString title, wxString typeOfWidget, wxString desc);
};

#endif