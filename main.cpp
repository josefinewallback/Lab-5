#include "smallmodel.h"
#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char* argv[]){
    //slm (-a int alpha=0)  int k  string filename  int outout_length
    //slm -a int alpha  int k  string filename int outout_length

    std::string filename;

    if (argc == 4) { // alpha = 0 path
        // hej
    } else if (argc == 6 && argv[1] == "-a") { // set alpha path
        // hej
    } else { // bad input 
        // hej
    };

    smallmodel slm(5,0.01);

    try {
        slm.train(filename);
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        return 1;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument error: " << e.what() << std::endl;
        return 2;
    };

    




};

//Errors to handle - see pdf for more details on it

//wrong nr of arguments
//either k or output_length not a positive integer, output_length < k
// option -a when not followed by non-negative number, or an unknown option

// all above^^ handled directly in main


// training file cannot be opened, or training file too short to contain any kgram followed by a character
// see line 29 and 34 in smallmodel.cpp for this^^
