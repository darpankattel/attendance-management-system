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

wxColor* primaryColor = new wxColor(72, 201, 176);
wxColor* secondaryColor = new wxColor(20, 174, 92);

wxString* smallLogo = new wxString("resources/images/ams-logo-small.png");
wxString* mediumLogo = new wxString("resources/images/ams-logo-medium.png");
wxString* largeLogo = new wxString("resources/images/ams-logo-large.png");

wxString* defaultUserImage = new wxString("resources/images/default-user.png");

wxString* logInContainerLeftText = new wxString("Please Login with your details to use the app. We are just collecting your details, we won't sign you up!");