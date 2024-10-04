    #include <iostream>
    using namespace std;

    void increase_func(int n, int ind, int aux[]){
        if(ind == n){
            for(int i=0; i<n; i++)
                cout << aux[i] << " ";
            cout << endl;
            return;
        }
        while(aux[ind] != n+1){
            increase_func(n, ind+1, aux);
            aux[ind]++;
        }
        aux[ind] = 1;
    }

    int main(){
        int n; cin >> n;
        int aux[n];
        for(int i=0; i<n; i++)
            aux[i] = 1;

        increase_func(n, 0, aux);

        return 0;
    }