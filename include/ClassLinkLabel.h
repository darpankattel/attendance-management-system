#ifndef CLASSLINKLABEL_H
#define CLASSLINKLABEL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <TopStatusBar.h>

class ClassLinkLabel: public wxButton
{
    private:
    wxString className;
    wxString classId;
    wxScrolledWindow *controllingWindow;
    TopStatusBar *topStatusBar;
    public:
    ClassLinkLabel(wxWindow *parent, wxWindowID id, wxString className, const wxPoint& pos, const wxSize& size, wxString classId);
    void OnClick(wxCommandEvent& event);
    void setControllingWindow(wxScrolledWindow *window);
    void setTopStatusBar(TopStatusBar *statusBar);
};

#endif