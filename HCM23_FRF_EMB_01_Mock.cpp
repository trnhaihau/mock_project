#include <stdio.h>
#include <stdlib.h>
#include "Functions.h"
extern void Test(arr_string(*pattackList)(arr_string, int, int));


/*
* attackList() function return a list of user(s) attacked the server.
* Description:
* Step 1: Creating an arr_string to store attacker's username
* Step 2: Using for loop to check element by element in the accessList.arr if this user is an attacker or not then storing the username if it's true
* Step 3: Sorting the array in ascending order
*/
arr_string attackList(arr_string accessList, int m, int n) {
	//create an arr_string expected to store ouput
	arr_string expected = create_arr_string(accessList.size);
	int expected_arr_index = 0;

	//use for loop to visit and check each element of accessList.arr
	for (int i = 0; i < accessList.size; i++) {
		expected.size = expected_arr_index;
		/*
		if condition is used to determine whether i - th element's username was in the output or not
				if valid: move to the next element((i + 1) - th element)
				if not valid: start checking element 
		*/
		if (is_element_in_array(accessList, expected, i)) {
			continue; 
		}
		else {
			/*
			if condition is used to determine whether i - th element's user is attacker or not 
				if valid: user is an ATTACKER, store the username in < expected.arr
				if not valid: is NOT AN ATTACKER
			*/
			if (is_user_an_attacker(accessList, i, m, n)) {
				Name* p = ACCESS_USERNAME(i);
				expected.arr[expected_arr_index] = (char*)p->name;
				expected_arr_index++;
			}
		} 
	}

	/*
	when the loop is over, if expected.size = 0, it means that there is NO ATTACKER (not any user name is stored)
				if valid: expected.arr = NULL
	*/
	if (expected.size == 0) {
		expected.arr = NULL;
		return expected;
	}
	sort_arr_string(expected);
	return expected;
}
int main()
{
	Test(attackList);
	
	return 0;
}
