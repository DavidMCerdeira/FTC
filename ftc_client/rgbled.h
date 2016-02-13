#ifndef RGBLED_H
#define RGBLED_H

#define RED    0
#define GREEN  1
#define BLUE   2
#define WHITE  3
#define YELLOW 4

class RGBLed
{
    int currentColor;

public:
    RGBLed();
    ~RGBLed();

    void setColor(int newColor);
    void blinkAndChange(int newColor);

    const static int STAND_BY  = YELLOW;
    const static int USR_DETCD = BLUE;
    const static int USR_VALID = GREEN;
    const static int USR_UNKWN = RED;
    const static int USR_LEFT  = WHITE;
};

#endif // RGBLED_H
