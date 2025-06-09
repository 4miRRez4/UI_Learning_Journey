#include <iostream>
#include <cstring>
#include <chrono>
using namespace std::chrono;

using namespace std;

int main()
{
    int goodness = 0;
//    auto start = high_resolution_clock::now();
    //getting the suspect string from input using c style strings;
    char suspect[1000];
    cin >> suspect;


    char order[100];
    cin >> order;

    int order_c = 0;
    do {
        order_c++;
        //comparing order and doing the job;
        if (strcmp(order, "copy") == 0) {

            //extracting the key from input
            char key[1000];
            cin >> key;

            //extracting the count from input;
            int count;
            cin >> count;

            //sticking key to key count time;
            int j=0;
            int keyLen = strlen(key);
            for(int k=0; k<count; k++)
            {
                for(int z=0; z<keyLen; z++)
                {
                    key[j] = key[z];
                    j++;
                }
            }
            key[j] = '\0';

            //placing newKey in suspect from left;
            int newKeyLen = strlen(key);
            for(int m=0; m<newKeyLen; m++)
            {
                suspect[m] = key[m];
            }

        } else if (strcmp(order, "compare") == 0)
        {


            //extracting the key from input
            char key[1000];
            cin >> key;

            //condition for comparing suspect with key;
            if(strcmp(suspect, key) == 0)
            {
                goodness++;
            }



        } else if (strcmp(order, "substr") == 0)
        {


            //extracting the key from input
            char key[1000];
            cin >> key;

            //extracting the count from input;
            int count;
            cin >> count;

            //counting appearance of key in suspect;
            int appearance = 0;
            int suspectLen = strlen(suspect);
            int keyLen = strlen(key);
            for(int s=0; s<=suspectLen-keyLen; s++)
            {
                bool status = true;
                for(int c=0; c<keyLen; c++)
                {
                    if(key[c] != suspect[s+c])
                    {
                        status = false;
                        break;
                    }
                }

                if(status)
                {
                    appearance++;
                }
            }

            if(appearance == count)
            {
                goodness++;
            }

        } else if (strcmp(order, "attach") == 0) {


            //extracting the key from input
            char key[1000];
            cin >> key;


            //extracting the count from input;
            int count;
            cin >> count;

            //extracting str from input
            char str[100];
            cin >> str;

            //adding str to key;
            int le = strlen(key) + strlen(str);
            char newKey[le];
            int progress = 0;
            for(int i =0; i<strlen(key); i++)
            {
                newKey[progress] = key[i];
                progress++;
            }
            for(int i =0; i<strlen(str); i++)
            {
                newKey[progress] = str[i];
                progress++;
            }



            //counting appearance of key in suspect;
            int appearance = 0;
            int suspectLen = strlen(suspect);
            int keyLen = progress;
            for (int s = 0; s <= suspectLen - keyLen; s++) {
                bool status = true;
                for (int c = 0; c < keyLen; c++) {
                    if (newKey[c] != suspect[s + c]) {
                        status = false;
                        break;
                    }
                }

                if (status) {
                    appearance++;
                }
            }

            if (appearance == count) {
                goodness++;
            }

        }else if (strcmp(order, "length") == 0)
        {


            //extracting the count from input
            int count;
            cin >> count;

            int suspectLen = strlen(suspect);
            if(count == suspectLen )
            {
                goodness++;
            }

        }



        cin >> order;
    }while(strcmp(order,"Is") != 0);

    //checking condition of goodness;
    if(goodness >= order_c/2)
    {
        cout << "Eyval";
    }else
    {
        cout << "HeifShod";
    }
//    auto stop = high_resolution_clock::now();
//    auto duration = duration_cast<seconds>(stop - start);
//    cout << duration.count() << endl;



    return 0;
}
