#include "smallmodel.h"
#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char* argv[]){
    //slm (-a int alpha=0)  int k  string filename  int outout_length
    //slm -a int alpha  int k  string filename int outout_length

    std::string filename;
    int output_length, k;
    double alpha;

    // only read here
    if (argc == 4) { // alpha = 0 path
        alpha = 0.0;
        k = std::stoi(argv[1]);
        filename = argv[2];
        output_length = std::stoi(argv[3]);
    } else if (argc == 6 && std::string(argv[1]) == "-a") { // set alpha path
        alpha = std::stod(argv[2]);
        k = std::stoi(argv[3]);
        filename = argv[4];
        output_length = std::stoi(argv[5]);

    } else { // bad input 
        //covers wrong nr. of arguments and unknown option (not -a)
        std::cerr << "Bad formatting of arguments" << std::endl;
        return 3;
    };

    // Here check correctness of arguments
    try{
        if (k<=0) {
            throw std::invalid_argument("The length of the kgrams cannot be non-positive");
        }
        if (alpha < 0) {
            throw std::invalid_argument("The pseudocount cannot be negative");
        }
        if (output_length < k) {
            throw std::invalid_argument("The output length cannot be shorter than k");
        }
    } catch (const std::invalid_argument& err) {
        std::cerr << "Invalid argument error: " << err.what() << std::endl;
        return 4;
    };
    

    smallmodel slm(k,alpha);
    
    // Train model - errors related to file caught when training model
    try {
        slm.train(filename);
    } catch (const std::runtime_error& err) { // File cannot be opened
        std::cerr << "Runtime error: " << err.what() << std::endl;
        return 1;
    } catch (const std::invalid_argument& err) { //Training text to short for chosen word size k
        std::cerr << "Invalid argument error: " << err.what() << std::endl;
        return 2;
    };
    // Diff. nr to keep track of diff. errors
    // Use exit(0) (good) or exit(1) (bad) if not already in main
    

    // Generate text 
    std::cout << slm.generate(output_length) << std::endl;;
    
    return 0; 

};
