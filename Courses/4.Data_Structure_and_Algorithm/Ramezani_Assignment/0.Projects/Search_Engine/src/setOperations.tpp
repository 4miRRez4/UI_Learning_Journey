#ifndef SETOPERATIONS_TPP
#define SETOPERATIONS_TPP

#include "../include/setOperations.h"  

namespace setOperations{
    inline bool isStrNumeric(const std::string& str) {
        for(int i=0; i<str.size(); i++){
            if(!isdigit(str[i]))
                return false;
        }
        return true;
    }

    template <typename T>
    set<T> unionSets(const set<T>& set1, const set<T>& set2){ 
        set<T> unionSet;
        typename set<T>::iterator it1 = set1.begin();
        typename set<T>::iterator it2 = set2.begin();
        if((it1 == set1.end() || isStrNumeric(*it1)) && (it2 == set2.end() || isStrNumeric(*it2))){
            while(it1 != set1.end() || it2 != set2.end()){
                if(it1 == set1.end() || (it2 != set2.end() && stoi(*it2) < stoi(*it1))){
                    unionSet.insert(*it2);
                    ++it2;
                }
                else if(it2 == set2.end() || (it1 != set1.end() && stoi(*it2) > stoi(*it1))){
                    unionSet.insert(*it1);
                    ++it1;
                }
                else{ // *it1 == *it2
                    unionSet.insert(*it1);
                    ++it1;
                    ++it2;
                }
            }
        }
        else{
            while(it1 != set1.end() || it2 != set2.end()){
                if(it1 == set1.end() || (it2 != set2.end() && *it2 < *it1)){
                    unionSet.insert(*it2);
                    ++it2;
                }
                else if(it2 == set2.end() || (it1 != set1.end() && *it2 > *it1)){
                    unionSet.insert(*it1);
                    ++it1;
                }
                else{ // *it1 == *it2
                    unionSet.insert(*it1);
                    ++it1;
                    ++it2;
                }

            }
        }

        return unionSet;
    }

    template <typename T>
    set<T> intersectionSets(const set<T>& set1, const set<T>& set2){
        set<T> intersectionSet;
        typename set<T>::iterator it1 = set1.begin();
        typename set<T>::iterator it2 = set2.begin();

        while(it1 != set1.end() && it2 != set2.end()){
            if(*it1 == *it2){
                intersectionSet.insert(*it1);
                ++it1;
                ++it2;
            }
        else if (isStrNumeric(*it1) && isStrNumeric(*it2)) {
            if (stoi(*it1) < stoi(*it2)) {
                ++it1;
            } else {
                ++it2;
            }
        } else {
            if (*it1 < *it2) {
                ++it1;
            } else {
                ++it2;
            }
        }

            
        }

        return intersectionSet;
    }

    template <typename T>
    set<T> differenceSets(const set<T>& set1, const set<T>& set2){ //set1 - set2
        set<T> diffSet;
        typename set<T>::iterator it1 = set1.begin();
        typename set<T>::iterator it2 = set2.begin();

        while(it1 != set1.end() && it2 != set2.end()){
            if(*it1 == *it2){
                ++it1;
                ++it2;
            }

            else if (isStrNumeric(*it1) && isStrNumeric(*it2)) {
                if (stoi(*it1) < stoi(*it2)) {
                    diffSet.insert(*it1);
                    ++it1;
                } else {
                    ++it2;
                }
            } else {
                if (*it1 < *it2) {
                    diffSet.insert(*it1);
                    ++it1;
                } else {
                    ++it2;
                }
            }
                
        }

        while(it1 != set1.end()){
            diffSet.insert(*it1);
            ++it1;
        }

        return diffSet;
    }


}

#endif