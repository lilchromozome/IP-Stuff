/*
William Li
wli128
*/
#include <iostream>
#include "language_model.h"
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

/**
 * readFile
 * 
 * @param fileName (const string&): the name of the file to be read
 * @param dict (map<trigram, int>&):the dictionary that holds the trigrams and counts
 * 
 * return void
 *
 * takes input file and updates the dictionary with the words in the files provided in fileName
*/
void readFile(const string& fileName, std::map<trigram, int>& dict){
    std::ifstream file(fileName);
    vector<string> files;
    string f;
    if(file.is_open()){
        while(file >> f){
            if (f.size() > 4 && f.substr(f.size() - 4) == ".txt") {
                        // Read the file with the given name
                        vector <string> subwords = readWords(f);
                        vector <trigram> t = get_trigrams(subwords);
                        update_dict(dict, t);
                        continue;
            }
            else{
                cerr << "Invalid file: " << f << endl;
            }
        }
    }
}

/**
 * readWords
 * 
 * @param fileName (const string&): the name of the file to be read
 * 
 * return words: a vector of strings beginning with <START_1>, <START_2> ... and ending with <END_1>, <END_2>
*/
vector <string> readWords(const string& fileName){
    std::ifstream file(fileName);
    vector<string> words;
    string word;
    if(file.is_open()){
        words.insert(words.begin(), "<START_2>");
        words.insert(words.begin(), "<START_1>");
        while(file >> word){
            words.push_back(word);
        }
        words.push_back("<END_1>");
        words.push_back("<END_2>");
    }
    return words;
}

/**
 * get_trigrams
 * 
 * @param words (vector<string>): a vector of strings that contains all the words in a file
 * 
 * return t: a vector of trigrams of the ordered triplets from words
 *
 * creates and returns all the trigrams in a file
*/
vector<trigram> get_trigrams(vector<string> words){
    vector <trigram> t;
    if(words.size() > 2){
        for(unsigned long int i = 0; i < words.size() - 2;i++){
            string first = words[i];
            string second = words[i+1];
            string third = words[i+2];
            trigram triplet = std::make_tuple(first, second, third);
            t.push_back(triplet);
        }
    }
    return t;
}

/**
 * update_dict
 * 
 * @param dict (map<trigram, int>&):the dictionary that holds the trigrams and counts
 * @param t (vector<trigram>): a vector of trigrams from a file
 *
 * return void
 *
 * updates the dictionary by adding new trigrams or incrementing existing trigrams
*/
void update_dict(std::map<trigram, int>& dict, vector<trigram> t){
    for(unsigned long int j = 0; j < t.size(); j++){
        if(dict.find(t.at(j)) == dict.end()){
            dict[t.at(j)] = 1;
        }
        else{
            dict[t.at(j)] += 1;
        }
    }
}
/**
 * print_dict
 * 
 * @param dict (map<trigram, int>&):the dictionary that holds the trigrams and counts
 *
 * return void
 *
 * prints all the elements of the dictionary in lexigraphical order
 *      used for debugging
*/
void print_dict(std::map<trigram, int>& dict){
    //print in forward order
    for(map<trigram, int>::iterator it = dict.begin(); it!=dict.end();++it){
        cout << it->second << " - [" << get<0>(it->first) << " " << get<1>(it->first) << " "<< get<2>(it->first) <<"]" << endl;
    }
}
/**
 * ascend
 * 
 * @param dict (map<trigram, int>&):the dictionary that holds the trigrams and counts
 *
 * return void
 *
 * prints all the elements of the dictionary in lexigraphical order, same as print_dict
*/
void ascend(std::map<trigram, int>& dict){
    print_dict(dict);
}
/**
 * descend
 * 
 * @param dict (map<trigram, int>&):the dictionary that holds the trigrams and counts
 *
 * return void
 *
 * prints all the elements of the dictionary in reverse lexigraphical order
*/
void descend(std::map<trigram, int>& dict){
    //print dict in reverse order
    for(map<trigram, int>::reverse_iterator it = dict.rbegin(); it!=dict.rend();++it){
        cout << it->second << " - [" << get<0>(it->first) << " " << get<1>(it->first) << " "<< get<2>(it->first) <<"]" << endl;
    }
}
/**
 * cmp
 * 
 * @param a (const std::pair<trigram, int>&): one instance of the map
 * @param b (const std::pair<trigram, int>&): another instance of the map
 *
 * return bool
 *
 * returns whichever pair has more occurances and breaks ties with alphabetical order
 */
bool cmp(const std::pair<trigram, int>& a, const std::pair<trigram, int>& b) {
    if (a.second != b.second) {
        return a.second > b.second;
    } else {
        return a.first < b.first;
    }
}
/**
 * dec_count
 * 
 * @param dict (map<trigram, int>&):the dictionary that holds the trigrams and counts
 *
 * return void
 *
 * prints the order of dictionary in descending order based on number of occurances and breakin ties with alphabetical order
 */
void dec_count(const map<trigram, int>& dict) {
    // Convert the map to a vector of pairs
    vector<std::pair<trigram, int>> dict_as_vec(dict.begin(), dict.end());
    // Sort the vector using custom comparison function
    std::sort(dict_as_vec.begin(), dict_as_vec.end(), cmp);
    // Print the sorted vector
    for (const auto& pair : dict_as_vec) {
        cout << pair.second << " - [" << get<0>(pair.first) << " " << get<1>(pair.first) << " "<< get<2>(pair.first) <<"]" << endl;
    }
}
/**
 * third_freq
 * 
 * @param dict (map<trigram, int>&):the dictionary that holds the trigrams and counts
 * @param word1 (string): first word
 * @param word2 (string): second word
 *
 * return void
 *
 * prints the most frequently occuring trigram with the dirst word being word1 and second order being word2
 */
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
        cerr << "No trigrams of the form [" << word1 << " " << word2 << " ?]" <<endl;
    }
}