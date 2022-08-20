#ifndef CONFIG_H
#define CONFIG_H
// define default variables here

extern std::string appName;
extern std::string appNameFull;
extern wxString* teacherFullname;
extern wxString* teacherImage;

extern wxString widgetBgClass;
extern wxString widgetBgStudent;

extern wxColor* primaryColor;
extern wxColor* secondaryColor;
extern wxColor* tertiaryColor;

extern wxColor* primaryBlack;
extern wxColor* primaryWhite;
extern wxColor* primaryGrey;

extern wxString* smallLogo;
extern wxString* mediumLogo;
extern wxString* largeLogo;

extern wxString* defaultUserImage;
extern wxString* defaultClassImage;

extern wxString* logInContainerLeftText;

// get my document root directory
extern wxString myDocRoot;
extern wxString myDocRootPath;
extern wxString myDocRootPathConfig;
extern wxString myDocRootPathDb;

#endif