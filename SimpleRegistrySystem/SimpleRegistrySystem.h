// SimpleRegistrySystem.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <stdint.h>

#define PROTOCOL_VER 1 //uint8_t

#define U16BQA(x)(x&0xFF)
#define U16BQB(x)(x&0x00FF<<8)

#define U32BQA(x)(x&0x000000FF) 
#define U32BQB(x)(x&0x0000FF00>>8) 
#define U32BQC(x)(x&0x00FF0000>>16) 
#define U32BQD(x)(x&0xFF000000>>24) 

typedef uint8_t* PreallocSafeMem; //hehe

//first 8 bits for type, next 8 bits for general flags, and next 16 bits for page count 
typedef uint32_t pagekey;


/*
All the semi - extraneous stuff at the start is to make it easier for the thing
to "explain itself". And also because why not.

Do not make the label string any longer than 239 chars, it *will* discombobulate
the header ingeneral, which isn't exactly very good. Null termination is not
necessary, it's added by the function.
*/

void generate_manifest(
	uint8_t label_length, uint32_t item_count,
	uint16_t page_size, uint8_t block_size,
	char* label, uint8_t buf[256]) {
	//All blocks are terminated with 0x42, except for the final one, mainly 
	//just to get a slightly more normal alignment. 0x00 is used for the final
	//one, because it means strcpy can be used.
	uint8_t header_start[16]{

		//Block A, general info
		'S','R','S','P','F', //Label at the start
		PROTOCOL_VER,        //Exactly what they say on the tin
		label_length,        //technically useless, but oh well
		0x42,                //End byte

		//Block B, stored data size info
		U32BQA(item_count),  //Number of allocated pages
		U32BQB(item_count),  //
		U32BQC(item_count),  //
		U32BQD(item_count),  //
		U16BQA(page_size),   //Size of each page, in bytes
		U16BQB(page_size),   //
		block_size,          //Size of each block, in pages
		0x00                 //Null terminator
	};

	memcpy(buf, header_start, 16);
	memcpy(buf+16, label, (label_length>239) ? 239 : label_length); //The ternary is just to clamp the value
	buf[256] = 0x00;
}

template<uint16_t page_size> void generate_datinfo_start(
	uint8_t buf[page_size-256]) {

}

// TODO: Reference additional headers your program requires here.
