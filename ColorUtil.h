/*
	ColorUtil.h
	Written by Ronan Murphy circa Aug-Sep 2013.
*/
#ifndef COLORUTIL_H
#define COLORUTIL_H

#include <SFML/Graphics.hpp>

namespace ColorUtil
{
	struct RGB{	float r, g, b;	};

	RGB			HSLtoRGB(int p_hue, float p_saturation, float p_lightness);
	int			GetRandomHue();
	sf::Color	HueToRGB(int p_hue);
}
#endif