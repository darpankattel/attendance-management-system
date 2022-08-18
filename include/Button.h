#ifndef BUTTON_H
#define BUTTON_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class Button: public wxButton
{
    public:
        Button(wxWindow *parent, wxWindowID id, const wxString &label=wxEmptyString, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=0, wxString bitmapPath = wxEmptyString);
        void OnClick(wxMouseEvent& event);
        void OnMouseEnter(wxMouseEvent& event);
        void OnMouseLeave(wxMouseEvent& event);
    private:
        bool isActive;
};

#endif