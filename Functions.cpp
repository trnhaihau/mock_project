#include "Functions.h"

arr_string create_arr_string(int size) {
	arr_string arr_str;
	arr_str.arr = (char**)calloc(size, sizeof(char*));
	arr_str.size = size;
	if (NULL != arr_str.arr) {
		return arr_str;
	}
	else;
}
bool check_attacker(arr_string LogInHistory, int m, int n) { 
	/*
	* check_attacker() function checks if the user is attacker or not 
	* Description:
	* Step 1: Using union to separate the time unit by unit 
	* Step 2: Calculating the difference of time in seconds by using 2 nested for loops
	*		  Using static variable static_count to count the number of times this user accesses the server
	* Step 3: If the log-in history has met the condition: within maximum_time, access the server >= n times: return true 
	*		  Else, when the loops are over, it means the condition haven't been met: return false	
	*/
	int maximum_time = m * SECOND;
	static int static_count;
	static_count = 1;
	if (n == 1) return true;
	else {
		for (int i = 0; i < LogInHistory.size - 1; i++) {
			for (int j = i + 1; j < LogInHistory.size; j++) {
				History* h_i = USER_LOGIN_TIME(i);
				History* h_j = USER_LOGIN_TIME(j); 
				char temp[TIME_UNIT_DIGITS] = { 0 }; 
				memcpy(temp, h_i->UnitsofTime.date, TIME_UNIT_DIGITS); 
				int date_i = atoi(temp);
				memcpy(temp, h_i->UnitsofTime.hour, TIME_UNIT_DIGITS); 
				int hour_i = atoi(temp); 
				memcpy(temp, h_i->UnitsofTime.minute, TIME_UNIT_DIGITS); 
				int minute_i = atoi(temp); 
				memcpy(temp, h_i->UnitsofTime.second, TIME_UNIT_DIGITS); 
				int second_i = atoi(temp); 

				memcpy(temp, h_j->UnitsofTime.date, TIME_UNIT_DIGITS); 
				int date_j = atoi(temp);
				memcpy(temp, h_j->UnitsofTime.hour, TIME_UNIT_DIGITS); 
				int hour_j = atoi(temp);
				memcpy(temp, h_j->UnitsofTime.minute, TIME_UNIT_DIGITS);
				int minute_j = atoi(temp);
				memcpy(temp, h_j->UnitsofTime.second, TIME_UNIT_DIGITS);
				int second_j = atoi(temp);
				//calculate the difference of time between 2 accesses
				if (second_i > second_j)
				{
					second_j += SECOND;
					--minute_j;
				}

				if (minute_i > minute_j)
				{
					minute_j += MINUTE;
					--hour_j;
				}
				if (hour_i > hour_j)
				{
					hour_j += HOUR;
					--date_j;
				}
				int diferrence_of_time = (date_j - date_i) * HOUR * MINUTE * SECOND + (hour_j - hour_i) * MINUTE * SECOND + (minute_j - minute_i) * SECOND + second_j - second_i;

				if (diferrence_of_time > maximum_time) {
					break;
				}
				else {
					static_count++;
					if (static_count >= n) {
						return true;
					}
					else;
				}
			}
		}
	}
	return false;
}
bool is_user_an_attacker(arr_string accessList, int accessList_index, int m, int n) {
	/*
	* is_user_an_attacker() function scan the log-in history and call check_attacker() to check if the user is in accessList.arr is attacker or not
	* Description:
	* Step 1: Creating an arr_string to store log-in history of one user
	* Step 2: Sorting the LogInHistory.arr array from lowest to highest
	* Step 3: Checking whether this user is attacker or not by using check_attacker()
	*		if check_attacker() return true : AN ATTACKER -> return true
	*		if check_attacker() return false: NOT AN ATTACKER -> return false
	*/
	arr_string LogInHistory = create_arr_string(accessList.size);
	if (LogInHistory.arr != NULL) {
		History* h_i = ACCESS_HISTORY(accessList_index);
		Name* n_i = ACCESS_USERNAME(accessList_index);
		LogInHistory.arr[0] = (char*)(h_i->time); //storing the 1st log-in histpry of the user
		int LogInHistory_index = 1; 
		for (int j = accessList_index + 1; j < accessList.size; j++) {
			History* h_j = ACCESS_HISTORY(j); 
			Name* n_j = ACCESS_USERNAME(j);
			/*
			* If condition checks whether the next username is the same with the current user
			* if valid: store the log-in history in LogInHistory.arr
			*/
			if (strcmp((char*)n_i->name, (char*)n_j->name) == 0) {				
				LogInHistory.arr[LogInHistory_index] = (char*)(h_j->time);
				LogInHistory_index++;
			}
		}
		LogInHistory.size = LogInHistory_index--;
		sort_arr_string(LogInHistory);
		/*
			* If condition checks whether the curent user is an attacker
			* if valid: return true
			* if not valid: return false
		*/
		if (check_attacker(LogInHistory, m, n)) {
			free(LogInHistory.arr);
			return true;
		} 
		else {
			free(LogInHistory.arr);
			return false;
		}
	}
}
bool is_element_in_array(arr_string accessList, arr_string expected, int i) {
	/*
	* is_element_in_array() function, checks if ith-element in accessList.arr was in expected.arr or not
	* Description:
	* Step 1: Using for loop to visit each element of expected.arr 
	*		if expected.arr = NULL, it means there's no element in expected.arr, return: false
	* Step 2: Checking by using strcmp() to compare i-th element in accessList.arr with j-th element in expected.arr
	*		if they are the same : return true (ith-element in accessList.arr was in expected.arr)
	*		if they are different: move the next j-th element
	* Step 3: when the loop is over, it means that i-th element in accessList.arr doesn't match with any j-th elements in expected.arr
	*		return: false
	*/
	for (int j = 0; j < expected.size; j++) {
		Name* access_user = ACCESS_USERNAME(i);
		Name* attack_user = ATTACK_USERNAME(j);
		if (attack_user == NULL) {
			return false;
		}
		else {
			if (strcmp(access_user->name, attack_user->name) == 0) {
				return true;
			}
			else continue;
		}
	}
	return false;

}
void sort_arr_string(arr_string arr_string) {
	//sort_arr_string() function, rearranges the given array of char* from lowest to highest based on selection sort
	for (int i = 0; i < (arr_string.size - 1); i++) {
		if (arr_string.arr[i] != NULL) {
			for (int j = i + 1; j < arr_string.size; j++) {
				if (arr_string.arr[j] != NULL) {
					if (strcmp(arr_string.arr[i], arr_string.arr[j]) > 0) {
						char** p1 = &arr_string.arr[i];
						char** p2 = &arr_string.arr[j];
						char* temp = *p1;
						*p1 = *p2;
						*p2 = temp;
					}
				}
			}
		}
	}
}