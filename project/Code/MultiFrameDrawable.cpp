/*
----------------------------------------------------------------------------------------------------------
	File: MultiFrameDrawable.h
	Author: Ozzie Mercado
	Created: September 25, 2020
	Modified: November 25, 2020
	Description: See header file for more documentation.
----------------------------------------------------------------------------------------------------------
*/

#include "MultiFrameDrawable.h"
#include <assert.h>

MultiFrameDrawable::MultiFrameDrawable(const unsigned int* _pixels, unsigned int _width, unsigned int _height, unsigned int _totalFrames) :
	Drawable(_pixels, _width, _height, 0, 0, false),
	frameHead(_pixels),
	frame(0),
	totalFrames(_totalFrames)
{
}

MultiFrameDrawable::~MultiFrameDrawable()
{
	frameHead = nullptr;
}

void MultiFrameDrawable::SetFrame(unsigned int _frame)
{
	assert(_frame < totalFrames); // _frame is outside of the number of frames available.

	frame = _frame;
	SetPixels(frameHead + static_cast<long long>(GetPixelCount()) * frame, GetWidth(), GetHeight());
}
