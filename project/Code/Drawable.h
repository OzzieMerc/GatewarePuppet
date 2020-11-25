/*
----------------------------------------------------------------------------------------------------------
	File: Drawable.h
	Author: Ozzie Mercado
	Created: September 25, 2020
	Modified: November 25, 2020
	Description: An object that represents an array of pixels and its relation to the screen. This object
		can render to a given set of pixels, such as the pixels for a framebuffer.
----------------------------------------------------------------------------------------------------------
*/

#pragma once

namespace Puppet
{
	class Drawable
	{
	private:
		const unsigned int* pixels; // Points to the Pixels that represent an image.
		int x, y;					// Local coordinates of the image.
		unsigned int width, height;	// Image dimensions.
		unsigned int pixelCount;	// Total area of the image. Based off the width and height of the image.

	protected:
		int offsetX, offsetY;		// The divergence of the image from its local position.
		bool flipped;				// True if the image is to be rendered from right to left, creating a mirror image.

	public:
		Drawable(const unsigned int* _pixels, unsigned int _width, unsigned int _height, int _x = 0, int _y = 0, bool _flipped = false);
		virtual ~Drawable();

		int GetPosX() const;
		int GetPosY() const;
		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
		unsigned int GetPixelCount() const;
		void SetPixels(const unsigned int* _pixels, unsigned int _width, unsigned int _height);
		void SetPos(int _x, int _y);
		void SetOffset(int _x, int _y);
		void SetFlipped(bool _flipped);
		void Render(unsigned int* _canvas, unsigned int _width, unsigned int _height) const;
		void DrawPixel(unsigned int* _canvas, int _x, int _y, unsigned int _width, unsigned int _color) const;
	};
}