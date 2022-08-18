#include <About.h>

About::About(wxFrame *parent, wxWindowID id, const wxPoint& pos, const wxSize& size) : wxFrame(parent, id, "About", pos, size)
{
    wxPanel *panel = new wxPanel(this);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText *text = new wxStaticText(panel, wxID_ANY, "This is a simple wxWidgets application.");
    sizer->Add(text, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
    panel->SetSizer(sizer);
    panel->Layout();
    sizer->Fit(this);
    Centre();
}