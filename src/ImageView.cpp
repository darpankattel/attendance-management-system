#include <ImageView.h>
extern wxString* defaultUserImage;

ImageView::ImageView(wxWindow *parent, wxPoint pos, wxSize size, wxString &defaultImage, wxBitmapType type)
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
    defaultWxBitmap->Rescale(*defaultWxBitmap, size);
    // rounded image corners
    defaultWxStaticBitmap = new wxStaticBitmap(parent, wxID_ANY, *defaultWxBitmap, wxPoint(0, 0), size);
}
void ImageView::setSizerCustom(wxBoxSizer *boxSizer, double proportion = 0, int flag = 0, int border = 0)
{
    boxSizer->Add(this->defaultWxStaticBitmap, proportion, flag, border);
}
void ImageView::SetBackgroundColor(wxColour color)
{
    this->defaultWxStaticBitmap->SetBackgroundColour(color);
}
void ImageView::SetSizeCustom(wxSize size)
{
    this->size = size;
    this->defaultWxStaticBitmap->SetSize(size);
}
void ImageView::ChangeImage(wxString imagePath, wxBitmapType type = wxBITMAP_TYPE_ANY)
{
    this->imagePath = imagePath;
    wxImage *defaultWxImage = new wxImage(imagePath, type);
    wxBitmap *defaultWxBitmap = new wxBitmap(*defaultWxImage);
    defaultWxBitmap->Rescale(*defaultWxBitmap, this->size);
    this->defaultWxStaticBitmap->SetBitmap(*defaultWxBitmap);
}