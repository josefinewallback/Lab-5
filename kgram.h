#include <string>
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
        // Constructor
        kgram(unsigned k, std::string kgram_str, double alpha, std::string alphabet);

        // Methods

        // Adjusts relevant attributes each time kgram appears in training data
        void appear_in_training(std::string c); 
        
        // Return next k-gram ("abcd" -> slumpa fram "e" -> nästa kgram "bcde")
        std::string next_kgram();
    
};