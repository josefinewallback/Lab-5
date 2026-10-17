#include <map>
#include <string>
#include <vector>
#include "kgram.h"

class smallmodel {
    private:
        //Attributes
        unsigned k; //Length of kgrams
        std::vector<std::string> alphabet; //Vector of all characters in text

        std::map<std::string, kgram> kgrams; //Dictionary of kgrams

    public:
        //Constructor
        smallmodel(unsigned k, std::string filename, unsigned)

        // Method for "training" the model on a given text
        void train(std::string filename);

        
        // Method for generating text based on output length
        std::string generate(unsigned output_length);

}