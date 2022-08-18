#include <Button.h>
#include <Config.h>
extern wxColor *primaryBlack;
extern wxColor *primaryColor;

Button::Button(wxWindow *parent, wxWindowID id, const wxString &label, const wxPoint &pos, const wxSize &size, long style, wxString bitmapPath)
: wxButton(parent, id, label, pos, size, style)
{
    isActive = false;
    wxButton::SetBackgroundColour(*primaryBlack);
    wxButton::SetForegroundColour(wxColour(255, 255, 255));
    // border 
    wxButton::SetWindowStyle(wxBORDER_NONE);
    // change font size only
    wxFont font = wxButton::GetFont();
    font.SetPointSize(font.GetPointSize() + 2);
    wxButton::SetFont(font);
    // wxButton::SetFont(wxFont(16, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
    wxButton::SetCursor(wxCURSOR_HAND);
    wxBitmap bitmap = wxBitmap(bitmapPath, wxBITMAP_TYPE_PNG);
    wxButton::SetBitmap(bitmap);
    // left margin for bitmap
    wxButton::SetBitmapMargins(wxSize(30, 0));
    wxButton::SetBitmapPosition(wxDirection::wxLEFT);
    // button align left
    // wxButton::SetExtraStyle(wxALIGN_LEFT);
    this->Bind(wxEVT_LEFT_DOWN, &Button::OnClick, this);
    this->Bind(wxEVT_ENTER_WINDOW, &Button::OnMouseEnter, this);
    this->Bind(wxEVT_LEAVE_WINDOW, &Button::OnMouseLeave, this);
}

void Button::OnClick(wxMouseEvent& event)
{
    isActive = true;
    int id = wxButton::GetId();
}

void Button::OnMouseEnter(wxMouseEvent& event)
{
    if (!isActive){
        wxButton::SetBackgroundColour(*primaryColor);
        wxButton::Refresh();
    }
}

void Button::OnMouseLeave(wxMouseEvent& event)
{
    if (!isActive){
        wxButton::SetBackgroundColour(wxColour(0, 0, 0));
        wxButton::Refresh();
    }
}
