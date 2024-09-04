# LineOccurences
This project aims to search for occurences in files, there are two type of usage :
- ###1st case : 1 file is given in parameter, in this case the lines that have at least 2 occurences are displayed like this ```X, Y, Z, ...  LINE``` where X, Y, Z are the line numbers.  
- ###2nd case : 2 files or more are given, this time the program displays the lines that appear at least one time in each files, ```X, Y, Z, ...  LINE``` where X, Y, Z are the occurences of the line in each file.

## Build and Execute instructions
A makefile is doing the build  
Go to the LineOccurences directory
```bash
cd LinesOccurences
cd lnid_test
make
./lnid [OPTIONS] FILE_1 FILE_2 ...
```
## Options
We can add options to our search, they are specified in the helper :  
```bash
./lnid --help
#  Usage: ./lnid [OPTIONS] FILE [OTHER_FILES]
#  LIST OF OPTIONS :
#    -f CLASS or --filter=CLASS : Display lines where the characters respect
#              the function CLASS, CLASS being a function from
#              <ctype.h> such as isalpha, isalnum...
#  
#   -s WORD or --sort=WORD : Display the sorted lines according to WORD,
#          if WORD=standard we use the strcmp function
#          if WORD=locate we use the strcoll function
#
#   -u or --uppercasing : Converts each line to uppercase
#  
#  2 TYPES OF USAGE:
#   FIRST TYPE : You can choose options and the put a file, an example:
#   ./lnid -f isalpha -s locale test.txt, then we will display the lines
#       that occur at least two times followed by the line, an example of
#   display: 110,55-->football
#
#   SECOND TYPE : You chan choose options and then put multiple files, 
#   an example: ./lnid -s standard --uppercasing test1.txt test2.txt, 
#   then we will display the lines that occur at least one time in each 
#   file given, an example of display : 1-->2-->baseball
```
## Examples of usage
TODO
