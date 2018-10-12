//
//  main.cpp
//  HW08
//
//  Created by Rohan Nair on 6/4/17.
//  Copyright © 2017 Rohan Nair. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <time.h>
#include "graph.hpp" 

using namespace std;
/***************************************************************************************************
read dict words into 2 data structures
 1. map (key = word, value = node #)
 2. vector (word @ index of node #)
 add vertex in graph for every word
find edges by masking off one letter at a time and compare to every other word in dict
 - create edge when words are the same (differing by one letter)
 call shortest_path function with node #'s of words
 print words corresponding to node #'s of shortest_path solution
***************************************************************************************************/
int main(){
    clock_t t1, t2;
    t1 = clock();
    graph g;
    ifstream in;
    string dictfile;
    cout << "Please enter dictionary file name (full path): " << endl;
    cin >> dictfile;
    in.open(dictfile);
    if (in.fail()){
        cout << "failed" << endl;
        exit(1);
    }
    string temp;
    int count = 0;
    map<string,int> m1; // holds dictionary word and corresponding node #
    vector<string> vec1; // holds dict word at index of node #
    while (in >> temp){
        m1[temp] = count;
        vec1.push_back(temp);
        g.add_vertex();
        ++count;
    }
    
    for (int i = 0; i < count; ++i){
        temp = vec1[i];
        for (int j = 0; j < 5; ++j){
            string temp1 = temp;
            temp1[j] = '-';
            for (int k = i; k < count; ++k){
                string temp2 = vec1[k];
                temp2[j] = '-';
                if (temp1 == temp2){
                    g.add_edge(i, k);
                }
            }
        }
    }
    vector<pair<string,string>> puzzles;
    puzzles.push_back(make_pair("black","white"));
    puzzles.push_back(make_pair("tears","smile"));
    puzzles.push_back(make_pair("small","giant"));
    puzzles.push_back(make_pair("stone","money"));
    puzzles.push_back(make_pair("angel","devil"));
    puzzles.push_back(make_pair("amino","right"));
    puzzles.push_back(make_pair("amigo","signs"));
    for (auto e : puzzles){
        vector<int> v = g.shortest_path(m1[e.first],m1[e.second]);
        for (vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it){
            cout << vec1[*it] << endl;
        }
        cout << endl;
        cout << endl;
    }
    cout << endl;
    t2 = clock();
    cout << (t2 - t1)/CLOCKS_PER_SEC << endl;
}
