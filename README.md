Briefly describes your software, how to compile code and how to use it.

What software does:
Software constructs a small language model. The program reads a text file, infers a language model from it, and then use that model to generate new “text” (not necessarily correct).

The lanugage model operates on k-grams or "words" of fixed length k, generating new text based on sampling the next character of a k-gram based on frequencies in the training data. 

It should generate text fine with input texts containing only plain ASCII. I'm however unsure if this truly holds. The training data is presumed plain ASCII but the output in the terminal is not what is expected then. It seems that there may be more than 128 unique characters, so more than what char and string can contain. The files are rather maybe UTF-8. For example, row 169  contains 3 non-ASCII characters (I think they can be called curly quotes or slanted quotation marks).

EDIT: If one runs `file --mime-encoding texts/moby_dick.txt` in the project root, it will indeed be confirmed that the files are encoded as utf-8 rather than us-ascii.


To compile you first need to open the terminal in project root and write `make`.

What it is and how to use:
The software is a Unix tool 'slm' that takes in three arguments and one option.
- An integer k that decides the word size.
- The name of a text file, containing any kind of text, that is used for training the model.
- An integer that decides how many characters to output, including the starting k-gram. It must be at least k.

The user can give the pseudocount alpha with the option -a, placed before the three arguments. If the option is not given, alpha = 0.

Acceptable input can look like the following:
```
slm 2 moby_dick.txt 5
```
or 
```
slm -a 0.01 3 moby_dick.txt 40
```

Note:
In order to properly access the program as a UNIX command line tool, you need to:
1. Make the binary executable 
```
chmod +x slm
```
2. Ensure the bin directory exists
```
sudo mkdir -p /usr/local/bin
```
3. Create a global symbolic link to your bin
```
sudo ln -sf "$(pwd)/slm" /usr/local/bin/slm
```

If you do not want to do these steps, you can simply replace `slm` by `./slm` in all the above commands.




