/*
----------------------------------------------------------------------------------------------------------
	File: Face.cpp
	Author: Ozzie Mercado
	Created: September 25, 2020
	Modified: November 25, 2020
	Description: See header file for more documentation.
----------------------------------------------------------------------------------------------------------
*/

#include "Face.h"
#include "../Assets/AssetColorPallete.h"
#include "../Assets/AssetMouth.h"
#include <assert.h>

namespace Puppet
{
	Face::Face(unsigned int _width, unsigned int _height) :
		color(Color::Violet),
		mouth(MOUTH_PIXELS, MOUTH_WIDTH, MOUTH_HEIGHT, MOUTH_FRAMES),
		leftEye((_width >> 1) - 100, (_height >> 1) - 80, true), 
		rightEye((_width >> 1) + 100, (_height >> 1) - 80, false),
		expression(Expression::Smile)
	{
		assert(_width != 0 && _height != 0); // Invalid dimensions.

		mouth.SetPos(_width >> 1, (_height >> 1) + 170);
	}

	void Face::ResetEyes()
	{
		leftEye.MoveBrow(0.0f);
		rightEye.MoveBrow(0.0f);
		leftEye.MoveLid(0.0f);
		rightEye.MoveLid(0.0f);
		leftEye.Move(0.0f, 0.0f);
		rightEye.Move(0.0f, 0.0f);
	}

	void Face::SetColor(Color _color)
	{
		assert(_color != Color::Size); // Color::Size is not a valid color for the face.

		color = _color;
	}

	void Face::SetMouth(Expression _expression)
	{
		assert(_expression != Expression::Size); // Expression::Size is not a valid expression for the mouth.

		expression = _expression;
		mouth.SetFrame(static_cast<unsigned int>(expression));
	}

	void Face::MoveEye(float _xscale, float _yscale, Side _side)
	{
		assert(_side != Side::Size); // Side::Size is not a valid side of the face.

		switch (_side)
		{
		case Face::Side::Left: leftEye.Move(_xscale, _yscale); break;
		case Face::Side::Right: rightEye.Move(_xscale, _yscale); break;
		default: break;
		}
	}

	void Face::MoveEyebrow(float _scale, Side _side)
	{
		assert(_side != Side::Size); // Side::Size is not a valid side of the face.

		switch (_side)
		{
		case Face::Side::Left: leftEye.MoveBrow(_scale); break;
		case Face::Side::Right: rightEye.MoveBrow(_scale); break;
		default: break;
		}
	}

	void Face::AdjustEyelid(float _scale, Side _side)
	{
		assert(_side != Side::Size); // Side::Size is not a valid side of the face.

		switch (_side)
		{
		case Face::Side::Left: leftEye.MoveLid(_scale); break;
		case Face::Side::Right: rightEye.MoveLid(_scale); break;
		default: break;
		}
	}

	void Face::Render(unsigned int* _canvas, unsigned int _width, unsigned int _height) const
	{
		assert(_canvas); // _canvas should never point to nullptr.
		assert(_width != 0 && _height != 0); // Invalid dimensions.

		// Fill in the background.
		unsigned int bgColor = static_cast<unsigned int>(color);
		unsigned int pixelCount = _width * _height;

		for (unsigned int i = 0; i < pixelCount; ++i)
			_canvas[i] = COLORPALLETE_PIXELS[bgColor];

		// Draw the different parts of the face.
		mouth.Render(_canvas, _width, _height);
		leftEye.Render(_canvas, _width, _height);
		rightEye.Render(_canvas, _width, _height);
	}
}