#include "rtp_memery.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
rtp_nalu_t* RTPMemery::RTPNaluCalloc(int size)
{
	rtp_nalu_t *n;
	if ((n = (rtp_nalu_t*)calloc (1, sizeof (rtp_nalu_t))) == NULL)
	{
		return NULL;
	}
	n->max_size=size;
	if ((n->buf = (unsigned char*)calloc (size, sizeof (char))) == NULL)
	{
		free (n);
		return NULL;
	}
	return n;
}

void RTPMemery::RTPNaluFree(rtp_nalu_t* n)
{
	if(n)
	{
		if (n->buf)
		{
			free(n->buf);
			n->buf=NULL;
		}
		free (n);
	}
}