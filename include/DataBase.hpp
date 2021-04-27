#include<stdio.h>
#include<iostream>
#include<vector>
#include<sqlite3.h>

#ifndef DATABASE_HPP
#define DATABASE_HPP

void CreateDB(std::string database);
void Execute_Query(std::string query,std::string database);

using Record = std::vector<std::string>;
using Records = std::vector<Record>;

int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names);
Records select_stmt(const char* stmt, sqlite3* db);

#endif