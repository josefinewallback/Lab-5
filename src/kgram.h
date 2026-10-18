#ifndef KGRAM_H
#define KGRAM_H

#include <string>
#include <vector>
#include <map>


class kgram {
    private:
        //Attributes
        unsigned k; // Length of kgram
        std::string kgram_str; // Actual kgram string
        unsigned total_count; // Nr. of times kgram has been seen
        double alpha; // Smoothing parameter

        std::string alphabet; // Alphabet string
        std::vector<unsigned> alphabet_count; // Count of how many times each char in the alphabet has been seen after this kgram

    public:
        // Constructors
        kgram(unsigned k, std::string kgram_str, double alpha, std::string alphabet);

        // We need a default constructor and a default copy assignment operator later
        kgram() = default; // Required to use map::operator[] in smallmodel.cpp
        kgram& operator=(const kgram&) = default; // Required to overwrite or assign new kgram in generate method in smallmodel.cpp
        // "The map::operator[] will create an item with the given key and a default-constructed value, if an item with the key doesn't exist."

        // Methods

        // Adjusts relevant attributes each time kgram appears in training data
        void appear_in_training(char c); 
        
        unsigned get_total_count() const; // Used to get the starting kgram 

        // Return next k-gram ("abcd" -> slumpa fram "e" -> nästa kgram "bcde")
        std::string next_kgram();
    
};

#endif