/*
----------------------------------------------------------------------------------------------------------
	File: MultiFrameDrawable.h
	Author: Ozzie Mercado
	Created: September 25, 2020
	Modified: November 23, 2020
	Description: An object that extends the functionality of Drawable to allow for images with mulitple
		frames of images like sprite strips.
----------------------------------------------------------------------------------------------------------
*/

#pragma once

#include "Drawable.h"

class MultiFrameDrawable : public Drawable
{
private:
	const unsigned int* frameHead;	// Points to the head of the sprite strip.
	unsigned int frame;				// The current frame number.
	unsigned int totalFrames;		// The total amount of frames in the sprite strip.

public:

	MultiFrameDrawable(const unsigned int* _pixels, unsigned int _width, unsigned int _height, unsigned int _totalFrames);
	virtual ~MultiFrameDrawable();

	void SetFrame(unsigned int _frame);
};