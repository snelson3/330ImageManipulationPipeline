#include "image.h"
#include<iostream>

#include "filters.h"
#include "PNMreader.h"

/* Standard Setters and Getters */
int Image:: getWidth() const { return width; }
int Image:: getHeight() const { return height; }
void Image::setWidth(int w){ width = w; }
void Image::setHeight(int h){ height = h; }
Filter *Image::getFilter() const { return filter;}
PNMreader *Image::getPNM() const {return pnm;}
void Image::setFilter(Filter *f){filter = f;}
void Image::setPNM(PNMreader *p){pnm = p;}
Pixel Image::getPixel(int i, int j) const { return buffer[i*width+j]; }
void Image::setPixel(int i, int j, Pixel pix){ buffer[i*width+j] = pix; }
void Image::setPixel1D(int i, Pixel pix){ buffer[i] = pix; }
Pixel Image::getPixel1D(int i) const { return buffer[i]; }

/*Calls the update method of whater filter this belongs to*/
void Image::Update() const
{
	if (getFilter() != NULL)
			getFilter()->Update();
	else if (pnm != NULL)
			if(pnm->fileread == false)
				pnm->Update();
}

/* Resets the size of the image to w and h, and reallocates memory for the buffer */
void Image::resetSize(int w, int h)
{

	if (w <= 0)
		{
			char msg[1024];
			sprintf(msg, "Invalid Width");
			DataFlowException e("Image",msg);
			throw e;
		}	
		
	if (h <= 0)
		{
			char msg[1024];
			sprintf(msg, "Invalid Height");
			DataFlowException e("Height",msg);
			throw e;
		}	

	width = w;
	height = h;
	buffer = new Pixel[width*height];
}



/* copies this images buffer to &output's buffer of the same size */
void Image::copyBuffer(Image &output) const
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			output.setPixel(i,j,getPixel(i,j));
}



/* Default Image Constructor */
Image::Image(void){pnm = NULL;width = 0; height = 0;}

/* Parameterized Constructor */
Image::Image(int w, int h)
{
	pnm = NULL;
	filter = NULL;
	width = w; 
	height = h;
	buffer = new Pixel[width*height];
}

/* Copy Constructor */
Image::Image(Image &image)
{
	pnm = NULL;
	width = image.width; 
	height = image.height;
	buffer = new Pixel[width*height];
	buffer = image.buffer;
}
