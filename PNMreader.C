#include "PNMreader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include <iostream>
#include "logging.h"
/* Source is its parent */

/* Parameterized constructor */
PNMreader::PNMreader(char *f) { image = new Image;image->setPNM(this);filename = f; }

/* Reads in the image */
void PNMreader::Execute()
{
	FILE *f = fopen(filename, "rb");
	char magicNum[128];
	int  width, height, maxval;
	Pixel pix;

    		if (f == NULL)
		{
			char msg[1024];
			sprintf(msg,  "Unable to open file %s\n", filename);
			DataFlowException e(getName(),msg);
			throw e;
		}	

    	fscanf(f, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
    	printf("Magic num = %s width = %d, height = %d, maxval = %d\n",
            	magicNum, width, height, maxval);
    	
    
    		if (strcmp(magicNum, "P6") != 0)
		{
			char msg[1024];
			sprintf(msg,"Unable to read from file %s, because it is not a PNM file of type P6\n", filename);
			DataFlowException e("PNMreader",msg);
			throw e;
		}	

    
	GetOutput()->resetSize(width,height);

	for (int i = 0; i < width*height; i++)
	{
		char *redbuffer = new char;
		char *greenbuffer = new char;
		char *bluebuffer = new char;
		fread(redbuffer, sizeof(char), 1, f);
		fread(greenbuffer, sizeof(char), 1, f);
		fread(bluebuffer, sizeof(char), 1, f);
		pix.red = *redbuffer;
		pix.green = *greenbuffer;
		pix.blue = *bluebuffer;
		GetOutput()->setPixel1D(i,pix);
        }

}

void PNMreader::Update()
{ 
Logger::LogEvent("PNMreader:about to execute");
Execute();
Logger::LogEvent("PNMreader:done executing");
fileread = true;
}