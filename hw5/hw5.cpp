/*
William Li
wli128
*/
#include <iostream>
#include <fstream>
#include "language_model.h"

using std::cout;
using std::endl;



int main(int argc, char * argv[]){
    std::map<trigram, int> dict;
    if(argc > 1){
        readFile(argv[1], dict);
        if(argc > 2){
            char command = argv[2][0];
            switch(command){
                case 'a':
                    ascend(dict);
                    break;
                case 'd':
                    descend(dict);
                    break;
                case 'c':
                    dec_count(dict);
                    break;
                case 'f':
                    if(argc > 4){
                        third_freq(dict, (string)argv[3], (string)argv[4]);
                        break;
                    }
                    else{
                        std::cerr << "Invalid argument list: f requires two additional command-line arguments" << endl;
                        exit(1);
                    }
                default:
                    std::cerr << "Invalid command: valid options are a, d, c, and f" << endl;
                    exit(1);
            }
        }
        else{
            std::cerr << "Invalid command: valid options are a, d, c, and f" <<endl;
            exit(1);
        }
    } 
    return 0;
}