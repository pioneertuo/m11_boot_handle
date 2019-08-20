#ifndef __PARSE_H__
#define __PARSE_H__

#include "sys.h"

#define PARSE_FRAME_SIZE	MAX_TRANSFER_SIZE

typedef struct{
	enum{
		Parse_Head1,
		Parse_Head2,
		Parse_Len,
		Parse_Content,
		Parse_Checksum,
	}state;
	
	uint8_t frame[PARSE_FRAME_SIZE];
	uint8_t frame_len;
	
	uint8_t cnt;
	
	uint8_t sum;
}parse_type;

void parse_init(parse_type *parse);
uint8_t parse_process(parse_type *parse, uint8_t in);

#endif
