#ifndef STUDENTOBJECT_H
#define STUDENTOBJECT_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class StudentObject
{
    private:
        wxString name;
        wxString id;
        wxString roll_no;
        wxString className;
    public:
        StudentObject(wxString name = "NONE", wxString id = "NONE", wxString roll_no = "NONE", wxString className = "NONE");
        wxString getName();
        wxString getId();
        wxString getRollNo();
        wxString getClassName();
        //setters
        void setName(wxString &name);
        void setId(wxString &id);
        void setRollNo(wxString &roll_no);
        void setClassName(wxString &className);
};

#endif // STUDENTOBJECT_H