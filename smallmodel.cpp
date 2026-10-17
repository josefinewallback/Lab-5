#include "smallmodel.h"
#include <fstream>
#include <iostream>
#include <sstream>

// See note at beginning of train and generate method

void smallmodel::make_alphabet(std::string contents) {
    // Sort the string, and then deduplicate using std::unique and erase the duplicates to get alphabet
    std::sort(contents.begin(), contents.end());
    contents.erase(std::unique(contents.begin(), contents.end()), contents.end()); 
    //Seems all duplicated are 'moved' to the end using unique and erase is needed to delete them so that string length is correct

    alphabet = contents;
}

void smallmodel::train(std::string filename) {
    //Notes:
    //Last kgram in entire training data will not be constructud if it does not appear earlier - can cause issue while generating
    //Data string includes "\n", unsure if supposed to or not.
    //How to deal with alpha !=0?, i.e. adding the characters, their counts and total counts


    //Read in training data as one long string
    std::ifstream datafile;
    datafile.open(filename);

	std::stringstream buffer;

	buffer << datafile.rdbuf();     //.rdbuf() : Get stream buffer
    std::string file_contents = buffer.str();
    
    datafile.close();

    //Make alphabet from training data, takes in file_contents string
    smallmodel::make_alphabet(file_contents); 
    
    // Actual training on the data
    std::string curr_kgram_str;

    for(size_t i=k; i < file_contents.length(); i++){
        // Index i will refer to the character after the current kgram in string. I.e. will loop thorugh to the end of the string and check every kgram except the very last one.

        curr_kgram_str = file_contents.substr(i-k, k); // (pos of 1st elem, substr length)

        // If kgram has not appeared previously in text: 
        if (kgrams.count(curr_kgram_str) == 0) { 
            //curr_kgram_str not found in dict key list
            kgram new_kgram(k, curr_kgram_str); // Constructs kgram
            kgrams[curr_kgram_str] = new_kgram; // Adds kgram to dict kgrams
        };
        
        kgrams[curr_kgram_str].appear_in_training(file_contents[i]); // Add relevant counts to kgram
    };
};



std::string smallmodel::generate(unsigned output_length) {
    //Later: 
    //Need to generate starting kgram
    //Need to handle when new_kgram doesn't exist as a kgram object
    //With alpha = 0, happens if new_kgram only occurs last in training text and has no probs for next_chars.
    //With alpha != 0, can happen elsewhere since characters with probs 0 get changed to probs alpha then.

    std::string result = "";

    //Assume we have a starting kgram for now
    std::string start = "abcd";
    
    result += start;
    kgram current_kgram = kgrams[start]; //Takes the kgram object from dictionary
    std::string new_kgram;

    //Generate next character, starting loop on k so assumes have starting kgram already
    for(unsigned i= k; i< output_length; i++) {
        new_kgram = current_kgram.next_kgram();
        
        result += new_kgram[k-1]; //append new character only

        current_kgram = kgrams[new_kgram];
    };
    return result;
};

