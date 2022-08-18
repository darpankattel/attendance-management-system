#ifndef BGPANEL_H
#define BGPANEL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class BGPanel: public wxPanel
{
    public:
        BGPanel(wxFrame *parent, wxWindowID id, const wxPoint& pos, const wxSize& size);
    private:
        // void OnPaint(wxPaintEvent& event);
        // void OnSize(wxSizeEvent& event);
        // void OnEraseBackground(wxEraseEvent& event);
        // wxDECLARE_EVENT_TABLE();
};

#endif