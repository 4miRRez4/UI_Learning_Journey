#include <iostream>
#include <cstring>
#include <chrono>
#include <thread>
#include <conio.h>
#include <fstream>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define KEY_LEFT 75
#define KEY_ENTER 13



int row, column; //making number of  rows and columns of array global;
time_t startTime = time(nullptr);

int tableLen;
int maxLen;

int textCode;
int frameCode;

struct player{
    char name[20];
    char pass[20];
    int score;
};

struct game{
    int elapsedTime;
};

int strLen(string str)
{
    int l =0;
    while(str[l])
    {
        l++;
    }
    return l;
}

int stringToInt(string str)
{
    int out=0;
    int i=0;
    int p=1;
    while(str[i])
    {
        int digit = str[i]-48;
        out = out*10 + digit;
        i++;
    }
    return out;
}

string intToString(int num)
{
    string rev = "";
    while(num != 0)
    {
        int digit = num%10;
        rev += digit+48;
        num = (num-digit)/10;
    }
    string out = "";
    for(int i=strLen(rev)-1; i>=0; i--)
    {
        out += rev[i];
    }
    return out;
}

void invalidInput();

void clearTerminal() {
    //cout << "\033[2J\033[H"; // ANSI escape codes to clear the screen
    system("cls"); //use clear for unix base
}

void changeTextColor(int colorCode) {

// [1;31m	Bold Red
// [1;32m	Bold Green
// [1;33m	Bold Yellow
// [1;34m	Bold Blue
// [1;35m	Bold Magenta
// [1;36m	Bold Cyan

    cout << "\033[1;" << colorCode << "m";
}

void selectTextColor(int color)
{
    // 1=>red 2=>blue;
    switch (color)
    {
        case 1:
        {
            textCode = 31;
            break;
        }
        case 2:
        {
            textCode = 34;
            break;
        }
        default:
        {
            invalidInput();
        }

    }
}

void selectFrameColor(int color)
{
    // 1->Green 2->Yellow 3->$ed 4->Blue
    switch (color)
    {
        case 1:
        {
            frameCode = 31;
            break;
        }
        case 2:
        {
            frameCode = 34;
            break;
        }
        default:
        {
            invalidInput();
        }

    }
}

void resetTextColor() {
    cout << "\033[0m";
}

void printNtime(char character, int n)
{
    for(int i=0; i<n; i++)
        cout << character;
}

void printSymmetry(string out)
{
    int length = strLen(out);

    changeTextColor(frameCode);
    cout << "$";
    changeTextColor(textCode);
    printNtime(' ', (maxLen-length-2)/2);
    cout << out;
    printNtime(' ', (maxLen-length-2)/2);
    if(length%2 != 0) cout << " ";
    changeTextColor(frameCode);
    cout<< "$" << endl;

}

void printBoard(char **numbers, int selecteds[4])
{
    clearTerminal();

    //printf("\x1B[40;1m"); //setting background to black using ansi codes

    //printing Header
    changeTextColor(frameCode);
    printNtime('$', maxLen); cout << endl;
    printSymmetry("NUMBERAMA");
    printNtime('$', maxLen); cout << endl;
    resetTextColor();

    //printing the Table
    changeTextColor(frameCode);
    cout << "$";
    changeTextColor(textCode);
    printNtime(' ', (maxLen-tableLen-2)/2);
    printNtime('-', tableLen);
    printNtime(' ', (maxLen-tableLen-2 +1)/2);
    changeTextColor(frameCode);
    cout << "$" << endl;

    for(int r=0; r<row; r++)
    {
        cout << "$";
        changeTextColor(textCode);
        printNtime(' ', (maxLen-tableLen-2)/2);
        cout << "|";
        for(int c=0; c<column ; c++)
        {
            //printing selected elemets colored yellow
            if ((selecteds[0] == r) && (selecteds[1] == c) || (selecteds[2] == r) && (selecteds[3] == c))
            {
                changeTextColor(33);
                cout << " " << numbers[r][c];
                changeTextColor(textCode);
                cout << " |";
            }else if(numbers[r][c] == 0)
            {
                changeTextColor(32);
                cout << " " << numbers[r][c];
                changeTextColor(textCode);
                cout << " |";
            }
            else
                cout << " " << numbers[r][c] << " |"; //ordinary elements colored textColor

        }
        printNtime(' ', (maxLen-tableLen-2)/2 +1);
        changeTextColor(frameCode);
        cout << "$" << endl;

        cout << "$";
        changeTextColor(textCode);
        printNtime(' ', (maxLen-tableLen-2)/2);
        printNtime('-', tableLen);
        printNtime(' ', (maxLen-tableLen-2 +1)/2);
        changeTextColor(frameCode);
        cout << "$" << endl;
    }
    printNtime('$', maxLen); cout << endl;

    resetTextColor();
};

