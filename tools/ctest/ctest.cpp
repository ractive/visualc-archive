// ctest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>


int str_repl ( char *str, char *str_mod, const char *str_1, const char *str_2) {
	int match;
	unsigned int i, j, k, l;
	i = 0;
	j = 0;
	k = 0;
	l = 0; 
	match = 0;


	while ( i <= strlen (str) ) {
		if ( str[i] == str_1[k] ) {
			if ( strlen(str_1) == k + 1 ) {
				match++;
				for ( l = 0; l < strlen(str_2); l++  ) {
					str_mod[j] = str_2[l];
					j++;
				}
				k = 0;
			}
			else {
				k++;
			}
		}
		else {
			k = 0;
			str_mod[j] = str[i];
			j++;
		}
		i++;
	}
	return match;
}

int str_repl2 ( char *str, char *str_mod, const char *str_1, const char *str_2) {
	
	char * str_pos = str;
	char * str_old_pos = str;
	int len_1 = strlen(str_1);
	int len_2 = strlen(str_2);
	int match = 0;

	// See if str contains str_1 as a substring
	while(str_pos = strstr(str, str_1)) {
		match++;
		// Append the part until the substring to the new string
		strncat(str_mod, str, str_pos - str_old_pos);
		// Append the replacement string
		strncat(str_mod, str_2, len_2);
		// Advance the str-pointer
		str += str_pos - str_old_pos;
		str += len_1;
		// Keep the current position to calculate the remaining string
		str_old_pos = str;
	}

	// Append the rest of the string
	strncat(str_mod, str, str_pos - str_old_pos);

	return match;
}

void str_repl3 ( char *str, char *str_mod, const char *str_1, const char *str_2, int &match) {

	char * str_pos = str;
	char * str_old_pos = str;
	int len_1 = strlen(str_1);
	int len_2 = strlen(str_2);

	// See if str contains str_1 as a substring
	if (str_pos = strstr(str, str_1)) {
		match++;
		// Append the part until the substring to the new string
		strncat(str_mod, str, str_pos - str_old_pos);
		// Append the replacement string
		strncat(str_mod, str_2, len_2);
		// Advance the str-pointer
		str += str_pos - str_old_pos;
		str += len_1;
		// Keep the current position to calculate the remaining string
		str_old_pos = str;

		str_repl3 (str, str_mod, str_1, str_2, match);
	}
	else {
		// Append the rest of the string
		strncat(str_mod, str, str_pos - str_old_pos);
	}
}

int main(int argc, char* argv[])
{
	char str_1[32] = "xxx";
	char str_2[32] = "yyyy";
	char str_mod[32] = "";
	char str[32] = "_abc_xxx_xx_def_";

	int m = 0;

	m = str_repl(str, str_mod, str_1, str_2);
	printf("m = %d\r\nstr: %s\r\nstr_mod: %s\r\nstr_1: %s\r\nstr_2 = %s\r\n\r\n", m, str, str_mod, str_1, str_2);

	str_mod[0] = '\0';
	m = str_repl2(str, str_mod, str_1, str_2);
	printf("m = %d\r\nstr: %s\r\nstr_mod: %s\r\nstr_1: %s\r\nstr_2 = %s\r\n\r\n", m, str, str_mod, str_1, str_2);

	str_mod[0] = '\0';
	str_repl3(str, str_mod, str_1, str_2, m);
	printf("m = %d\r\nstr: %s\r\nstr_mod: %s\r\nstr_1: %s\r\nstr_2 = %s\r\n\r\n", m, str, str_mod, str_1, str_2);


	return 0;
}

