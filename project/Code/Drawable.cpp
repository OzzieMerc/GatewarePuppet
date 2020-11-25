/*
----------------------------------------------------------------------------------------------------------
	File: Drawable.cpp
	Author: Ozzie Mercado
	Created: September 25, 2020
	Modified: November 25, 2020
	Description: See header file for more documentation.
----------------------------------------------------------------------------------------------------------
*/

#include "Drawable.h"
#include <assert.h>

namespace Puppet
{
	Drawable::Drawable(const unsigned int* _pixels, unsigned int _width, unsigned int _height, int _x, int _y, bool _flipped) :
		pixels(_pixels),
		x(_x), y(_y),
		width(_width), height(_height),
		pixelCount(_width * _height),
		offsetX(0), offsetY(0),
		flipped(_flipped)
	{
		assert(_pixels); // _pixels should never point to nullptr.
		assert(_width != 0 && _height != 0); // Invalid dimensions.
	}

	Drawable::~Drawable()
	{
		pixels = nullptr;
	}

	int Drawable::GetPosX() const
	{
		return x;
	}

	int Drawable::GetPosY() const
	{
		return y;
	}

	unsigned int Drawable::GetWidth() const
	{
		return width;
	}

	unsigned int Drawable::GetHeight() const
	{
		return height;
	}

	unsigned int Drawable::GetPixelCount() const
	{
		return pixelCount;
	}

	void Drawable::SetPixels(const unsigned int* _pixels, unsigned int _width, unsigned int _height)
	{
		assert(_pixels); // _pixels should never point to nullptr.
		assert(_width != 0 && _height != 0); // Invalid dimensions.

		pixels = _pixels;
		width = _width;
		height = _height;
		pixelCount = _width * _height;
	}

	void Drawable::SetPos(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	void Drawable::SetOffset(int _x, int _y)
	{
		offsetX = _x;
		offsetY = _y;
	}

	void Drawable::SetFlipped(bool _flipped)
	{
		flipped = _flipped;
	}

	void Drawable::Render(unsigned int* _canvas, unsigned int _width, unsigned int _height) const
	{
		assert(_canvas); // _canvas should never point to nullptr.
		assert(_width != 0 && _height != 0); // Invalid dimensions.

		if (flipped)
		{
			// Find the corners of the area that is to be drawn on, top-right and bottom-left.
			int endX = x + offsetX - (width >> 1);
			int startY = y + offsetY - (height >> 1);
			int startX = endX + width - 1;
			int endY = startY + height;

			// Fit the corners inside the canvas area.
			// If the corner is off the canvas, return because it won't be seen.
			if (startX < 0)
				return;
			else if (startX >= static_cast<int>(_width))
				startX = _width - 1;

			if (endX >= static_cast<int>(_width))
				return;
			else if (endX < 0)
				endX = 0;

			if (startY < 0)
				startY = 0;
			else if (startY >= static_cast<int>(_height))
				return;

			if (endY > static_cast<int>(_height))
				endY = static_cast<int>(_height);
			else if (endY < 1)
				return;

			// Draw a mirror image.
			for (int i = 0, r = startY; r < endY; ++r)
				for (int c = startX; c >= endX; --c, ++i)
					DrawPixel(_canvas, c, r, _width, pixels[i]);
		}
		else
		{
			// Find the corners of the area that is to be drawn on, top-left and bottom-right.
			int startX = x + offsetX - (width >> 1);
			int startY = y + offsetY - (height >> 1);
			int endX = startX + width;
			int endY = startY + height;

			// Fit the corners inside the canvas area.
			// If the corner is off the canvas, return because it won't be seen.
			if (startX < 0)
				startX = 0;
			else if (startX >= static_cast<int>(_width))
				return;

			if (endX > static_cast<int>(_width))
				endX = static_cast<int>(_width);
			else if (endX < 1)
				return;

			if (startY < 0)
				startY = 0;
			else if (startY >= static_cast<int>(_height))
				return;

			if (endY > static_cast<int>(_height))
				endY = static_cast<int>(_height);
			else if (endY < 1)
				return;

			// Draw the image.
			for (int i = 0, r = startY; r < endY; ++r)
				for (int c = startX; c < endX; ++c, ++i)
					DrawPixel(_canvas, c, r, _width, pixels[i]);
		}
	}

	void Drawable::DrawPixel(unsigned int* _canvas, int _x, int _y, unsigned int _width, unsigned int _color) const
	{
		assert(_canvas); // _canvas should never point to nullptr.
		assert(_x >= 0 && _y >= 0 && _x < static_cast<int>(_width)); // Coordinates are outside of the _canvas.
		assert(_width != 0); // Invalid dimension. _width should never be 0.

		if (_color != 0)
			_canvas[_y * _width + _x] = _color;
	}
}