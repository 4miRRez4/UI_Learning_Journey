#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
using namespace std;

int TABLE_LENGTH = 14*6 + 7*2 + 2 + 12; //6 cards + 7 spaces + 2 frame + title
int CARD_WIDTH = 14;
int CARD_HEIGHT = 5;

enum cardType {KaleKado, GorBeGor, KohnePich};
string ctArr[3] = {"KaleKado", "GorBeGor", "KohnePich"};

struct Card{
    cardType type;
    int score;
};

struct Player{
    string name;
    int score=0;
    vector<Card> hand;
    vector<Card> show;
};

class cardStack{
    public:
    cardStack(){ top = -1;}
    void push(Card x){
        if(top == 89)
        {
            cout << "ERROR!" << endl;
            return;
        }
        arr[++top] = x;
    }
    void pop(){
        if(top == -1)
        {
            cout << "ERROR!" << endl;
            return;
        }
        top--;
    }
    Card Top()
    {
        if(top == -1)
        {
            cout << "ERROR!!!!!!!!!!!" << endl;
            Card c; return c;
        }
        return arr[top];
    }
    void shuffle_kastel();
    int Size()
    {
        return top+1;
    }
    void free()
    {
        top = -1;
    }
    private:
    Card arr[90];
    int top;    
};
void cardStack::shuffle_kastel()
{
    srand(time(0));
    for(int i=0; i<200; i++)
    {
        int a = rand() % 90;
        int b = rand() % 90;
        Card tmp = arr[a];
        arr[a] = arr[b];
        arr[b] = arr[a];
    }
}

class bad_input_exception {};

void to_magneta(){
    cout << "\033[1;35m";
}
void to_cyan(){
    cout << "\033[1;36m";
}
void reset_color(){
    cout << "\033[0m";
}
void clear_terminal(){
    system("clear");
}

void print_n_time(int n, char ch)
{
    for(int i=0; i<n; i++)
        cout << ch;
}

void print_text(string str)
{
    int spaces = (TABLE_LENGTH-2-str.length()) / 2;
    to_magneta();
    cout << "$";
    to_cyan();
    print_n_time(spaces, ' ');
    cout << str;
    print_n_time(spaces, ' ');
    if(str.length() %2 != 0)
        cout << " ";
    to_magneta();
    cout << "$";
    reset_color();
}

void print_header()
{
    to_magneta();
    print_n_time(TABLE_LENGTH, '$'); cout << endl;
    reset_color();
    print_text("KASTEL GAME TABLE"); cout << endl;
    to_magneta();
    print_n_time(TABLE_LENGTH, '$'); cout << endl;
    reset_color();
}

void print_cards(int playerInd, string name, vector<Card> cards)
{
        print_text(to_string(playerInd+1) + "." + name + ":"); cout << endl;
        //prining dashes for first line of card
        string line = "";
        for(int j=0; j<cards.size(); j++)
        {
            for(int i=0; i<CARD_WIDTH; i++)
                line += "-";
            line += "  ";
        }
        print_text(line); cout << endl;

        //printing score of card for second line of card
        line = "";
        for(int j=0; j<cards.size(); j++)
        {
            line += "|";
            line += to_string(cards[j].score);
            if(cards[j].score < 10)
                line += " ";
            for(int m=0; m<10; m++)
                line += " ";
            line += "|  ";
        }
        print_text(line); cout << endl;

        //prining spaces for third line of card
        line = "";
        for(int j=0; j<cards.size(); j++)
        {
            line += "|";
            for(int m=0; m<CARD_WIDTH-2; m++)
                line += " ";
            line += "|  ";
        }
        print_text(line); cout << endl;

        //printing type of card for forth line of card
        line = "";
        for(int j=0; j<cards.size(); j++)
        {
            line += "|";
            for(int m=0; m<(CARD_WIDTH-2-ctArr[cards[j].type].length())/2; m++)
                line += " ";
            line += ctArr[cards[j].type];
            for(int m=0; m<(CARD_WIDTH-2-ctArr[cards[j].type].length())/2; m++)
                line += " ";
            if(ctArr[cards[j].type].length()%2 != 0)
                line += " ";
            line += "|  ";
        }
        print_text(line); cout << endl;

        //prining spaces
        line = "";
        for(int j=0; j<cards.size(); j++)
        {
            line += "|";
            for(int m=0; m<CARD_WIDTH-2; m++)
                line += " ";
            line += "|  ";
        }
        print_text(line); cout << endl;

        //prining score
        line = "";
        for(int j=0; j<cards.size(); j++)
        {
            line += "|";
            for(int m=0; m<CARD_WIDTH-2-2; m++)
                line += " ";
            if(cards[j].score < 10)
                line += " ";
            line += to_string(cards[j].score);
            line += "|  ";
        }
        print_text(line); cout << endl;

        //printing dashes
        line = "";
        for(int j=0; j<cards.size(); j++)
        {
            for(int i=0; i<CARD_WIDTH; i++)
                line += "-";
            line += "  ";
        }
        print_text(line); cout << endl;
}

