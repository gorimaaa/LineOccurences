//  bst.h : partie interface d'un module polymorphe pour les arbres binaires.

#ifndef bst__H
#define bst__H

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//  Fonctionnement général :
//  - la structure de données ne stocke pas d'objets mais des références vers
//      ces objets. Les références sont du type générique « void * » ;
//  - si des opérations d'allocation dynamique sont effectuées, elles le sont
//      pour la gestion propre de la structure de données, et en aucun cas pour
//      réaliser des copies ou des destructions d'objets ;
//  - les fonctions qui possèdent un paramètre de type « bst * » ou « bst ** »
//      ont un comportement indéterminé lorsque ce paramètre ou sa déréférence
//      n'est pas l'adresse d'un contrôleur préalablement renvoyée avec succès
//      par la fonction bst_empty et non révoquée depuis par la fonction
//      bst_dispose ;
//  - aucune fonction ne peut ajouter NULL à la structure de données ;
//  - les fonctions de type de retour « void * » renvoient NULL en cas d'échec.
//      En cas de succès, elles renvoient une référence de valeur actuellement
//      ou auparavant stockée par la structure de données ;
//  - l'implantation des fonctions dont la spécification ne précise pas qu'elles
//      doivent gérer les cas de dépassement de capacité ne doivent avoir
//      affaire avec aucun problème de la sorte.

//  struct bst, bst : type et nom de type d'un contrôleur regroupant les
//    informations nécessaires pour gérer un arbre binaire de recherche de
//    d'objets quelconques.
typedef struct bst bst;

//  bst_empty : tente d'allouer les ressources nécessaires pour gérer un nouvel
//    arbre binaire de recherche initialement vide. La fonction de comparaison
//    des objets via leurs références est pointée par compar. Renvoie NULL en
//    cas de dépassement de capacité. Renvoie sinon un pointeur vers le
//    contrôleur associé à l'arbre.
extern bst *bst_empty(int (*compar)(const void *, const void *));

//  bst_dispose : sans effet si *tptr vaut NULL, Libère sinon les ressources
//    allouées à la gestion de l'arbre binaire de recherche associé à *tptr puis
//    affecte NULL à *tptr.
extern void bst_dispose(bst **tptr);


//  bst_dispose_one_file : sans effet si *tptr vaut NULL, Libère sinon les ressources
//    allouées à la gestion de l'arbre binaire de recherche associé à *tptr ainsi que 
//    les références, ce dispose est réservé au cas où la structure est utilisé avec line_table,
//    puis affecte NULL à *tptr.
extern void bst_dispose_one_file(bst **tptr);

//  bst_dispose_multiple_files : sans effet si *tptr vaut NULL, Libère sinon les ressources
//    allouées à la gestion de l'arbre binaire de recherche associé à *tptr ainsi que 
//    les références, ce dispose est réservé au cas où la structure est utilisé avec occurence_table,
//    puis affecte NULL à *tptr.
extern void bst_dispose_multiple_files(bst **tptr);


//  bst_add_endofpath : renvoie NULL si ref vaut NULL. Recherche sinon dans
//    l'arbre binaire de recherche associé à t la référence d'un objet égal à
//    celle de référence ref au sens de la fonction de comparaison. Si la
//    recherche est positive, renvoie la référence trouvée. Tente sinon
//    d'ajouter la référence selon la méthode de l'ajout en bout de chemin ;
//    renvoie NULL en cas de dépassement de capacité ; renvoie sinon ref.
extern void *bst_add_endofpath(bst *t, const void *ref);

// bst_add_endofpath_one_file : renvoie -1 si ref vaut NULL. Recherche sinon dans
//    l'arbre binaire de recherche associé à t la référence d'un objet égal à
//    celle de référence ref au sens de la fonction de comparaison. Si la
//    recherche est positive, on ajoute line dans le fourretout line_table associé à la cellule de ref
//    et on renvoie 0. Tente sinon d'ajouter la référence selon la méthode de l'ajout en bout de chemin si le mot n'est pas blanc;
//    renvoie -1 en cas de dépassement de capacité 0 si ref est blanc, 1 sinon
extern int bst_add_endofpath_one_file(bst *t, const void *ref, size_t *line);

