
#ifndef SOURCE
#define SOURCE
#include <iostream>
#include <string>
#include "image.h"

class Source
{
	protected:
		 virtual void Execute(){}
		 Image *image;
	public:
		virtual void Update();
		Image * GetOutput();
		void SetOutput(Image *i);
		virtual const char *getName() { return "Source";}

};

#endif