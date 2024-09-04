//options.h : partie interface d'un module flexible permettant de tester 
//	et mettre à jour les options entrés par l'utilisateur

// Une structure options permet la mémorisation de toutes les options et
// le nom des fichiers textes que
// l'utilisateur peut entrer en ligne de commande à l'appel du programme.
// En outre cette structure permet d'utiliser les fonctions mémorisées.

// Fonctionnement général : 
//  - la fonction is_class n'est utilisable que si filter est vrai, son utilisation provoque sinon un comportement indéterminé 
//  - Cette structure est définie de manière à être modifiable sur le nom des options, ainsi que les préfixes de celles-ci, 
//	  par exemple la macroconstante FILTER_LONG peut avoir un nom modifié de sorte que l'utilisateur puisse rentrer "--fonction=isalpha"
//	  au lieu de "--filter=isalpha" si jamais "filter" pour FILTER_LONG est modifié en "fonction"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "holdall.h"

// Options modulable
#define OPT__SHORT  "-"
#define OPT__LONG   "--"
#define OPT_HELP_L  OPT__LONG "help"
#define FILTER_SHORT "f"
#define FILTER_LONG "filter"
#define SORT_SHORT "s"
#define SORT_LONG "sort"
#define UPPERCASE_SHORT "u"
#define UPPERCASE_LONG "uppercasing" 
#define IS_FILE "."


//  struct options, options : type et nom de type d'une structure gérant les options
// entrées par l'utilisateur
typedef struct options options;



//------------Getter-------------//
// opt_filter : renvoie le booléan filter
extern bool opt_filter(options *opt);

// opt_sort : renvoie le booléan sort
extern bool opt_sort(options *opt);

// opt_compar_fun : renvoie un pointeur vers la fonction compar 
extern int (*opt_compar_fun(options *opt))(const void *, const void *);

// opt_uppercase : renvoie le booléan uppercase
extern bool opt_uppercase(options *opt);

// opt_file_names : renvoie un pointeur vers la fonction file_names
extern holdall *opt_file_names(options *opt);

// test_short_filter : vérifie si s est la même chaîne de caractères que la concaténation de OPT__SHORT et FILTER_SHORT,
//		si c'est le cas, la fonction renvoie true, sinon elle renvoie false
extern bool test_short_filter(char *s);

// test_short_sort : vérifie si s est la même chaîne de caractères que la concaténation de OPT__SHORT et SORT_SHORT,
//		si c'est le cas, la fonction renvoie true, sinon elle renvoie false
extern bool test_short_sort(char *s);

// help : Affiche le fonctionnement du programme et son utilisation sur la sortie standard
extern void help();
//------------------------------//


// opt_compar : renvoie le résultat de la fonction de comparaison compar qui a pris
//		en argument a et b, cela renvoie 1 si a > b, 0 si a == b et -1 si a < b
extern int opt_compar(options *opt, const void *a, const void *b);

// opt_class : renvoie le résultat de la fonction is_class qui a pris c en argument,
//		filter doit être vrai pour utiliser cette fonction, le comportement est sinon 
//		indéterminé.
extern int opt_class(options *opt, int c);

// test_short_uppercase : vérifie si s est la même chaîne de caractères que la concaténation de OPT__SHORT et UPPERCASE_SHORT,
//		si c'est le cas, uppercase passe à vrai et la fonction renvoie true, sinon elle renvoie false
extern bool test_short_uppercase(char *s, options *opt);

// test_short_opt_filter : compare la chaîne de caractères s à toutes les fonctions de <ctype.h> (isalpha, isdigit ...), si un cas
//		match, alors filter passe à true et is_class prend cette fonction en paramètre, puis la fonction renvoie 1. Renvoie 0 si
//		aucun cas ne match.
extern int test_short_opt_filter(char *s, options *opt);

// test_short_opt_sort : compare la chaîne de caractères s aux deux options "locale" et "standard"
//		s'il y a un match avec standard sort passe à true et la fonction renvoie 1, s'il y a un match avec
//		locale sort passe à true, la fonction setlocate() est appelé et compar pointe vers strcoll puis renvoie 1.
//		Renvoie 0 si aucun cas ne match.
extern int test_short_opt_sort(char *s, options *opt);
// test_long_opt : Test si la chaîne de caractères pointé par s fait partie de la liste des filtres long 
// renvoie 1 si c'est le cas, -1 en cas d'erreur système, 0 si s n'est pas un filtre long

// test_long_opt : compare la chaîne de caractères s à la concaténation de OPT__LONG, FILTER_LONG et :
//		-Chaque fonction de <ctype.h> (isalpha, isdigit ...) ou
//		-Aux chaînes "locale" ou "standard" ou
//		-UPPERCASE_LONG 
//		S'il y a un match avec les fonctions ctype alors filter passe à true, is_class pointe vers la fonction
//		ctype et la fonction renvoie 1.
//		S'il y a un match avec "standard" sort passe à true et la fonction renvoie 1, s'il y a un match avec "locale"
//		sort passe à true, la fonction setlocate() est appelé et compar pointe vers strcoll puis renvoie 1.
//		S'il y a un match avec UPPERCASE_LONG uppercase passe à true et renvoie 1.
//		Renvoie -1 si une erreur a lieu, 0 si aucun match n'est fait.
extern int test_long_opt(char *s, options *opt);

// opt_initialize : Alloue et initialise une structure de type options, alloue aussi le fourretout associé, filter, sort et uppercase sont
//		mis à false, compar est initialisé à strcmp.
extern options *opt_initialize();

// dispose_opt : Libère l'espace alloué au fourretout et la structure.
extern void dispose_opt(options *opt);

