
// Name: Quynh Dinh
// ID: 991486726
// Assignment1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void encipher(char message[], char key[]);
void decipher(char ecrypted[], char key[]);

int main() {
	
	char message[100];
	char key[100];
	int i = 0;
	int time = 0;
	int isAlphaMessage;
	int isAlphaKey;
	
	/* Ask user to enter message and keyword */
	do {
		printf("Enter a message and keyword (letter values only): ");
		scanf("%s", message);
		scanf("%s", key);
		
		/* 
		 *	Check each entered character in message and keyword 
		 *	If the character is non-alpha, set isAlphaMessage or isAlphaKey = 0
		 *	And print the error for the user
		 *	Then leave the current for loop instantly
		 *	Else set isAlphaMessage or isAlphaKey = 1 then move to next character
		*/
		for(i = 0; i < strlen(message); i++){
			if(isalpha(message[i])==0) {
				isAlphaMessage = 0;
				printf("You have entered non-alpha character(s) in message!\n");
				break;
			} else {
				isAlphaMessage = 1;
			}
		}
		
		for(i = 0; i < strlen(key); i++){
			if(isalpha(key[i])==0) {
				isAlphaKey = 0;
				printf("You have entered non-alpha character(s) in keyword!\n");
				break;
			} else {
				isAlphaKey = 1;
			}
		}
		
		/*	
		 *	Check if the program already ask user to input one more time 
  		 *	and user still enters non-alpha character(s)
  		 *	in message or key
  		 *	Exit the program
		 */
		if(time > 0 && (isAlphaMessage==0 || isAlphaKey==0)) {
			printf("Exit program!");
			exit(0);
		}		
		time++;
		
	} while(isAlphaMessage==0 || isAlphaKey==0);
	
	/* Convert all characters in message to lowercase */
	for(i = 0; i < strlen(message); i++){
		message[i] = tolower(message[i]); 
	}
	
	/* Convert all characters in keyword to lowercase */
	for(i = 0; i < strlen(key); i++){
		key[i] = tolower(key[i]); 
	}
	
	/* Call encipher function to encrypt the message */
	encipher(message, key);
	
	return 0;
}

/* encipher function to encipher the message based on the key */
void encipher(char message[], char key[]) {
	
	printf("\n***** Encipher *****\n");
	printf("Message: %s\n", message);
	printf("Key: %s\n", key);
	
	/* Declare counters */
	int i = 0;
	int j = 0;
	
	/* 
	 *	Create new key string that has length = message length 
	*/
	char newKey[strlen(message)];
	for(i = 0; i < strlen(message); i++){
		
		/*	
		 *	If the counter j = length of key
		 *	Reuse letters in key
	 	 */
		if(i == strlen(key)) {
			j = 0;
		}
		newKey[i] = key[j];
		j++;
	}
	newKey[strlen(message)] = '\0';
	
	/* Calculate shifting integers */
	int shifting[strlen(newKey)];
	for(i = 0; i < strlen(newKey); i++) {
		shifting[i] = newKey[i] - 'a';
	}
	
	/* Encrypt the message based on the formula */
	for(i = 0; i < strlen(message); i++){
		int represent = message[i] - 'a';
		int intChar = (represent + shifting[i]) % 26;
		message[i] = intChar + 'a';
	}
	
	printf("Encrypted Message: %s\n", message);
	
	/* Call decipher to decrypt the encrypted message*/
	decipher(message, key);
}

/* decipher function to decrypt the encrypted message based on the key */
void decipher(char encrypted[], char key[]){
	
	printf("\n***** Decipher *****\n");
	printf("Encrypted Message: %s\n", encrypted);
	printf("Key: %s\n", key);
	
	/* Declare counters */
	int i = 0;
	int j = 0;
	
	/* 
	 *	Create new key string that has length = encrypted message length 
	*/
	char newKey[strlen(encrypted)];
	for(i = 0; i < strlen(encrypted); i++){
		
		/*	
		 *	If the counter j = length of key
		 *	Reuse letters in key
	 	 */
		if(i == strlen(key)) {
			j = 0;
		}
		newKey[i] = key[j];
		j++;
	}
	newKey[strlen(encrypted)] = '\0';
	
	/* Calculate shifting integers */
	int shifting[strlen(newKey)];
	for(i = 0; i < strlen(newKey); i++) {
		shifting[i] = newKey[i] - 'a';
	}
	
	/* Decrypt the message based on the formula */
	for(i = 0; i < strlen(encrypted); i++){
		int represent = encrypted[i] - 'a';
		int intChar = (represent - shifting[i]) % 26;
		if(intChar < 0) {
			intChar += 26;
		}
		encrypted[i] = intChar + 'a';
	}
	
	printf("Message: %s\n", encrypted);
}

