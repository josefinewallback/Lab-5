#include "smallmodel.h"
#include "kgram.h"
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <map>
#include <stdexcept>

// See note at beginning of method

smallmodel::smallmodel(unsigned k, double alpha) : k(k), alpha(alpha) {};

void smallmodel::make_alphabet(std::string contents) {
    // Sort the string, and then deduplicate using std::unique and erase the duplicates to get alphabet
    std::sort(contents.begin(), contents.end());
    contents.erase(std::unique(contents.begin(), contents.end()), contents.end()); 
    //Seems all duplicated are 'moved' to the end using unique and erase is needed to delete them so that string length is correct

    alphabet = contents;
};

void smallmodel::train(std::string filename) {
    //Notes:
    //Last kgram in entire training data will not be constructud if it does not appear earlier - can cause issue while generating
    //Data string includes "\n", unsure if supposed to or not.


    //Read in training data as one long string

    std::ifstream datafile;
    datafile.open(filename); 
    
    // After this, check that the file is open and throw error if not 
    if(!datafile.is_open()) {
        throw  std::runtime_error("Failed to open file " + filename);
    };


	std::stringstream buffer;

	buffer << datafile.rdbuf();     //.rdbuf() : Get stream buffer
    std::string file_contents = buffer.str(); 
    
    // check that file_contents.length() >= k+1 and throw error if not
    if(file_contents.length() < k+1) {
        throw std::invalid_argument("File length is too small for this value of k");
    };
    
    datafile.close();
    

    //Make alphabet from training data, takes in file_contents string
    make_alphabet(file_contents); 


    
    // Actual training on the data
    std::string curr_kgram_str;

    for(size_t i=k; i < file_contents.length(); i++){
        // Index i will refer to the character after the current kgram in string. I.e. will loop thorugh to the end of the string and check every kgram except the very last one.

        curr_kgram_str = file_contents.substr(i-k, k); // (pos of 1st elem, substr length)

        // If kgram has not appeared previously in text: 
        if (kgrams.count(curr_kgram_str) == 0) { 
            //curr_kgram_str not found in dict key list
            kgram new_kgram(k, curr_kgram_str, alpha, alphabet); // Constructs kgram
            kgrams[curr_kgram_str] = new_kgram; // Adds kgram to dict kgrams
        };
        
        kgrams[curr_kgram_str].appear_in_training(file_contents[i]); // Add relevant counts to kgram
    };

    nr_kgrams_total = file_contents.length() - k;
};

std::string smallmodel::sample_start_kgram() {
    // Initialize a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, nr_kgrams_total - 1);

    size_t random_number = distrib(gen);

    // Method for picking the kgram based of the generated random_number is the same as when s new character c is sampled in next_kgram method. If needed, seeee comments in kgram.cpp for more explanation. Here it iterates through the dictionary (map) instead. 
    size_t counter = 0;
    for (const auto& [kgram_str, kgram_obj] : kgrams) { // Better to use const whenever possible 
        counter += kgram_obj.get_total_count();
        if (counter >= random_number) {
            return kgram_str;
        }
        // reference is "like the object" but references the same place in the memory (so changes will be made directly to object)
        // pointer is a unsigned int with the memory address (similar, but syntax is different and 'scarier' why? more tied to place in memory rather than object)
    }
    return ""; // should never happen but is needed for compiler to be happy
};



std::string smallmodel::generate(unsigned output_length) {
    std::string result = "";

    // Sample starting kgram

    std::string start = sample_start_kgram();
    
    result += start;
    kgram current_kgram = kgrams[start]; // Takes the kgram object from dictionary
    std::string new_kgram_str;

    // Generate next character, starting loop on k so assumes have starting kgram already
    for(unsigned i= k; i< output_length; i++) {
        new_kgram_str = current_kgram.next_kgram(); // Generate string for new kgram
        
        result += new_kgram_str[k-1]; // Append new character only

        // Handle whether new_kgram exists here before loop starts over
        // With alpha = 0, happens if new_kgram only occurs last in training text and has no probs for next_chars. With alpha != 0, can happen elsewhere since characters with probs 0 get changed to probs alpha then.
        if (kgrams.count(new_kgram_str) == 0) { // kgram not in dictionary
            if (alpha != 0.0) { 
                current_kgram = kgram(k, new_kgram_str, alpha, alphabet); // Distribution will not depend on kgram, but on alpha only so no reason to save kgram in dictionary, only create the kgram to acces next_kgram method (i.e. sample next character). Essentially just a uniform distribution, but generating the nect character by creating a kgram allows us to continue the loop
            } else {
                break; // I.e. alpha = 0 and then current kgram has no transitions and so will stop text generation early. Only possible for the last kgram in training text.
            };
        } else { // kgram in dictionary
            current_kgram = kgrams[new_kgram_str]; // Overwrite current_kgram with new kgram (copy the new kgram and assign to current_kgram)
        }
    };
    return result;
};

