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
        size_t nr_kgrams_total;

        //Helper methods
        std::string sample_start_kgram(); //Helper method for generate to get starting kgram
        void make_alphabet(std::string contents); //Helper method for train to get possible characters to store in kgrams

    public:
        //Constructor
        smallmodel(unsigned k, double alpha);

        // Method for "training" the model on a given text
        void train(std::string filename);

        // Method for generating text based on output length
        std::string generate(unsigned output_length);
};