#ifndef FILTERS
#define FILTERS
#include <string>
#include "logging.h"
#include <stdlib.h>
#include "source.h"
#include "sink.h"



class Color : public Source
{
	public:
		bool fileread;
		char *filename;
		Color(int w, int h, int r, int g, int b){ //might need to change colors
		      //need to make a new image with those qualifications
              image = new Image(w,h);
            Pixel pix;
            pix.red = r;
            pix.green = g;
            pix.blue = b;
 
             for (int i = 0; i < h; i++)
 	             for (int j = 0; j < w; j++)
 		         {
 		             image->setPixel(i,j,pix);
 		         }}
             //might need image->setPNM(this) but I don't think so
		   virtual void Update(){;};
		   virtual void Execute(){;};
		   virtual const char *getName() { return "Color"; }
};

class Filter : public Source, public Sink {
	public:
		Filter(void);
		virtual void SetInput(Image *image);
		virtual void SetInput2(Image *image);
		virtual void Update();
		virtual const char *getName(){return "Filter";}
		bool In1;
		bool In2;
};

class Shrinker : public Filter
{
	protected:
		virtual void Execute();
	public:
		virtual 	const char *getName(){return "Shrinker";}
		
};

class LRConcat : public Filter
{
	protected:
		virtual void Execute();
	public:
		virtual const char *getName(){return "LRConcat";}

};

class TBConcat : public Filter
{
	protected:
		virtual void Execute();
	public:
		virtual const char *getName(){return "TBconcat";}
};

class Blender : public Filter
{
	protected:
		virtual void Execute();
	private:
		float factor;
	public:
		void SetFactor(float f);
		virtual const char *getName(){return "Blender";}
};

class Crop : public Filter
{
	private:
		int ibegin,iend,jbegin,jend;
	protected:
		virtual void Execute();
	public:
		void SetRegion(int ib, int ie, int jb, int je);
		Crop() { ibegin = iend = jbegin = jend = -1; }
		virtual const char *getName(){return "Crop";}
};

class Transpose : public Filter
{
	protected:
		virtual void Execute();
	public:
		virtual const char *getName(){return "Transpose";}
};

class Invert : public Filter
{
	protected:
		virtual void Execute();
	public:
		virtual const char *getName(){return "Invert";}
};

class CheckSum : public Filter
{
	public:
		virtual const char *getName(){return "CheckSum";}
		void OutputCheckSum(const char *filename);
};

#endif
