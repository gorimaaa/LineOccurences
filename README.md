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
![Capture d'écran 2023-11-13 201617](https://github.com/gorimaaa/occurences_lignes/assets/136479651/6ed60a90-09a1-4f65-822d-96a2e5f5dd36)

## Screenshots
First Case of use :  
![Image1](https://github.com/gorimaaa/occurences_lignes/assets/136479651/61dcb579-9a1b-4cbf-ac02-388072d16229)

Second case :  
![Image2](https://github.com/gorimaaa/occurences_lignes/assets/136479651/249dbd97-4ba1-4a7f-990e-6b43e599a0df)
