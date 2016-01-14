#ifndef PNMREADER
#define PNMREADER

#include "source.h"
#include <string.h>
#include "image.h"

class PNMreader : public Source
{
	protected:
		virtual void Execute();
	public:
		bool fileread;
		char *filename;
		PNMreader(char *f);
		virtual void Update();
		
};

#endif