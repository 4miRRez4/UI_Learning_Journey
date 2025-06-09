#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;



int len(string str)
{
    int i =0;
    int l =0;
    while(str[i])
    {
        i++;
        l++;
    }
    return l;
}

int stringToInt(string str)
{
    int l = len(str);
    int sum=0;
    for(int i=0; i<l; i++)
    {
        sum = sum*10 + str[i]-48;
    }
    return sum;
}

string intToString(int num)
{
    string reversed = "";
    while(num != 0)
    {
        char digit = (num % 10)+48;
        reversed += digit;
        num = (num-num%10)/10;
    }

    //reversing
    string out = "";
    for(int i=len(reversed)-1; i>=0; i--)
    {
        out += reversed[i];
    }

    return out;
}

void addTextToLine(const string& inputFileName, int targetLine, const string& newText) {
    //opening the file
    fstream read_file;
    read_file.open(inputFileName);

    // If file failed to open, exit with an error message and error exit status
    if (read_file.fail())
    {
        cout << "Error opening file." << endl;
    }

    vector<string> lines;
    string line;

    // Reading each line of the file and store it as the next element of the vector,
    while (getline(read_file, line))
        lines.push_back(line);

    read_file.close();

    ofstream write_file;
    write_file.open(inputFileName);

    if(write_file.fail())
        cout << "Error opening file." << endl;

    int end = (targetLine<lines.size()) ? lines.size():targetLine;
    for(int i=0; i< end+1; i++)
    {
        if(i != targetLine)
        {
            write_file << lines[i] << endl;
        }else
        {
            write_file << newText << endl;
        }
    }


}

void updateAndShift(const string& inputFileName, const string& newText)
{
    fstream read_file;
    read_file.open(inputFileName);

    if(read_file.fail())
    {
        cout << "Error opening file." << endl;
    }

    vector<string> lines;
    string line;

    while(getline(read_file, line))
    {
        lines.push_back(line);
    }
    read_file.close();

    ofstream write_file;
    write_file.open(inputFileName);
    if(write_file.fail())
        cout << "Error opening file." << endl;

    for(int i=0; i<10; i++)
    {
        //line 0 being same;
        if(i == 0 || i == 1)
            write_file << lines[i] << endl;
        else
            // shifting line backward
            write_file << lines[i+1] << endl;
    }
    write_file << newText << endl; // adding last outcome
}

void showHistory(int totalRounds)
{
    ifstream read_file;
    read_file.open("history.txt");

    if(read_file.fail())
        cout << "Error opening file.";

    printf("\033[01;33m");
    string line;
    int c = 1;
    while(getline(read_file, line)) {
        if(line == "") continue;
        if (c == 1) {
            cout << "number of rounds: " << line << endl;
        }else if(totalRounds >10) {
            cout << "Winner of round " << c+(totalRounds-11) << " -> " << line << endl;
        }else
        {
            cout << "Winner of round " << c-1 << " -> " << line << endl;
        }
        c++;
    }
    read_file.close();
    printf("\033[1;35m");
}


void settingBoard(char board[3][3], string def)
{
    // setting board to place num or last board:
    int k =0;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            board[i][j] = def[k];
            k++;
        }
    }
}

void printingHeader()
{
    printf("\033[1;35m");
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    cout << "$" ;
    printf("\033[1;36m");
    cout << "             ";
    cout << "\U0001F47E";
    cout << "Welcome to XO Game";
    cout << "\U0001F47E";
    cout << "             ";
    printf("\033[1;35m");
    cout << "$" << endl;
}

void printingDescription()
{
    printf("\033[1;35m");
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    cout << "$" ;
    printf("\033[1;36m");
    cout << "  press:  1->start         2->show history      ";
    printf("\033[1;35m");
    cout << "$" << endl;
    cout << "$" ;
    printf("\033[1;36m");
    cout << "          3->instructions  4->reset   5->exit   ";
    printf("\033[1;35m");
    cout << "$" << endl;
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
}

