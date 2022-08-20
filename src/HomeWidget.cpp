#include <HomeWidget.h>
#include <Config.h>
#include <ImageView.h>
extern wxColor* primaryWhite;
extern wxColor* primaryColor;

HomeWidget::HomeWidget(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, wxString bgPath, wxString title, wxString typeOfWidget, wxString desc)
: wxPanel(parent, id, pos, size)
{
    this->typeOfWidget = typeOfWidget;
    this->title = title;
    this->SetCursor(wxCURSOR_HAND);
    
    ImageView *bgImageView = new ImageView(this, wxPoint(0, 0), size, bgPath, wxBITMAP_TYPE_PNG);

    wxStaticText *titleLabel = new wxStaticText(this, wxID_ANY, title, wxPoint(10, 10+30), wxDefaultSize);
    titleLabel -> SetForegroundColour(*primaryWhite); 
    titleLabel -> SetBackgroundColour(*primaryColor);
    titleLabel -> SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxStaticText *descriptionLabel = new wxStaticText(this, wxID_ANY, desc, wxPoint(10, 40+30), wxDefaultSize);
    descriptionLabel -> SetForegroundColour(*primaryWhite);
    descriptionLabel -> SetBackgroundColour(*primaryColor);
    descriptionLabel -> SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
}
