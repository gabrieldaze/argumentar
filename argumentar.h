// argumentar.h
// Author: Gabriel D. Azevedo
// Date:   2022-06-18

#ifndef LIB_ARGUMENTAR_H
#define LIB_ARGUMENTAR_H

#include <stdio.h>
#include <string.h>

/*
 * FLAG option sets if the argument is followed by a value or not
 * KEY_NAME option is the short name (EX: -i)
 * FULL_NAME option is the full name (EX: --input)
 * DEFAULT_VALUE option sets the default value for NON FLAG arguments
 * DESCRIPTION option sets the description for the argument
 * SET_VALUE(CHAR*) option sets the callback for setting the NON FLAG value
 * SET_FLAG(INT) option sets the callback for setting the FLAG value
 */
struct argument_option
{
  int   flag;
  char* key_name;
  char* full_name;
  char* default_value;
  char* description;
  void  (*set_value)(char*);
  void  (*set_flag)(int);
};

typedef struct argument_option arg_opt;

void reset_options(int optc, arg_opt* args)
{ 
  for (int i = 0; i < optc; i++) {

    if (args[i].flag) {

      /* Set the current option default FLAG value to 0 */
      if (args[i].set_flag != NULL)
	args[i].set_flag(0);
      
    } else {

      /* Set the current option default NON FLAG value to be equal DEFAULT VALUE */
      if (args[i].set_value != NULL && args[i].default_value != NULL)
	args[i].set_value(args[i].default_value);
      
    }
  }
}

void parse_arguments(int argc, char** argv, int optc, arg_opt* args)
{
  unsigned int index = 0;
  reset_options(optc, args);

  /* Iterate through the list of arguments */
  while (index < argc) {

    /* Iterate through the list of options */
    for (int i = 0; i < optc; i++) {

      char* arg_name = args[i].full_name;
      char* arg_key  = args[i].key_name;

      /* Check if the current argument matches the current option */
      if (strcmp(argv[index], arg_name) == 0 || strcmp(argv[index], arg_key) == 0) {

	/* Check if the current option is marked as a FLAG */
	if (args[i].flag) {

	  /* Set the current option FLAG value to 1 */
	  if (args[i].set_flag != NULL) args[i].set_flag(1);
	  
	} else {

	  if (args[i].set_value != NULL) {

	    if (index+1 < argc) {
	      
	      index++;
	      /* Set the current option NON FLAG value to equal the next argument */
	      if (args[i].set_value != NULL) args[i].set_value(argv[index]);
	      
	    }
	  } 
	}
      }
    }
    
    index++;
  }
}

#endif
