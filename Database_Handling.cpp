#include "databasehandler.h"
#define dbName "bleh.db"


using namespace std;

sqlite3 *dbfile;
bool dbOpen=false;

void openTheDB(){
	if ( sqlite3_open(dbName, &dbfile) == SQLITE_OK )
    {
        dbOpen = true;
    }     
}
string getCategories()
{
	if(!dbOpen)
		openTheDB();
    sqlite3_stmt *statement;
	string stat;
    char *query = "select id,category from super_market";

    if ( sqlite3_prepare(dbfile, query, -1, &statement, 0 ) == SQLITE_OK ) 
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )
        {
            res = sqlite3_step(statement);

            if ( res == SQLITE_ROW ) 
            {
                for ( int i = 0; i < ctotal; i++ ) 
                {
                    string s = (char*)sqlite3_column_text(statement, i);
                    stat=stat+s+"\t";
                }
                stat+="\n";
            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                stat+="Enter desired category: ";
                break;
            }    
        }
        sqlite3_finalize(statement);
    }
    return stat;
}