void printOptions()
{
    printSymmetry("press:  s->start u->userScores    ");
    printSymmetry("        t->textColor f->frameColor");
    printSymmetry("        h->help r->reset   e->exit");
    printNtime('$', maxLen); cout << endl;
    printSymmetry("Please press a key");
    printNtime('$', maxLen); cout << endl;
}

void printHelp()
{
    clearTerminal();

    printNtime('$', maxLen); cout << endl;
    printSymmetry("A pair can be removed if either the two digits");
    printSymmetry("are same or, the sum of two digits is ten and ");
    printSymmetry("those two digits are placed next to each other");
    printSymmetry("horizontally or vertically.");
    printSymmetry("If other number between them have been removed");
    printSymmetry("then it is also a valid pair.");
    printSymmetry("The game is over, when there is not any valid ");
    printSymmetry("move in the board.");
    printSymmetry("Have Fun.");
    printNtime('$', maxLen);

}

//int maxNumberNeeded()
//    //*this functions can be used for true game logic(that we have edited it for now)
//{
//    //calculating maximum number that can be used in the table;
//    int numOfPlace = row * column;
//    int maxNum;
//    if (numOfPlace < 9)
//        maxNum = numOfPlace;
//    else
//    {
//        maxNum = (((numOfPlace - 9) / 2)) + 9;
//        if (((numOfPlace - 9) % 2) != 0)
//            maxNum++;
//    }
//    return maxNum;
//}

//string defaulBoardGenerator()
//{
//    string def = "";
//    int counter = 1;
//    for(int i=0; i<maxNumberNeeded(); i++)
//    {
//        def += intToString(counter);
//        counter++;
//    }
//    return def;
//}

string defaultBoardGenerator()
{
    string zeros ="";
    for(int i=0; i<row*column; i++)
    {
        zeros += "0";
    }
    return zeros;
}

string randBoardGenerator() {

    //generating random numbers to fill table(numbers until 9 fill just one place, and after that numbers fill two of them);
    string generated = "";

    srand(time(0));
    //generating random numbers in range (1,9)
    int randomNumber;
    for(int i=0; i<row*column; i++)
    {
        randomNumber = (rand() % 9) +1;
        //adding number generated to string
        generated += intToString(randomNumber);
    }

    //random place for star
    int starPlace = (rand() % row*column);
    generated[starPlace] = '*';

    //making sure that one pair is valid
    int randPlace = (rand() % row*column);
    generated[randPlace] = '3';
    generated[randPlace+1] = '3';

    return generated;
}

void settingBoard(char **numbers, string Board)
{
    int state_i =0;
    for(int r=0; r<row; r++) //iterating on rows
    {
        for(int c=0; c<column; c++) //iterating on columns;
        {
            numbers[r][c] = Board[state_i];
            state_i++;
        }
    }
}

void sorting(char *tmpForSort, int l)
{
    //bubble sort
    for(int i=0; i<l-1; i++)
    {
        for(int j=0; j<l-i-1; j++)
        {
            if(tmpForSort[j] > tmpForSort[j+1])
            {
                char temp = tmpForSort[j];
                tmpForSort[j] = tmpForSort[j+1];
                tmpForSort[j+1] = temp;
            }
        }
    }


}

void sortingPlayers(player *players, int allInd)
{
    //insertion sort
    for(int i=1; i<allInd; i++)
    {
        player tmp = players[i];
        int j;
        for(j=i-1; j>=0; j--)
        {
            if(tmp.score == players[j].score && strcmp(tmp.name, players[j].name) < 0) {
                players[j + 1] = players[j];
            }
            else if(tmp.score < players[j].score)
            {
                players[j+1] = players[j];
            }else
            {
                break;
            }
        }
        players[j+1] = tmp;
    }
}

