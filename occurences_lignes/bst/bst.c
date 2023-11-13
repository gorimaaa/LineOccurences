//  bst.c : partie implantation d'un module polymorphe pour les arbres binaires.
#include "bst.h"
#include "../holdall/holdall.h"

//=== Type cbst ================================================================

//--- Définition cbst ----------------------------------------------------------

typedef struct cbst cbst;

struct cbst {
  cbst *next[2];
  const void *ref;
  int height;
  union {
    holdall *line_table;
    int *occurence_table;
  };
};

#if defined(ROTATION)

#endif

//--- Raccourcis cbst ----------------------------------------------------------

#define EMPTY()     NULL
#define IS_EMPTY(p) ((p) == NULL)
#define LEFT(p)     ((p)->next[0])
#define RIGHT(p)    ((p)->next[1])
#define REF(p)      ((p)->ref)
#define HEIGHT(p)   ((p)->height)
#define NEXT(p, d)  ((p)->next[(d) > 0])
#define OCC(p)      ((p)->occurence_table)
#define LINE(p)     ((p)->line_table)
#define Cbst_BALANCING 5

//--- Divers -------------------------------------------------------------------

static size_t add__size_t(size_t x1, size_t x2) {
  return x1 + x2;
}

static int max__int(int x1, int x2) {
  return x1 > x2 ? x1 : x2;
}

static int min__int(int x1, int x2) {
  return x1 < x2 ? x1 : x2;
}

//--- Fonctions cbst -----------------------------------------------------------

//  DEFUN_Cbst__MEASURE : définit la fonction récursive de nom « cbst__ ## fun »
//    et de paramètre un pointeur d'arbre binaire, qui renvoie zéro si l'arbre
//    est vide et « 1 + oper(r0, r1) » sinon, où r0 et r1 sont les valeurs
//    renvoyées par les appels récursifs de la fonction avec les pointeurs des
//    sous-arbres gauche et droit de l'arbre comme paramètres.
#define DEFUN_Cbst__MEASURE(fun, oper)                                         \
  static size_t cbst__ ## fun(const cbst * p) {                                \
    return IS_EMPTY(p)                                                         \
      ? 0                                                                      \
      : 1 + oper(cbst__ ## fun(LEFT(p)), cbst__ ## fun(RIGHT(p)));             \
  }


DEFUN_Cbst__MEASURE(size, add__size_t)

static int cbst__distance(const cbst *p) {
  if (IS_EMPTY(p)) {
    return 0;
  }
  return 1 + min__int(cbst__distance(LEFT(p)), cbst__distance(RIGHT(p)));
}

static int cbst__height(const cbst *p) {
  return p == NULL ? 0 : HEIGHT(p);
}

static void cbst__update_height(cbst *p) {
  HEIGHT(p) = max__int(cbst__height(LEFT(p)) + 1, cbst__height(RIGHT(p)) + 1);
}

static int cbst__balance(const cbst *p) {
  return IS_EMPTY(p) ? 0 : cbst__height(LEFT(p)) - cbst__height(RIGHT(p));
}

static void cbst__rotation_left(cbst **pp) {
  if (!IS_EMPTY(RIGHT(*pp)) && !IS_EMPTY(*pp)) {
    cbst *p = RIGHT(*pp);
    RIGHT(*pp) = LEFT(p);
    LEFT(p) = *pp;
    *pp = p;
    cbst__update_height(LEFT(*pp));
    cbst__update_height(*pp);
  }
}

static void cbst__rotation_right(cbst **pp) {
  if (!IS_EMPTY(LEFT(*pp)) && !IS_EMPTY(*pp)) {
    cbst *p = LEFT(*pp);
    LEFT(*pp) = RIGHT(p);
    RIGHT(p) = *pp;
    *pp = p;
    cbst__update_height(RIGHT(*pp));
    cbst__update_height(*pp);
  }
}

static void cbst__rotation_left_right(cbst **pp) {
  if (!IS_EMPTY(*pp) && !IS_EMPTY(LEFT(*pp)) && !IS_EMPTY(RIGHT(LEFT(*pp)))) {
    cbst__rotation_left(&LEFT(*pp));
    cbst__rotation_right(&(*pp));
  }
}

static void cbst__rotation_right_left(cbst **pp) {
  if (!IS_EMPTY(*pp) && !IS_EMPTY(RIGHT(*pp)) && !IS_EMPTY(LEFT(RIGHT(*pp)))) {
    cbst__rotation_right(&RIGHT(*pp));
    cbst__rotation_left(&(*pp));
  }
}

