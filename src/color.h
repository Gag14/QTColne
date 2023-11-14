#ifndef __COLOR__
#define __COLOR__

#include <iostream>
#include <string>

namespace QTC
{
    class Color
    {
    public:
        // Constructors and Destructor
        Color();  // Default constructor (sets white as default)
        Color(unsigned int red, unsigned int green, unsigned int blue);  // Constructor with RGB values
        ~Color();  // Destructor

        // Getters
        unsigned int getRed() const;  // Get the red component
        unsigned int getGreen() const;  // Get the green component
        unsigned int getBlue() const;  // Get the blue component

        // Setters
        void setRed(const unsigned int red);  // Set the red component
        void setGreen(const unsigned int green);  // Set the green component
        void setBlue(const unsigned int blue);  // Set the blue component

        // Exact color setters
        void setAsWhite();  // Set the color as white
        void setAsBlack();  // Set the color as black
        void setAsRed();  // Set the color as red
        void setAsGreen();  // Set the color as green
        void setAsBlue();  // Set the color as blue

    private:
        unsigned int red_;  // Red component of the color
        unsigned int green_;  // Green component of the color
        unsigned int blue_;  // Blue component of the color
    };
}  // namespace QTC

#endif
