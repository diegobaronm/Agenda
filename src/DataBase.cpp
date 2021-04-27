#include"DataBase.hpp"

sqlite3 *db;

void CreateDB(std::string database){

    char* data = const_cast<char*>(database.c_str());

    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(data, &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }
    std::string create_table_Event_query =
        "CREATE TABLE Events("
        "EID INT PRIMARY KEY     NOT NULL, "
        "DATE          TEXT     NOT NULL, "
        "COMMENT    TEXT     NOT NULL); ";


    std::string create_table_MainTask_query =
        "CREATE TABLE MainTasks("
        "TID INT PRIMARY KEY     NOT NULL, "
        "EID INT     NOT NULL, "
        "COMPLETED      INT    NOT NULL, "
        "DATE          TEXT     NOT NULL, "
        "ASSIGNMENT    TEXT     NOT NULL); ";


    std::string create_table_SubTask_query =
        "CREATE TABLE SubTasks("
        "SUBT_ID INT PRIMARY KEY NOT NULL,"
        "TID INT    NOT NULL, "
        "COMPLETED      INT    NOT NULL, "
        "DATE  TEXT  NOT NULL, "
        "ASSIGNMENT    TEXT     NOT NULL); ";

    sqlite3_exec(db, create_table_Event_query.c_str(), NULL, 0, &zErrMsg);
    sqlite3_exec(db, create_table_MainTask_query.c_str(), NULL, 0, &zErrMsg);
    sqlite3_exec(db, create_table_SubTask_query.c_str(), NULL, 0, &zErrMsg);


    sqlite3_close(db);
}

void Execute_Query(std::string query,std::string database){
    char* data = const_cast<char*>(database.c_str());
    char* qry = const_cast<char*>(query.c_str());
    int exit = 0;
    char* messaggeError;

    std::cout<<data<<std::endl;
    std::cout<<query<<std::endl;

    exit = sqlite3_open(data, &db);
    exit = sqlite3_exec(db, qry , NULL, 0, &messaggeError);

    //std::cout<<messaggeError<<std::endl;

    if (exit != SQLITE_OK) {
        std::cerr << "Error Create Table" << std::endl;
        sqlite3_free(messaggeError);
    }
    else
        std::cout << "Table created Successfully" << std::endl;
    sqlite3_close(db);
}

int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names){

    Records* records = static_cast<Records*>(p_data);
    records->emplace_back(p_fields, p_fields + num_fields);
    return 0;
}

Records select_stmt(const char* stmt, sqlite3* db){
    Records records;
    char *errmsg;
    int ret = sqlite3_exec(db, stmt, select_callback, &records, &errmsg);
    if (ret != SQLITE_OK) {
    std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]\n";
    }
    else {
    std::cerr<< records.size() << " records returned.\n";
    }

    return records;
}
