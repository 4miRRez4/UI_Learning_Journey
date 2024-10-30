#include <iostream>
#include <sstream>
using namespace std;

const int MAX_SIZE = 10e4;

class Min_Heap{
public:
    pair<string, int>* customers[MAX_SIZE]; //<name, expire date>
    int last_ind;
    bool (*compare) (pair<string, int>*, pair<string, int>*);

    Min_Heap(bool (*funcPtr)(pair<string, int>*, pair<string, int>*)){
        last_ind = 0;
        customers[0] = new pair<string, int> {"", 0};
        compare = funcPtr;
    }

    static bool compare_by_expire_date(pair<string, int>* a, pair<string, int>* b){
        return a->second > b->second;
    }
    static bool compare_by_name(pair<string, int>* a, pair<string, int>* b){
        return (a->first.compare(b->first) > 0) ? 1:0;
    }

    int get_father(int i){ return i/2; }
    int get_left_child(int i){ return 2*i + 1; }
    int get_right_child(int i){ return 2*i+1; }

    void bubble_up(int i){
        int father_ind = get_father(i);
        while(father_ind >= 0 && compare(father_ind, i)){
            pair<string, int>* tmp = customers[i];
            customers[i] = customers[father_ind];
            customers[father_ind] = tmp;

            i = father_ind;
            father_ind = get_father(i);
        }
    }

    void bubble_down(int i){
        while(i <= this->last_ind){
            int child_ind = -1;

            int left_child_ind = get_left_child(i);
            if(left_child_ind <= this->last_ind && compare(customers[i], customers[left_child_ind]))
                child_ind = left_child_ind;

            int right_child_ind = get_right_child(i);
            if(right_child_ind <= this->last_ind && compare(customers[i], customers[right_child_ind]))
                child_ind = right_child_ind;

            if(child_ind == -1)
                break;

            pair<string, int>* tmp = customers[i];
            customers[i] = customers[child_ind];
            customers[child_ind] = tmp;
        }
    }

    void insert(pair<string, int>* newCust){
        this->customers[++last_ind] = newCust;
        bubble_up(last_ind);
    }

    pair<string, int> pop_min(){
        if(last_ind == 0)
            return;

        pair<string, int> min = *customers[0];
        customers[0] = customers[last_ind];
        last_ind--;
        bubble_down(0);

        return min;
    }
};


int main(){
    Min_Heap* heap_by_expiry = new Min_Heap(Min_Heap::compare_by_expire_date);
    Min_Heap* heap_by_name = new Min_Heap(Min_Heap::compare_by_name);

    int q; cin >> q;
    cin.ignore();
    for(int day=1; day<=q; day++){
        string line;
        getline(cin, line);
        stringstream ss(line);
        int k; ss >> k;
        for(int p=0; p<k; p++){
            string name; int expiry_days;
            pair<string, int>* newCust = new pair<string, int>{name, day + expiry_days - 1};
            heap_by_expiry->insert(newCust);
            heap_by_name->insert(newCust);
        }
        //TODO: handle other methods
    }



    return 0;
}