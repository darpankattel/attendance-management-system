#include <Query.h>

Query::Query(wxString path)
{
    this->path = path;
    int rc = sqlite3_open(this->path.ToStdString().c_str(), &this->db);
    if (rc)
    {
        std::cout << "Can't open database: " << sqlite3_errmsg(this->db) << std::endl;
        sqlite3_close(this->db);
        wxMessageBox("Error creating/opening database, tried 2 times.", "Error", wxICON_ERROR);
        return;
    }

    std::cout << "Opened database successfully..." << std::endl;

}

Query::~Query()
{
    sqlite3_close(this->db);
}

void Query::query(wxString sql)
{
    char *zErrMsg = 0;
    int rc = sqlite3_exec(this->db, sql.ToStdString().c_str(), 0, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        std::cout << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }
}

sqlite3_stmt* Query::execute(wxString sql)
{
    std::cout << "Executing query: " << sql << std::endl;
    char *zErrMsg = 0;
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(this->db, sql.ToStdString().c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        std::cout << "SQL error: " << sqlite3_errmsg(this->db) << std::endl;
        sqlite3_free(zErrMsg);
        return NULL;
    }
    std::cout << "SQL executed successfully..." << std::endl;
    return stmt;
}

int Query::length(sqlite3_stmt *stmt)
{
    // return the number of rows in the result set
    int count = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        count++;
    }
    // reset the statement to the first row
    sqlite3_reset(stmt);
    return count;
}

void Query::close()
{
    sqlite3_close(this->db);
}