#ifndef IMAGE
#define IMAGE

#include "image.h"
#include <stdlib.h>

class Sink
{
	protected:
		const Image *input1;
		const Image *input2;
	public:
		virtual void SetInput(Image *image);
		virtual void SetInput2(Image *image);
		const Image *GetInput();
		const Image *GetInput2();
};

#endif