void printingBoard(char board[3][3])
{
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    cout << "$" << "                                                " << "$" << endl;
    cout << "$" << "                 " ;
    printf("\033[1;36m");
    cout << "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501" ;
    printf("\033[1;35m");
    cout << "                  " << "$" << endl;
    cout << "$" << "                 " ;
    printf("\033[1;36m");
    cout << "\u2503 " << board[0][0] << " ";
    cout << "\u2503 " << board[0][1] << " ";
    cout << "\u2503 " << board[0][2] << " \u2503" ;
    printf("\033[1;35m");
    cout << "                  " << "$" << endl;

    cout << "$" << "                 " ;
    printf("\033[1;36m");
    cout << "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501" ;
    printf("\033[1;35m");
    cout << "                  " << "$" << endl;
    cout << "$" << "                 " ;
    printf("\033[1;36m");
    cout << "\u2503 " << board[1][0] << " ";
    cout << "\u2503 " << board[1][1] << " ";
    cout << "\u2503 " << board[1][2] << " \u2503" ;
    printf("\033[1;35m");
    cout << "                  " << "$" << endl;

    cout << "$" << "                 " ;
    printf("\033[1;36m");
    cout << "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501" ;
    printf("\033[1;35m");
    cout << "                  " << "$" << endl;
    cout << "$" << "                 " ;
    printf("\033[1;36m");
    cout << "\u2503 " << board[2][0] << " ";
    cout << "\u2503 " << board[2][1] << " ";
    cout << "\u2503 " << board[2][2] << " \u2503" ;
    printf("\033[1;35m");
    cout << "                  " << "$" << endl;
    cout << "$" << "                 " ;
    printf("\033[1;36m");
    cout << "\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501" ;
    printf("\033[1;35m");
    cout << "                  " << "$" << endl;

    cout << "$" << "                                                " << "$" << endl;
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;

}

void printingInstructions()
{
    printf("\033[01;33m");
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    cout << "$ " << "The XO game, also known as Tic-Tac-Toe, is a" << "   $" << endl;
    cout << "$ " << "simple two-player game played on a 3x3 grid." << "   $" << endl;
    cout << "$ " << "The goal is to be the first to create a line" << "   $" << endl;
    cout << "$ " << "of three of your own symbols (either X or O)" << "   $" << endl;
    cout << "$ " << "either horizontally, vertically, or         " << "   $" << endl;
    cout << "$ " << "dianoally.                                  " << "   $" << endl;
    cout << "$ " << "Here are the basic instructions for playing:" << "   $" << endl;
    cout << "$ " << "Objective:Be the first player to form a line" << "   $" << endl;
    cout << "$ " << "of three of your symbols (X or O) in a row, " << "   $" << endl;
    cout << "$ " << "either horizontally, vertically, or         " << "   $" << endl;
    cout << "$ " << "diagonally.                                 " << "   $" << endl;
    cout << "$ " << "Draw:                                       " << "   $" << endl;
    cout << "$ " << "If all the cells are filled and no player has" << "  $" << endl;
    cout << "$ " << "formed a line of three, the game is a draw. " << "   $" << endl;
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    printf("\033[01;35m");



}

void start(char board[3][3], string def)
{
    settingBoard(board, def);
    printingHeader();
    printingBoard(board);
    //printingDescription();
}

bool checkWinning(char board[3][3], char player) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }

    return false;
}

bool isDraw(char board[3][3]) {
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++) {
            if (board[i][j] <= '9' && board[i][j] >= '1')
                return false;
        }
    }
    return true;
}

void invalidInput()
{
    printf("\033[1;31m");
    cout << "Invalid input. please try again." << endl;
    printf("\033[1;35m");
}

void cleaning(string fileName)
{
    ofstream write_file;
    write_file.open(fileName);
    cout << "";
    write_file.close();
}

