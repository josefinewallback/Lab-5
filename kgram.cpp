#include "kgram.h"
#include <random>

//See note at end of next_kgram method

kgram::kgram(unsigned k, std::string kgram_str) : k(k), kgram_str(kgram_str), total_count(0) {};


void kgram::appear_in_training(std::string c){
    //Adds one appearance of character c after kgram

    // Get index of c in next_chars or string::npos if not in next_chars
    size_t index = next_chars.find(c);
    if(index != string::npos ){
        next_chars_count[index] += 1; // Adds +1 to counter of c
    } else{
        next_chars += c; // Adds c as a next character
        next_chars_count.push_back(1); //Starts a counter for appearances
    };

    total_count += 1; // Add +1 to total counter of kgram
};

std::string kgram::next_kgram() {
    //Returns a string with the next kgram, using sampled character c

    // Generate next character c
    std::string c;

    // Initialize a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, total_count-1);

    // Generate random number in the range [0, count-1]
    int random_number = distrib(gen);

    // Sums counts in vector next_chars_count by adding count at index i until random_number < sum (of indices 0 to i) and return next_char at index i in string next_chars. See example.
    // Example: next_chars "abc" with next_chars_counts {4, 5, 1} -> total count 10. Then P(a) = 4/10. Tal mellan 0 och 9 slumpas, {0,1,2,3} kommer ge "a", {4,5,6,7,8} kommer ge "b", etc. Vi slumpar fram 6. Om vi summerar över vektorn får vi först 4, sedan 4+5=9, vilket är >= 6

    int count_sum = 0;
    for(int i = 0; i< next_chars.length(); i++){
        count_sum += next_chars_count[i]
        if(random_number <= count_sum){
            c = next_chars[i];
            break
        };
    };

    // Create string with new kgram 
    std::string result = kgram_str[1:] + c; //unsure if can get all but first character in kgram_str like this, otherwise can try std::string kgram_str.substr(1,k-1) (creates a copy of substring starting at pos 1 and of length k-1)
    return result;
};
