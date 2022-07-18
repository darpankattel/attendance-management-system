#ifndef LOGINFRAME_H
#define LOGINFRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class LogInFrame: public wxFrame
{
    public:
    LogInFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
};

#endif // LOGINFRAME_H