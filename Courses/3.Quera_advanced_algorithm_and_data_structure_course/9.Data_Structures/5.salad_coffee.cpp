#include <iostream>
#include <sstream>
using namespace std;

const int MAX_SIZE = 10e4;

class Min_Heap{
public:
    pair<string, int>* customers[MAX_SIZE]; //<name, expire date>
    int last_ind;
    int (*compare) (pair<string, int>*, pair<string, int>*);

    Min_Heap(int (*funcPtr)(pair<string, int>*, pair<string, int>*)){
        last_ind = 0;
        customers[0] = new pair<string, int> {"", 0};
        compare = funcPtr;
    }

    static int compare_by_expire_date(pair<string, int>* a, pair<string, int>* b){
        if(a->second > b->second)
            return 1;
        if(a->second < b->second)
            return -1;
        return 0;
    }
    static int compare_by_name(pair<string, int>* a, pair<string, int>* b){
        return a->first.compare(b->first);
    }

    int get_size(){ return last_ind;}
    int get_father(int i){ return i/2; }
    int get_left_child(int i){ return 2*i; }
    int get_right_child(int i){ return 2*i+1; }

    void bubble_up(int i){
        int father_ind = get_father(i);
        while(father_ind > 0 && compare(customers[father_ind], customers[i]) > 0){
            pair<string, int>* tmp = customers[i];
            customers[i] = customers[father_ind];
            customers[father_ind] = tmp;

            i = father_ind;
            father_ind = get_father(i);
        }
    }

    void bubble_down(int i){
        while(i <= this->last_ind){
            int child_ind = i;

            int left_child_ind = get_left_child(i);
            if(left_child_ind <= this->last_ind && compare(customers[i], customers[left_child_ind]) > 0)
                child_ind = left_child_ind;

            int right_child_ind = get_right_child(i);
            if(right_child_ind <= this->last_ind && compare(customers[child_ind], customers[right_child_ind]) > 0)
                child_ind = right_child_ind;

            if(child_ind == i)
                break;

            pair<string, int>* tmp = customers[i];
            customers[i] = customers[child_ind];
            customers[child_ind] = tmp;
            i = child_ind;
        }
    }

    void insert(string name, int expiry){
        pair<string, int>* newCust = new pair<string, int>{name, expiry};
        this->customers[++last_ind] = newCust;
        bubble_up(last_ind);
    }

    int get_min_expiry(){
        return (last_ind == 0) ? 0:customers[1]->second;
    }

    pair<string, int> pop_min(){
        if(last_ind == 0)
            return *customers[0];

        pair<string, int> min = *customers[1];
        delete customers[1];
        customers[1] = customers[last_ind];
        customers[last_ind] = nullptr;
        last_ind--;
        bubble_down(1);

        return min;
    }

    int find_customer(pair<string, int> cust, int curr_ind = 1){
        if(curr_ind > last_ind)
            return -1;
        if(customers[curr_ind]->first.compare(cust.first) == 0)
            return curr_ind;

        int left_result = find_customer(cust, get_left_child(curr_ind));
        if(left_result != -1)
            return left_result;

        return find_customer(cust, get_right_child(curr_ind));
    }

    void delete_customer(pair<string, int> cust){
        int cust_ind = find_customer(cust);
        if(cust_ind == -1)
            return;

        delete customers[cust_ind];
        customers[cust_ind] = customers[last_ind];
        customers[last_ind] = nullptr;
        last_ind--;
        bubble_down(cust_ind);
        
    }  

    void clear(){
        while(last_ind != 0){
            delete customers[last_ind];
            customers[last_ind] = nullptr;
            last_ind--;
        }
    }
};


int main(){
    Min_Heap* heap_by_expiry = new Min_Heap(Min_Heap::compare_by_expire_date);
    Min_Heap* heap_by_name = new Min_Heap(Min_Heap::compare_by_name);
    Min_Heap* deleteds = new Min_Heap(Min_Heap::compare_by_name);

    int q; cin >> q;
    cin.ignore();
    for(int day=1; day<=q; day++){
        string line;
        getline(cin, line);
        stringstream ss(line);
        int k; ss >> k;
        for(int p=0; p<k; p++){
            string name; int expiry_days;
            ss >> name; ss >> expiry_days;
            // pair<string, int>* newCust = new pair<string, int>{name, day + expiry_days - 1};
            heap_by_expiry->insert(name, day + expiry_days - 1);
            heap_by_name->insert(name, day + expiry_days - 1);
        }

        pair<string, int> deleted_cust;
        if(day != q){
            //delete finished accounts
            while(heap_by_expiry->get_min_expiry() == day){
                deleted_cust = heap_by_expiry->pop_min();
                heap_by_name->delete_customer(deleted_cust);
                deleteds->insert(deleted_cust.first, deleted_cust.second);
            }

            //fun delete
            deleted_cust = heap_by_name->pop_min();
            heap_by_expiry->delete_customer(deleted_cust);
            deleteds->insert(deleted_cust.first, deleted_cust.second);
        }else{
            //delete all
            while(heap_by_name->get_size() != 0){
                deleted_cust = heap_by_name->pop_min();
                deleteds->insert(deleted_cust.first, deleted_cust.second);
            }
            heap_by_expiry->clear();
        }

        while(deleteds->get_size() != 0){
            cout << deleteds->pop_min().first << " ";
        }
        cout << endl;
    }



    return 0;
}