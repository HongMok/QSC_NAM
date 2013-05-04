#include "functions.h"

#include "ac.h"

#define FILE "foo"
#define ADAPT 1

void ac_decompress_array(vector<int> &Q, int NSYM, int count)
{
	ac_decoder acd;
	ac_model acm;
	int sym, i;

	//long MASK = (0x1 << bit_len) - 1;
	//long NSYM = (MASK + 1);

	ac_decoder_init (&acd, FILE);
	ac_model_init (&acm, NSYM, NULL, ADAPT);

	for (i=0; i<count; i++)  
	{
		sym = ac_decode_symbol (&acd, &acm);
		Q.push_back(sym);
	}

	ac_decoder_done (&acd);
	ac_model_done (&acm);

}