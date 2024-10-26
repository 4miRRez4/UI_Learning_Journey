#include <iostream>
#include <cstdio>
using namespace std;


int main(){
    int n; scanf("%d", &n);
    int x, y; scanf("%d %d", &x, &y);

    int min_sum, max_sum;
    min_sum = max_sum = x + y;
    int min_sub, max_sub;
    min_sub = max_sub = x - y;

    for(int i=1; i<n; i++){
        scanf("%d %d", &x, &y);

        int new_sum = x + y;
        int new_sub = x - y;

        if(new_sum < min_sum)
            min_sum = new_sum;
        else if(new_sum > max_sum)
            max_sum = new_sum;
        
        if(new_sub < min_sub)
            min_sub = new_sub;
        else if(new_sub > max_sub)
            max_sub = new_sub;
    }

    printf("%d\n", max(max_sum - min_sum, max_sub - min_sub));



    return 0;
}