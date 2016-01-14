#ifndef IMAGE_H
#define IMAGE_H

class Filter;
class PNMreader;

struct Pixel
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

class Image
{
	private:
		int width, height;
		Pixel *buffer;
		Filter *filter;
		PNMreader *pnm;
//		Image & operator=(const Image &) {};//dont think i need this
	
	public:
		Image(void);
		Image(int w, int h);
		Image(Image &image);
	
		int getWidth() const;
		int getHeight() const;
		void resetSize(int w, int h);
		void copyBuffer(Image &output) const;
		Pixel getPixel(int i, int j) const;
		void setPixel(int i, int j, Pixel pix);
		void setPixel1D(int i, Pixel pix);
		Pixel getPixel1D(int i) const;
		void setHeight(int h);
		void setWidth(int w);
		Filter *getFilter() const;
		PNMreader *getPNM() const;
		void setFilter(Filter *f);
		void setPNM(PNMreader *p);
		void Update() const;
};

#endif
