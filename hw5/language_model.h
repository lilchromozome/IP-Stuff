/*
William Li
wli128
*/
#ifndef LANGUAGE_MODEL_H
#define LANGUAGE_MODEL_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::vector;
using std::string;

typedef std::tuple<string, string, string> trigram;
typedef std::map<trigram, int> dict;


void readFile(const string& fileName, std::map<trigram, int>& dict);
vector <string> readWords(const string& fileName);
vector<trigram> get_trigrams(vector<string> line);
void update_dict(std::map<trigram, int>& dict, vector<trigram> t);

void print_dict(std::map<trigram, int>& dict);

void ascend(std::map<trigram, int>& dict);
void descend(std::map<trigram, int>& dict);
void dec_count(const std::map<trigram, int>& dict);
void third_freq(std::map<trigram, int>& dict, string word1, string word2);


#endif // PLAYER_H