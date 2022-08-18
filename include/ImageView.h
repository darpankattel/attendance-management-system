#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class ImageView: public wxBitmap, public wxWindow
{
    protected:
    wxPoint pos;
    wxSize size;
    wxString imagePath;
    wxString defaultImage;
    
    public:
    wxStaticBitmap *defaultWxStaticBitmap;
    ImageView(wxWindow *parent, wxPoint pos, wxSize size, wxString &defaultImage, wxBitmapType type);
    void setSizerCustom(wxBoxSizer *boxSizer, double proportion, int flag, int border);
    void SetBackgroundColor(wxColour color);
    void SetSizeCustom(wxSize size);
    void ChangeImage(wxString imagePath, wxBitmapType type);
};

#endif