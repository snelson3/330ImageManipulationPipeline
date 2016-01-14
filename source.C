#include "image.h"
#include "source.h"
#include <iostream>

Image *Source::GetOutput(){ return image; }
void Source::SetOutput(Image *i) { image = i; } 
void Source::Update(){}