static void cbst__dispose(cbst *p) {
  if (!IS_EMPTY(p)) {
    cbst__dispose(LEFT(p));
    cbst__dispose(RIGHT(p));
    free(p);
  }
}
static void cbst__dispose_one_file(cbst *p){
  if(!IS_EMPTY(p)) {
    cbst__dispose_one_file(LEFT(p));
    cbst__dispose_one_file(RIGHT(p));
    free((void *) REF(p));
    holdall_dispose_all(&LINE(p));
    free(p);
  }
}
static void cbst__dispose_multiple_files(cbst *p){
  if(!IS_EMPTY(p)) {
    cbst__dispose_multiple_files(LEFT(p));
    cbst__dispose_multiple_files(RIGHT(p));
    free((void *) REF(p));
    free(p->occurence_table);
    free(p);
  }

}

static int cbst__balancing(cbst **pp) {
  cbst__update_height(*pp);
  int e = cbst__balance(*pp);
  if (e == 2) {
    if (cbst__balance(LEFT(*pp)) >= 0) {
      cbst__rotation_right(pp);
    } else {
      cbst__rotation_left_right(pp);
    }
    return Cbst_BALANCING;
  }
  if (e == -2) {
    if (cbst__balance(RIGHT(*pp)) <= 0) {
      cbst__rotation_left(pp);
    } else {
      cbst__rotation_right_left(pp);
    }
    return Cbst_BALANCING;
  }
  return 0;
}

static void *cbst__remove_max(cbst **pp) {
  if (IS_EMPTY(RIGHT(*pp))) {
    cbst *t = *pp;
    const void *v = REF(*pp);
    *pp = LEFT(*pp);
    free(t);
    return (void *) v;
  }
  void *a = cbst__remove_max(&RIGHT(*pp));
  cbst__balancing(pp);
  return a;
}

static void cbst__remove_root(cbst **pp) {
  if (IS_EMPTY(LEFT(*pp))) {
    if (IS_EMPTY(RIGHT(*pp))) {
      free(*pp);
      *pp = EMPTY();
      return;
    }
    cbst *p = RIGHT(*pp);
    free(*pp);
    *pp = p;
  } else {
    void *v = cbst__remove_max(&LEFT(*pp));
    cbst__balancing(pp);
    REF(*pp) = v;
  }
}

static void *cbst__remove_climbup_left(cbst **pp, const void *ref, int (*compar)(
    const void *,
    const void *)) {
  if (IS_EMPTY(*pp)) {
    return NULL;
  }
  int c = compar(ref, REF(*pp));
  if (c == 0) {
    const void *v = REF(*pp);
    cbst__remove_root(pp);
    return (void *) v;
  }
  void *a = cbst__remove_climbup_left(&NEXT(*pp, c), ref, compar);
  cbst__balancing(pp);
  return a;
}

static void *cbst__add_endofpath(cbst **pp, const void *ref, int (*compar)(
    const void *, const void *)) {
  if (IS_EMPTY(*pp)) {
    *pp = malloc(sizeof **pp);
    if (*pp == NULL) {
      return NULL;
    }
    REF(*pp) = ref;
    LEFT(*pp) = EMPTY();
    RIGHT(*pp) = EMPTY();
    HEIGHT(*pp) = 1;
    return (void *) REF(*pp);
  }
  int c = compar(ref, REF(*pp));
  if (c == 0) {
    return (void *) REF(*pp);
  }
  void *a = cbst__add_endofpath(&NEXT(*pp, c), ref, compar);
  cbst__balancing(pp);
  return a;
}

