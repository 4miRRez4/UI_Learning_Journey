#include <iostream>
using namespace std;

string q2(int val){
    int tmp = val;
    int reverse = 0;
    while(tmp > 0){
        reverse *= 10;
        reverse += tmp%10;
        tmp /= 10;
    }
    string answer = to_string(reverse) + "\n";

    int sum;
    while(val/10 != 0){
        sum =0;
        while(val > 0){
            sum += val%10;
            val /= 10;
        }
        val = sum;
    }
    answer += to_string(val);
    return answer;
}

// int main(){
//     int n; cin >> n;
//     cout << q2(n) << endl;

//     return 0;
// }

#include<vector>
int main()
{
    int arr_n,temp, number;
    cin>> number;
    temp = number;
    arr_n = 0;
    while (temp != 0 )
    {

        temp = temp / 10;
        arr_n += 1;
    }
    vector<int> array(arr_n);
    int number_org = number;
    for (int i = 0; i < arr_n; i++)
    {
        temp = number % 10;
        array[i] = temp;
        number = number / 10;
    }

    for (int i = 0; i < arr_n; i++)
    {
        cout<<array[i];
    }
    cout<<""<<endl;
    int sum = 0;
    number = number_org;
    temp = number;

    while (number >= 10)
    {
        int sum = 0;
        while (number > 0)
        {
            sum += number % 10;
            number /= 10;
        }
        number = sum;
        
    }
    cout <<number<<endl;
    
    return 0;
}