bool isPairValid(int selectedElement, int suspectedElement)
{
    if(suspectedElement == 'X' || selectedElement == 'X')
        return false;

    //is sum ten?
    else if((suspectedElement-48) + (selectedElement-48) == 10)
        return true;

    //is it same?
    else if(suspectedElement == selectedElement)
        return true;

    else
        return false;
}

int isGameOver(char **numbers)
{
    //iterating on every element
    //checking if there is another correct move
    for(int r=0; r<row; r++)
    {
        for(int c=0; c<column; c++)
        {
            char selectedElement = numbers[r][c];
            int elementC = c;
            int elementR = r;
            bool isThereMove = false;
            if(selectedElement != '*' && selectedElement != 'X') {
                //checking horizontally
                char suspectedElement = 'X';
                //selecting right element
                while (suspectedElement == 'X' || suspectedElement == '*') {
                    if ((elementC > 0) && (elementC < column-1)) {
                        suspectedElement = numbers[r][elementC + 1];
                        elementC++;
                    }else
                        break;

                }
                isThereMove = isPairValid(selectedElement, suspectedElement);
                if (isThereMove)
                    return r*10 + c;

                suspectedElement = 'X';
                elementC = c;
                //selecting left element
                while (suspectedElement == 'X' || suspectedElement == '*') {
                    if ((elementC > 0) && (elementC < column-1)) {
                        suspectedElement = numbers[r][elementC - 1];
                        elementC--;
                    }else
                        break;
                }
                isThereMove = isPairValid(selectedElement, suspectedElement);
                if (isThereMove)
                    return r*10 + c;

                suspectedElement = 'X';
                //selecting down element
                while (suspectedElement == 'X' || suspectedElement == '*') {
                    if ((elementR > 0) && (elementR < row-1)) {
                        suspectedElement = numbers[elementR + 1][c];
                        elementR++;
                    }else
                        break;
                }
                isThereMove = isPairValid(selectedElement, suspectedElement);
                if (isThereMove)
                    return r*10 + c;

                suspectedElement = 'X';
                //selecting up element
                while (suspectedElement == 'X' || suspectedElement == '*') {
                    if ((elementR > 0) && (elementR < row-1)) {
                        suspectedElement = numbers[elementR-1][c];
                        elementR--;
                    }else
                        break;
                }
                isThereMove = isPairValid(selectedElement, suspectedElement);
                if (isThereMove)
                    return r*10 + c;
            }
        }
    }

    return -1;
}

void invalidInput()
{
    printSymmetry("Invalid input! please try again.");
    printNtime('$', maxLen);

    // Adding a delay
    this_thread::sleep_for(chrono::seconds(1));
}

void moving(int move, int selecteds[4], int which)
{
    if(move == 0 || move == 224) //checking if pressed button is arrows
    {
        switch (getch()) {
            //moving around board
            case KEY_UP: {
                if (selecteds[which + 0] > 0)//checking row
                    selecteds[which + 0] -= 1;
                else {
                    invalidInput();
                }
                break;
            }
            case KEY_DOWN: {
                if (selecteds[which + 0] < row - 1)//checking row
                {
                    selecteds[which + 0] += 1;
                } else {
                    invalidInput();
                }
                break;
            }
            case KEY_RIGHT: {
                if (selecteds[which + 1] < column - 1)//checking column
                    selecteds[which + 1] += 1;
                else {
                    invalidInput();
                }
                break;
            }
            case KEY_LEFT: {
                if (selecteds[which + 1] > 0)// checking column
                    selecteds[which + 1] -= 1;
                else {
                    invalidInput();
                }
                break;
            }

            default: {
                invalidInput();
            }
        }
    }else
    {
        invalidInput();
    }
}

