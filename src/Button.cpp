#include <Button.h>
#include <Config.h>
extern wxColor *primaryBlack;
extern wxColor *primaryColor;

Button::Button(wxWindow *parent, wxWindowID id, const wxString &label, const wxPoint &pos, const wxSize &size, long style)
: wxButton(parent, id, label, pos, size, style)
{
    wxButton::SetBackgroundColour(*primaryBlack);
    wxButton::SetForegroundColour(wxColour(255, 255, 255));
    // border 
    wxButton::SetWindowStyle(wxBORDER_NONE);
    // change font size only
    wxFont font = wxButton::GetFont();
    font.SetPointSize(font.GetPointSize() + 2);
    wxButton::SetFont(font);
    wxButton::SetCursor(wxCURSOR_HAND);
    this->Bind(wxEVT_LEFT_DOWN, &Button::OnClick, this);
    this->Bind(wxEVT_ENTER_WINDOW, &Button::OnMouseEnter, this);
    this->Bind(wxEVT_LEAVE_WINDOW, &Button::OnMouseLeave, this);
}

void Button::OnClick(wxMouseEvent& event)
{
    wxMessageBox("Button clicked.", "Button", wxICON_INFORMATION);
}

void Button::OnMouseEnter(wxMouseEvent& event)
{
    wxButton::SetBackgroundColour(*primaryColor);
    wxButton::Refresh();
}

void Button::OnMouseLeave(wxMouseEvent& event)
{
    wxButton::SetBackgroundColour(wxColour(0, 0, 0));
    wxButton::Refresh();

}
