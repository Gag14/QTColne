#include "color.h"

unsigned int max = 65535;
namespace QTC
{
    // Constructors and destructor
    Color::Color() : red_(0), green_(0), blue_(0) {}
    Color::Color(unsigned int red, unsigned int green, unsigned int blue) : red_(red), green_(green), blue_(blue) {}
    Color::~Color() {}

    // Getters
    unsigned int Color::getRed() const { return red_; }
    unsigned int Color::getGreen() const { return green_; }
    unsigned int Color::getBlue() const { return blue_; }

    // Setters
    void Color::setRed(unsigned int red) { red_ = red; }
    void Color::setGreen(unsigned int green) { green_ = green; }
    void Color::setBlue(unsigned int blue) { blue_ = blue; }

    // Exact Color setters
    void Color::setAsWhite()
    {
        red_ = 0;
        green_ = 0;
        blue_ = 0;
    }
    void Color::setAsRed()
    {
        red_ = max;
        green_ = 0;
        blue_ = 0;
    }
    void Color::setAsGreen()
    {
        red_ = 0;
        green_ = max;
        blue_ = 0;
    }
    void Color::setAsBlue()
    {
        red_ = 0;
        green_ = 0;
        blue_ = max;
    }
    void Color::setAsBlack()
    {
        red_ = max;
        green_ = max;
        blue_ = max;
    }
}