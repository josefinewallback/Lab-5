#include <string>
#include <map>


class kgram {
    private:
        //Attributes
        unsigned k; // Length of kgram
        std::string kgram_str; // Actual kgram string

        unsigned count; // Nr. of times kgram has been seen
        std::map<char, unsigned> next_char_counts; // Map containing the counts of each next character

    public:
        // Constructor
        kgram(unsigned k, std::string kgram_str) : k(k), kgram_str(kgram_str);

        // Method
        // Return next k-gram ("abcd" -> slumpa fram "e" -> nästa kgram "bcde")
        std::string next_kgram();
    
}