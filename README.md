# occurences_lignes
Il y a deux cas à distinguer :
-Si un seul nom de fichier est passé en paramètre le programme recherche les lignes de texte qui apparaissent au moins deux fois dans le fichier et affiche les numéros de lignes correspondants ainsi que le contenu commun associé à ces lignes. Par exemple si la phrase « toto mange » est à la ligne 15 et 43 alors l’affichage sera : 

15, 43 --⟩ toto mange

 -Si au moins deux noms de fichiers figurent sur la ligne de commande, il faut afficher pour chaque ligne de texte non vide apparaissant au moins une fois dans tous les fichiers leurs occurrences dans chacun de ces fichiers suivis du contenu de cette ligne. Par exemple si la phrase « toto boit » apparaît une fois dans le premier fichier et cinq fois dans le deuxième, l’affichage serait :
![Image1](https://github.com/gorimaaa/occurences_lignes/assets/136479651/61dcb579-9a1b-4cbf-ac02-388072d16229)

1 --⟩ 5 --⟩ toto boit

De plus l’utilisateur peut entrer différentes options dans la saisie par ligne de commande, ces options permettent de faire des modifications du programme (sur l’affichage, la sélection des lignes etc…)
