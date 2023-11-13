#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "bst.h"
#include "holdall.h"

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


typedef struct options options;

struct options{
  bool filter;
  int (*is_class)(int); // faire un pointeur de fonction
  bool sort;
  int (*compar)(const void *, const void *);
  bool uppercase;
  holdall *file_names;
};

void help(){
  printf("\nUsage: ./lnid [OPTIONS] FILE [OTHER_FILES]\n\n"
         "LIST OF OPTIONS :\n\n"
          "  -f CLASS or --filter=CLASS : Display lines where the characters respect\n"
          "            the function CLASS, CLASS being a function from\n"
          "            <ctype.h> such as isalpha, isalnum...\n\n"
          "  -s WORD or --sort=WORD : Display the sorted lines according to WORD,\n"
          "        if WORD=standard we use the strcmp function\n"
          "        if WORD=locate we use the strcoll function\n\n"
          "  -u or --uppercasing : Converts each line to uppercase\n\n"
          "2 TYPES OF USAGE:\n"
          " FIRST TYPE : You can choose options and the put a file, an example:\n"
          " ./lnid -f isalpha -s locale test.txt, then we will display the lines\n"
          "     that occur at least two times followed by the line, an example of\n"
          " display: 110,55-->football\n\n"
          " SECOND TYPE : You chan choose options and then put multiple files, \n"
          " an example: ./lnid -s standard --uppercasing test1.txt test2.txt, \n"
          " then we will display the lines that occur at least one time in each \n"
          " file given, an example of display : 1-->2-->baseball\n\n");
}

bool test_short_uppercase(char *s, options *opt){
  if(strcmp(s, "-u") == 0){
    opt->uppercase = true;
    return true;
  }
  return false;

}

