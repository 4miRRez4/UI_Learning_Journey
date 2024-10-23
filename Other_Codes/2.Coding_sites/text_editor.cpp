//https://leetcode.com/problems/design-a-text-editor/
#include <iostream>
#include <regex>
using namespace std;

struct Node{
    char data;
    Node* next;
    Node* prev;

    Node(char c): data(c), next(nullptr), prev(nullptr) {}
};

class Cursor{
public:
    Node* c_node;
    int left_size; //number of elements left of the cursor including the cursor node 
    int right_size;

    Cursor(): c_node(nullptr), left_size(0), right_size(0) {}

    void move_left(){
        if(c_node){
            c_node = c_node->prev;
            left_size--;
            right_size++;
        }
    }
    void move_right(){
        if(c_node){
            c_node = c_node->next;
            left_size++;
            right_size--;
        }
    }
};

class Text_Editor_LL{
public:
    Node* dummy_header;
    Node* tail;
    Cursor* cursor;

    Text_Editor_LL(): tail(nullptr), dummy_header(new Node('\0')), cursor(new Cursor()) {}

    void addChar(char c){
        Node* newNode = new Node(c);

        if(!dummy_header->next){
            dummy_header->next = tail = cursor->c_node = newNode;
            newNode->prev = dummy_header;
            cursor->left_size++;
        }else{
            if(cursor->c_node->next){
                newNode->next = cursor->c_node->next;
                cursor->c_node->next->prev = newNode;
            }else{
                tail = newNode;
            }

            cursor->c_node->next = newNode;
            newNode->prev = cursor->c_node;

            cursor->c_node = newNode;
            cursor->left_size++;
        }
    }
    void addText(string text){
        for(int i=0; i<text.length(); i++){
            addChar(text[i]);
        }
    }

    int deleteText(int k){
        int deleted_num = 0;
        while(k > 0 && cursor->c_node != nullptr && cursor->left_size != 1){
            Node* cursor_prev = cursor->c_node->prev;
            if(cursor->c_node->next){
                cursor->c_node->next->prev = cursor->c_node->prev;
            }else{
                tail = cursor_prev;
            }
            
            cursor->c_node->prev->next = cursor->c_node->next;
            delete cursor->c_node;
            cursor->c_node = cursor_prev;

            cursor->left_size--;
            k--;
            deleted_num++;
        }

        if(cursor->left_size == 1 && k != 0){
            Node* cursor_next = cursor->c_node->next;
            if(cursor_next){
                cursor_next->prev = dummy_header;
            }else{
                tail = nullptr;
            }
            dummy_header->next = cursor_next;
            delete cursor->c_node;
            cursor->c_node = cursor_next;

            cursor->left_size--;
            k--;
            deleted_num++;
        }
        return deleted_num;
    }

    int cursorLeft(int k){
        while(k>0 && cursor->left_size != 0){
            cursor->move_left();
            k--;
        }
        return min(10, cursor->left_size);
    }

    int cursorRight(int k){
        while(k>0 && cursor->right_size != 0){
            cursor->move_right();
            k--;
        }
        return min(10, cursor->left_size);
    }

    string print(){
        string p ="";
        Node* tmp = dummy_header->next;
        while(tmp){
            p += tmp->data;
            tmp = tmp->next;
        }
        return p;
    }
};


int main(){
    Text_Editor_LL* te = nullptr;
    
    int n; cin >> n;
    cin.ignore();
    
    for(int i=0; i<n; i++){
        string command;
        getline(cin, command);

        regex command_regex(R"((\w+)\((?:"([^"]*)\"|(\d+))?\))");
        smatch matches;
        if(regex_match(command, matches, command_regex)){
            string method = matches[1];
            string text_arg;
            int num_arg;
            
            if(matches[2].matched)
                text_arg = matches[2];
            if(matches[3].matched)
                num_arg = stoi(matches[3]);

            if(method == "TextEditor"){
                te = new Text_Editor_LL();
            }
            else if(method == "addText"){
                te->addText(text_arg);
            }
            else if(method == "deleteText"){
                cout << te->deleteText(num_arg) << endl;
            }
            else if(method == "cursorLeft"){
                cout << te->cursorLeft(num_arg) << endl;
            }
            else if(method == "cursorRight"){
                cout << te->cursorRight(num_arg) << endl;
            }

            // cout << te->print() << endl;
            // if(te->cursor->c_node)
            //     cout << te->cursor->c_node->data << endl;     
        }
    }  

    return 0;
}
