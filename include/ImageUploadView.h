#ifndef IMAGEUPLOADVIEW_H
#define IMAGEUPLOADVIEW_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <ImageView.h>

class ImageUploadView: public ImageView
{
    protected:
    wxString title;
    wxString tooltipText;
    
    public:
    ImageUploadView(wxPanel *parent, wxString title, wxPoint pos, wxSize size, wxString& defaultImage, wxBitmapType type, wxString tooltip);
    void setSizerCustom(wxBoxSizer *boxSizer, double proportion, int flag, int border);
    void SetSizeCustom(wxSize size);
    void OnClick(wxMouseEvent& event);
    std::string getImageFullPath();
    bool setImageType(wxBitmapType type);
};

#endif