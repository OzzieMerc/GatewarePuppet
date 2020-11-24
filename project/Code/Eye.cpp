/*
----------------------------------------------------------------------------------------------------------
	File: Eye.cpp
	Author: Ozzie Mercado
	Created: September 25, 2020
	Modified: November 23, 2020
	Description: See header file for more documentation.
----------------------------------------------------------------------------------------------------------
*/

#include "Eye.h"
#include "../Assets/AssetEye.h"
#include "../Assets/AssetEyebrow.h"
#include "../Assets/AssetEyelid.h"
#include <assert.h>

Eye::Eye(int _x, int _y, bool _isLeft) :
	x(_x),
	y(_y),
	pupil(PUPIL_PIXELS, PUPIL_WIDTH, PUPIL_HEIGHT, _x, _y),
	lid(EYELID_PIXELS, EYELID_WIDTH, EYELID_HEIGHT, EYELID_FRAMES),
	brow(EYEBROW_PIXELS, EYEBROW_WIDTH, EYEBROW_HEIGHT, _x, _y - browOffset, _isLeft),
	white(EYE_PIXELS, EYE_WIDTH, EYE_HEIGHT, _x, _y)
{
	lid.SetPos(_x, _y);
	lid.SetFlipped(_isLeft);
}

void Eye::SetIsLeft(bool _isLeft)
{
	lid.SetFlipped(_isLeft);
	brow.SetFlipped(_isLeft);
}

void Eye::SetPos(int _x, int _y)
{
	x = _x;
	y = _y;

	white.SetPos(x, y);
	pupil.SetPos(x, y);
	lid.SetPos(x, y);
	brow.SetPos(x, y - browOffset);
}

void Eye::MoveBrow(float _scale)
{
	assert(_scale >= -1.0f && _scale <= 1.0f); // _scale must be inclusively between -1.0f and 1.0f.

	brow.SetOffset(0, static_cast<int>(_scale * browRange));
}

void Eye::MoveLid(float _scale)
{
	assert(_scale >= 0.0f && _scale <= 1.0f); // _scale must be inclusively between 0.0f and 1.0f.

	lid.SetFrame(static_cast<unsigned int>((EYELID_FRAMES - 1) * _scale));
}

void Eye::Move(float _xscale, float _yscale)
{
	assert(_xscale >= 0.0f || _xscale <= 1.0f); // _xscale must be inclusively between 0.0f and 1.0f.
	assert(_yscale >= 0.0f || _yscale <= 1.0f); // _xscale must be inclusively between 0.0f and 1.0f.

	pupil.SetOffset(static_cast<int>(_xscale * pupilRangeX), static_cast<int>(_yscale * pupilRangeY));
}

void Eye::Render(unsigned int* _canvas, unsigned int _width, unsigned int _height) const
{
	assert(_canvas); // _canvas should never point to nullptr.
	assert(_width != 0 && _height != 0); // Invalid dimensions.

	white.Render(_canvas, _width, _height);
	pupil.Render(_canvas, _width, _height);
	lid.Render(_canvas, _width, _height);
	brow.Render(_canvas, _width, _height);
}