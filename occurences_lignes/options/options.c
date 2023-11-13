#include "options.h"



struct options{
  bool filter;
  int (*is_class)(int); // faire un pointeur de fonction
  bool sort;
  int (*compar)(const void *, const void *);
  bool uppercase;
  holdall *file_names;
};

bool opt_filter(options *opt){
  return opt->filter;
}

int opt_class(options *opt, int c){
  return opt->is_class(c);
}

bool opt_sort(options *opt){
  return opt->sort;
}

int (*opt_compar_fun(options *opt))(const void *, const void *) {
    return opt->compar;
}

int opt_compar(options *opt, const void *a, const void *b){
  return opt->compar(a, b);
}

bool opt_uppercase(options *opt){
  return opt->uppercase;
}

holdall *opt_file_names(options *opt){
  return opt->file_names;
}


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
  char message[30];
  if(sprintf(message, "%s%s", OPT__SHORT, UPPERCASE_SHORT) == EOF){
    return false;
  }
  if(strcmp(s, message) == 0){
    opt->uppercase = true;
    return true;
  }
  return false;
}

bool test_short_filter(char *s){
  char message[30];
  if(sprintf(message, "%s%s", OPT__SHORT, FILTER_SHORT) == EOF){
    return false;
  }
  return (strcmp(s, message) == 0);
}

bool test_short_sort(char *s){
  char message[30];
  if(sprintf(message, "%s%s", OPT__SHORT, SORT_SHORT) == EOF){
    return false;
  }
  return (strcmp(s, message) == 0);
}

int test_short_opt_filter(char *s, options *opt){
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
  return 0;
}

int test_short_opt_sort(char *s, options *opt){
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

