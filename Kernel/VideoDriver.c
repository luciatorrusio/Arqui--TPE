#include <VideoDriver.h>
#include <stdint.h>
#include <font.h>

unsigned int SCREEN_bPP = 3;


struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;

	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;

	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__((packed));

struct vbe_mode_info_structure * screenData = (void*)0x5C00;

void init_VM_Driver() {
	SCREEN_bPP = screenData->bpp / 8;
	SCREEN_HEIGHT = screenData->height;
	SCREEN_WIDTH = screenData->width;
}

void drawPixel(unsigned int x, unsigned int y, int color)
{
    char * screen = screenData->framebuffer; 
    unsigned where = (x + y*SCREEN_WIDTH) * SCREEN_bPP;
    screen[where] = color & 255;              // BLUE
    screen[where + 1] = (color >> 8) & 255;   // GREEN
    screen[where + 2] = (color >> 16) & 255;  // RED
}



void startVideoDriver(){
    init_VM_Driver();
}




void drawChar(int x, int y, char character, int fontColor, int background){

	int aux_x = x;
	int aux_y = y;
	unsigned char * toDraw = charBitmap(character);

	char bitIsPresent ;

	for(int i = 0; i < CHAR_HEIGHT; i++){
		for(int j = 0 ; j < CHAR_WIDTH ; j++){
			bitIsPresent = (1<< (CHAR_WIDTH-j)) & toDraw[i];

			if(bitIsPresent)
				drawPixel(aux_x,aux_y,fontColor);
			else
				drawPixel(aux_x,aux_y,background);
			
			aux_x++;
		}
		aux_x = x;
		aux_y++;
	}


}
void print(int *pos,int lenght,int height,int fontColor){
	int x = pos[0];
	int y = pos[1];
	
	for(int i=0;i<lenght/2;i++){
		for(int j=0;j<height/2;j++){
			drawPixel(x+i,y+j,fontColor);
			drawPixel(x+i,y-j,fontColor);
			drawPixel(x-i,y+j,fontColor);
			drawPixel(x-i,y-j,fontColor);
		}
	}
}

//Print de un tile seleccionado, muy usado para donde esta paradoo el usr
void print_border(int *pos,int lenght,int height,int fontColor){
	int x = pos[0];
	int y = pos[1];
	for (int i = 2; i < lenght-2; i++)
	{
		drawPixel(x+i, y+4, fontColor);
		drawPixel(x+i, y+5, fontColor);
		drawPixel(x+i, y+6, fontColor);
		drawPixel(x+i, y+height-4, fontColor);
		drawPixel(x+i, y+height-3, fontColor);
		drawPixel(x+i, y+height-2, fontColor);
	}
	for (int j = 2; j < height-2; j++)
	{
		drawPixel(x+4, y+j, fontColor);
		drawPixel(x+5, y+j, fontColor);
		drawPixel(x+6, y+j, fontColor);
		drawPixel(x+lenght-4, y+j, fontColor);
		drawPixel(x+lenght-3, y+j, fontColor);
		drawPixel(x+lenght-3, y+j, fontColor);
	}
}
//Print de un tile highlighteado, usado para mostrarle las opciones para mover una pieza al usuario
void print_highlight(int *pos,int lenght,int height,int fontColor){
	int x = pos[0];
	int y = pos[1];
	for (int i = 2; i <height-2; i++)
    {
        for (int j = 2; j < lenght-2; j++)
        {
            if( (i%6 == 0 && j%6 == 0 )|| (i%6 != 0 && j%6 != 0)){
                  
            }else{
				drawPixel(x+j, y+i, fontColor);
			}
        }
	}
     
}

void print_piece(int * pos, int piece, int fontColor) {
	int aux_x = pos[0];
	int aux_y = pos[1];
	int charSize = 4;
	unsigned char * toDraw = pieceBitmap(piece);

	char bitIsPresent ;

	for(int i = 0; i < CHAR_HEIGHT; i++){
		for(int j = 0 ; j < CHAR_WIDTH ; j++){
			bitIsPresent = (1<< (CHAR_WIDTH-j)) & toDraw[i];
			if(bitIsPresent){
				for (int z = 0; z < charSize ; z++){
					for(int s = 0; s < charSize ; s++){
						drawPixel(aux_x, aux_y, fontColor);
						aux_y++;
					}
					aux_x++;
					aux_y = aux_y - charSize;
				}
			}else {
				for (int z = 0; z < charSize ; z++){
					for (int s = 0; s < charSize ; s++){
						//drawPixel(aux_x, aux_y, backgroundColor);
						aux_y++;
					}
					aux_x++;
					aux_y = aux_y - charSize;
				}
				
			}
				// drawPixel(aux_x,aux_y,fontColor);			
			
		}
		aux_y += charSize;
		aux_x = pos[0];
		// aux_y++;
	}
}

void setSize(unsigned int s){
	SCREEN_bPP=s;
}

void getBpp(int * size){
	*size=SCREEN_bPP;
}