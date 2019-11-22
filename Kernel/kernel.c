#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <idtLoader.h>
#include <Curses.h>
#include <VideoDriver.h>
#include <font.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];

	// ncPrint("[x64BareBones]");
	// ncNewline();

	// ncPrint("CPU Vendor:");
	// ncPrint(cpuVendor(buffer));
	// ncNewline();

	// ncPrint("[Loading modules]");
	// ncNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	// ncPrint("[Done]");
	// ncNewline();
	// ncNewline();

	// ncPrint("[Initializing kernel's binary]");
	// ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	// ncPrint("  text: 0x");
	// ncPrintHex((uint64_t)&text);
	// ncNewline();
	// ncPrint("  rodata: 0x");
	// ncPrintHex((uint64_t)&rodata);
	// ncNewline();
	// ncPrint("  data: 0x");
	// ncPrintHex((uint64_t)&data);
	// ncNewline();
	// ncPrint("  bss: 0x");
	// ncPrintHex((uint64_t)&bss);
	// ncNewline();

	// ncPrint("[Done]");
	// ncNewline();
	// ncNewline();
	return getStackBase();
}

extern void WritePITConfiguration(uint8_t val);
extern void WritePIT2Data(uint8_t val);
extern uint8_t ReadSpeakerData();
extern void WriteSpeakerData(uint8_t val);


 static void play_sound(uint32_t nFrequence) {
 	uint32_t Div;
 	uint8_t tmp;
 
        //Set the PIT to the desired frequency
 	Div = 1193180 / nFrequence;
 	WritePITConfiguration(0xb6);
 	WritePIT2Data((uint8_t) (Div) );
 	WritePIT2Data((uint8_t) (Div >> 8));
 
        //And play the sound using the PC speaker
 	tmp = ReadSpeakerData();
  	if (tmp != (tmp | 3)) {
 		WriteSpeakerData( tmp | 3);
 	}
 }
 
 //make it shutup
 static void nosound() {
 	uint8_t tmp = ReadSpeakerData() & 0xFC;
 
 	WriteSpeakerData(tmp);
 }
 
 //Make a beep
 void beep() {
 	 play_sound(1000);
 	 
	for (int i = 99999999; i >0; i--)
	{
		/* code */
	}
	
	  

 	 nosound();
          //set_PIT_2(old_frequency);
 }

int main()
{	
	load_idt();
	startVideoDriver();
	initializeConsoleDriver(CHAR_HEIGHT,CHAR_WIDTH, SCREEN_HEIGHT,SCREEN_WIDTH);

	// play_sound(1000);
	// play_sound(2000);
	// play_sound(3000);
	// play_sound(4000);
	
	//((EntryPoint)sampleCodeModuleAddress)();


	return 0;
}
