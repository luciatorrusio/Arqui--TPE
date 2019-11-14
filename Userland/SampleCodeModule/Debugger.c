#include "../Include/Debugger.h"
#include "../Include/String.h"



bool assertEqual(void * val1, void * val2){

    if(val1 == val2){
        char temp[100];
        char temp2 [20];

        append("Values EQUAL:  ",temp,100);
        IntToString(temp2,20,(uint64_t)val1);
        
        append(temp2,temp,100);
        
        for(int i = 0 ; i < 20 ;i++)
            temp2[i] = 0;
        
        IntToString(temp2,20,(uint64_t)val2);

        append(" == ",temp,100);

        append(temp2,temp,100);

       // formatString(temp,75,"Values %d == %d",val1,val2);
        ThrowCustomException(temp);
    }

    return val1 == val2;
}

bool assertNotEqual(void * val1, void * val2){

        if(val1 != val2){
        char temp[100];
        char temp2 [20];

        append("Values NOT EQUAL:  ",temp,75);
        IntToString(temp2,20,(uint64_t)val1);
        
        append(temp2,temp,100);
        
        for(int i = 0 ; i < 20 ;i++)
            temp2[i] = 0;
        
        IntToString(temp2,20,(uint64_t)val2);

        append(" != ",temp,100);

        append(temp2,temp,100);

       // formatString(temp,75,"Values %d == %d",val1,val2);
        ThrowCustomException(temp);
    }

    return val1 != val2;

}