#ifndef ABOUT_H
#define ABOUT_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class About: public wxFrame
{
    public:
        About(wxFrame *parent, wxWindowID id, const wxPoint& pos, const wxSize& size);
    private:
};

#endif