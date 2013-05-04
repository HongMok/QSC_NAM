#include "functions.h"

#include "ac.h"

#define FILE "foo"
#define ADAPT 1

void ac_compress_array(vector<int> &Q, int NSYM)
{
	ac_encoder ace;
	ac_model acm;
	int sym, i;

	//cout<<"bitlen: "<<bit_len<<endl;

	//long MASK = (0x1 << bit_len) - 1;
	//long NSYM = (MASK + 1);

	ac_encoder_init (&ace, FILE);

	ac_model_init (&acm, NSYM, NULL, ADAPT);

	for(i = 0; i < Q.size(); i++)
	{
		ac_encode_symbol (&ace, &acm, Q[i]);
	}

	ac_encoder_done (&ace);
	ac_model_done (&acm);

	//printf ("bits for encoder : %d\n", (int) ac_encoder_bits (&ace));
	_coor_table_size = (int) ac_encoder_bits (&ace);
}