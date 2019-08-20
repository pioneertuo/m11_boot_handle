#include "parse.h"
#include "includes.h"

void parse_init(parse_type *parse)
{
	parse->state = Parse_Head1;
	
	parse->frame_len = 0;
	
	parse->cnt = 0;
	parse->sum = 0;
}

uint8_t parse_process(parse_type *parse, uint8_t in)
{
	switch(parse->state)
	{
		case Parse_Head1:
			if(in == FRAME_HEAD1){
				parse->cnt = 0;
				parse->sum = 0;
				
				parse->frame[parse->cnt] = in;
				parse->cnt += 1;
				
				parse->sum += in;
				
				parse->state = Parse_Head2;
			}
			break;
			
		case Parse_Head2:
			if(in == FRAME_HEAD2){
				parse->frame[parse->cnt] = in;
				parse->cnt += 1;
				
				parse->sum += in;
				
				parse->state = Parse_Len;
			}
			else{
				parse->state = Parse_Head1;
			}
			break;
			
		case Parse_Len:
            if(in != 0){
                parse->frame_len = in+4;
                
                parse->frame[parse->cnt] = in;
                parse->cnt += 1;
                
                parse->sum += in;
                
                parse->state = Parse_Content;
            }
            else{
                parse->state = Parse_Head1;
            }
			break;
		
		case Parse_Content:
			parse->frame[parse->cnt] = in;
			parse->cnt += 1;
			
			parse->sum += in;
			
			if(parse->cnt == parse->frame_len-1){
				parse->state = Parse_Checksum;
			}
			break;
		
		case Parse_Checksum:
			parse->frame[parse->cnt] = in;
			parse->cnt += 1;
		
			parse->state = Parse_Head1;
			
			if(parse->sum == in){
				return 1;
			}
			break;
	}
	
	return 0;
}
