#include "rgbled.h"

RGBLed::RGBLed()
{

}

RGBLed::~RGBLed()
{

}

void RGBLed::setColor(int newColor)
{
    currentColor = newColor;
}

void RGBLed::blinkAndChange(int newColor)
{
    currentColor = newColor;
}
