#include <iostream>



int main() {
    int n;
    std::cin >> n;

    int profit[n];
    for(int i = 0; i<n; i++)
    {
        std::cin >> profit[i];
    }

    int max =0;
    //iterating for variable l as length of days straight ahead;
    for(int l=1; l<=n; l++)
    {
        //iterating for variable s as start day;
        for(int s=0; s<=n-l; s++)
        {
            int tmp=0;
            //iterating for adding up l element started from s straight ahead;
            for(int p=0; p<l; p++)
            {

                tmp += profit[s+p];
            }
            //checking max profit with selected efraz;
            if(tmp > max)
            {
                max = tmp;
            }
        }
    }

    std::cout << max;

    return 0;
}