void specialChar(char **numbers, int selecteds[4], player *p, int currentInd)
{
    int len;
    bool isRow = false;
    bool isSort = false;
    if(selecteds[0] == selecteds[2])//sorting selected row
    {
        sorting(numbers[selecteds[0]], column);
        numbers[selecteds[0]][0] = 'X'; // deleting star;
        len = column;
        isRow = true;
        isSort = true;
    }else if (selecteds[1] == selecteds[3])//sorting selected column
    {
        char columnForSort[row];
        for(int i=0; i<row; i++)
            columnForSort[i] = numbers[i][selecteds[1]];

        sorting(columnForSort, row);

        numbers[0][selecteds[1]] = 'X'; // deleting star;
        for(int i=1; i<row; i++)
            numbers[i][selecteds[1]] = columnForSort[i];

        len = row;
        isRow = false;
        isSort = true;
    }else
    {
        invalidInput();
        isSort=false;
    }

    if(isSort) {
        for (int i = 1; i < len - 1; i++)//iteration and check if there is a pair;
        {
            if (isRow) {
                if (i + 1 < column && isPairValid(numbers[selecteds[0]][i], numbers[selecteds[0]][i+1])) {
                    numbers[selecteds[0]][i] = 'X';
                    numbers[selecteds[0]][i + 1] = 'X';
                    p[currentInd].score++;
                }
                if (selecteds[0] - 1 >= 0 && isPairValid(numbers[selecteds[0]][i], numbers[selecteds[0]-1][i])) {
                    numbers[selecteds[0]][i] = 'X';
                    numbers[selecteds[0]-1][i] = 'X';
                    p[currentInd].score++;
                }
                if (selecteds[0] + 1 < row && isPairValid(numbers[selecteds[0]][i], numbers[selecteds[0]+1][i])) {
                    numbers[selecteds[0]][i] = 'X';
                    numbers[selecteds[0]+1][i] = 'X';
                    p[currentInd].score++;
                }
            } else {
                if (selecteds[1]+1 < column && isPairValid(numbers[i][selecteds[1]], numbers[i][selecteds[1]+1])) {
                    numbers[i][selecteds[1]] = 'X';
                    numbers[i][selecteds[1]+1] = 'X';
                    p[currentInd].score++;
                }
                if (selecteds[1]-1 >= 0 && isPairValid(numbers[i][selecteds[1]], numbers[i][selecteds[1]-1])) {
                    numbers[i][selecteds[1]] = 'X';
                    numbers[i][selecteds[1]-1] = 'X';
                    p[currentInd].score++;
                }
                if (i + 1 < row && isPairValid(numbers[i][selecteds[1]], numbers[i+1][selecteds[1]])) {
                    numbers[i][selecteds[1]] = 'X';
                    numbers[i+1][selecteds[1]] = 'X';
                    p[currentInd].score++;
                }
            }
        }
    }
}

