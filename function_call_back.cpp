//ramting khosravi section 16
#include <iostream>
using namespace std;

// typedef void (*funcPtr)(int);

// void print(int x) {
//     cout << x << endl;
// }

// void print_twice(int x) {
//     cout << x << ' ' << x << endl;
// }


// typedef int (*binop)(int, int);
// int f(binop op, int x, int y, int z){
//     return op(op(x,y), z);
// }
// inline int add(int x, int y) { return x+y; }
// inline int sub(int x, int y) { return x-y; }
// int main() {
//     // void (*funcPtr)(int);
//     // funcPtr fp;
//     // fp = print;
//     // fp(2);

//     // fp = print_twice;
//     // fp(3);


//     // cout << f(add, 1,2,3) << endl;
//     // cout << f(sub, 1,2,3) << endl;
//     return 0;
// }

#include <map>

typedef int (*operation)(int, int);
inline int add(int x, int y) { return x+y; }
inline int sub(int x, int y) { return x-y; }
inline int mul(int x, int y) { return x*y; }
inline int dvi(int x, int y) { return x/y; }

int main(){
    char exp[100]={}; scanf("%s", exp);
    map<char, operation> ops;
    ops['+'] = add;
    ops['-'] = sub;
    ops['*'] = mul;
    ops['/'] = dvi;
    int out = exp[0]-'0';
    for(int i=1; exp[i]; i+=2){
        out = ops[exp[i]](out, exp[i+1]-'0');
    }
    cout << out << endl;
    return 0;
}