static int cbst_add_endofpath_one_file(cbst **pp, const void *ref, int (*compar)(
    const void *,
    const void *), size_t *line) {
  if (ref == NULL) {
    return -1;
  }
  if (IS_EMPTY(*pp)) {
    bool is_not_blank = false;
    for (size_t i = 0; i < strlen((char *) ref); i++) {
      char *c = (char *) ref;
      if (!isblank(c[i])) {
        is_not_blank = true;
        break;
      }
    }
    if (is_not_blank) {
      *pp = malloc(sizeof **pp);
      if (*pp == NULL) {
        return -1;
      }
      REF(*pp) = ref;
      LEFT(*pp) = EMPTY();
      RIGHT(*pp) = EMPTY();
      holdall *h = holdall_empty();
      if (h == NULL) {
        return -1;
      }
      if (holdall_add(h, line) != 0) {
        return -1;
      }
      LINE(*pp) = h;
      HEIGHT(*pp) = 1;
      return 1;
    } else {
      free(line);
      return 0;
    }
  }
  int c = compar(ref, REF(*pp));
  if (c == 0) {
    if (holdall_add(LINE(*pp), line) != 0) {
      return -1;
    }
    return 0;
  }
  int a = cbst_add_endofpath_one_file(&NEXT(*pp, c), ref, compar, line);
  cbst__balancing(pp);
  return a;
}

static int cbst_add_endofpath_multiple_file(cbst **pp, const void *ref, int (*compar)(
    const void *,
    const void *), size_t index,
    size_t number_of_files) {
  if (ref == NULL) {
    return -1;
  }
  if (IS_EMPTY(*pp)) { 
    bool is_not_blank = false;
    for (size_t i = 0; i < strlen((char *) ref); i++) {
      char *c = (char *) ref;
      if (!isblank(c[i])) {
        is_not_blank = true;
        break;
      }
    }
    if (index == 0 && is_not_blank) {
      *pp = malloc(sizeof **pp);
      if (*pp == NULL) {
        return -1;
      }
      REF(*pp) = ref;
      LEFT(*pp) = EMPTY();
      RIGHT(*pp) = EMPTY();
      int *t = malloc((sizeof *t) * number_of_files);
      if (t == NULL) {
        return -1;
      }
      // Initialisation des cases du tableau à 0
      for (size_t k = 0; k < number_of_files; ++k) {
        t[k] = 0;
      }
      OCC(*pp) = t;
      OCC(*pp)[index] += 1;
      HEIGHT(*pp) = 1;
      return 1;
    } else {
      return 0;
    }
  }
  int c = compar(ref, REF(*pp));
  if (c == 0) {
    OCC(*pp)[index] += 1;
    return 0;
  }
  int a = cbst_add_endofpath_multiple_file(&NEXT(*pp,
      c), ref, compar, index,
      number_of_files);
  cbst__balancing(pp);
  return a;
}


static void cbst_add_endofpath_same_file(cbst *pp, size_t index, size_t index_similar){
  if (IS_EMPTY(pp)) {
    return;
  }
  OCC(pp)[index]= OCC(pp)[index_similar];
  cbst_add_endofpath_same_file(LEFT(pp),index, index_similar);
  cbst_add_endofpath_same_file(RIGHT(pp),index, index_similar);

}

static void *cbst__search(const cbst *p, const void *ref, int (*compar)(
    const void *, const void *)) {
  if (IS_EMPTY(p)) {
    return NULL;
  }
  int c = compar(ref, REF(p));
  if (c == 0) {
    return (void *) REF(p);
  }
  return cbst__search(NEXT(p, c), ref, compar);
}

static size_t cbst__number(const cbst *p, const void *ref, int (*compar)(
    const void *, const void *), size_t number) {
  if (IS_EMPTY(p)) {
    return number;
  }
  int c = compar(ref, REF(p));
  if (c == 0) {
    return number;
  }
  return c
    > 0 ? cbst__number(RIGHT(p), ref, compar, 2 * number + 1) : cbst__number(LEFT(
      p), ref, compar, 2 * number);
}

static size_t cbst__rank(const cbst *p, const void *ref, int (*compar)(
    const void *, const void *), size_t rank) {
  if (IS_EMPTY(p)) {
    return rank;
  }
  int c = compar(ref, REF(p));
  if (c == 0) {
    return rank + cbst__size(LEFT(p));
  }
  return c > 0 ? cbst__rank(RIGHT(p), ref, compar, rank + cbst__size(LEFT(
      p)) + 1) : cbst__rank(LEFT(p), ref, compar, rank);
}

#define REPR__TAB 4

static void cbst__repr_graphic(const cbst *p, void (*put)(
    const void *ref), size_t level) {
  if (IS_EMPTY(p)) {
    printf("%*c\n", (int) (level * REPR__TAB + 1), '|');
    return;
  }
  cbst__repr_graphic(RIGHT(p), put, level + 1);
  printf("%*c", (int) (level * REPR__TAB), ' ');
  put(REF(p));
  printf(" h = %d", HEIGHT(p));
  printf(" b = %d", cbst__balance(p));
  printf("\n");
  cbst__repr_graphic(LEFT(p), put, level + 1);
}

