#include "smallmodel.h"


std::string smallmodel::generate(unsigned output_length) {
    //Later: 
    //Need to generate starting kgram
    //Need to handle when new_kgram doesn't exist 
    //With alpha = 0, happens if new_kgram only occurs last in training text and has no probs for next_chars.
    //With alpha != 0, since characters with probs 0 get changed to probs alpha then.

    std::string result = "";

    //Assume we have a starting kgram for now
    std::string start = "abcd";
    
    result += start;
    kgram current_kgram = kgrams[start]; //Takes the kgram object from dictionary
    std::string new_kgram;

    //Generate next character, starting loop on k so assumes have starting kgram already
    for(unsigned i= k; i< output_length; i++) {
        new_kgram = current_kgram.generate_next();
        
        result += new_kgram[k-1]; //append new character only

        current_kgram = kgrams[new_kgram];
        
    }
    return result;
};