void playingGame(char **numbers, int *selecteds, player *p, int *currentInd)
{
    auto startTime = chrono::steady_clock::now();
    const int timerDurationSeconds = 90;

    // Main game loop
    for(int i=0; i<4; i++)
    {
        selecteds[i] = 0;
    }
    game g;
    g.elapsedTime=0;
    int which =0;
    while (true) {
        // Calculating elapsed time
        auto currentTime = chrono::steady_clock::now();
        g.elapsedTime = chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

        // Displaying the game board
        printBoard(numbers, selecteds);

        // Displaying the timer
        string s = "Remaining Time => ";
        string time = intToString(timerDurationSeconds - g.elapsedTime);
        printSymmetry(s + time);
        printNtime('$', maxLen);
        cout << endl;

        //Displaying help for playing
        printSymmetry("Use 'ARROWS' to move and 'ENTER' for selecting");
        printSymmetry("Press 'q' for quit.");
        printSymmetry("Press 'h' for hint.");
        printNtime('$', maxLen);
        cout << endl;

        // Check if the timer has expired
        if (g.elapsedTime >= timerDurationSeconds) {
            printSymmetry("Time's up! Game Over!");
            printNtime('$', maxLen);
            // Adding a delay
            this_thread::sleep_for(chrono::seconds(1));
            break;
        }

        //checking if game is over;
        int hint = isGameOver(numbers);
        if(hint == -1)
        {
            printSymmetry("Congratulations! you won!");
            p[*currentInd].score++;
            // Adding a delay
            this_thread::sleep_for(chrono::seconds(2));
            break;
        }

        // game logic:
        //user selecting two elements
        int move = getch();
        if(move == 'h')
        {
            cout << "attention on row " << hint/10 << " and column " << hint%10;
            this_thread::sleep_for(chrono::seconds(1));
        }
        else if (move == KEY_ENTER) {
            //condition of selecting first one
            if (numbers[selecteds[0]][selecteds[1]] == 'X') {
                invalidInput();
                which = 0;
                continue;
            }
            else {
                if(which == 0)
                    which = 2; //going to select second one after this
                else//second enter
                {
                    if (numbers[selecteds[2]][selecteds[3]] == 'X') {
                        invalidInput();
                        which = 0;
                        continue;
                    }
                    if(numbers[selecteds[2]][selecteds[3]] == '*' || numbers[selecteds[0]][selecteds[1]] == '*')
                    {
                        specialChar(numbers, selecteds, &p[0], *currentInd);
                        continue;
                    }

                    //checking neighborhood
                    if(selecteds[1] == selecteds[3]) //checking if they're neighbors vertically;
                    {
                        if(selecteds[0] < selecteds[2])//second element is in downside of first one;
                        {
                            int suspectedRow = selecteds[0] + 1;

                            while (numbers[suspectedRow][selecteds[1]] == 'X' && suspectedRow < row)
                                suspectedRow++;

                            if (numbers[suspectedRow][selecteds[1]] == 'X' || suspectedRow != selecteds[2]) {
                                invalidInput();
                                which = 0;
                                continue;
                            }
                        }else //second element is in above of first one;
                        {
                            int suspectedRow = selecteds[0] - 1;

                            while (numbers[suspectedRow][selecteds[1]] == 'X' && suspectedRow >= 0)
                                suspectedRow--;

                            if (numbers[suspectedRow][selecteds[1]] == 'X' || suspectedRow != selecteds[2]) {
                                invalidInput();
                                which = 0;
                                continue;
                            }
                        }
                    }else if (selecteds[0] == selecteds[2]) //checking if they're neighbors horizontally;
                    {
                        if(selecteds[1] < selecteds[3]) //checking downside of first one
                        {
                            int suspectedCol = selecteds[1] + 1;

                            while (numbers[selecteds[0]][suspectedCol] == 'X' && suspectedCol < column)
                                suspectedCol++;

                            if (numbers[selecteds[0]][suspectedCol] == 'X' || suspectedCol != selecteds[3]) {
                                invalidInput();
                                which = 0;
                                continue;
                            }
                        }
                        else//checking left side of first element
                        {
                            int suspectedCol = selecteds[1] - 1;

                            while (numbers[selecteds[0]][suspectedCol] == 'X' && suspectedCol >= 0)
                                suspectedCol--;

                            if (numbers[selecteds[0]][suspectedCol] == 'X' || suspectedCol != selecteds[3]) {
                                invalidInput();
                                which = 0;
                                continue;
                            }
                        }

                    }else//they're not neighbors horizontally or vertically at all;
                    {
                        invalidInput();
                        which = 0;
                        continue;
                    }

                    //checking condition of pairs
                    if (isPairValid(numbers[selecteds[0]][selecteds[1]], numbers[selecteds[2]][selecteds[3]])) {
                        numbers[selecteds[0]][selecteds[1]] = 'X';
                        numbers[selecteds[2]][selecteds[3]] = 'X';

                        which = 0;

                        p[*currentInd].score++;
                    }
                    else {
                        invalidInput();
                        which = 0;
                    }
                }

            }

        }else if(move == 'q')
        {
            for(int i=0; i<4; i++)
            {
                selecteds[i] = 0;
            }
            //save;
            break;
        }
        else
            moving(move, selecteds, which); //moving for selecting


        // Adding a delay to make the timer update every second
        //this_thread::sleep_for(chrono::seconds(1));
    }
}


