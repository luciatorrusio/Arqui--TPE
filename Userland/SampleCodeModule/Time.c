#include "../Include/Time.h"

extern int __GetTime__(int code);


int GetSeconds(){
    int ss1 = __GetTime__(0)/16;
    int ss2 = __GetTime__(0) - ss1*16;
    return ss1*10 + ss2;
}

int GetMinutes(){
    int mm1 = __GetTime__(2)/16;
    int mm2 = __GetTime__(2) - mm1*16;
    return mm1*10 + mm2;
}

int GetHours(){
    int hh1 = __GetTime__(4)/16;
    int hh2 = __GetTime__(4) - hh1*16;
    return hh1*10 + hh2;
}

int GetDayOfWeek(){
    return __GetTime__(6)/16;
}
int GetDayOfMonth(){
    int mm1 = __GetTime__(7)/16;
    int mm2 = __GetTime__(7) - mm1*16;
    return mm1*10 + mm2;
    }

int GetMonth(){
    int mm1 = __GetTime__(8)/16;
    int mm2 = __GetTime__(8) - mm1*16;
    return mm1*10 + mm2;
}

int GetYear(){
    int aa1 = __GetTime__(9);
    int aa2 = __GetTime__(9)/16 - aa1*16 ;
    return 2000 + aa1 * 10 + aa2;
}