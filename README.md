# LineOccurences
Ce projet a pour but de chercher dans des fichiers passés en paramètre et d'afficher dans le premier cas les numéros de lignes qui ont au moins 2 occurences identiques dans un seul fichier sous la forme ```X, Y  LINE```, 
dans le deuxième cas 2 fichiers ou plus sont traités, cette fois le programme affiche les lignes aparaissants au moins une fois dans chaque fichier avec leurs ocurrences dans chacun de ces fichiers sous la forme ```X, Y, ...  LINE```

## Build instructions
A makefile is doing the build
Go to the LineOccurences directory
```bash
cd LinesOccurences
cd lnid_test
make
./lnid [OPTIONS] FILE_1 FILE_2 ...
```
Voici le helper du programme : 
![Capture d'écran 2023-11-13 201617](https://github.com/gorimaaa/occurences_lignes/assets/136479651/6ed60a90-09a1-4f65-822d-96a2e5f5dd36)
[Capture vidéo du 03-09-2024 19:05:43.webm](https://github.com/user-attachments/assets/a5cc70ed-3f9e-46ba-be44-a5b71e3d6cb7)

Ce programme lit des noms de fichiers passés en ligne de commande et effectue des traitements sur ceux-ci
Il y a deux cas à distinguer :

-Si un seul nom de fichier est passé en paramètre le programme recherche les lignes de texte qui apparaissent au moins deux fois dans le fichier et affiche les numéros de lignes correspondants ainsi que le contenu commun associé à ces lignes. Par exemple si la phrase « toto mange » est à la ligne 15 et 43 alors l’affichage sera : 
15, 43 --⟩ toto mange
Avec notre programme : 
![Image1](https://github.com/gorimaaa/occurences_lignes/assets/136479651/61dcb579-9a1b-4cbf-ac02-388072d16229)



-Si au moins deux noms de fichiers figurent sur la ligne de commande, il faut afficher pour chaque ligne de texte non vide apparaissant au moins une fois dans tous les fichiers leurs occurrences dans chacun de ces fichiers suivis du contenu de cette ligne. Par exemple si la phrase « toto boit » apparaît une fois dans le premier fichier et cinq fois dans le deuxième, l’affichage serait :
1 --⟩ 5 --⟩ toto boit
Avec notre programme : 
![Image2](https://github.com/gorimaaa/occurences_lignes/assets/136479651/249dbd97-4ba1-4a7f-990e-6b43e599a0df)


De plus l’utilisateur peut entrer différentes options dans la saisie par ligne de commande, ces options permettent de faire des modifications du programme (sur l’affichage, la sélection des lignes etc…)

Un rapport complet du projet est disponible, il détaille tout le développement de ce projet.
