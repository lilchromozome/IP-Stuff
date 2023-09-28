/*
William Li
wli128
*/
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


vector<vector<string>> readLines(const string& fileName, vector<vector<string>>& lines) {
    std::ifstream file(fileName);
    if (file.is_open()) {
        string line;
        int line_num = 0;
        bool first = true;
        while (std::getline(file, line)) {                      //add error catching if file is empty
            std::stringstream ss(line);
            vector<string> lineWords;
            string word;
            
            while (ss >> word) {
                 if (word.size() > 4 && word.substr(word.size() - 4) == ".txt") {
                    // Open the file with the given name
                    readLines(word, lines);
                    line_num--;
                    continue;
                 }
                if(first){
                    lineWords.push_back("<START_1>");
                    lineWords.push_back("<START_2>");
                    // cout << word << endl;
                    first = false;
                }
                lineWords.push_back(word);
            }
            line_num++;
            if(!lineWords.empty()){
                lines.push_back(lineWords);
            }
        }
        file.close();
        if(line_num > 0){
            lines[lines.size()-1].push_back("<END_1>");
            lines[lines.size()-1].push_back("<END_2>");      
        }
    }
    else{
        cout << "Invalid file list: " << fileName << endl;
    }
    return lines;
}

void print_lines(vector<vector<string>> lines){
    for(unsigned long int i = 0; i < lines.size(); i++){
        for(unsigned long int j = 0; j < lines[i].size(); j++){
            cout << lines[i][j] << " ";
        }
        cout << endl;
    }
}

vector<trigram> get_trigrams(vector<string> line){
    vector <trigram> t;
    for(unsigned long int i = 0; i < line.size() - 2;i++){
        string first = line[i];
        string second = line[i+1];
        string third = line[i+2];
        trigram words = std::make_tuple(first, second, third);
        t.push_back(words);
    }
    return t;
}

void update_dict(std::map<trigram, int>& dict, const string& fileName, vector<vector<string>>& l){
    vector<vector<string>> lines = readLines(fileName, l);
    for(unsigned long int i = 0; i < lines.size(); i++){
        vector <trigram> t = get_trigrams(lines[i]);
        for(unsigned long int j = 0; j < t.size(); j++){
            if(dict.find(t[j]) == dict.end()){
                dict[t[j]] = 1;
            }
            else{
                dict[t[j]] = dict[t[j]]+1;
            }
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