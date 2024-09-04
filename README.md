# LineOccurences
Ce projet a pour but de chercher dans des fichiers textes l'occurence des lignes, il y a deux exemples d'usage:
- 1er cas :  *1 fichier* est passé en paramètre dans ce cas les numéros de lignes qui ont au moins 2 occurences identiques sont affichés sous la forme ```X, Y, Z, ...  LINE```
- 2ème cas : *2 fichiers ou plus* sont traités, cette fois le programme affiche les lignes aparaissants au moins une fois dans chaque fichier avec leurs ocurrences dans chacun de ces fichiers sous la forme ```X, Y, ...  LINE```

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
We can add options to our search, they are specified in the helper (./lnid --help) :  
```bash
./lnid --help

Usage: ./lnid [OPTIONS] FILE [OTHER_FILES]

LIST OF OPTIONS :

  -f CLASS or --filter=CLASS : Display lines where the characters respect
            the function CLASS, CLASS being a function from
            <ctype.h> such as isalpha, isalnum...

  -s WORD or --sort=WORD : Display the sorted lines according to WORD,
        if WORD=standard we use the strcmp function
        if WORD=locate we use the strcoll function

  -u or --uppercasing : Converts each line to uppercase

2 TYPES OF USAGE:
 FIRST TYPE : You can choose options and the put a file, an example:
 ./lnid -f isalpha -s locale test.txt, then we will display the lines
     that occur at least two times followed by the line, an example of
 display: 110,55-->football

 SECOND TYPE : You chan choose options and then put multiple files, 
 an example: ./lnid -s standard --uppercasing test1.txt test2.txt, 
 then we will display the lines that occur at least one time in each 
 file given, an example of display : 1-->2-->baseball
```
## Screenshots
First Case of use :  
![Image1](https://github.com/gorimaaa/occurences_lignes/assets/136479651/61dcb579-9a1b-4cbf-ac02-388072d16229)

Second case :  
![Image2](https://github.com/gorimaaa/occurences_lignes/assets/136479651/249dbd97-4ba1-4a7f-990e-6b43e599a0df)
