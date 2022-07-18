#include <ImageView.h>
extern wxString* defaultUserImage;

ImageView::ImageView(wxWindow *parent, wxPoint pos, wxSize size, wxString& defaultImage, wxBitmapType type)
{
    if (defaultImage.IsEmpty())
        this->defaultImage = wxString("defaultUserImage.png");
    else
        this->defaultImage = defaultImage;
    this->imagePath = wxString("");
    this->pos = pos;
    this->size = size;


    wxImage *defaultWxImage = new wxImage(defaultImage, type);
    wxBitmap *defaultWxBitmap = new wxBitmap(*defaultWxImage);
    defaultWxBitmap->Rescale(*defaultWxBitmap, wxSize(100, 271/3));
    defaultWxStaticBitmap = new wxStaticBitmap(parent, wxID_ANY, *defaultWxBitmap, wxPoint(0, 0), wxSize(100, 271/3));
}
void ImageView::setSizerCustom(wxBoxSizer *boxSizer, double proportion = 0, int flag = 0, int border = 0)
{
    boxSizer->Add(this->defaultWxStaticBitmap, proportion, flag, border);
}
void ImageView::SetBackgroundColor(wxColour color)
{
    this->defaultWxStaticBitmap->SetBackgroundColour(color);
}
