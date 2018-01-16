#include <iostream>
#include <map>
#include <set>
#include <cstdlib>
#include <cstdio>
#include<string>
#include <fstream>
#include <math.h>
using namespace std;

int main()
{
    ifstream input,stopword;
    input.open("input.txt");
    stopword.open("stopwords.txt");
    set<string> stopset;
    map<string,int> freq;
    string word;
    int numberOfwords = 0;
    int numberOfwordStop = 0;
    map <string,int>::iterator it;
    multimap <int, string> freq2;
    multimap <int, string>::iterator it2;
    while(stopword >> word ){
        stopset.insert(word);
    }
    while(input >> word){
        if( word[0] >= 'A' && word[0] <= 'Z'){
            word[0] = word[0] - 'A' + 'a';
        }
        if( stopset.find(word) != stopset.end() ){
            freq[word]++;
        }
    }
    numberOfwords = freq.size();
    numberOfwordStop = stopset.size();
    for(it = freq.begin(); it != freq.end() ; it++ ){
        freq2.insert(make_pair(it->second,it->first));
    }
    cout << "Stopword Count On Input On Stop\n";
    for(it2 = freq2.end(),it2-- ; it2 != freq2.begin() ; it2-- ){
        cout << it2->second << "\t" << it2->first << "\t%"  << ceil( ((float)it2->first /(float) numberOfwords)*100)<<"\t%"<< ceil( ((float)it2->first /(float)numberOfwordStop )*100)<<endl;
    }

    return 0;
}

