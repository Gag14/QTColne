#include <iostream>
#include <string>
#include <functional>
#include <exception>
#include <utility>
#include <X11/Xft/Xft.h>

#include <X11/Xlib.h>

#include <thread>
#include "button.h"
#include "window.h"
#include "color.h"


namespace QTC
{
    Button::Button(QWindow *main)
        : display_(main->getDisplay()), x_(10), y_(10), width_(100), height_(100), label_("Here")
    {

        if (!display_)
        {
            XCloseDisplay(display_);
            throw std::runtime_error("Button Received Null Display");
        }

        buttonWindow_ = XCreateSimpleWindow(display_, main->getWindow(), x_, y_, width_, height_, 1, BlackPixel(display_, 0), WhitePixel(display_, 0));
        if (!buttonWindow_)
        {
            XCloseDisplay(display_);
            throw std::runtime_error("Unable to create button window");
        }
        XSelectInput(display_, buttonWindow_, ExposureMask | ButtonPressMask);
        XMapWindow(display_, buttonWindow_);

        // Load a font for rendering text
        const char *fontName = "Sans:style=Bold";
        int fontSize = 12;
        font_ = XftFontOpenName(display_, DefaultScreen(display_), fontName);
        if (!font_)
        {
            std::cerr << "Failed to open font" << std::endl;
            exit(1);
        }

        draw_ = XftDrawCreate(display_, buttonWindow_, DefaultVisual(display_, DefaultScreen(display_)), DefaultColormap(display_, DefaultScreen(display_)));

        // Set text color
        XRenderColor xColor = {0, 0, 0, 0xffff};
        XftColorAllocValue(display_, DefaultVisual(display_, DefaultScreen(display_)), DefaultColormap(display_, DefaultScreen(display_)), &xColor, &textColor_);
    }

    Button::Button(QWindow *main, int width, int height) : display_(main->getDisplay()), x_(10), y_(10), width_(width), height_(height), label_("Here")
    {

        if (!display_)
        {
            XCloseDisplay(display_);
            throw std::runtime_error("Button Received Null Display");
        }
        buttonWindow_ = XCreateSimpleWindow(display_, main->getWindow(), x_, y_, width_, height_, 1, BlackPixel(display_, 0), WhitePixel(display_, 0));
        if (!buttonWindow_)
        {
            XCloseDisplay(display_);
            throw std::runtime_error("Unable to create button window");
        }
        XSelectInput(display_, buttonWindow_, ExposureMask | ButtonPressMask);
        XMapWindow(display_, buttonWindow_);

        // Load a font for rendering text
        const char *fontName = "Sans:style=Bold";
        int fontSize = 12;
        font_ = XftFontOpenName(display_, DefaultScreen(display_), fontName);
        if (!font_)
        {
            std::cerr << "Failed to open font" << std::endl;
            exit(1);
        }

        draw_ = XftDrawCreate(display_, buttonWindow_, DefaultVisual(display_, DefaultScreen(display_)), DefaultColormap(display_, DefaultScreen(display_)));

        // Set text color
        XRenderColor xColor = {0, 0, 0, 0xffff};
        XftColorAllocValue(display_, DefaultVisual(display_, DefaultScreen(display_)), DefaultColormap(display_, DefaultScreen(display_)), &xColor, &textColor_);
    }
    Button::Button(QWindow *main, int x, int y, const std::string &label) : display_(main->getDisplay()), x_(x), y_(y), width_(100), height_(40), label_(label)
    {

        if (!display_)
        {
            XCloseDisplay(display_);
            throw std::runtime_error("Button Received Null Display");
        }
        buttonWindow_ = XCreateSimpleWindow(display_, main->getWindow(), x_, y_, width_, height_, 1, BlackPixel(display_, 0), WhitePixel(display_, 0));
        if (!buttonWindow_)
        {
            XCloseDisplay(display_);
            throw std::runtime_error("Unable to create button window");
        }
        XSelectInput(display_, buttonWindow_, ExposureMask | ButtonPressMask);
        XMapWindow(display_, buttonWindow_);

        // Load a font for rendering text
        const char *fontName = "Sans:style=Bold";
        int fontSize = 12;
        font_ = XftFontOpenName(display_, DefaultScreen(display_), fontName);
        if (!font_)
        {
            std::cerr << "Failed to open font" << std::endl;
            exit(1);
        }

        draw_ = XftDrawCreate(display_, buttonWindow_, DefaultVisual(display_, DefaultScreen(display_)), DefaultColormap(display_, DefaultScreen(display_)));

        // Set text color
        XRenderColor xColor = {0, 0, 0, 0xffff};
        XftColorAllocValue(display_, DefaultVisual(display_, DefaultScreen(display_)), DefaultColormap(display_, DefaultScreen(display_)), &xColor, &textColor_);
    }
    Button::Button(QWindow *main, const Color &color, const std::string &label)
    {
        if (!display_)
        {
            XCloseDisplay(display_);
            throw std::runtime_error("Button Received Null Display");
        }
        buttonWindow_ = XCreateSimpleWindow(display_, main->getWindow(), x_, y_, width_, height_, 1, BlackPixel(display_, 0), WhitePixel(display_, 0));
        if (!buttonWindow_)
        {
            XCloseDisplay(display_);
            throw std::runtime_error("Unable to create button window");
        }
        XSelectInput(display_, buttonWindow_, ExposureMask | ButtonPressMask);
        XMapWindow(display_, buttonWindow_);

        // Load a font for rendering text
        const char *fontName = "Sans:style=Bold";
        int fontSize = 12;
        font_ = XftFontOpenName(display_, DefaultScreen(display_), fontName);
        if (!font_)
        {
            throw std::runtime_error("Unable to Open Font");
        }

        draw_ = XftDrawCreate(display_, buttonWindow_, DefaultVisual(display_, DefaultScreen(display_)), DefaultColormap(display_, DefaultScreen(display_)));

        // Set text color
        XRenderColor xColor = {0, 0, 0, 0x05478};
        XftColorAllocValue(display_, DefaultVisual(display_, DefaultScreen(display_)), DefaultColormap(display_, DefaultScreen(display_)), &xColor, &textColor_);
    }
    Button::~Button()
    {
        XftDrawDestroy(draw_);
        XftFontClose(display_, font_);
        if (eventLoopThread_.joinable())
            eventLoopThread_.join();
    }

