#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <Config.h>
// define default variables here

std::string appName = "PresentSir";
std::string appNameFull = "PresentSir - 3Qu-Bits";
wxString* teacherFullname = new wxString("");
wxString* teacherImage = new wxString("");

wxString widgetBgClass = wxString("resources/images/class-widget-bg.png");
wxString widgetBgStudent = wxString("resources/images/student-widget-bg.png");
wxString widgetBgPresence = wxString("resources/images/presence-widget-bg.png");

wxColor* primaryColor = new wxColor(72, 201, 176);
wxColor* secondaryColor = new wxColor(20, 174, 92);
wxColor* tertiaryColor = new wxColor(39, 156, 134);

wxColor* primaryBlack = new wxColour(11, 21, 15);
wxColor* primaryWhite = new wxColor(255, 255, 255);
wxColor* primaryGrey = new wxColor(217, 217, 217);

wxString* smallLogo = new wxString("resources/images/ams-logo-small.png");
wxString* mediumLogo = new wxString("resources/images/ams-logo-medium.png");
wxString* largeLogo = new wxString("resources/images/ams-logo-large.png");
wxString* newLogo = new wxString("resources/images/ams-logo-new-small.png");

wxString* defaultUserImage = new wxString("resources/images/default-user.png");
wxString* defaultStudentImage = new wxString("resources/images/student-circled.png");
wxString* defaultClassImage = new wxString("resources/images/class-logo.png");

wxString* logInContainerLeftText = new wxString("Please Login with your details to use the app. We are just collecting your details, we won't sign you up!");

wxString myDocRoot = wxString("");
wxString myDocRootPath = wxString("");
wxString myDocRootPathConfig = wxString("");
wxString myDocRootPathDb = wxString("");

