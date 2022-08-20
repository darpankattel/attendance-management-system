#include <Button.h>
#include <Config.h>
#include <Student.h>
#include <Query.h>
#include <TopStatusBar.h>
#include <cstring>
#include <ClassLinkLabel.h>
#include <HomeWidget.h>
#include <ImageView.h>
#include <wx/hyperlink.h>

extern wxColor *primaryBlack;
extern wxColor *primaryColor;
extern wxColor *tertiaryColor;

extern wxString widgetBgClass;
extern wxString widgetBgStudent;
extern wxString widgetBgPresence;

extern std::string appName;

Button::Button(wxWindow *parent, wxWindowID id, const wxString &label, const wxPoint &pos, const wxSize &size, long style, wxString bitmapPath)
: wxButton(parent, id, label, pos, size, style)
{
    this->id = id;
    wxButton::SetBackgroundColour(*primaryColor);
    wxButton::SetForegroundColour(*primaryWhite);
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
    controllingWindow->DestroyChildren();
    ShowYourWindow();
    if (id == 12) {
        topStatusBar->setTitle("Home");
    } 
    // 13 classes
    else if (id == 13) {
        topStatusBar->setTitle("Class");
    }
    // 14 settings
    else if (id == 14) {
        topStatusBar->setTitle("Settings");
    }
    // 15 about
    else if (id == 15) {
        topStatusBar->setTitle("About");
    }
}

void Button::OnMouseEnter(wxMouseEvent& event)
{
    wxButton::SetBackgroundColour(*tertiaryColor);
    wxButton::Refresh();
}

void Button::OnMouseLeave(wxMouseEvent& event)
{
    wxButton::SetBackgroundColour(*primaryColor);
    wxButton::Refresh();
}

