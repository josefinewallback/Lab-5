Briefly describes your software, how to compile code and how to use it.

What software does:
Software constructs a small language model. The program reads a text file, infers a language model from it, and then use that model to generate new “text” (not necessarily correct).

The lanugage model operates on k-grams or "words" of fixed length k, generating new text based on sampling the next character of a k-gram based on frequencies in the training data. 

It should generate text fine with input texts containing only plain ASCII. 


How to compile:
Open terminal in project root, then write `make`.

What it is and how to use:
The software is a Unix tool 'slm' that takes in three arguments and one option.
- An integer k that decides the word size.
- The name of a text file, containing any kind of text, that is used for training the model.
- An integer that decides how many characters to output, including the starting k-gram. It must be at least k.

The user can give the pseudocount alpha with the option -a, placed before the three arguments. If the option is not given, alpha = 0.

Acceptable input can look like the following:
```slm 2 moby_dick.txt 5```
or 
```slm -a 0.01 3 moby_dick.txt 40```



