#include <string>
#include <map>


class kgram {
    private:
        //Attributes
        unsigned k; // Length of kgram
        std::string kgram_str; // Actual kgram string

        unsigned total_count; // Nr. of times kgram has been seen
        // std::map<char, unsigned> next_char_counts; // Map containing the counts of each next character

        std::string next_chars; //String of next characters

        std::vector<unsigned> next_chars_count; //Nr. of times next character seen (at corresponding index in string)

    public:

        // Constructor
        kgram(unsigned k, std::string kgram_str);

        // Method
        // Return next k-gram ("abcd" -> slumpa fram "e" -> nästa kgram "bcde")
        std::string next_kgram();
    
};