int test_short_opt(char *s, options *opt){
  if(strcmp(s, "isalnum") == 0){
    opt->filter = true;
    opt->is_class = isalnum;
    return 1;
  }
  if(strcmp(s, "isalpha") == 0){
    opt->filter = true;
    opt->is_class = isalpha;
    return 1;
  }
  if(strcmp(s, "isblank") == 0){
    opt->filter = true;
    opt->is_class = isblank;
    return 1;
  }
  if(strcmp(s, "iscntrl") == 0){
    opt->filter = true;
    opt->is_class = iscntrl;
    return 1;
  }
  if(strcmp(s, "isdigit") == 0){
    opt->filter = true;
    opt->is_class = isdigit;
    return 1;
  }
  if(strcmp(s, "isgraph") == 0){
    opt->filter = true;
    opt->is_class = isgraph;
    return 1;
  }
  if(strcmp(s, "islower") == 0){
    opt->filter = true;
    opt->is_class = islower;
    return 1;
  }
  if(strcmp(s, "isprint") == 0){
    opt->filter = true;
    opt->is_class = isprint;
    return 1;
  }
  if(strcmp(s, "ispunct") == 0){
    opt->filter = true;
    opt->is_class = ispunct;
    return 1;
  }
  if(strcmp(s, "isspace") == 0){
    opt->filter = true;
    opt->is_class = isspace;
    return 1;
  }
  if(strcmp(s, "isupper") == 0){
    opt->filter = true;
    opt->is_class = isupper;
    return 1;
  }
  if(strcmp(s, "isxdigit") == 0){
    opt->filter = true;
    opt->is_class = isxdigit;
    return 1;
  }
  if(strcmp(s, "standard") == 0){
    opt->sort = true;
    return 1;
  }
  if(strcmp(s, "locale") == 0){
    opt->sort = true;
    setlocale(LC_COLLATE, "");
    opt->compar = (int (*)(const void *, const void *))strcoll;
    return 1;
  }
  return 0;
}
// test_long_opt : Test si la chaîne de caractères pointé par s fait partie de la liste des filtres long 
// renvoie 1 si c'est le cas, -1 en cas d'erreur système, 0 si s n'est pas un filtre long
int test_long_opt(char *s, options *opt){
  char message[30];
  if(sprintf(message, "%s%s%s", OPT__LONG, FILTER_LONG, "=isalnum") == EOF){
    return -1;
  }
  if(strcmp(message, s) == 0){
    opt->filter = true;
    opt->is_class = isalnum;
    return 1;
  }
  message[0] = '\0';
  if(sprintf(message, "%s%s%s", OPT__LONG, FILTER_LONG, "=isalpha") == EOF){
    return -1;
  }
  if(strcmp(message, s) == 0){
    opt->filter = true;
    opt->is_class = isalpha;
    return 1;
  }
  message[0] = '\0';
  if(sprintf(message, "%s%s%s", OPT__LONG, FILTER_LONG, "isblank") == EOF){
    return -1;
  }
  if(strcmp(message, s) == 0){
    opt->filter = true;
    opt->is_class = isblank;
    return 1;
  }
  message[0] = '\0';
  if(sprintf(message, "%s%s%s", OPT__LONG, FILTER_LONG, "=iscntrl") == EOF){
    return -1;
  }
  if(strcmp(message, s) == 0){
    opt->filter = true;
    opt->is_class = iscntrl;
    return 1;
  }
  message[0] = '\0';
  if(sprintf(message, "%s%s%s", OPT__LONG, FILTER_LONG, "=isdigit") == EOF){
    return -1;
  }
  if(strcmp(message, s) == 0){
    opt->filter = true;
    opt->is_class = isdigit;
    return 1;
  }
  message[0] = '\0';
  if(sprintf(message, "%s%s%s", OPT__LONG, FILTER_LONG, "=isgraph") == EOF){
    return -1;
  }
  if(strcmp(message, s) == 0){
    opt->filter = true;
    opt->is_class = isgraph;
    return 1;
  }
  message[0] = '\0';
  if(sprintf(message, "%s%s%s", OPT__LONG, FILTER_LONG, "=islower") == EOF){
    return -1;
  }
  if(strcmp(message, s) == 0){
    opt->filter = true;
    opt->is_class = islower;
    return 1;
  }
  message[0] = '\0';
  if(sprintf(message, "%s%s%s", OPT__LONG, FILTER_LONG, "=isprint") == EOF){
    return -1;
  }
  if(strcmp(message, s) == 0){
    opt->filter = true;
    opt->is_class = isprint;
    return 1;
  }
  message[0] = '\0';
  if(sprintf(message, "%s%s%s", OPT__LONG, FILTER_LONG, "=ispunct") == EOF){
    return -1;
  }
  if(strcmp(message, s) == 0){
    opt->filter = true;
    opt->is_class = ispunct;
    return 1;
  }
  message[0] = '\0';
  if(sprintf(message, "%s%s%s", OPT__LONG, FILTER_LONG, "=isspace") == EOF){
    return -1;
  }
  if(strcmp(message, s) == 0){
    opt->filter = true;
    opt->is_class = isspace;
    return 1;
  }
  message[0] = '\0';
  if(sprintf(message, "%s%s%s", OPT__LONG, FILTER_LONG, "=isupper") == EOF){
    return -1;
  }
  if(strcmp(message, s) == 0){
    opt->filter = true;
    opt->is_class = isupper;
    return 1;
  }
  message[0] = '\0';
  if(sprintf(message, "%s%s%s", OPT__LONG, FILTER_LONG, "=isxdigit") == EOF){
    return -1;
  }
  if(strcmp(message, s) == 0){
    opt->filter = true;
    opt->is_class = isxdigit;
    return 1;
  }
  message[0] = '\0';
  if(sprintf(message, "%s%s%s", OPT__LONG, SORT_LONG, "=standard") == EOF){
    return -1;
  }
  if(strcmp(message, s) == 0){
    opt->sort = true;
    return 1;
  }
  message[0] = '\0';
  if(sprintf(message, "%s%s%s", OPT__LONG, SORT_LONG, "=locale") == EOF){
    return -1;
  }
  if(strcmp(message, s) == 0){
    opt->sort = true;
    setlocale(LC_COLLATE, "");
    opt->compar = (int (*)(const void *, const void *))strcoll;
    return 1;
  }
  message[0] = '\0';
  if(sprintf(message, "%s%s", OPT__LONG, UPPERCASE_LONG) == EOF){
    return -1;
  }
  if(strcmp(message, s) == 0){
    opt->uppercase = true;
    return 1;
  }

  return 0;
}

