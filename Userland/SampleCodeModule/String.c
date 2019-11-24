#include <stdarg.h>
#include <stdbool.h>
#include "../Include/String.h"
#include <stdarg.h>

int strlen(char * str){
    int i = 0;
    while(str[i]!=0)
        i++;
    return i;
}


void IntToString(char * buffer, int buffSize, uint64_t num){

	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = num % 10;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (num /= 10);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
}

int stringToInt(char * buff){
	int aux=0;
	for(int i=0;*(buff+i)!=0;i++){
		aux=aux*10+(*(buff+i)-'0');
	}
	return aux;
}

int power(int x,int y){
	if(y == 0)
		return 1;
	else
		return x * power(x,y-1);
}


void DoubleToString(char * buff, int buffSize, float num){
	IntToString(buff,buffSize, num);
	int start =strlen(buffSize);

	if(start + 1 < buffSize){
		buff[start++] = '.';

		int digits = (buffSize - (start+10) > 0) ? 10 : buffSize -start -1;


		int newNumber = ((float)(num - (int) num)) * power(10,digits);

		IntToString(start,buffSize - start, newNumber);
	}
}





// Taken from the base project
void HexToString(char * buffer, int buffSize, uint64_t num){

	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = num % 16;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (num /= 16);

	// Terminate string in buffer.
	*p = 0;

	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
	
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

int strcmp(char * s1,char * s2){
    int i;
    for(i=0;*(s1+i)!=0 && *(s2+i)!=0 && *(s1+i)==*(s2+i);i++);

    if(*(s1+i)==0 && *(s2+i)==0)
     return 1;
    return 0; 
}

void formatString(char * string, int size,char format,...){
	va_list args;
	va_start(args,format);
	snprintf(string,size,format,args);
	va_end(args);
}

void snprintf(char * string, int size, char * format, va_list args){
	int i=0,k=0;
	char c;
	while(((c=(*(format+i)))!=0)&& k<size){
		if(c=='%'){
			i++;
			handleFormat(*(format+i),&k,string,size,args);
		}
		else{
			*(string+k)=*(format+i);	
			k++;
		}
		i++;
	}
	*(string+k)=0;
}

void handleFormat(char type,int * k,char * string,int size,va_list args){
	switch(type){
		case 'c':{
			char aux=va_arg(args,int);
			*(string+(*k))=aux;
			break;
		}
		case 'd':
		case 'i':
		{	int aux1=va_arg(args,int);
			IntToString(string+(*k),size-1-(*k),aux1);
			break;}
		case 's':
			{char * aux2 =va_arg(args,char *);
			append(aux2,string+(*k),size-1-(*k));	
			break;}	
		case 'f':
		case 'F':{
			int aux3=va_arg(args,int);
			DoubleToString(string+(*k),size-1-(*k),aux3);
		}
		case 'x':
		case 'X':
		{	
			HexToString(string+(*k),size-1-(*k),va_arg(args,int));
			break;
		}
		default: 
			{	*(string+(*k))='%';
				*(string+(*k+1))=type;}
	}
			*k=strlen(string);	

}
