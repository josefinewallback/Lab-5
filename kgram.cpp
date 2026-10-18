#include <vector>
#include <random>
#include <string>
#include "kgram.h"

//See if can shorten comment on how loop works in next_kgram

kgram::kgram(unsigned k, std::string kgram_str, double alpha, std::string alphabet) 
: k(k), kgram_str(kgram_str), total_count(0), alpha(alpha), alphabet(alphabet) {
    alphabet_count = std::vector<unsigned>(alphabet.size(), 0); // Initialize alphabet_count with zeros
};


void kgram::appear_in_training(char c){
    //Adds one appearance of char c after kgram

    alphabet_count[alphabet.find(c)] += 1; // Get index of c in alphabet and adds +1 to counter of c
    total_count += 1; // Add +1 to total counter of kgram
};

unsigned kgram::get_total_count() const {
    return total_count;
};

std::string kgram::next_kgram() {
    //Returns a string with the next kgram, using sampled character c


    //Generate random number for sampling

    // Initialize a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distrib(0.0, 1.0);

    // Generate random number in the range [0.0, 1.0)
    double random_number = distrib(gen);

    // Scale random number to the range [0, total_count + alpha * alphabet.size()) 
    double scaled_random_number = random_number * (total_count + alpha * alphabet.size()); 
    


    // Get sampled character c
    std::string c;
    double count_sum = 0.0;

    // Loops through the partial sums of nr. of occurences of characters in the order they appear in the string alphabet until the scaled_random_number <= the partial sums (of indices 0 to i) and will return the character at index i in string alphabet. Smoothing parameter is taked into account with +alpha in each term of the sum. See example for how loop works.
    // Example: Take "abc" with counts {4, 5, 1} -> total count 10. Let alpha = 0.5. A number between 0 and 11.5 is generated. 4+0.5=4.5 or less gives "a", larger than 4.5 but ledd than 4.5+(5+0.5)=10 gives "b", etc. Say we get 6.5. Summing over the count vector, we first get 4.5, then 4.5+5.5=10 >= 6.5. So sampled character is "b"
    for(size_t i = 0; i< alphabet.length(); i++){
        count_sum += (alphabet_count[i] + alpha);
        if(scaled_random_number <= count_sum){
            c = alphabet[i];
            break;
        };
    };

    // Create string with new kgram 
    std::string result = kgram_str.substr(1, k-1) + c; // (creates a copy of substring starting at pos 1 and of length k-1)
    return result;
};
