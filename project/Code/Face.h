/*
----------------------------------------------------------------------------------------------------------
	File: Face.h
	Author: Ozzie Mercado
	Created: September 25, 2020
	Modified: November 25, 2020
	Description: An object that represents and renders a face with two eyes, a mouth.
----------------------------------------------------------------------------------------------------------
*/

#pragma once

#include "Eye.h"
#include "MultiFrameDrawable.h"

namespace Puppet
{
	class Face final
	{
	public:
		enum class Color
		{
			Red,
			Orange,
			Yellow,
			Green,
			Blue,
			Purple,
			Violet,
			Size // Size is useful for iterating through colors.
		};

		enum class Side
		{
			Left,
			Right,
			Size
		};

		enum class Expression
		{
			Smile,
			Happy,
			Suprise,
			Sad,
			Size
		};

	private:
		Eye leftEye, rightEye;
		MultiFrameDrawable mouth;
		Expression expression;
		Color color;

	public:
		Face(unsigned int _width, unsigned int _height);
		virtual ~Face() = default;

		void ResetEyes();
		void SetColor(Color _color);
		void SetMouth(Expression _expression);
		void MoveEye(float _xscale, float _yscale, Side _side);
		void MoveEyebrow(float _scale, Side _side);
		void AdjustEyelid(float _scale, Side _side);
		void Render(unsigned int* _canvas, unsigned int _width, unsigned int _height) const;
	};
}