/*
----------------------------------------------------------------------------------------------------------
	File: AssetColorPallete.h
	Author: Ozzie Mercado
	Created: September 25, 2020
	Modified: November 23, 2020
	Description: The color pallete used for the color of the face.
----------------------------------------------------------------------------------------------------------
*/

#pragma once

constexpr unsigned int COLORPALLETE_WIDTH = 7; // The width of the image.
constexpr unsigned int COLORPALLETE_HEIGHT = 1; // The height of the image.
constexpr unsigned int COLORPALLETE_PIXEL_COUNT = COLORPALLETE_WIDTH * COLORPALLETE_HEIGHT; // Total pixels in the image.

// The pixels that make up the image.
constexpr unsigned int COLORPALLETE_PIXELS[COLORPALLETE_PIXEL_COUNT] =
{ 
	0xffed1c24, 0xffff7f27, 0xfffff200, 0xff22b14c, 0xff00a2e8, 0xff3f48cc, 0xffa349a4,
};