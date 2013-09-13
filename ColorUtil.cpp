/*
	ColorUtil.cpp
	Written by Ronan Murphy circa Aug-Sep 2013. with contributions from elsewhere.
*/
#include "ColorUtil.h"

namespace ColorUtil
{
	/*
	Function taken from StackOverflow question, from user : JavaRunner, and contributed to by user : Michael Sh .
	http://stackoverflow.com/questions/13407393/cant-convert-from-hsl-to-rgb
	*/
	RGB HSLtoRGB( int p_hue, float p_saturation, float p_lightness ) 
	{

    RGB rgb1, rgbResult;

    float chroma = ( 1.0 - (float) abs( 2.0 * p_lightness - 1.0 ) ) * p_saturation;
    float h1 = p_hue / 60.0;
    //float x = chroma * ( 1.0 - (float) abs( (float) ( (int) h1 % 2 ) - 1.0 ) );
	float x = chroma * ( 1.0 - (float) abs( fmodf(h1, 2.0) - 1.0 ));

    if ( ( 0 <= h1 ) && ( h1 < 1 ) ) {

        rgb1.r = chroma;
        rgb1.g = x;
        rgb1.b = 0.0;

    } else if ( ( 1 <= h1 ) && ( h1 < 2 ) ) {

        rgb1.r = x;
        rgb1.g = chroma;
        rgb1.b = 0.0;

    } else if ( ( 2 <= h1 ) && ( h1 < 3 ) ) {

        rgb1.r = 0.0;
        rgb1.g = chroma;
        rgb1.b = x;

    } else if ( ( 3 <= h1 ) && ( h1 < 4 ) ) {

        rgb1.r = 0.0;
        rgb1.g = x;
        rgb1.b = chroma;

    } else if ( ( 4 <= h1 ) && ( h1 < 5 ) ) {

        rgb1.r = x;
        rgb1.g = 0.0;
        rgb1.b = chroma;

    } else if ( ( 5 <= h1 ) && ( h1 < 6 ) ) {

        rgb1.r = chroma;
        rgb1.g = 0;
        rgb1.b = x;

    } else {

        rgb1.r = 0.0;
        rgb1.g = 0.0;
        rgb1.b = 0.0;

    }

    float m = p_lightness - 0.5 * chroma;

    rgbResult.r = rgb1.r + m;
    rgbResult.g = rgb1.g + m;
    rgbResult.b = rgb1.b + m;

    return rgbResult;
	}

	/*
	Name:	GetRandomHue
	Desc:	Returns a random number in the range 0-359, to represent a random hue in the HSL table.
	Args:	None
	Rtrn:	None
	*/
	int GetRandomHue()
	{
		//srand(time(0));
		return rand() * 359;
	}

	/*
	Name:	HueToRGB
	Desc:	given a hue in the form of an int, it will return a sf::Color with that hue, with full saturation and meduim
			lightness.
	Args:	p_hue,	the number representing the hue you want.
	Rtrn:	the sf::Color of the hue you gave it.
	*/
	sf::Color HueToRGB(int p_hue)
	{
		ColorUtil::RGB color = HSLtoRGB(p_hue, 1, 0.5);
		sf::Color temp(color.r*255, color.g*255, color.b*255, 255);
		return temp;
	}
}
