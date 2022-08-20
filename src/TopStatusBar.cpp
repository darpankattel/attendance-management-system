#include <TopStatusBar.h>
#include <Config.h>
extern wxColor* primaryWhite;
extern wxColor* primaryBlack;

TopStatusBar::TopStatusBar(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
: wxPanel(parent, id, pos, size)
{
    wxPanel *leftStatusPanel = new wxPanel(this, wxID_ANY);
    // leftStatusPanel->SetBackgroundColour(wxColor(0, 255, 0));

    wxPanel *rightStatusPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(50, 80));
    // rightStatusPanel->SetBackgroundColour(wxColor(255, 0, 0));

    wxPanel *titleStatusPanel = new wxPanel(leftStatusPanel, wxID_ANY, wxDefaultPosition, wxSize(160, 80));
    // titleStatusPanel -> SetBackgroundColour(wxColor(255, 0, 0));
    wxPanel *controlsStatusPanel = new wxPanel(leftStatusPanel, wxID_ANY, wxDefaultPosition, wxSize(200, 80));
    // controlsStatusPanel -> SetBackgroundColour(wxColor(0, 255, 0));
    wxPanel *labelsStatusPanel = new wxPanel(leftStatusPanel, wxID_ANY, wxDefaultPosition, wxSize(300, 80));
    // labelsStatusPanel -> SetBackgroundColour(wxColor(0, 0, 255));

    statusBarTitle = new wxStaticText(titleStatusPanel, wxID_ANY, "Home", wxPoint(10, 10));
    statusBarTitle->SetFont(wxFont(20, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    statusBarTitle->SetForegroundColour(*primaryBlack);

    // wxButton *actionButton = new wxButton(titleStatusPanel,wxID_ANY,"Action 1",wxPoint(5,35),wxDefaultSize);
    // actionButton -> SetBackgroundColour(*primaryWhite);
    // actionButton -> SetForegroundColour(*primaryBlack);
    // // actionButton -> SetFont(wxFont(12,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxF));
    // actionButton -> SetCursor(wxCURSOR_HAND);
    // actionButton -> SetWindowStyle(wxBORDER_NONE);

    // wxCheckBox *markingAsHover = new wxCheckBox(controlsStatusPanel,wxID_ANY,"Mark presence in hover",wxPoint(0,35),wxSize(200,20));
    // // wxCHK_3STATE | wxCHK_ALLOW_3RD_STATE_FOR_USER  
    // markingAsHover -> SetFont(wxFont(13,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL));
    // markingAsHover -> SetForegroundColour( wxColour("#ff0000") );
    actionButton2 = new wxButton(controlsStatusPanel,wxID_ANY,"Mark Everyone Present");
    actionButton2 -> SetBackgroundColour(*primaryColor);
    actionButton2 -> SetForegroundColour(*primaryWhite);
    // actionButton -> SetFont(wxFont(12,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxF));
    actionButton2 -> SetCursor(wxCURSOR_HAND);
    actionButton2 -> SetWindowStyle(wxBORDER_NONE);

    actionButton3 = new wxButton(controlsStatusPanel,wxID_ANY,"Mark Everyone Absent");
    actionButton3 -> SetBackgroundColour(*primaryColor);
    actionButton3 -> SetForegroundColour(*primaryWhite);
    // actionButton -> SetFont(wxFont(12,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxF));
    actionButton3 -> SetCursor(wxCURSOR_HAND);
    actionButton3 -> SetWindowStyle(wxBORDER_NONE);

    wxBoxSizer *controlsStatusPanelSizer = new wxBoxSizer(wxVERTICAL);
    controlsStatusPanelSizer -> Add(actionButton2, 1, wxTOP | wxBOTTOM | wxALIGN_CENTER, 5);
    controlsStatusPanelSizer -> Add(actionButton3, 1, wxBOTTOM | wxTOP | wxALIGN_CENTER, 5);
    controlsStatusPanel -> SetSizer(controlsStatusPanelSizer);

    wxPanel* leftLabelPanel = new wxPanel(labelsStatusPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    // leftLabelPanel -> SetBackgroundColour(wxColor(0, 255, 255));
    wxPanel* rightLabelPanel = new wxPanel(labelsStatusPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    // rightLabelPanel -> SetBackgroundColour(wxColor(255, 0, 255));

    leftLabelTitle = new wxStaticText(leftLabelPanel,wxID_ANY,"No. of Students");
    leftLabelTitle->SetForegroundColour(*primaryBlack);
    leftLabelTitle -> SetFont(wxFont(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL));
     
    leftLabelValue = new wxStaticText(leftLabelPanel,wxID_ANY,"98");
    leftLabelValue->SetForegroundColour(*primaryBlack);
    leftLabelValue -> SetFont(wxFont(20,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_EXTRABOLD));

    rightLabelTitle = new wxStaticText(rightLabelPanel,wxID_ANY,"Below 70%");
    rightLabelTitle->SetForegroundColour(*primaryBlack);
    rightLabelTitle -> SetFont(wxFont(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL));

    rightLabelValue = new wxStaticText(rightLabelPanel,wxID_ANY,"12");
    rightLabelValue->SetForegroundColour(*primaryBlack);
    rightLabelValue -> SetFont(wxFont(20,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_EXTRABOLD));

    wxBoxSizer *leftLabelSizer = new wxBoxSizer(wxVERTICAL);
    leftLabelSizer -> Add(leftLabelTitle, 0, wxALL | wxALIGN_CENTER, 5);
    leftLabelSizer -> Add(leftLabelValue, 0, wxALL | wxALIGN_CENTER, 5);
    leftLabelPanel -> SetSizer(leftLabelSizer);

    wxBoxSizer *rightLabelSizer = new wxBoxSizer(wxVERTICAL);
    rightLabelSizer -> Add(rightLabelTitle, 0, wxALL | wxALIGN_CENTER, 5);
    rightLabelSizer -> Add(rightLabelValue, 0, wxALL | wxALIGN_CENTER, 5);
    rightLabelPanel -> SetSizer(rightLabelSizer);

    wxBoxSizer *labelPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    labelPanelSizer -> Add(leftLabelPanel, 1, wxEXPAND | wxLEFT, 5);
    labelPanelSizer -> Add(rightLabelPanel, 1, wxEXPAND | wxLEFT, 5);
    labelsStatusPanel -> SetSizer(labelPanelSizer);

    addButton = new wxButton(rightStatusPanel, wxID_ANY, "", wxPoint(0, 20), wxSize(30, 30));
    addButton->SetWindowStyle(wxBORDER_NONE);
    addButton->SetBackgroundColour(*primaryWhite);
    addButton->SetCursor(wxCURSOR_HAND);

    wxBitmap bitmapForAddButton = wxBitmap("resources/images/plus.png", wxBITMAP_TYPE_PNG);
    addButton->SetBitmap(bitmapForAddButton);
    // left margin for bitmap
    addButton->SetBitmapMargins(wxSize(0, 0));
    addButton->SetBackgroundColour(*primaryWhite);
    // addButton->SetBitmapPosition(wxDirection::wxLEFT);

    wxBoxSizer *leftStatusPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    leftStatusPanelSizer->Add(titleStatusPanel, 0, wxEXPAND | wxALL, 0);
    leftStatusPanelSizer->Add(controlsStatusPanel, 1, wxEXPAND | wxTOP | wxBOTTOM, 5);
    leftStatusPanelSizer->Add(labelsStatusPanel, 0, wxEXPAND | wxALL, 0);
    leftStatusPanel->SetSizer(leftStatusPanelSizer);


    wxBoxSizer *topStatusBarSizer = new wxBoxSizer(wxHORIZONTAL);
    topStatusBarSizer->Add(leftStatusPanel, 1, wxEXPAND);
    topStatusBarSizer->Add(rightStatusPanel, 0, wxEXPAND);
    this->SetSizer(topStatusBarSizer);

}
void TopStatusBar::setTitle(wxString title){
    statusBarTitle -> SetLabel(title);
}
void TopStatusBar::setFirstLabelTitle(wxString title){
    leftLabelTitle -> SetLabel(title);
}
void TopStatusBar::setFirstLabelValue(wxString value){
    leftLabelValue -> SetLabel(value);
}
void TopStatusBar::setSecondLabelTitle(wxString title){
    rightLabelTitle -> SetLabel(title);
}
void TopStatusBar::setSecondLabelValue(wxString value){
    rightLabelValue -> SetLabel(value);
}

void TopStatusBar::hideActionButton2(){
    actionButton2 -> Hide();
}
void TopStatusBar::hideActionButton3(){
    actionButton3 -> Hide();
}

void TopStatusBar::showActionButton2(){
    actionButton2 -> Show();
}
void TopStatusBar::showActionButton3(){
    actionButton3 -> Show();
}