int main() {
    char board[3][3];
    char player1 = 'X';
    char player2 = 'O';

    //getting gamesplayed from history;
    fstream history("history.txt"); //opening file
    if (!history.is_open()) {
        cout << "Failed to open the file for reading." << endl;
        return 1;
    }

    int gamesPlayedI = 0;
    string gamesPlayed;
    getline(history, gamesPlayed);
    if(gamesPlayed != "")
        gamesPlayedI = stringToInt(gamesPlayed);
    history.close();

    string defaultBoard = "123456789";
    start(board, defaultBoard);

    while(true)
    {
        printingDescription();
        string condition ;
        cout << "Please press a number: ";
        cin >> condition;



        switch (stringToInt(condition)){
            case 1: {
                char currentPlayer = (gamesPlayedI % 2 == 0) ? player1 : player2; //switiching starter in each game;
                //checking for last board;
                ifstream read_file;
                read_file.open("lastBoard.txt");
                string lastBoard = "";
                getline(read_file,lastBoard);
                read_file.close();

                defaultBoard = "123456789";
                if(lastBoard != "")
                {
                    cout << "You have been playing!" <<endl;
                    cout << "You wanna continue or  play new game: (c or n) ";
                    char corn;
                    cin >> corn;
                    if (corn == 'c') {
                        defaultBoard = lastBoard;
                    }
                }
                settingBoard(board, defaultBoard);


                string outcome ="";
                while (true) //playing game
                {
                    printingBoard(board);

                    //player making a move
                    int place, row, column;
                    cout << "Player " << currentPlayer << ", enter your move(1-9): ";
                    cin >> place;
                    if (place % 3 != 0) {
                        row = place / 3;
                        column = place % 3 - 1;
                    } else {
                        row = (place / 3) - 1;
                        column = 2;
                    }

                    //checking if chosen place in valid;
                    if ((place < 1 || place > 9) || board[row][column] == 'X' || board[row][column] == 'O') {
                        invalidInput();
                        continue;
                    }
                    //making the move
                    board[row][column] = currentPlayer;

                    //saving the board;
                    string tmp="";
                    for(int r=0; r<3; r++)
                    {
                        for(int c=0; c<3; c++)
                        {
                            tmp += board[r][c];
                        }
                    }
                    ofstream write_file;
                    write_file.open("lastBoard.txt");
                    write_file << tmp << endl;
                    write_file.close();




                    //cheking if the current player has won;
                    if (checkWinning(board, currentPlayer)) {
                        printingBoard(board);
                        cout << "Player " << currentPlayer << " won!" << endl;
                        outcome += currentPlayer;
                        break;
                    }

                    //cheking for draw
                    if(isDraw(board))
                    {
                        printingBoard(board);
                        cout << "Draw!" << endl;
                        outcome += "Draw";
                        break;
                    }

                    //switching player for next round
                    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                }
                //cleaning last board
                ofstream write_file;
                write_file.open("lastBoard.txt");
                write_file << "";
                write_file.close();




                //updating number of games played;
                gamesPlayedI++;
                gamesPlayed = intToString(gamesPlayedI);
                addTextToLine("history.txt", 0, gamesPlayed);

                //adding result to end of history;
                if (gamesPlayedI > 10)
                    updateAndShift("history.txt", outcome);
                else
                    addTextToLine("history.txt", gamesPlayedI, outcome);
                break;
            }

            case 2: {
                if(gamesPlayedI == 0)
                    cout << "You haven't played yet! Enter 1." << endl;
                else
                    showHistory(gamesPlayedI);
                break;
            }

            case 3: {
                printingInstructions();
                break;
            }

            case 4: {
                //cleaning history
                cleaning("history.txt");

                //cleaning last board
                cleaning("lastBoard.txt");

                //setting number of played games to zero;
                gamesPlayedI =0;
                gamesPlayed ="0";

                defaultBoard = "123456789";
                start(board, defaultBoard);
                break;
            }
            case 5: {
                cout << "Have a good day.";
                return 0;
            }
            default:
            {
                invalidInput();
            }
        }
    }

    return 0;
}
