/* Sink is its parent */

#include "PNMwriter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

//Writes input1 to a file
void PNMwriter::Write(char *filename)
{
	FILE *f = fopen(filename,"w");
	fprintf(f, "P6 %d %d 255\n",input1->getWidth(),input1->getHeight());
	for (int i = 0;i<input1->getHeight();i++)
		for(int j = 0; j < input1->getWidth(); j++)
		{
			fprintf(f,"%c",input1->getPixel(i,j).red);
			fprintf(f,"%c",input1->getPixel(i,j).green);
			fprintf(f,"%c",input1->getPixel(i,j).blue);
		}
}

PNMwriter::PNMwriter(void){input1 = new Image; input2 = new Image;}
