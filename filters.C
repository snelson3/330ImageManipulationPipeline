#include "filters.h"
#include "image.h"
#include <iostream>
#include "source.h"
#include "sink.h"

void Filter::SetInput(Image *image) { input1 = image; GetOutput()->setFilter(this); In1 = true;}
void Filter::SetInput2(Image *image) { input2 = image;GetOutput()->setFilter(this); In2 = true;}


/* Halves an Image in size */
void Shrinker::Execute()
{
		if (In1 != true)
		{
			char msg[1024];
			sprintf(msg, "no input1!");
			DataFlowException e(getName(),msg);
			throw e;
		}	

	image->resetSize(input1->getWidth()/2,input1->getHeight()/2);
	for (int i = 0; i < image->getHeight(); i++)
		for (int j = 0; j < image->getWidth(); j++)
			image->setPixel(i,j,input1->getPixel(2*i,2*j));
}



/* Takes two images with the same height and makes a single image combined left-to-right */
void LRConcat::Execute()
{
		if (In1 != true)
		{
			char msg[1024];
			sprintf(msg, "no input1!");
			DataFlowException e(getName(),msg);
			throw e;
		}	

		if (In2 != true)
		{
			char msg[1024];
			sprintf(msg, "no input2!");
			DataFlowException e(getName(),msg);
			throw e;
		}	

		if (input1->getHeight() != input2->getHeight())
		{
			char msg[1024];
			sprintf(msg, "heights must match: %d, %d", input1->getHeight(),input2->getHeight());
			DataFlowException e(getName(),msg);
			throw e;
		}	


	image->resetSize(input1->getWidth()+input2->getWidth(), input1->getHeight());
	input1->copyBuffer(*image);

	for (int i = 0; i < image->getHeight();i++)
		for (int j = 0; j < input2->getWidth(); j++)
			image->setPixel(i,j+input1->getWidth(),input2->getPixel(i,j));
}



/* Takes two images with the same width and makes a single image combined top-to-bottom */
void TBConcat::Execute()
{

		if (In1 != true)
		{
			char msg[1024];
			sprintf(msg, "no input1!");
			DataFlowException e(getName(),msg);
			throw e;
		}	

		if (In2 != true)
		{
			char msg[1024];
			sprintf(msg, "no input2!");
			DataFlowException e(getName(),msg);
			throw e;
		}	

	if (input1->getWidth() != input2->getWidth())
		{
			char msg[1024];
			sprintf(msg, "widths must match: %d, %d", input1->getWidth(),input2->getWidth());
			DataFlowException e(getName(),msg);
			throw e;
		}	

	image->resetSize(input1->getWidth(), input1->getHeight()+input2->getHeight());
	input1->copyBuffer(*image);
	
	for (int i = 0; i < input2->getHeight(); i++)
		for (int j = 0; j <image->getWidth();j++)	
			image->setPixel(i+input1->getHeight(),j,input2->getPixel(i,j));
}



/* Takes two input images with the same width and height and blends them together,
      such that the output image is factor% image1 and 1-factor% image2 */
void Blender::Execute()
{

		if (In2 != true)
		{
			char msg[1024];
			sprintf(msg, "no input2!");
			DataFlowException e(getName(),msg);
			throw e;
		}	

	if (factor < 0)
		{
			char msg[1024];
			sprintf(msg, "Invalid factor for Blender : %f", factor);
			DataFlowException e(getName(),msg);
			throw e;
		}	

	if (factor > 1)
		{
			char msg[1024];
			sprintf(msg, "Invalid factor for Blender : %f", factor);
			DataFlowException e(getName(),msg);
			throw e;
		}	

	image->resetSize(input1->getWidth(),input1->getHeight());
	for (int i = 0; i < image->getHeight(); i++)
		for (int j = 0; j < image->getWidth(); j++)
			{
				Pixel pix1 = input1->getPixel(i,j);
				Pixel pix2 = input2->getPixel(i,j);
				pix1.red = (int)(pix1.red*(factor)+pix2.red*(1-factor)) ;
				pix1.green = (int)(pix1.green*(factor)+pix2.green*(1-factor));
				pix1.blue = (int)(pix1.blue*(factor)+pix2.blue*(1-factor));
				image->setPixel(i,j,pix1);
		}
}



