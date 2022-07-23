#include <ImageUploadView.h>
extern wxString* defaultUserImage;

ImageUploadView::ImageUploadView(wxWindow *parent, wxString title, wxPoint pos, wxSize size, wxString& defaultImage, wxBitmapType type, wxString tooltip) : ImageView(parent, pos, size, defaultImage, type)
{
    if (title.IsEmpty())
        this->title = wxString("Image Upload");
    else
        this->title = title;
    if (tooltip.IsEmpty())
        this->tooltipText = wxString("Click to Upload a Image");
    else
        this->tooltipText = tooltip;

    ImageView::defaultWxStaticBitmap->SetToolTip(tooltipText);
    ImageView::defaultWxStaticBitmap->SetCursor(wxCursor(wxCURSOR_HAND));
    // bind an onclick event to the defaultWxStaticBitmap
    ImageView::defaultWxStaticBitmap->Bind(wxEVT_LEFT_DOWN, &ImageUploadView::OnClick, this);
}
void ImageUploadView::setSizerCustom(wxBoxSizer *boxSizer, double proportion = 0, int flag = 0, int border = 0)
{
    boxSizer->Add(this->defaultWxStaticBitmap, proportion, flag, border);
}
void ImageUploadView::SetSizeCustom(wxSize size)
{
    this->ImageView::size = size;
    this->ImageView::defaultWxStaticBitmap->SetSize(size);
}
void ImageUploadView::OnClick(wxMouseEvent& event)
{
    wxFileDialog *openFileDialog = new wxFileDialog(this, wxString("Choose a Image"), wxEmptyString, wxEmptyString, wxString("Image Files (*.png;*.jpg;*.bmp)|*.png;*.jpg;*.bmp"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog->ShowModal() == wxID_CANCEL)
        return;
    this->imagePath = openFileDialog->GetPath();
    std::cout<<"imagePath: "<<this->imagePath<<std::endl;
    ImageView::ChangeImage(this->imagePath);
    this->defaultWxStaticBitmap->SetToolTip(this->imagePath);
    // wxImage *wxImage = new wxImage(this->imagePath);
    // wxBitmap *wxBitmap = new wxBitmap(*wxImage);
    // wxBitmap->Rescale(*wxBitmap, this->size);
    // this->defaultWxStaticBitmap->SetBitmap(*wxBitmap);
    // this->defaultWxStaticBitmap->SetToolTip(wxString("Click to Remove Image"));
    // this->defaultWxStaticBitmap->SetCursor(wxCursor(wxCURSOR_HAND));
    // this->defaultWxStaticBitmap->Bind(wxEVT_LEFT_DOWN, &onRemove, this);
}