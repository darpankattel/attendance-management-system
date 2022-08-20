#ifndef BUTTON_H
#define BUTTON_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <TopStatusBar.h>
class Button: public wxButton
{
    public:
        Button(wxWindow *parent, wxWindowID id, const wxString &label=wxEmptyString, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=0, wxString bitmapPath = wxEmptyString);
        void OnClick(wxMouseEvent& event);
        void OnMouseEnter(wxMouseEvent& event);
        void OnMouseLeave(wxMouseEvent& event);
        void ShowYourWindow();
        void setControllingWindow(wxScrolledWindow *window);
        void setTopStatusBar(TopStatusBar *statusBar);
    private:
        wxScrolledWindow *controllingWindow;
        wxWindowID id;
        TopStatusBar *topStatusBar;
};

#endif