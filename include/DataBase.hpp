#include<stdio.h>
#include<iostream>
#include<vector>
#include<sqlite3.h>

#ifndef DATABASE_HPP
#define DATABASE_HPP

// Header file for database related functions.

// Function to create a database for an agenda.
void CreateDB(std::string database);
// Function to execture a query in the database.
void Execute_Query(std::string query,std::string database);

//Defintion of types to make them easier to call.
using Record = std::vector<std::string>;
using Records = std::vector<Record>;
//Functions to return contents of the database as vectors of vectors.
int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names);
Records select_stmt(const char* stmt, sqlite3* db);

#endif