#include "SpeakerDriver.h"
#include <stdint.h>
#include <timer.h>

/**********************************************************************
*                           funciones ASM                             *
***********************************************************************/

extern void WritePITConfiguration(uint8_t val);
extern void WritePIT2Data(uint8_t val);
extern uint8_t ReadSpeakerData();
extern void WriteSpeakerData(uint8_t val);

/**********************************************************************
*                           Declaraciones                             *
***********************************************************************/

static void startSound(uint32_t nFrequence);
static void stopSound();


/**********************************************************************
*                      funciones Publicas                             *
***********************************************************************/

void playSound(int tickDuration){

    startSound(1000);
    uint64_t startTick = ticks_elapsed();

    //Bloqueo a thread hasta que pase tanto tiempo
    while (ticks_elapsed()-startTick != tickDuration );
    
    stopSound();


}

void beep(){

    startSound(1000);

	// CANTIDAD MINIMA DE TIEMPO QUE SE PUEDE PONER. NO CAMBIAR!
	// Lo hago de esta forma y no con ticks por que esta funcion va a ser llamada 
	// desde userspace con una syscall, entonces se van a bloquear las interrupciones nuevas del
	// timer.
	for(int i = 0; i < 9999999; i++);
    
    stopSound();
}



/**********************************************************************
*                      funciones Privadas                             *
***********************************************************************/

static void startSound(uint32_t nFrequence) {
 	uint32_t Div;
 	uint8_t tmp;
 
 	Div = 1193180 / nFrequence;
 	WritePITConfiguration(0xb6);
 	WritePIT2Data((uint8_t) (Div) );
 	WritePIT2Data((uint8_t) (Div >> 8));
 
 	tmp = ReadSpeakerData();
  	if (tmp != (tmp | 3)) {
 		WriteSpeakerData( tmp | 3);
 	}
 }
 
 static void stopSound() {
 	uint8_t tmp = ReadSpeakerData() & 0xFC;
 	WriteSpeakerData(tmp);
 }
 