// bst_add_endofpath_multiple_file : renvoie -1 si ref vaut NULL. Recherche sinon dans
//    l'arbre binaire de recherche associé à t la référence d'un objet égal à
//    celle de référence ref au sens de la fonction de comparaison. Si la
//    recherche est positive, on incrémente occurence_table à l'indice index et on renvoie 0.
//    Tente sinon d'ajouter la référence selon la méthode de l'ajout en bout de chemin si le mot n'est pas blanc et index != 0;
//    renvoie -1 en cas de dépassement de capacité 0 si ref est blanc ou que indice == 0, 1 sinon.
extern int bst_add_endofpath_multiple_file(bst *t, const void *ref,
    size_t index,
    size_t number_of_files);

// bst_add_endofpath_same_file : parcours l'arbre binaire de recherche associé à t
//    en copiant l'occurence de occurence_table à l'indice index_similar dans occurence_table
//    à l'indice index pour chaque cellule de l'arbre binaire.
extern void bst_add_endofpath_same_file(bst *t, size_t index, size_t index_similar);

//  bst_remove_climbup_left : recherche dans l'arbre binaire de recherche
//    associé à t la référence d'un objet égal à celle de référence ref au sens
//    de la fonction de comparaison. Si la recherche est négative, renvoie NULL.
//    Retire sinon la référence trouvée selon la méthode du retrait par remontée
//    gauche et renvoie la référence trouvée.
extern void *bst_remove_climbup_left(bst *t, const void *ref);

//  bst_search : recherche dans l'arbre binaire de recherche associé à t la
//    référence d'un objet égal à celle de référence ref au sens de la fonction
//    de comparaison. Renvoie NULL si la recherche est négative, la référence
//    trouvée sinon.
extern void *bst_search(bst *t, const void *ref);

//  bst_size, bst_height, bst_distance : renvoie la taille, la hauteur, la
//    distance de l'arbre binaire de recherche associé à t.
extern size_t bst_size(bst *t);
extern size_t bst_height(bst *t);
extern size_t bst_distance(bst *t);

//  bst_number, bst_rank : calcule le numéro, le rang du nœud de l'arbre binaire
//    de recherche associé à t dont la valeur est égale à celle de l'objet
//    pointé par ref au sens de la fonction de comparaison. Renvoie ce numéro,
//    ce rang si une telle valeur existe. Renvoie sinon le numéro, le rang
//    qu'aurait le nœud si la référence ref était ajoutée à l'arbre.
extern size_t bst_number(bst *t, const void *ref);
extern size_t bst_rank(bst *t, const void *ref);

//  bst_repr_graphic : affiche sur la sortie standard une représentation
//    graphique de l'arbre binaire de recherche associé à t. La fonction put est
//    utilisée pour l'affichage de chacune des valeurs dont les références sont
//    stockées dans l'arbre. La fonction bst_repr_graphic est libre d'afficher
//    des informations supplémentaires liées  aux sous-arbres.
extern void bst_repr_graphic(bst *t, void (*put)(const void *ref));

//  bst_repr_graphic_one_file : parcours l'arbre binaire associé à t pour afficher 
//      les lignes de line_table séparés par une virgule suivi d'une tabulation suivi de ref 
//      pour chaque cellule de l'arbre binaire, cela uniquement dans le cas où line_table contient au moins deux lignes.
extern void bst_display_one_file(bst *t);

//  bst_repr_graphic_multiple_file : parcours l'arbre binaire associé à t pour afficher 
//      les occurences du tableau occurence_table séparés par une tabulation puis suivi d'une tabulation suivi de ref 
//      pour chaque cellule de l'arbre binaire, cela uniquement dans le cas où occurence_table ne contient pas d'occurences à 0.
extern void bst_display_multiple_file(bst *t, size_t number_of_files);


#endif
