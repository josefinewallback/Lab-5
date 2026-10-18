#include <map>
#include <string>
#include <vector>
#include "kgram.h"

class smallmodel {
    private:
        //Attributes
        unsigned k; //Length of kgrams
        double alpha; //Smoothing parameter

        std::string alphabet; // String of all characters in text

        std::map<std::string, kgram> kgrams; // Dictionary of kgrams in text

        std::string sample_start_kgram();

        size_t nr_kgrams_total;


    public:
        //Constructor
        smallmodel(unsigned k, std::string filename, double alpha);

        // Methods for "training" the model on a given text
        void make_alphabet(std::string contents);
        void train(std::string filename);

        
        // Method for generating text based on output length
        std::string generate(unsigned output_length);

};