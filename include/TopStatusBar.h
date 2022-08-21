#ifndef TOPSTATUSBAR_H
#define TOPSTATUSBAR_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class TopStatusBar: public wxPanel
{
    public:
    wxStaticText *statusBarTitle;
    wxButton *actionButton2;
    wxButton *actionButton3;
    wxStaticText *leftLabelTitle;
    wxStaticText *leftLabelValue;
    wxStaticText *rightLabelTitle;
    wxStaticText *rightLabelValue;
    wxButton *addButton;
    wxString statusBarFor;
        TopStatusBar(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size);
        void setTitle(wxString);
        void setFirstLabelTitle(wxString);
        void setFirstLabelValue(wxString);
        void setSecondLabelTitle(wxString);
        void setSecondLabelValue(wxString);
        void hideActionButton2();
        void hideActionButton3();
        void showActionButton2();
        void showActionButton3();
        void setStatusBarFor(wxString);
        void onAddButtonClick(wxCommandEvent& event);
};

#endif