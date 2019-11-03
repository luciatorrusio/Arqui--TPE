#include "../Include/String.h"


int strlen(char * str){
    int i = 0;
    while(str[i]!=0)
        i++;
    return i;
}

void IntToString(char * buffer, int buffSize, int num){

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

void HexToString(char * buffer, int buffSize, int num){
    for(int i = 0 ; i < buffSize ; i++)
		buffer[i] = 0;

	buffer[0]='0';
	buffer[1]='0';


    int temp = num;
	int i = 0;

	while(temp!= 0 && i < buffSize-3){

		int stVal = temp;
		int numToSave = temp - 16*(stVal/16);

		if(numToSave <10 ){
			buffer[i++] = '0' + numToSave;
		}
		else{
			buffer[i++] = 'A' + numToSave-10;
		}
		
		temp = temp/16;
	}
    i--;

	for(int a = 0 ; a <= i/2 ; a++){
		char temp = buffer[a];
		buffer[a] = buffer[i-a];
		buffer[i-a] = temp;
	}


	
}