#include <iostream>
#include <unordered_map>
using namespace std;

int calcCode(string name){
    int code = 0;
    int weight = 30*30*30;
    for(int i=0; i<name.size(); i++){
        code += weight * ((name[i] - 'a' + 1) * 4 + 2);
        weight /= 30;
    }
    
    return code;
}

void countingSort(int codes[], int n, int maxCode){
    // //calculate max value
    // int maxCode=0, weight = 1;
    // for(int i=0; i<4; i++){
    //     maxCode += weight * (('z' - 'a' + 1)*4 + 2);
    //     weight *= 26;
    // }

    int countArr[maxCode+1] = {};

    //update count array
    for(int i=0; i<n; i++){
        countArr[codes[i]]++;
    }

    //update codes to be sorted
    int codes_ind=0;
    for(int i=0; i<maxCode+1; i++){
        for(int c=0; c<countArr[i]; c++){
            codes[codes_ind] = i;
            codes_ind++;
        }
    }
}

int main(){
    int n; cin >> n;
    unordered_map<int, string> codeAndName;
    
    string name;
    int codes[n];
    int maxCode=0;
    for(int i=0; i<n; i++){
        cin >> name;
        int code = calcCode(name);
        codeAndName[code] = name;
        codes[i] = code;

        if(code > maxCode) maxCode = code;
    }

    countingSort(codes, n, maxCode);

    for(int i=0; i<n; i++){
        cout << codeAndName[codes[i]] << endl;
    }


    return 0;
}