#include "../include/dataBase.h"
#include "../include/cli.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    Database* db = new Database();
    handleUserInput(db);

    return 0;
}
