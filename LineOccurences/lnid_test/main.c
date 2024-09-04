#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "bst.h"
#include "holdall.h"
#include "options.h"


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
  if(strcmp(argv[1], OPT_HELP_L) == 0){
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
        if(test_short_filter(argv[i])){
          if( (c = test_short_opt_filter(argv[i + 1], opt)) == 1){}
            else if(c == 0){
              dispose_opt(opt);
              goto error_use;
            }
        }else if(test_short_sort(argv[i])){
           if( (c = test_short_opt_sort(argv[i + 1], opt)) == 1){}
            else if(c == 0){
              dispose_opt(opt);
              goto error_use;
            }
        }else{
          dispose_opt(opt);
          goto error_use;
        }
      }
    }else if(strstr(argv[i], IS_FILE) != NULL){
        for(size_t j = i; j < (size_t)argc; j++){
          if(holdall_add(opt_file_names(opt), argv[j]) != 0){
            goto error_alloc_aux;
          }
        }
        break;
    }
  }



  
  size_t TAB_SIZE = 2;
  size_t count = 0;
  size_t k = 1;
  bst *b = bst_empty((int (*)(const void *, const void *))opt_compar_fun(opt));
  if (b == NULL) {
    goto error_alloc_aux;
  }
  for (size_t i = 0; i < holdall_count(opt_file_names(opt)); i++) {
    char *s = (char *)holdall_search_index(opt_file_names(opt), i);
    if(s == NULL){
      r = EXIT_FAILURE;
      if(i >= 1){
        goto dispose_multiple_file;
      }
      goto dispose_one_file;
      
    }
    bool same_file = false;
    for(size_t n = 0; n < i; n++){
      if (strcmp(s ,(char *)holdall_search_index(opt_file_names(opt),n)) == 0){
        bst_add_endofpath_same_file(b, i, n);
        same_file = true;
      }
    }

    if(!same_file){
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
          if(opt_filter(opt) && !opt_class(opt, c)){
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
            if(opt_uppercase(opt)){
              t[count] = (char)toupper(c);
            }else{
              t[count] = (char) c;
            }
            ++count;
          }
        }
        t[count] = '\0';
        int m;
        if (holdall_count(opt_file_names(opt)) == 1) {
          if((m = bst_add_endofpath_one_file(b, t, compteur)) == -1){ 
            free(t);
            fprintf(stderr, "*** Error: Not enough memory\n");
            goto dispose_one_file;
          }else if(m == 0){
            free(t);
          }
        } else {
          if((m = bst_add_endofpath_multiple_file(b, t, i, holdall_count(opt_file_names(opt)))) == -1){
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
    
  }
  if (holdall_count(opt_file_names(opt)) == 1) {
    char *s;
    s = holdall_search_index(opt_file_names(opt), 0);
    printf("\n%s\n", s);
    bst_display_one_file(b);
    goto dispose_one_file;
  }else{
    printf("\n");
    for(size_t i = 0; i < holdall_count(opt_file_names(opt)); i++){
      char *s = holdall_search_index(opt_file_names(opt), i);
      printf("%s\t", s);
    }
    printf("\n");
    bst_display_multiple_file(b, holdall_count(opt_file_names(opt)));
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
  bst_dispose_one_file(&b);
  return r;

dispose_multiple_file:
  dispose_opt(opt);
  bst_dispose_multiple_files(&b);
  return r;
}
