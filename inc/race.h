#ifndef RACE_H
#define RACE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>

void mx_printchar(char c);
void mx_printint(int n);
void mx_printstr(const char*s);
int mx_atoi(const char *str);
bool mx_isdigit(int c);
bool mx_isspace(char c);
int mx_strlen(const char *s);
void mx_printerr(const char *s);
int mx_strcmp(const char *s1, const char *s2);

#endif