void Invert::Execute()
{
		if (In1 != true)
		{
			char msg[1024];
			sprintf(msg, "no input1!");
			DataFlowException e(getName(),msg);
			throw e;
		}	

	image->resetSize(input1->getWidth(),input1->getHeight());

	for (int i = 0; i < image->getHeight(); i++)
		for (int j = 0; j < image->getWidth(); j++)
			{
				Pixel pix = input1->getPixel(i,j);
				pix.red = (int)(255-pix.red);
				pix.green = (int)(255-pix.green);
				pix.blue = (int)(255-pix.blue);
				image->setPixel(i,j,pix);
			}
}

void Transpose::Execute()
{

if (In1 != true)
		{
			char msg[1024];
			sprintf(msg, "no input1!");
			DataFlowException e(getName(),msg);
			throw e;
		}	

image->resetSize(input1->getHeight(),input1->getWidth());
		
for (int i = 0; i < image->getHeight(); i++)
	for (int j = 0; j < image->getWidth(); j++){
		image->setPixel(i,j,input1->getPixel(j,i));}
//I need to have a temporary pixel that I can use to store each one, and then its just like a xy = yx thing
}

void Crop::Execute(){

if (In1 != true)
		{
			char msg[1024];
			sprintf(msg, "no input1!");
			DataFlowException e(getName(),msg);
			throw e;
		}	

    if (ibegin < 0 || iend < 0 || jbegin < 0 || jend < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: uninitialized region", getName());
        DataFlowException e(getName(), msg);
        throw e;
    }
    if (ibegin >= input1->getWidth() || iend >= input1->getWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image width", getName());
        DataFlowException e(getName(), msg);
        throw e;
    }
    if (jbegin >= input1->getHeight() || jend >= input1->getHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image height", getName());
        DataFlowException e(getName(), msg);
        throw e;
    }
    if (iend < ibegin || jend < jbegin)
    {
        char msg[1024];
        sprintf(msg, "%s: invalid region", getName());
        DataFlowException e(getName(), msg);
        throw e;
    }

//so I end up making the width the height
    int height = iend-ibegin+1;
    int width  = jend-jbegin+1;
    image->resetSize(height,width);
    for (int i = 0; i < width; i++)
    	for (int j = 0; j < height; j++)
    	{
    		image->setPixel(i,j,input1->getPixel(jbegin+i,ibegin+j));
        }
    /*
    unsigned char *buffer = output.GetBuffer();
    const unsigned char *buffer1 = input->GetBuffer();
    for (int i = Istart ; i <= Istop ; i++)
        for (int j = Jstart ; j <= Jstop ; j++)
        {
            int idx1 = j*inputWidth+i;
            int idx  = (j-Jstart)*width+(i-Istart);
            buffer[3*idx]   = buffer1[3*idx1];
            buffer[3*idx+1] = buffer1[3*idx1+1];
            buffer[3*idx+2] = buffer1[3*idx1+2];
        }*/

}


void Blender::SetFactor(float f){ factor = f;}

void Crop::SetRegion(int ib, int ie, int jb, int je)
{
	ibegin = ib;
	iend = ie;
	jbegin = jb;
	jend = je;
}

Filter::Filter(void){In1 = false; In2 = false; image = new Image; input1 = new Image; input2 = new Image;}

void Filter::Update(){
	char msg[128];
	if (In1 != false)
	{
		sprintf(msg, "%s: about to update input1", getName());
		Logger::LogEvent(msg);
		input1->Update(); 
		sprintf(msg, "%s: done updating input1", getName());
		Logger::LogEvent(msg);
	}
	if (In2 != false)
	{
		sprintf(msg, "%s: about to update input2", getName());
		Logger::LogEvent(msg);
		input2->Update(); 
		sprintf(msg, "%s: done updating input2", getName());
		Logger::LogEvent(msg);
	}
	
	sprintf(msg, "%s: about to execute",getName());
	Logger::LogEvent(msg);
	Execute();
	sprintf(msg, "%s: done executing",getName());
	Logger::LogEvent(msg);
}

int mod(int d)
{
  int r;
  int g = d/255;
  int o = g*255;
  r = d-o;
  
  
return r;
}

void CheckSum::OutputCheckSum(const char *filename)
{
    unsigned char redsum = 0;
    unsigned char bluesum = 0;
    unsigned char greensum = 0;
    
    for (int i=0;i<input1->getHeight();i++)
    	for (int j=0; j<input1->getWidth();j++)
    	{
    		Pixel pix = input1->getPixel(i,j);
    		redsum = pix.red+redsum;
    		bluesum = pix.blue+bluesum;
    		greensum = pix.green+greensum;
    	}
    	
	FILE *f = fopen(filename,"w");
	fprintf(f, "CHECKSUM: %d, %d, %d\n",redsum,greensum,+bluesum);


}