static void cbst__display_one_file(const cbst *p) {
  if (IS_EMPTY(p)) {
    return;
  }
  if (holdall_count(LINE(p)) <= 1) {
    cbst__display_one_file(LEFT(p));
    cbst__display_one_file(RIGHT(p));
  } else {
    cbst__display_one_file(LEFT(p));
    holdall_print_one_file(LINE(p));
    printf("\t%s\n", (char *) REF(p));
    cbst__display_one_file(RIGHT(p));
  }
}

static void cbst__display_multiple_file(const cbst *p,
    size_t number_of_files) {
  if (IS_EMPTY(p)) {
    return;
  }
  bool all_different_zero = true;
  for (size_t i = 0; i < number_of_files; i++) {
    if (OCC(p)[i] == 0) {
      all_different_zero = false;
    }
  }
  if (all_different_zero) {
    cbst__display_multiple_file(LEFT(p), number_of_files);
    for (size_t i = 0; i < number_of_files; i++) {
      printf("%d\t", OCC(p)[i]);
    }
    printf("%s\n", (char *) REF(p));
    cbst__display_multiple_file(RIGHT(p), number_of_files);
  } else {
    cbst__display_multiple_file(LEFT(p), number_of_files);
    cbst__display_multiple_file(RIGHT(p), number_of_files);
  }
}

//=== Type bst =================================================================

//--- Définition bst -----------------------------------------------------------

struct bst {
  int (*compar)(const void *, const void *);
  cbst *root;
};

//--- Fonctions bst ------------------------------------------------------------

bst *bst_empty(int (*compar)(const void *, const void *)) {
  bst *t = malloc(sizeof *t);
  if (t == NULL) {
    return NULL;
  }
  t->compar = compar;
  t->root = EMPTY();
  return t;
}

void bst_dispose(bst **tptr) {
  if (*tptr == NULL) {
    return;
  }
  cbst__dispose((*tptr)->root);
  free(*tptr);
  *tptr = NULL;
}
void bst_dispose_one_file(bst **tptr){
  if(*tptr == NULL){
    return;
  }
  cbst__dispose_one_file((*tptr)->root);
  free(*tptr);
  *tptr = NULL;
}

void bst_dispose_multiple_files(bst **tptr){
  if(*tptr == NULL){
    return;
  }
  cbst__dispose_multiple_files((*tptr)->root);
  free(*tptr);
  *tptr = NULL;
}


void *bst_remove_climbup_left(bst *t, const void *ref) {
  return cbst__remove_climbup_left(&t->root, ref, t->compar);
}

void *bst_add_endofpath(bst *t, const void *ref) {
  return cbst__add_endofpath(&(t->root), ref, t->compar);
}

int bst_add_endofpath_one_file(bst *t, const void *ref, size_t *line){
  return cbst_add_endofpath_one_file(&(t->root), ref, t->compar, line);
}

int bst_add_endofpath_multiple_file(bst *t, const void *ref, size_t index,
    size_t number_of_files){
  return cbst_add_endofpath_multiple_file(&(t->root), ref, t->compar, index,
      number_of_files);
}

void bst_add_endofpath_same_file(bst *t, size_t index, size_t index_similar){
  cbst_add_endofpath_same_file(t->root,index, index_similar);
}

void *bst_search(bst *t, const void *ref) {
  return cbst__search(t->root, ref, t->compar);
}

size_t bst_size(bst *t) {
  return cbst__size(t->root);
}

size_t bst_height(bst *t) {
  return (size_t) cbst__height(t->root);
}

size_t bst_distance(bst *t) {
  return (size_t) cbst__distance(t->root);
}


size_t bst_number(bst *t, const void *ref) {
  return cbst__number(t->root, ref, t->compar, 1);
}

size_t bst_rank(bst *t, const void *ref) {
  return cbst__rank(t->root, ref, t->compar, 0);
}


void bst_repr_graphic(bst *t, void (*put)(const void *ref)) {
  cbst__repr_graphic(t->root, put, 0);
}

void bst_display_one_file(bst *t) {
  cbst__display_one_file(t->root);
}

void bst_display_multiple_file(bst *t, size_t number_of_files) {
  cbst__display_multiple_file(t->root, number_of_files);
}
