#ifndef CLI_H
#define CLI_H

#include "dataBase.h"

void displayMenu();
void handleUserInput(Database* db);
void createTable(Database* db);
void insertRecord(Database* db);
void updateRecord(Database* db);
void deleteRecord(Database* db);
void searchRecord(Database* db);
void printAllRecords(Database* db);
void performAggregation(Database* db);

#endif