// Crée et initialise une structure options 
options *opt_initialize(){
  options *opt = malloc(sizeof *opt);
  if(opt == NULL){
    return NULL;
  }
  opt->filter = false;
  opt->sort = false;
  opt->uppercase = false;
  holdall *h = holdall_empty();
  if(h == NULL){
    return NULL;
  }
  opt->compar = (int (*)(const void *, const void *))strcmp; 
  opt->file_names = h;
  return opt;
}

void dispose_opt(options *opt){
  holdall_dispose(&opt->file_names);
  free(opt);
}

void put(const void *ref) {
  printf("%s", (char *) ref);
}

int main(int argc, char **argv) {
  options *opt = opt_initialize();
  int r = EXIT_SUCCESS;
  if(opt == NULL){
    return EXIT_FAILURE;
  }
  if(argc < 2){
    dispose_opt(opt);
    goto error_use;
  }
  if(strcmp(argv[1], "--help") == 0){
    dispose_opt(opt);
    help();
    return EXIT_SUCCESS;
  }
  int c = 0;
  for(size_t i = 1; i < (size_t)argc; i++){
    if(strstr(argv[i], OPT__LONG) != NULL){
      if( (c = test_long_opt(argv[i], opt)) == 1){
      }else if(c == -1){
        goto error_sprintf;
      }else if(c == 0){
        dispose_opt(opt);
        goto error_use;
      }
    }
    else if(strstr(argv[i], OPT__SHORT) != NULL){
      if(test_short_uppercase(argv[i], opt)){
      }
      else if(i + 1 < (size_t)argc){
        if( (c = test_short_opt(argv[i + 1], opt)) == 1){
        }else if(c == 0){
          dispose_opt(opt);
          goto error_use;
        }
      }
    }else if(strstr(argv[i], IS_FILE) != NULL){
      for(size_t j = i; j < (size_t)argc; j++){
        if(holdall_add(opt->file_names, argv[j]) != 0){
          goto error_alloc_aux;
        }
      }
      break;
    }
  }



  
  size_t TAB_SIZE = 2;
  size_t count = 0;
  size_t k = 1;
  bst *b = bst_empty((int (*)(const void *, const void *))opt->compar);
  if (b == NULL) {
    goto error_alloc_aux;
  }
  for (size_t i = 0; i < holdall_count(opt->file_names); i++) {
    char *s = (char *)holdall_search_index(opt->file_names, i);
    if(s == NULL){
      r = EXIT_FAILURE;
      if(i >= 1){
        goto dispose_multiple_file;
      }
      goto dispose_one_file;
      
    }
    FILE *src = fopen(s, "r");
    if (src == NULL) {
      fprintf(stderr, "Illegal number of parameters or unrecognized option.\n");
      fprintf(stderr, "Try '%s %s'.\n", argv[0], OPT_HELP_L);
      r = EXIT_FAILURE;
      if(i >= 1){
        goto dispose_multiple_file;
      }
      goto dispose_one_file;
      
    }
    int c;
    while ((c = fgetc(src)) != EOF) {
      size_t *compteur = malloc(sizeof *compteur);
      if (compteur == NULL) {
        r = EXIT_FAILURE;
        if(i >= 1){
          goto dispose_multiple_file;
        }
        goto dispose_one_file;
        
      }
      *compteur = k;
      TAB_SIZE = 2;
      count = 0;
      char *t = malloc((sizeof *t) * TAB_SIZE);
      if (t == NULL) {
        r = EXIT_FAILURE;
        if(i >= 1){
          goto dispose_multiple_file;
        }
        goto dispose_one_file;
        
      }
      if (fseek(src, -1, SEEK_CUR) != 0) {
        r = EXIT_FAILURE;
        fprintf(stderr, "*** Error: A read error occurs\n");
        if(i >= 1){
          goto dispose_multiple_file;
        }
        goto dispose_one_file;
      }
      bool filtered;
      while ((c = fgetc(src)) != '\n' && c != EOF) {
        filtered = true;
        if(opt->filter && !opt->is_class(c)){
          filtered = false;
        }
        if(count + 1 >= TAB_SIZE && filtered) {
          TAB_SIZE *= 2;
          char *s = realloc(t, TAB_SIZE * (sizeof *s));
          if (s == NULL) {
            r = EXIT_FAILURE;
            if(i >= 1){
              goto dispose_multiple_file;
            }
            goto dispose_one_file;
            
          }
          t = s;
        }

        if(filtered){
          if(opt->uppercase){
            t[count] = (char)toupper(c);
          }else{
            t[count] = (char) c;
          }
          ++count;
        }
      }
      /*char *l = realloc(t, (count + 1) * (sizeof *l));
      if (l == NULL) {
        r = EXIT_FAILURE;
        if(i >= 1){
          goto dispose_multiple_file;
        }
          goto dispose_one_file;
      }
      t = l;*/
      t[count] = '\0';
      int m;
      if (holdall_count(opt->file_names) == 1) {
        if((m = bst_add_endofpath_one_file(b, t, compteur)) == -1){ // Tester le cas où ça renvoie NULL
          free(t);
          fprintf(stderr, "*** Error: Not enough memory\n");
          goto dispose_one_file;
        }else if(m == 0){
          free(t);
        }
      } else {
        if((m = bst_add_endofpath_multiple_file(b, t, i, holdall_count(opt->file_names))) == -1){
          free(t);
          free(compteur);
          fprintf(stderr, "*** Error: Not enough memory\n");
          goto dispose_multiple_file;
        }else if(m == 0){
          free(t);
        }
        free(compteur);
      }
      ++k;
    }
    if (!feof(src)) {
      r = EXIT_FAILURE;
      fprintf(stderr, "*** Error: A read error occurs\n");
      if(i >= 1){
          goto dispose_multiple_file;
      }
      goto dispose_one_file;
    }
    if (fclose(src) != 0) {
      r = EXIT_FAILURE;
      fprintf(stderr, "*** Error: A read error occurs\n");
      if(i >= 1){
        goto dispose_multiple_file;
      }
      goto dispose_one_file;
    }
  }
  if (holdall_count(opt->file_names) == 1) {
    char *s;
    s = holdall_search_index(opt->file_names, 0);
    printf("\n%s\n", s);
    bst_repr_graphic_one_file(b);
    goto dispose_one_file;
  }else{
    printf("\n");
    for(size_t i = 0; i < holdall_count(opt->file_names); i++){
      char *s = holdall_search_index(opt->file_names, i);
      printf("%s\t", s);
    }
    printf("\n");
    bst_repr_graphic_multiple_file(b, holdall_count(opt->file_names));
    goto dispose_multiple_file;
  }

error_sprintf:
  fprintf(stderr, "*** Error: Error with sprintf function\n");
  dispose_opt(opt);
  return EXIT_FAILURE;

error_alloc_aux:
  fprintf(stderr, "*** Error: Not enough memory\n");
  dispose_opt(opt);
  return EXIT_FAILURE;

error_use:
  fprintf(stderr, "Illegal number of parameters or unrecognized option.\n");
  fprintf(stderr, "Try '%s %s'.\n", argv[0], OPT_HELP_L);
  return EXIT_FAILURE;

dispose_one_file:

  dispose_opt(opt);
  //fprintf(stderr, "\noui\n");
  bst_dispose_ref(&b);
  bst_dispose_one_file(&b);
  return r;

dispose_multiple_file:
  dispose_opt(opt);
  bst_dispose_ref(&b);
  bst_dispose_multiple_files(&b);
  return r;
}
