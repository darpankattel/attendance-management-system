#include <ImageUploadView.h>
extern wxString* defaultUserImage;

ImageUploadView::ImageUploadView(wxWindow *parent, wxString title, wxPoint pos, wxSize size, wxString& defaultImage, wxBitmapType type, wxString tooltip)
{
    if (title.IsEmpty())
        this->title = wxString("Image Upload");
    else
        this->title = title;

    if (defaultImage.IsEmpty())
        this->defaultImage = wxString("defaultUserImage.png");
    else
        this->defaultImage = defaultImage;

    if (tooltip.IsEmpty())
        this->tooltipText = wxString("Click to Upload a Image");
    else
        this->tooltipText = tooltip;

    this->imagePath = wxString("");
    this->pos = pos;
    this->size = size;


    wxImage *defaultWxImage = new wxImage(defaultImage, type);
    wxBitmap *defaultWxBitmap = new wxBitmap(*defaultWxImage);
    defaultWxBitmap->Rescale(*defaultWxBitmap, wxSize(100, 271/3));
    defaultWxStaticBitmap = new wxStaticBitmap(parent, wxID_ANY, *defaultWxBitmap, wxPoint(0, 0), wxSize(100, 271/3));
    defaultWxStaticBitmap->SetToolTip(tooltipText);
    defaultWxStaticBitmap->SetCursor(wxCursor(wxCURSOR_HAND));
}
void ImageUploadView::setSizerCustom(wxBoxSizer *boxSizer, double proportion = 0, int flag = 0, int border = 0)
{
    boxSizer->Add(this->defaultWxStaticBitmap, proportion, flag, border);
}