void print_table(int numOfPlayers, vector<Player> players, int turnInd)
{
    clear_terminal();
    print_header();
    //printing shows
    for(int p=0; p<players.size(); p++)
        print_cards(p, players[p].name, players[p].show);
    //printing hand of specific player
    to_magneta();
    print_n_time(TABLE_LENGTH, '$'); cout << endl; reset_color();
    print_text("$$HAND$$"); cout << endl;
    print_cards(turnInd, players[turnInd].name, players[turnInd].hand);
    to_magneta();
    print_n_time(TABLE_LENGTH, '$'); cout << endl; reset_color();
}

void init_kastel(cardStack& kastel, cardType t)
{
    for(int i=0; i<2; i++)
        for(int j=1; j<=15; j++)
        {
            Card tmp; tmp.score = j; tmp.type = t;
            kastel.push(tmp);
        }
}

void rand_hand(int numOfPlayers, vector<Player>& players, cardStack& kastel)
{
    //giving 3 cards to each player from kastel that is ordered randomly;
    for(int i=0; i<3*numOfPlayers; i++)
    {
        players[i/3].hand.push_back(kastel.Top());
        kastel.pop();
    }
}

void initialize_game(int& numOfPlayers, vector<Player>& players, cardStack& kastel)
{
    //filling up kastel with ordered carded and then shuffle it.
    init_kastel(kastel, KaleKado);
    init_kastel(kastel, GorBeGor);
    init_kastel(kastel, KohnePich);
    kastel.shuffle_kastel();

    rand_hand(numOfPlayers, players, kastel);
}

bool is_round_finished(vector<Player> players, cardStack kastel)
{
    if(kastel.Size() == 0)
        return true;
    for(int p=0; p<players.size(); p++)
    {
        if(players[p].show.size() > 5)
            return true;
        if(players[p].hand.size() == 0)
            return true;
    }
    return false;
}

bool is_game_finished(vector<Player> players, int maxScore)
{
    //checking if anyone has reached max score
    for(int p=0; p<players.size(); p++)
    {
        if(players[p].score >= maxScore)
            return true;
    }
    return false;
}

void moving_card(vector<Player>& players, cardStack& kastel, int handOf, int showOf)
{
            to_cyan();
            int operation;
            cout << players[handOf].name << " please press: " << endl;
            cout << "       1->expanding shows.(putting aside cards)" << endl;
            cout << "       2->changing value of one show.(putting on one of cards)" << endl;
            cin >> operation;
            switch(operation)
            {
                
                case 1:
                {
                    int which;
                    cout << "picking up which card on your hand and replacing it with another card from kastel?(1-3)"<<endl; cin >> which;
                    players[showOf].show.push_back(players[handOf].hand[which-1]);
                    players[handOf].hand[which-1] = kastel.Top();
                    kastel.pop();
                    break;
                }
                case 2:
                {
                    if(players[showOf].show.size() == 0)
                    {
                        cout << "Show is empty!!!" << endl;
                        throw bad_input_exception();
                    }
                    int which, secWhich;
                    cout << "picking up which card on your hand and replacing it with another card from kastel?(1-3)" << endl; cin >> which;
                    cout << "changing value of which card at your show?(1-number of shows)" << endl; cin >> secWhich;
                    players[showOf].show[secWhich-1] = players[handOf].hand[which-1];
                    players[handOf].hand[which-1] = kastel.Top();
                    kastel.pop();
                    break;
                }
                default:
                {
                    cout << "WRONG INPUT!!!" <<endl;
                    throw bad_input_exception();
                }

            }
            reset_color();
}

void check_type(int& flag, Player player, cardType t)
{
    for(int i=0; i<player.show.size(); i++)
        if(player.show[i].type == t)
        {
            flag++;
            break;
        }
}

