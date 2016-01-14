#include "image.h"
#include "sink.h"

void Sink::SetInput(Image *image) { input1 = image;}
void Sink::SetInput2(Image *image) { input2 = image;}
const Image *Sink::GetInput() { return input1;}
const Image *Sink::GetInput2() {return input2;}