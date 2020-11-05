// Created from bdf2c Version 3, (c) 2009, 2010 by Lutz Sammer
//	License AGPLv3: GNU Affero General Public License version 3

#ifndef PIECES_BITMAPS_H
#define PIECES_BITMAPS_H

#include "include/pieces.h"

static unsigned char __pieces_bitmap__[] = {

//  pawn
//	width 8, bbx 0, bby -4, bbw 8, bbh 16
	________,
	________,
	________,
	________,
	________,
	________,
	__XXXX__,
	_XXXXXX_,
	_XXXXXX_,
	__XXXX__,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	__XXXX__,
	_XXXXXX_,

//  bishop
//	width 8, bbx 0, bby -4, bbw 8, bbh 16

	________,
	________,
	___XX___,
	__XXXX__,
	__XXXX__,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	__XXXX__,
	_XXXXXX_, 

//  rook
//	width 8, bbx 0, bby -4, bbw 8, bbh 16

	________,
	________,
	________,
	_X_XX_X_,
	_XXXXXX_,
	_XXXXXX_,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	__XXXX__,
	_XXXXXX_,

//  knight
//	width 8, bbx 0, bby -4, bbw 8, bbh 16

	________,
	________,
	________,
	___X__X_,
	_XXXXXX_,
	XXXXXXX_,
	XXXXXXX_,
	___XXXX_,
	___XXXX_,
	___XXX__,
	___XXX__,
	___XX___,
	___XX___,
	___XX___,
	__XXXX__,
	_XXXXXX_,
	
//  king
//	width 8, bbx 0, bby -4, bbw 8, bbh 16

	___XX___,
	__XXXX__,
	__XXXX__,
	___XX___,
	___XX___,
	__XXXX__,
	_XXXXXX_,
	_XXXXXX_,
	__XXXX__,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	__XXXX__,
	_XXXXXX_,

//  queen
//	width 8, bbx 0, bby -4, bbw 8, bbh 16

 	________,
	___XX___,
    _XXXXXX_,
	__XXXX__,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	___XX___,
	__XXXX__,
	_XXXXXX_,

};

unsigned char * pieceBitmap(int piece) {
	return (__pieces_bitmap__ + piece*BLOCK_HEIGHT);
}

#endif