void check_duplicate_card(vector<Player>& players)
{
    //checking if there is an duplicated card in shows and deleting it
    for(int p=0; p<players.size(); p++)
    {
        int showSize = players[p].show.size();
        for(int i=0; i<showSize-1; i++)
            for(int j=i+1; j<showSize; j++)
                if(players[p].show[i].score == players[p].show[j].score && players[p].show[i].type == players[p].show[j].type)
                    players[p].show.erase( players[p].show.begin() + j);
    }
}

void count_round_scores(vector<Player>& players)
{
    //counting up scores from last round
    for(int p=0; p<players.size(); p++)
    {
        //does player have all three types of card?
        int flag = 0;
        check_type(flag, players[p], KaleKado);
        check_type(flag, players[p], GorBeGor);
        check_type(flag, players[p], KohnePich);
        if(flag == 3)
        {
            for(int s=0; s<players[p].show.size(); s++)
                players[p].score += players[p].show[s].score;
        }else
        {
            players[p].score += 0;
        }
    }
}

void clear_cards(vector<Player>& players, cardStack& kastel)
{
    for(int p=0; p<players.size(); p++)
    {
        players[p].hand.clear();
        players[p].show.clear();
    }
    kastel.free();
}

void sort_players(vector<Player>& players)
{
    //soring players based on score using bubble sort
    bool isSwapped = false;
    for(int p=0; p<players.size()-1; p++)
    {
        for(int j=0; j<players.size()-p-1; j++)
        {
            if(players[j].score < players[j+1].score)
            {
                Player tmp = players[j];
                players[j] = players[j+1];
                players[j+1] = tmp;
                isSwapped = true;
            }
        }
        if(!isSwapped)  break;
    }
}

void print_score_board(vector<Player>& players)
{
    sort_players(players);
    print_text("$$GAME OVER$$"); cout << endl;
    print_text("Score Board"); cout << endl;
    for(int p=0; p<players.size(); p++)
    {
        print_text(to_string(p+1) + "->" + players[p].name + " : " + to_string(players[p].score));
        cout << endl;
    }
}

void play_game(int numOfPlayers, vector<Player>& players, int maxScore, cardStack& kastel)
{
    do
    {
        //initializing variables
        int turnInd = 0;
        initialize_game(numOfPlayers, players, kastel);
        do
        {
            print_table(numOfPlayers, players, turnInd);
            int operation;
            to_cyan();
            cout << players[turnInd].name << " please press: " << endl;
            cout << "       1->placing your card at your show" << endl; 
            cout << "       2->placing your card at somebody else's show" << endl;
            cin >> operation;
            reset_color();
            switch(operation)
            {
                case 1:
                {
                    moving_card(players, kastel, turnInd, turnInd);
                    break;
                }
                case 2:
                {
                    int showPlayer;
                    to_cyan();
                    cout << "do you want to place your card at which player show?(number before name of players)"<<endl;
                    cin >> showPlayer;
                    reset_color();
                    moving_card(players, kastel, turnInd, showPlayer-1);
                    break;
                }
                default:
                {
                    cout << "WRONG INPUT!!!" <<endl;
                    throw bad_input_exception();
                }
            
            }
            //deleting duplicated card
            check_duplicate_card(players);
            //next turn
            if(turnInd+1 < numOfPlayers)
                turnInd++;
            else
                turnInd=0;
        }while(!is_round_finished(players, kastel));
        print_table(numOfPlayers, players, turnInd);
        count_round_scores(players);
        clear_cards(players, kastel);
    }while(!is_game_finished(players, maxScore));
    print_score_board(players);
}   

int main()
{
    //getting input from user
    int numOfPlayers, maxScore;
    to_magneta();
    cout << "please enter number of players: ";
    cin >> numOfPlayers;
    vector<Player> players(numOfPlayers);
    for(int i=0; i<numOfPlayers; i++)
    {
        cout << "enter name of " << i+1 << "th player: ";
        cin >> players[i].name;
    }
    cout << "now enter maximum score: ";
    cin >> maxScore;
    clear_terminal();
    cardStack kastel;

    try
    {
        play_game(numOfPlayers, players, maxScore, kastel);//TODO: go for color and comment and bad input(review and bug shit)
    }
    catch(bad_input_exception e)
    {
        cout << "sorry!!! something wrong!!!";
    }
    

    return 0;
}