#include "kgram.h"
#include <random>


std::string kgram::next_kgram() {

    //Generate next character c
    std::string c;

    // Initialize a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, total_count-1);

    // Generate random number in the range [0, count-1]
    int random_number = distrib(gen);

    //Sums counts in vector next_chars_count by adding count at index i until random_number < sum (of indices 0 to i) and return next_char at index i in string next_chars. See example.
    // Example: next_chars "abc" with next_chars_counts {4, 5, 1} -> total count 10. Then P(a) = 4/10. Tal mellan 0 och 9 slumpas, {0,1,2,3} kommer ge "a", {4,5,6,7,8} kommer ge "b", etc. Vi slumpar fram 6. Om vi summerar över vektorn får vi först 4, sedan 4+5=9, vilket är >= 6

    int count_sum = 0;
    for(int i = 0; i< next_chars.length(); i++){
        count_sum += next_chars_count[i]
        if(random_number <= count_sum){
            c = next_chars[i];
            break
        };
    };

    //Create string with new kgram 
    std::string result = kgram_str[1:] + c;
    return result;
};