int main() {
    //getting row and column from input;
    cin >> row >> column;
    //allocating memory
    char **numbers = new char *[row];
    for(int r=0; r<row; r++)
        numbers[r] = new char [column];

    tableLen  = (column*4+1); //minimum len need for printing only table part
    maxLen =(tableLen > 50) ? tableLen+3:50; //len needed for printing frame

    //default colors
    textCode =35; //Magenta
    frameCode =36; //Cyan

    //main page
    while(true)
    {
        string Board = defaultBoardGenerator();
        settingBoard(numbers, Board);
        int selecteds[4] = {0}; //this array stores row and column of two elements for printing in yellow(r1, c1, r2, c2);
        printBoard(numbers, selecteds);
        printOptions();

        int option = getch();
        switch (option) {
            case 's': {
                //checking file for player info
                player players[20] = {0};
                int allInd=0;
                ifstream inFile("info.txt", ios::in);
                for(int i=0; i<20; i++)
                {
                    inFile >> players[i].name
                            >> players[i].pass
                            >> players[i].score;
                }
                while(strcmp(players[allInd].name, "") != 0)
                {
                    allInd++;
                }

                printSymmetry("Please enter your name: ");
                char name[10];
                cin >> name;
                printSymmetry("Please enter you password: ");
                char pass[10];
                cin >> pass;
                bool shouldBreak = false;
                bool isFound = false;
                int currentInd =0;
                for(int i=0; i<allInd; i++)
                {
                    if(strcmp(name, players[i].name) == 0)
                    {
                        if(strcmp(pass, players[i].pass) != 0)
                        {
                            printSymmetry("Your password is incorrect!!");
                            // Adding a delay
                            this_thread::sleep_for(chrono::seconds(2));
                            shouldBreak = true;
                        }else
                        {
                            isFound = true;
                            currentInd = i;
                        }
                        break;
                    }
                }
                if(!isFound)
                {
                    currentInd = allInd;
                    allInd++;
                    strcpy(players[currentInd].name, name);
                    strcpy(players[currentInd].pass, pass);
                    players[currentInd].score = 0;
                }
                if(shouldBreak) break;

                //playing
                Board = randBoardGenerator();
                settingBoard(numbers, Board);
                playingGame(numbers, &selecteds[0], &players[0], &currentInd);

                //sorting players
                sortingPlayers(players, allInd);

                //saving player info
                ofstream outFile("info.txt", ios::out);
                if (!outFile.is_open())
                {
                    printSymmetry("File didn't open!!!");
                    break;
                }
                for (int i = 0; i < allInd; ++i)
                {
                    outFile << players[i].name << " "
                            << players[i].pass << " "
                            << players[i].score << endl;
                }
                break;
            }

            case 'u': {
                clearTerminal();
                //printing history
                player players[20] = {0};
                int allInd=0;
                ifstream inFile("info.txt", ios::in);
                for(int i=0; i<20; i++)
                {
                    inFile >> players[i].name
                           >> players[i].pass
                           >> players[i].score;
                }
                while(strcmp(players[allInd].name, "") != 0)
                {
                    allInd++;
                }
                ofstream outFile("info.txt", ios::out);
                if (!outFile.is_open())
                {
                    printSymmetry("File didn't open!!!");
                    break;
                }
                for (int i = 0; i < allInd; ++i)
                {
                    outFile << players[i].name << " "
                            << players[i].pass << " "
                            << players[i].score << endl;
                }
                for(int i=0; i<allInd; ++i)
                {
                    cout << players[i].name << "->" << players[i].score << endl;
                }
                cout<<"Enter any key to continue";
                int tmp = getch();
                break;
            }

            case 't': {
                //changing text color
                printSymmetry("1->Red      2->Blue");
                printSymmetry("Please enter a number: ");
                string color;
                cin >> color;
                selectTextColor(stringToInt(color));
                break;
            }

            case 'f': {
                //changing frame color
                printSymmetry("1->Red     2 ->Blue");
                printSymmetry("Please enter a number: ");
                string color;
                cin >> color;
                selectFrameColor(stringToInt(color));
                break;
            }

            case 'h': {
                printHelp();
                cout << endl;
                printSymmetry("Enter any key to continue");
                printNtime('$', maxLen);
                int tmp = getch();
                break;
            }

            case 'r': {
                //reseting the game
                ofstream outFile("info.txt", ios::out);
                outFile << "";
                printSymmetry("you have reseted history!!!");
                this_thread::sleep_for(chrono::seconds(1));
                break;
            }

            case 'e': {
                //exiting the game

                printSymmetry("Have a good day.");
                printNtime('$', maxLen);
                //deleting allocated memory
                for(int r=0; r<row; r++)
                    delete [] numbers[r];
                delete [] numbers;

                resetTextColor();
                return 0;
            }

            default: {
                invalidInput();
            }
        }
    }

}
