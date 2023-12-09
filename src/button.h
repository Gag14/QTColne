#ifndef __BUTTON__
#define __BUTTON__

#include "window.h"
#include "color.h" // This is a header for Color class

#include <iostream>
#include <string>
#include <X11/Xft/Xft.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <functional>
#include <utility>
#include <thread>

namespace QTC
{
    class Button
    {
    public:
        // Constructors and Destuctor
        Button() = delete;       // No Constuctor without parent window
        Button(QWindow *parent); // Defoult in our case
        Button(QWindow *parent, int width, int height);
        Button(QWindow *parent, int Position_X, int Position_Y, const std::string &label);
        Button(QWindow *parent, const Color &buttonColor, const std::string &label);
        ~Button();

        // Main functions
        void setColor(const Color &color);
        void setLabel(const std::string &label);
        void resize(int width, int height);
        void move(int X, int Y);
        void setBorder(int s);
        void serBorderColor(const Color& color);
        template <typename Function, typename... Args>
        void setClickFunction(Function&& func, Args&&... args);
        void handleClick(XEvent &event);
        bool isEventRelated(const XEvent &event);
        void draw();
        void click(int MouseX, int MouseY);

    private:
        void createButton();

        int x_;
        int y_;
        int width_;
        int height_;
        int borderWidth_; // Border width of the window
        int borderHeight_;
        XftFont *font_;
        XftDraw *draw_;
        XftColor textColor_;
        Window buttonWindow_;
        QWindow *parent_;
        Display *display_;
        unsigned long borderColor_; // Border color of the window
        unsigned long backgroundColor_;
        std::thread eventLoopThread_;
        std::string label_;
        std::function<void(QWindow *w)> clickFunction_;
    };
}
#include "button.cpp"
#endif