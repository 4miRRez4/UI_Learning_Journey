#include <iostream>

using namespace std;



int main(){
    //getting length of sides from input.
    int a, b, c;
    cin >> a >> b >> c;

    //checking there is a triangle with these sides.
    if (a<b+c && b<a+c && c<b+a)
    {
        // Calculate squares of sides
        float a_squared = a * a;
        float b_squared = b * b;
        float c_squared = c * c;

        //using cosa theoreom
        float cosA = (b_squared + c_squared - a_squared)/(2*b*c);
        float cosB = (a_squared + c_squared - b_squared)/(2*a*c);
        float cosC = (b_squared + a_squared - c_squared)/(2*b*a);
    

        // Check for right-angled triangle
        if (a_squared + b_squared == c_squared || b_squared + c_squared == a_squared || c_squared + a_squared == b_squared) {
            cout << "right angle";
        } else if (cosA>0 && cosB>0 && cosC>0)
        {
            cout << "acute angle";
        } else if (cosA<0 || cosB<0 || cosC<0)
        {
            cout << "obtuse angle";
        }

    }else{
        cout << "error";
    }


    
    
    

}


