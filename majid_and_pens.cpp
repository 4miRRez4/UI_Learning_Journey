// https://quera.org/problemset/9109
#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int n, color; scanf("%d", &n);
    int occurrence[100]={}; //occurrence of each color(index)
    for(int i=0; i<n; i++){
        scanf("%d", &color);
        occurrence[color-1]++;
    }

    int minOccurrence=200;
    int minColor=200;
    for(int i=0; i<100; i++){
        if(occurrence[i] != 0 && occurrence[i] < minOccurrence)
        {
            minOccurrence = occurrence[i];
            minColor = i+1;
        }
    }
    printf("%d", minColor);


    // if occurance was important
    // int n; scanf("%d", &n);
    // int order[n]={};
    // int pens[100]={};
    // int color=0;
    // for(int i=0; i<n; i++){
    //     scanf("%d", &color);
    //     order[i] = color;
    //     pens[color-1]++;
    // }

    // int valMin =200;
    // int occuranceMin =200;
    // int indInOrder =200;
    // for(int k=0; k<100; k++){
    //     if(pens[k] != 0 && pens[k] <= occuranceMin){
    //         if(occuranceMin == pens[k]){
    //             int o1 = find(&order[0], order+n, k+1) - order;
    //             if(o1 > indInOrder)
    //                 break;
    //         }
    //         valMin = k+1;
    //         occuranceMin = pens[k];
    //         indInOrder = find(&order[0], order+n, k+1) - order;
    //     }
    // }
    // printf("%d", valMin);
    return 0;
}