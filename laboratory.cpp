//https://quera.org/problemset/6404
#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

int main(){
    int n, m , k; scanf("%d %d %d", &n, &m, &k);
    //corresponding matrix to graph of making new material(each formula has number for itself)
    vector<vector<vector<int>>> CorrespondingMatrix(n, vector<vector<int>> (n, vector<int> (1,0)));
    
    //which materials do we have in lab
    set<int> inLab;
    int tmp;
    for(int i=0; i<m; i++){
        scanf("%d", &tmp);
        inLab.insert(tmp);
    }

    //number of requirement from special formula
    vector<map<int, int>> numOfReq(n);

    //filling correspoding matrix with given formulas
    int p,q;
    for(int formula=1; formula<=k; formula++){
        scanf("%d %d", &p, &q);
        int reactants[p], products[q];
        for(int i=0; i<p; i++)
            scanf("%d", &reactants[i]);
        for(int i=0; i<q; i++)
            scanf("%d", &products[i]);

        for(int i=0; i<p; i++)
            for(int j=0; j<q; j++){
                CorrespondingMatrix[reactants[i]-1][products[j]-1].push_back(formula);
                if(numOfReq[products[j]-1].find(formula) != numOfReq[products[j]-1].end())
                    numOfReq[products[j]-1][formula] += 1;
                else
                    numOfReq[products[j]-1][formula] = 1;
            }
    }

    //printing corresponding matrix
    // for(int i=0; i<n; i++){
    //     for(int j=0; j<n; j++){
    //         printf("{");
    //         for(int k=1; k<CorrespondingMatrix[i][j].size(); k++){
    //             printf("%d", CorrespondingMatrix[i][j][k]);
    //         }
    //         printf("} ");
    //     }
    //     printf("\n");
    // }
    //printing numOfReq
    // for(int i=0; i<n; i++){
    //     printf("column %d ", i+1);
    //     for(auto it=numOfReq[i].begin(); it!=numOfReq[i].end(); it++){
    //         printf("%d : %d , ", it->first, it->second);
    //     }
    // }



    // checking if we can make new material
    int made = 0;
    for(int j=0; j<n; j++)//on columns(products)
    {
        //checking if its been made before
        if(inLab.find(j+1) == inLab.end()){
            //checking rows(reactants) that we have and check if we can satisfied the product needs.
            for(auto have : inLab)
            {
                if(CorrespondingMatrix[have-1][j].size() != 1)
                {
                    for(int f=1; f<CorrespondingMatrix[have-1][j].size(); f++){
                        numOfReq[j][CorrespondingMatrix[have-1][j][f]] -=1;
                        //all needs require?
                        if(numOfReq[j][CorrespondingMatrix[have-1][j][f]] == 0){
                            inLab.insert(j+1);
                            made++;
                            break;
                        }
                    }
                    //avoiding considering again
                    CorrespondingMatrix[have-1][j].clear();
                }
                if(made != 0){
                    made=0;
                    j=-1;
                    break;
                }
            }
            
        }
    }
    // cout << "*******" << endl;
    // printing inLab
    for(auto made: inLab)
        printf("%d ", made);
    printf("\n");
    return 0;
}