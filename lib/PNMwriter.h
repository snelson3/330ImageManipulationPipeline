#ifndef PNMWRITER
#define PNMWRITER

#include "sink.h"
#include <string.h>

class PNMwriter : public Sink
{
	public:
		void Write(char *filename);
		PNMwriter(void);
};


#endif