#include "../Include/String.h"
#include <stdbool.h>

int strlen(char * str){
    int i = 0;
    while(str[i]!=0)
        i++;
    return i;
}


void IntToString(char * buffer, int buffSize, uint64_t num){

    for(int i = 0 ; i < buffSize ; i++)
		buffer[i] = 0;

    int temp = num>0 ?num:-num;
	int i = 0;

	while(temp!= 0 && i < buffSize-1){

		int stVal = temp;
		int numToSave = temp - 10*(stVal/10);
		buffer[i++] = '0' + numToSave;
		temp = temp/10;
	}
    i--;

	for(int a = 0 ; a <= i/2 ; a++){
		char temp = buffer[a];
		buffer[a] = buffer[i-a];
		buffer[i-a] = temp;
	}

	if(num <0){
		for(int j = strlen(buffer)-2; j >=0; j--){
			buffer[j+1] = buffer[j];
		}
		buffer[0]='-';
	}
}


void HexToString(char * buffer, int buffSize, uint64_t num){



    for(int i = 0 ; i < buffSize ; i++)
		buffer[i] = '0';

	buffer[buffSize-1]= 0;

    uint64_t temp = num;
	int i = 0;

	while(temp!= 0 && i < buffSize){

		uint64_t stVal = temp;
		uint64_t numToSave = temp - 16*(stVal/16);

		if(numToSave <10 ){
			buffer[i++] = '0' + numToSave;
		}
		else{
			buffer[i++] = 'A' + numToSave-10;
		}
		
		temp = temp/16;
	}
    i = buffSize-2;

	for(int a = 0 ; a <= (buffSize-2)/2 ; a++){
		char temp = buffer[a];
		buffer[a] = buffer[i-a];
		buffer[i-a] = temp;
	}


	
}

void append(char * src, char * dest, unsigned size){
	int base = strlen(dest);

	for(int i = 0 ; i < size && src[i] != 0 ; i++){
		dest[base + i] = src[i];
	}

}

void preppend(char * src, char * dest, unsigned size){
	int srcLenght = strlen(src);
	int destLenght = strlen(dest);

	for(int i = destLenght ; i >=0  ; i--){
		dest[i + srcLenght ] = dest[i];
	}

	for(int i = 0 ; i < srcLenght-1 ; i++)
		dest[i] = src[i];

}

void removeFirstOccurrence(char * str, char ch){

	bool found = false;

	for(int i = 0 ; i < strlen(str); i++){
		
	}

}

void removeLastOccurrence(char * str, char ch){

}

void removeAllOcurrences(char * str, char ch){

}