void Button::ShowYourWindow()
{
    if (id == 12) {
        wxScrolledWindow *window = controllingWindow;
        Query *query = new Query(myDocRootPathDb);
        wxString sql = "SELECT * FROM student";
        sqlite3_stmt* stmt = query->execute(sql);
        int noOfStudents = query->length(stmt);
        sql = "SELECT * FROM class";
        stmt = query->execute(sql);
        int noOfClasses = query->length(stmt);

        topStatusBar->setFirstLabelTitle("");
        topStatusBar->setFirstLabelValue("");
        topStatusBar->setSecondLabelTitle("");
        topStatusBar->setSecondLabelValue("");
        topStatusBar->hideActionButton2();
        topStatusBar->hideActionButton3();

        window->SetSize(wxSize(680, 480));
        window->SetScrollbars(0, 0, 0, 0);

        wxPanel *homePanel = new wxPanel(window);
        homePanel->SetBackgroundColour(wxColor(240, 240, 240));

        HomeWidget *classWidget = new HomeWidget(homePanel, wxID_ANY, wxPoint(10, 10), wxSize(200, 125), widgetBgClass, std::to_string(noOfClasses), wxString("class"), wxString("number of classes"));

        HomeWidget *studentWidget = new HomeWidget(homePanel, wxID_ANY, wxPoint(240, 10), wxSize(200, 125), widgetBgStudent, std::to_string(noOfStudents), wxString("student"), wxString("number of students"));

        HomeWidget *presenceWidget = new HomeWidget(homePanel, wxID_ANY, wxPoint(470, 10), wxSize(200, 125), widgetBgPresence, "85%", wxString("statics"), wxString("average presence"));

        wxPanel *welcomePanel = new wxPanel(homePanel, wxID_ANY, wxPoint(10, 145), wxSize(680, 500));
        welcomePanel->SetBackgroundColour(wxColor(255, 255, 255));

        wxStaticText *helloText = new wxStaticText(welcomePanel, wxID_ANY, wxString("Hello, Daya Baral"), wxPoint(10, 10));
        helloText->SetForegroundColour(*primaryBlack);
        helloText->SetFont(wxFont(22, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_MAX, wxFONTWEIGHT_NORMAL));

        wxStaticText *welcomeText = new wxStaticText(welcomePanel, wxID_ANY, wxString("Welcome to " + appName), wxPoint(10, 60));
        welcomeText->SetForegroundColour(*primaryBlack);
        welcomeText->SetFont(wxFont(16, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_MAX, wxFONTWEIGHT_NORMAL));
        

        wxBoxSizer* mainContentSizer = new wxBoxSizer(wxVERTICAL);
        mainContentSizer->Add(homePanel, 1, wxEXPAND);
        window->SetSizer(mainContentSizer);
        query->close();

        // update window
        window->Layout();
        window->Refresh();
        window->Update();
        wxWindow *mainAppWindow = window->GetParent();
        mainAppWindow->Layout();
        mainAppWindow->Refresh();
        mainAppWindow->Update();
    }
    // 13 classes
    else if (id == 13) {
        std::cout<<"show classes window"<<std::endl;
        wxScrolledWindow *window = controllingWindow;

        Query *query = new Query(myDocRootPathDb);
        wxString sql = "SELECT * FROM class";
        sqlite3_stmt* stmt = query->execute(sql);
        int rows = query->length(stmt);

        window->SetSize(wxSize(680, rows*30+20));
        window->SetScrollbars(10, 10, 1, 1);
        // donot set scrollbars
        // window->SetScrollbars(0, 0, 0, 0);
        wxPanel *studentPanel = new wxPanel(window, wxID_ANY, wxDefaultPosition, wxSize(680, rows*30+20));
        studentPanel->SetBackgroundColour(wxColor(255, 255, 255));

        wxStaticText *classesLabelTitle = new wxStaticText(studentPanel, wxID_ANY, "All Class", wxPoint(10, 10), wxSize(200, 20));
        classesLabelTitle->SetForegroundColour(*primaryBlack);
        classesLabelTitle->SetFont(wxFont(16, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));

        wxBoxSizer* mainContentSizer = new wxBoxSizer(wxVERTICAL);
        mainContentSizer->Add(studentPanel, 1, wxEXPAND);
        window->SetSizer(mainContentSizer);

        int i = 1;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            wxString classId = wxString(sqlite3_column_text(stmt, 0));
            wxString className = wxString(sqlite3_column_text(stmt, 1));
            std::cout<<"Class info: "<<classId.ToStdString()<<" "<<className.ToStdString()<<std::endl;
            ClassLinkLabel *classLinkLabel = new ClassLinkLabel(studentPanel, wxID_ANY, className, wxPoint(10, 35*i+5), wxSize(100, 22), classId);
            classLinkLabel->setControllingWindow(window);
            classLinkLabel->setTopStatusBar(topStatusBar);
            i++;
        }
        
        
        topStatusBar->setFirstLabelTitle("");
        topStatusBar->setFirstLabelValue("");

        topStatusBar->setSecondLabelTitle("No. of Classes");
        topStatusBar->setSecondLabelValue(std::to_string(rows));
        
        // update window
        window->Layout();
        window->Refresh();
        window->Update();
        wxWindow *mainAppWindow = window->GetParent();
        mainAppWindow->Layout();
        mainAppWindow->Refresh();
        mainAppWindow->Update();
    }
    // 14 settings
    else if (id == 14) {
        std::cout<<"show settings window"<<std::endl;
        wxScrolledWindow *window = controllingWindow;
        window->SetSize(wxSize(680, 2*85+20));
        window->SetScrollbars(10, 10, 1, 1);
        wxPanel *studentPanel = new wxPanel(window, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
        studentPanel->SetBackgroundColour(wxColour(0, 255, 0));
        wxBoxSizer* mainContentSizer = new wxBoxSizer(wxVERTICAL);
        mainContentSizer->Add(studentPanel, 1, wxEXPAND);
        window->SetSizer(mainContentSizer);
        
        // update window
        window->Layout();
        window->Refresh();
        window->Update();
        wxWindow *mainAppWindow = window->GetParent();
        mainAppWindow->Layout();
        mainAppWindow->Refresh();
        mainAppWindow->Update();
    }
    // 15 about
    else if (id == 15) {
        wxScrolledWindow *window = controllingWindow;
        window->SetSize(wxSize(680, 2*85+20));
        window->SetScrollbars(10, 10, 1, 1);
        wxPanel *studentPanel = new wxPanel(window, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
        studentPanel->SetBackgroundColour(wxColour(0, 0, 255));

        wxBoxSizer* mainContentSizer = new wxBoxSizer(wxVERTICAL);
        mainContentSizer->Add(studentPanel, 1, wxEXPAND);
        window->SetSizer(mainContentSizer);
        // bibek's code starts

        wxString darpanImagePath = wxString("resources/images/darpan.png");

        wxString bishnuImagePath = wxString("resources/images/bishnu.png");

        wxString bibekImagePath = wxString("resources/images/bibek.png");

        wxString faceBookImagePath = wxString("resources/images/facebook.png");

        wxString instagramImagePath = wxString("resources/images/instagram.png");

        wxString webImagePath = wxString("resources/images/website.png");

        wxString phoneImagePath = wxString("resources/images/phone.png");

        wxPanel *aboutPanel = new wxPanel(studentPanel, wxID_ANY, wxDefaultPosition, wxSize(700, 980));

        aboutPanel->SetBackgroundColour(wxColor(255, 255, 255));

        wxStaticText *aboutAppTitle = new wxStaticText(aboutPanel, wxID_ANY, "About PresentSir", wxPoint(15, 15), wxDefaultSize);

        // aboutAppTitle->SetForegroundColour(wxColor(255,255,255));

        aboutAppTitle->SetFont(wxFont(24, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
        wxStaticText *aboutAppDescription = new wxStaticText(aboutPanel, wxID_ANY, "PresentSir is a simple and basic app made using wxWidgets(C++) which is \nan Attendance Management System(AMS).Through this App, we try to make \nthe Attendance System efficient and easy.Teacher can use this application to \ntake attendance of every class through their laptops.", wxPoint(15, 55), wxSize(60, 40), wxALL);

        aboutAppDescription->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_NORMAL));

        wxStaticText *developerTitle = new wxStaticText(aboutPanel, wxID_ANY, "Developers", wxPoint(15, 170), wxDefaultSize);

        developerTitle->SetFont(wxFont(24, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));

        int value1 = 45, value2 = 45;

        ImageView *darpanImage = new ImageView(aboutPanel, wxPoint(value1, 215), wxSize(165, 165), darpanImagePath, wxBITMAP_TYPE_PNG);

        ImageView *bishnuImage = new ImageView(aboutPanel, wxPoint(value1 + 165 + value2, 215), wxSize(165, 165), bishnuImagePath,
                                            wxBITMAP_TYPE_PNG);

        ImageView *bibekImage = new ImageView(aboutPanel, wxPoint(value1 + 165 + value2 + 165 + value2, 215), wxSize(165, 165), bibekImagePath,
                                            wxBITMAP_TYPE_PNG);
        wxStaticText *developerName1 = new wxStaticText(aboutPanel, wxID_ANY, "Darpan Kattel", wxPoint(55, 190+165+10+20), wxDefaultSize);
        developerName1->SetFont(wxFont(17, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));

        wxStaticText *developerName2 = new wxStaticText(aboutPanel, wxID_ANY, "Bishnu Datt Badu", wxPoint(245, 190+165+10+20), wxDefaultSize);
        developerName2->SetFont(wxFont(17, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));

        wxStaticText *developerName3 = new wxStaticText(aboutPanel, wxID_ANY, "Bibek Sunar", wxPoint(485, 190+165+10+20), wxDefaultSize);
        developerName3->SetFont(wxFont(17, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));

        wxStaticText *address1 = new wxStaticText(aboutPanel, wxID_ANY, "Jhapa, Nepal", wxPoint(55, 190+165+10+30+20), wxDefaultSize);
        address1->SetFont(wxFont(12, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_MAX, wxFONTWEIGHT_NORMAL));

        wxStaticText *address2 = new wxStaticText(aboutPanel, wxID_ANY, "Kanchanpur, Nepal", wxPoint(245, 190+165+10+30+20), wxDefaultSize);
        address2->SetFont(wxFont(12, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_MAX, wxFONTWEIGHT_NORMAL));

        wxStaticText *address3 = new wxStaticText(aboutPanel, wxID_ANY, "Arghakhanchi, Nepal", wxPoint(485, 190+165+10+30+20), wxDefaultSize);
        address3->SetFont(wxFont(12, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_MAX, wxFONTWEIGHT_NORMAL));

        ImageView *faceBookLogo1 = new ImageView(aboutPanel, wxPoint(45, 450), wxSize(35, 35), webImagePath, wxBITMAP_TYPE_PNG);
        ImageView *instagramLogo1 = new ImageView(aboutPanel, wxPoint(45, 500), wxSize(35, 35), faceBookImagePath, wxBITMAP_TYPE_PNG);
        ImageView *phoneLogo1 = new ImageView(aboutPanel, wxPoint(45, 550), wxSize(35, 35), instagramImagePath, wxBITMAP_TYPE_PNG);

        ImageView *faceBookLogo2 = new ImageView(aboutPanel, wxPoint(250, 450), wxSize(35, 35), faceBookImagePath, wxBITMAP_TYPE_PNG);
        ImageView *instagramLogo2 = new ImageView(aboutPanel, wxPoint(250, 500), wxSize(35, 35), instagramImagePath, wxBITMAP_TYPE_PNG);
        ImageView *phoneLogo2 = new ImageView(aboutPanel, wxPoint(250, 550), wxSize(35, 35), phoneImagePath, wxBITMAP_TYPE_PNG);

        ImageView *faceBookLogo3 = new ImageView(aboutPanel, wxPoint(455, 450), wxSize(35, 35), faceBookImagePath, wxBITMAP_TYPE_PNG);
        ImageView *instagramLogo3 = new ImageView(aboutPanel, wxPoint(455, 500), wxSize(35, 35), instagramImagePath, wxBITMAP_TYPE_PNG);
        ImageView *phoneLogo3 = new ImageView(aboutPanel, wxPoint(455, 550), wxSize(35, 35), phoneImagePath, wxBITMAP_TYPE_PNG);

        wxHyperlinkCtrl *facebookLink11 = new wxHyperlinkCtrl(aboutPanel, wxID_ANY, "darpankattel.com.np", "https://www.darpankattel.com.np/", wxPoint(85, 450), wxDefaultSize);
        wxHyperlinkCtrl *facebookLink21 = new wxHyperlinkCtrl(aboutPanel, wxID_ANY, "coderslap.com", "https://www.coderslap.com/", wxPoint(85, 470), wxDefaultSize);
        wxHyperlinkCtrl *facebookLink2 = new wxHyperlinkCtrl(aboutPanel, wxID_ANY, "Bishnu Datt Badu", "https://www.facebook.com/bishnudbadu.143", wxPoint(290, 460), wxDefaultSize);
        wxHyperlinkCtrl *facebookLink3 = new wxHyperlinkCtrl(aboutPanel, wxID_ANY, "Vivek Sunar", "https://www.facebook.com/profile.php?id=100011964697970", wxPoint(495, 460), wxDefaultSize);
        
        wxHyperlinkCtrl *instagramLink1 = new wxHyperlinkCtrl(aboutPanel, wxID_ANY, "Darpan Kattel", "https://www.facebook.com/darpan.kattel", wxPoint(85, 510), wxDefaultSize);
        wxHyperlinkCtrl *instagramLink2 = new wxHyperlinkCtrl(aboutPanel, wxID_ANY, "Bishnu Datt Badu", "9843761451", wxPoint(290, 510), wxDefaultSize);
        wxHyperlinkCtrl *instagramLink3 = new wxHyperlinkCtrl(aboutPanel, wxID_ANY, "Bibek Sunar", "9866564506", wxPoint(495, 510), wxDefaultSize);

        wxHyperlinkCtrl *phoneNumber1 = new wxHyperlinkCtrl(aboutPanel, wxID_ANY, "Darpan Kattel", "https://instagram.com/katteldarpan/", wxPoint(85, 560), wxDefaultSize);
        wxStaticText *phoneNumber2 = new wxStaticText(aboutPanel, wxID_ANY, "9843761451", wxPoint(290, 560), wxDefaultSize);
        wxStaticText *phoneNumber3 = new wxStaticText(aboutPanel, wxID_ANY, "9866564506", wxPoint(495, 560), wxDefaultSize);
        
        
        wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
        mainSizer->Add(aboutPanel, 1, wxEXPAND);

        studentPanel->SetSizer(mainSizer);


        //bibek's code ends
        
        // update window
        window->Layout();
        window->Refresh();
        window->Update();
        wxWindow *mainAppWindow = window->GetParent();
        mainAppWindow->Layout();
        mainAppWindow->Refresh();
        mainAppWindow->Update();
    }
}

void Button::setControllingWindow(wxScrolledWindow *window)
{
    this->controllingWindow = window;
}
void Button::setTopStatusBar(TopStatusBar *statusBar)
{
    this->topStatusBar = statusBar;
}