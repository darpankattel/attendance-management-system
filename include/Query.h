#ifndef QUERY_H
#define QUERY_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <sqlite3.h>

class Query
{
private:
    sqlite3 *db;
    wxString path;
public:
    Query(wxString myDocRootPathDb);
    ~Query();
    void query(wxString sql);
    sqlite3_stmt* execute(wxString sql);
    int length(sqlite3_stmt *stmt);
    void close();
};

#endif