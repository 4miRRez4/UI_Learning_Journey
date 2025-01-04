#include "../include/setOperations.h"  

namespace setOperations{

    set<string> unionSets(const set<string>& set1, const set<string>& set2){  
        set<string> unionSet;
        set<string>::iterator it1 = set1.begin();
        set<string>::iterator it2 = set2.begin();
        while(it1 != set1.end() || it2 != set2.end()){
            if(it1 == set1.end() || (it2 != set2.end() && stoi(*it2) < stoi(*it1))){
                unionSet.insert(*it2);
                ++it2;
            }
            else if(it2 == set2.end() || (it1 != set1.end() && stoi(*it2) > stoi(*it1))){
                unionSet.insert(*it1);
                ++it1;
            }
            else{ // stoi(*it2) == stoi(*it1)
                unionSet.insert(*it1);
                ++it1;
                ++it2;
            }
        }

        return unionSet;
    }

    set<string> intersectionSets(const set<string>& set1, const set<string>& set2){
        set<string> intersectionSet;
        set<string>::iterator it1 = set1.begin();
        set<string>::iterator it2 = set2.begin();

        while(it1 != set1.end() && it2 != set2.end()){
            if(*it1 == *it2){
                intersectionSet.insert(*it1);
                ++it1;
                ++it2;
            }
            else if(stoi(*it1) < stoi(*it2)){
                ++it1;
            }
            else{
                ++it2;
            }
        }

        return intersectionSet;
    }

    set<string> differenceSets(const set<string>& set1, const set<string>& set2){ //set1 - set2
        set<string> diffSet;
        set<string>::iterator it1 = set1.begin();
        set<string>::iterator it2 = set2.begin();

        while(it1 != set1.end() && it2 != set2.end()){
            if(*it1 == *it2){
                ++it1;
                ++it2;
            }
            else if(stoi(*it1) < stoi(*it2)){
                diffSet.insert(*it1);
                ++it1;
            }
            else{
                ++it2;
            }
        }

        while(it1 != set1.end()){
            diffSet.insert(*it1);
            ++it1;
        }

        return diffSet;
    }


}