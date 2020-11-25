/*
----------------------------------------------------------------------------------------------------------
	File: Eye.h
	Author: Ozzie Mercado
	Created: September 25, 2020
	Modified: November 25, 2020
	Description: An object represents and renders a single eye with pupil, eye white, eyelid, and eyebrow.
----------------------------------------------------------------------------------------------------------
*/

#pragma once

#include "../Assets/AssetPupil.h"
#include "Drawable.h"
#include "MultiFrameDrawable.h"

namespace Puppet
{
	class Eye final
	{
	private:
		static constexpr int pupilRangeX = (PUPIL_WIDTH >> 1) - 15;
		static constexpr int pupilRangeY = (PUPIL_HEIGHT >> 1) + 34;
		static constexpr int browRange = 15;
		static constexpr int browOffset = 160;
		
		MultiFrameDrawable lid;
		Drawable brow;
		Drawable pupil;
		Drawable white;
		int x, y;

	public:
		Eye(int _x, int _y, bool _isLeft);
		~Eye() = default;

		void SetIsLeft(bool _isLeft);
		void SetPos(int _x, int _y);
		void MoveBrow(float _scale);
		void MoveLid(float _scale);
		void Move(float _xscale, float _yscale);
		void Render(unsigned int* _canvas, unsigned int _width, unsigned int _height) const;
	};
}
