#include <iostream>
using namespace std;

int main() {
    int l;
    cin >> l;
    cin.ignore();

    char sentence[l + 1];
    cin.getline(sentence, l + 1);

    char characters[100] = {};
    int quantity[100] = {0};
    int characters_i = 0;
    for (int i = 0; i < l; i++) {
        bool existance = false;
        int existed_i;
        //checking if selected character has been counted before;
        for (int j = 0; characters[j]; j++) {
            if (sentence[i] == characters[j]) {
                existance = true;
                existed_i = j;
            }
        }

        if (existance) {
            quantity[existed_i] += 1;
        } else {
            characters[characters_i] = sentence[i];
            quantity[characters_i] += 1;
            characters_i++;
        }
    }

    for (int k = 0; characters[k]; k++)
    {
        if (characters[k] != ' ')  cout << characters[k] << " : " << quantity[k] << endl;
        else cout << "White Space" << " : " << quantity[k] << endl;
    }

    return 0;
}
