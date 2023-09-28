
#include <iostream>
// #include "language_model.h"
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;

using std::cout;
using std::endl;

using std::string;
using std::vector;


vector<string> readLines(const string& fileName) {
    vector<string> words;
    std::ifstream file(fileName);
    if (file.is_open()) {
        string word;
        int count = 0;
        while (file >> word) {                      //add error catching if file is empty
            if (word.size() > 4 && word.substr(word.size() - 4) == ".txt") {
                // Open the file with the given name
                vector<string> subWords = readLines(word);
                words.insert(words.end(), subWords.begin(), subWords.end());
                count--;
                continue;
                }
            words.push_back(word);
            count++;
        }
        file.close();
        if(count > 0){
            words.insert(words.begin(), "<START_2>");
            words.insert(words.begin(), "<START_1>");
            words.push_back("<END_1>");
            words.push_back("<END_2>");      
        }
    }
    else{
        cout << "Invalid file list: " << fileName << endl;
        exit(1);
    }
    return words;
}

void print_lines(vector<string> lines){
    for(unsigned long int i = 0; i < lines.size(); i++){
        cout << lines.at(i) << endl;
    }
}

vector<trigram> get_trigrams(vector<string> words){
    vector <trigram> t;
    for(unsigned long int i = 0; i < words.size() - 2;i++){
        string first = words[i];
        string second = words[i+1];
        string third = words[i+2];
        trigram words = std::make_tuple(first, second, third);
        t.push_back(words);
    }
    return t;
}

void update_dict(std::map<trigram, int>& dict, const string& fileName){
    vector<string> words = readLines(fileName);
    vector <trigram> t = get_trigrams(words);
    for(unsigned long int j = 0; j < t.size(); j++){
        if(dict.find(t.at(j)) == dict.end()){
            dict[t.at(j)] = 1;
        }
        else{
            dict[t.at(j)] = dict[t.at(j)]+1;
        }
    }
}

void print_dict(std::map<trigram, int>& dict){
    for(map<trigram, int>::iterator it = dict.begin(); it!=dict.end();++it){
        cout << it->second << " - [" << get<0>(it->first) << " " << get<1>(it->first) << " "<< get<2>(it->first) <<"]" << endl;
    }
}

void ascend(std::map<trigram, int>& dict){
    print_dict(dict);
}

void descend(std::map<trigram, int>& dict){
    for(map<trigram, int>::reverse_iterator it = dict.rbegin(); it!=dict.rend();++it){
        cout << it->second << " - [" << get<0>(it->first) << " " << get<1>(it->first) << " "<< get<2>(it->first) <<"]" << endl;
    }
}

bool cmp(const std::pair<trigram, int>& a, const std::pair<trigram, int>& b) {
    if (a.second != b.second) {
        return a.second > b.second;
    } else {
        return a.first < b.first;
    }
}

void dec_count(const map<trigram, int>& dict) {
    // Convert the map to a vector of pairs
    vector<std::pair<trigram, int>> dict_as_vec(dict.begin(), dict.end());
    
    // Sort the vector using our custom comparison function
    std::sort(dict_as_vec.begin(), dict_as_vec.end(), cmp);
    
    // Print the sorted vector
    for (const auto& pair : dict_as_vec) {
        cout << pair.second << " - [" << get<0>(pair.first) << " " << get<1>(pair.first) << " "<< get<2>(pair.first) <<"]" << endl;
    }
}

void third_freq(map<trigram, int>& dict, string word1, string word2){
    bool found = false;
    int max = 0;
    trigram key;
    for(map<trigram, int>::iterator it = dict.begin(); it!=dict.end();++it){
        if(get<0>(it->first) == word1 && get<1>(it->first) == word2){
            if(it->second > max){
                max = it->second;
                key = it->first;
                found = true;
            }
        }
    }
    if(found){
        cout << max << " - [" << get<0>(key) << " " << get<1>(key) << " "<< get<2>(key) <<"]" << endl;
    }
    else{
        cout << "No trigrams of the form [" << word1 << " " << word2 << " ?]" <<endl;
    }
}


