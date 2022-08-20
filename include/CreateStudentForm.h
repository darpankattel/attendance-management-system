#ifndef CREATESTUDENTFORM_H
#define CREATESTUDENTFORM_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class CreateStudentForm: public wxFrame
{
    protected:
    wxPoint pos;
    wxSize size;
    wxString imagePath;
    wxString defaultImage;
    wxBitmapType type;
    
    public:
    wxStaticBitmap *defaultWxStaticBitmap;
    CreateStudentForm(wxWindow *parent, wxPoint pos, wxSize size, wxString &title, wxString &defaultImage, wxBitmapType type);
    void setSizerCustom(wxBoxSizer *boxSizer, double proportion, int flag, int border);
    void SetBackgroundColor(wxColour color);
    void SetSizeCustom(wxSize size);
    void ChangeImage(wxString imagePath, wxBitmapType type);
    void OnSubmit(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);
    void OnSubmitScript(wxCommandEvent& event);
};

#endif