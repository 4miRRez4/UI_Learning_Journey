#include "../include/dataBase.h"
#include "../include/cli.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    Database* db = new Database();
    //TODO: default table users...
    handleUserInput(db);

    return 0;
}
