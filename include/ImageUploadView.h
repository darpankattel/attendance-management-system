#ifndef IMAGEUPLOADVIEW_H
#define IMAGEUPLOADVIEW_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class ImageUploadView: public wxBitmap, public wxWindow
{
    private:
    wxString title;
    wxPoint pos;
    wxSize size;
    wxString tooltipText;
    wxString imagePath;
    wxString defaultImage;
    
    public:
    wxStaticBitmap *defaultWxStaticBitmap;
    ImageUploadView(wxWindow *parent, wxString title, wxPoint pos, wxSize size, wxString& defaultImage, wxBitmapType type, wxString tooltip);
    // methods for boxSizer
    void setSizerCustom(wxBoxSizer *boxSizer, double proportion, int flag, int border);
};

#endif