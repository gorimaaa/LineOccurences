//  Partie interface du module holdall (fourretout).
//
//  Un fourretout permet la mémorisation d'une liste de références d'objets
//    quelconques, l'exécution de fonctions sur les objets repérés par les
//    références dans la liste selon l'ordre dans lequel les références y
//    figurent ainsi que la réorganisation de la liste.

#ifndef HOLDALL__H
#define HOLDALL__H

//  Fonctionnement général :
//  - la structure de données ne stocke pas d'objets mais des références vers
//      ces objets. Les références sont du type générique « void * » ;
//  - si des opérations d'allocation dynamique sont effectuées, elles le sont
//      pour la gestion propre de la structure de données, et en aucun cas pour
//      réaliser des copies ou des destructions d'objets ;
//  - les fonctions qui possèdent un paramètre de type « holdall * » ou
//      « holdall ** » ont un comportement indéterminé lorsque ce paramètre ou
//      sa déréférence n'est pas l'adresse d'un contrôleur préalablement
//      renvoyée avec succès par la fonction holdall_empty et non révoquée
//      depuis par la fonction holdall_dispose ;
//  - l'insertion d'une référence à un fourretout ne donne lieu à aucun test de
//      la valeur de la référence ;
//  - l'endroit où a lieu l'insertion d'une référence à un fourretout n'est pas
//      spécifié.

#include <stdlib.h>

//- STANDARD -------------------------------------------------------------------

//  struct holdall, holdall : type et nom de type d'un contrôleur regroupant les
//    informations nécessaires pour gérer un fourretout.
typedef struct holdall holdall;

//  holdall_empty : tente d'allouer les ressources nécessaires pour gérer un
//    nouveau fourretout initialement vide. Renvoie NULL en cas de dépassement
//    de capacité. Renvoie sinon un pointeur vers le contrôleur associé au
//    fourretout.
extern holdall *holdall_empty(void);

//  holdall_dispose : sans effet si *haptr vaut NULL. Libère sinon les
//    ressources allouées la gestion du fourretout associé à *haptr puis affecte
//    NULL à *haptr.
extern void holdall_dispose(holdall **haptr);

// holdall_dispose_all(holdall **haptr) : sans effet si *haptr vaut NULL. Libère sinon
// toutes les cellules associé au fourretout ainsi que leurs références.
extern void holdall_dispose_all(holdall **haptr);

//  holdall_put : tente d'insérer ref au fourretout associé à ha. Renvoie une
//    valeur non nulle en cas de dépassement de capacité. Renvoie sinon zéro.
extern int holdall_put(holdall *ha, void *ref);

//  holdall_add : tente d'insérer ref au fourreteout associé à ha. Renvoie une 
//  valeur non nulle en cas de dépassement de capacité. Renvoie sinon zéro.
//  De plus cette fonction rajoute systématiquement en queue.
extern int holdall_add(holdall *ha, void *ref);

// holdall_search_index : recherche l'élément à l'indice index dans le fourretout
// (les indices allant de 0 à holdall_count(ha) - 1), si l'élément existe renvoie
// ref, sinon renvoie NULL si l'indice n'est pas dans le fourretout.
extern void *holdall_search_index(holdall *ha, size_t index);

//  holdall_count : renvoie le nombre d'insertions effectuées avec succès dans
//    le fourretout associé à ha depuis sa création.
extern size_t holdall_count(holdall *ha);

// holdall_print : affiche tous les éléments ref du fourretout dans l'ordre croissant
// sous le format ref, ref, ref(...) 
extern void holdall_print_one_file(holdall *ha);

//  holdall_apply, holdall_apply_context, holdall_apply_context2 : parcourt le
//    fourretout associé à ha en appelant (respectivement) fun(ref),
//    fun2(ref, fun1(context, ref)), fun2(context2, ref, fun1(context1, ref))
//    pour chacune des références ref dans l'ordre dans lequel elles figurent
//    dans le fourretout. Si, lors du parcours, la valeur de l'appel n'est pas
//    nulle, l'exécution de la fonction prend fin et la fonction renvoie cette
//    valeur. Sinon, la fonction renvoie zéro.
extern int holdall_apply(holdall *ha, int (*fun)(void *));
extern int holdall_apply_context(holdall *ha,
    void *context, void *(*fun1)(void *context, void *ref),
    int (*fun2)(void *ref, void *resultfun1));
extern int holdall_apply_context2(holdall *ha,
    void *context1, void *(*fun1)(void *context1, void *ref),
    void *context2, int (*fun2)(void *context2, void *ref, void *resultfun1));


//------------------------------------------------------------------------------

#endif
