#include <iostream>
using namespace std;
// template<typename T> void swap(T& a, T& b){
//     T tmp = a;
//     a = b;
//     b = tmp;
// }
template <class T> void b_S(T a[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = n - 1; i < j; j--)
            if (a[j] < a[j - 1])
                swap(a[j], a[j - 1]);
}
template<typename T>
void print_arr(T arr[], int n){
    for(int i=0; i<n; i++)
        cout << arr[i] << " ";
    cout << endl;
}
int main(){
    int a[5] = {3,1,4,5,2};
    char b[4] = {'d', 'a', 'c', 'b'};
    b_S(a, 5);
    print_arr(a, 5);
    b_S(b, 4);
    print_arr(b, 4);
    return 0;
}
/*
    تابع داده شده از الگوریتم بابل سورت برای مرتب کردن داده های
    آرایه ی ورودی با تایپهای مختلف استفاده میکند.
    این تابع از تمپلیت استفاده کرده که میتواند از دوباره نوشتن آن
    برای نوع داده های مختلف جلوگیری کند 
    در واقع خود کامپایلر نوع داده مورد نظر را از ورودی
    نتیجه گیری کرده و به جای تی آن نوع داده را گذاشته و کامپایل میکند.
    حلقه بیرونی تعداد حلقه روی آرایه و حلقه دومی از آخر آرایه به سمت اول
     آرایه حرکت کرده و مقایسه را انجام میدهد که اگر کوچکتر بود جای آنها را عوض میکند.
*/