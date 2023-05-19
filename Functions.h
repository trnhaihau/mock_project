#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <corecrt.h>

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_


#define SECOND 60
#define MINUTE 60
#define HOUR 24
#define	ACCESS_USERNAME(X) (Name*)&accessList.arr[X][13]
#define ACCESS_HISTORY(X) (History*)&accessList.arr[X][0]
#define	ATTACK_USERNAME(X) (Name*)&expected.arr[X][0]
#define USER_LOGIN_TIME(X) (History*)&LogInHistory.arr[X][0]
#define TIME_DIGITS 12
#define TIME_UNIT_DIGITS 2
#define NAME_CHARACTERS 10


typedef struct arr_string {
	char** arr;
	int size;
} arr_string; 

typedef union {
	char time[TIME_DIGITS]; //yyMMddhhmmss
	struct {
		char year[TIME_UNIT_DIGITS];
		char month[TIME_UNIT_DIGITS];
		char date[TIME_UNIT_DIGITS];
		char hour[TIME_UNIT_DIGITS];
		char minute[TIME_UNIT_DIGITS];
		char second[TIME_UNIT_DIGITS];
	} UnitsofTime;
} History;

typedef struct {
	char name[NAME_CHARACTERS];
}Name;

arr_string create_arr_string(int size);
bool check_attacker(arr_string LogInHistory, int m, int n);
bool is_user_an_attacker(arr_string accessList, int i, int m, int n);
bool is_element_in_array(arr_string accessList, arr_string expected, int i);
void sort_arr_string(arr_string arr);

#endif
