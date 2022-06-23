// test.c
// Author: Gabriel D. Azevedo
// Date:   2022-06-23

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <argumentar.h>

void set_input(char*);
void set_output(char*);
void set_flag(int);

arg_opt args[] = {
  { 0, "-i", "--input",  NULL, "Set input value",  &set_input,  NULL },
  { 0, "-o", "--output", NULL, "Set output value", &set_output, NULL },
  { 1, "-f", "--flag",   0,    "Set flag to true", NULL,        &set_flag }
};

char* INPUT_VALUE;
char* OUTPUT_VALUE;
int   FLAG_VALUE = 0;

void print_usage(char* prog_name, int optc, arg_opt* args)
{
  printf("USAGE: %s [OPTION...]\n\n", prog_name);
  for (int i = 0; i < optc; i++) {
    printf("\t%s, %s,\t\t%s\n", args[i].key_name, args[i].full_name, args[i].description);
  }
}

void print_results()
{
  char* flag_label = FLAG_VALUE ? "true" : "false";
  printf("Results:\n\nInput:\t%s\nOutput:\t%s\nFlag:\t%s\n", INPUT_VALUE, OUTPUT_VALUE, flag_label);
}

int main(int argc, char** argv)
{
  if (argc < 2) {
    print_usage(argv[0], 3, args);
    return 1;
  }
  
  parse_arguments(argc, argv, 3, args);

  print_results();
  return 0;
}

void set_input(char* value)
{
  size_t size = strlen((const char*) value);
  INPUT_VALUE = (char*) malloc(size);
  strcpy(INPUT_VALUE, value);
}

void set_output(char* value)
{
  size_t size = strlen((const char*) value);
  OUTPUT_VALUE = (char*) malloc(size);
  strcpy(OUTPUT_VALUE, value);
}

void set_flag(int value)
{
  FLAG_VALUE = value;
}