    void Button::setColor(const Color &color)
    {
        XColor xColor;
        xColor.red = color.getRed();
        xColor.green = color.getGreen();
        xColor.blue = color.getBlue();
        XAllocColor(display_, DefaultColormap(display_, DefaultScreen(display_)), &xColor);
        backgroundColor_ = xColor.pixel;
    }
    void Button::setBorder(int s)
    {
        borderHeight_ = s;
        borderWidth_ = s;
    }
    void Button::serBorderColor(const Color &color)
    {
        XColor xColor;
        xColor.red = color.getRed();
        xColor.green = color.getGreen();
        xColor.blue = color.getBlue();
        XAllocColor(display_, DefaultColormap(display_, DefaultScreen(display_)), &xColor);
        borderColor_ = xColor.pixel;
    }
    template <typename Function, typename... Args>
    void Button::setClickFunction(Function &&func, Args &&...args)
    {
        // Capture the arguments within a lambda and store it
        clickFunction_ = std::bind(std::forward<Function>(func), std::forward<Args>(args)...);
    }
    void Button::handleClick(XEvent &event)
    {
        if (event.xbutton.button == Button1)
        {
            if (event.type == ButtonPress && event.xbutton.window == buttonWindow_)
            {
                // Handle the button click event
                std::cout << "Button clicked: " << label_ << std::endl;
                // You can add your custom button click logic here
                clickFunction_(parent_);
            }
        }
    }
    bool Button::isEventRelated(const XEvent &event)
    {
        // Assuming ButtonPress and ButtonRelease events are relevant
        if (event.type == ButtonPress || event.type == ButtonRelease)
        {
            int mouseX = event.xbutton.x;
            int mouseY = event.xbutton.y;
            std::cout << "X : " << mouseX << '\n'
                      << "Y :" << mouseY << std::endl;
            // Check if the event occurred within the button's area
            return (mouseX >= x_ && mouseX <= (x_ + width_) &&
                    mouseY >= y_ && mouseY <= (y_ + height_));
        }

        // Add more conditions if other event types are relevant
        return false;
    }
    void Button::draw()
    {
        XClearWindow(display_, buttonWindow_);

        // Draw the button background
        XSetForeground(display_, DefaultGC(display_, DefaultScreen(display_)), backgroundColor_);
        XFillRectangle(display_, buttonWindow_, DefaultGC(display_, DefaultScreen(display_)), 0, 0, width_, height_);

        // Draw the button border
        XSetForeground(display_, DefaultGC(display_, DefaultScreen(display_)), borderColor_);
        // XSetLineWidth(display_, DefaultGC(display_, DefaultScreen(display_)), borderWidth_);
        for (int i = 0; i < borderWidth_; ++i)
        {
            XDrawRectangle(display_, buttonWindow_, DefaultGC(display_, DefaultScreen(display_)), i, i, width_ - i * 2, height_ - i * 2);
        }
        XftDrawStringUtf8(draw_, &textColor_, font_, 15, 15, reinterpret_cast<const FcChar8 *>(label_.c_str()), label_.length());
    }
} // End of QTC namespace
