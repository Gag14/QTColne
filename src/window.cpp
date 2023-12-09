#include "window.h"
#include "color.h"

#include <iostream>
#include <string>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdexcept>

namespace QTC
{
    // Default Constructor
    QWindow::QWindow() : X_(100), Y_(100), width_(900), height_(700), borderWidth_(100)
    {
        // Open the X display connection
        display_ = XOpenDisplay(nullptr);

        // Check if the display connection is successful
        if (!display_)
        {
            std::cout << "!displey_\n";

            // If unable to open display, throw an exception
            throw std::runtime_error("Unable to open a window");
        }

        // Set default border and background colors
        borderColor_ = WhitePixel(display_, DefaultScreen(display_));
        backgroundColor_ = BlackPixel(display_, DefaultScreen(display_));

        // Create a simple window with specified dimensions and properties
        window_ = XCreateSimpleWindow(display_, DefaultRootWindow(display_),
                                      X_, Y_, width_, height_, borderWidth_, borderColor_, backgroundColor_);

        // Check if window creation is successful
        if (!window_)
        {
            std::cout << "!window_\n";

            // If window creation fails, release display resource
            XCloseDisplay(display_);
            throw std::runtime_error("Unable to create window");
        }

        std::cout << "!before map\n";

        // Map the window to the screen
        XMapWindow(display_, window_);
        std::cout << "!after map\n";

        // Flush the X server connection
        XFlush(display_);
        std::cout << "!after flush\n";
        try {
        eventLoopThread_ = std::thread([this]()
                                       {
        XEvent event;
        std::cout << "from thread window" << std::endl;
        while (true)
        {
            // XNextEvent(display_, &event);
            // draw();
            // handleClick(event);
        } });
        } catch (const std::exception& e) 
        {
            std::cerr << e.what() << std::endl;
        }
    }

    // Constructor with title
    QWindow::QWindow(const std::string &title) : X_(100), Y_(100), width_(900), height_(700), borderWidth_(1)
    {
        // Open the X display connection
        display_ = XOpenDisplay(nullptr);

        // Check if the display connection is successful
        if (!display_)
        {
            std::cout << "!displey_\n";

            // If unable to open display, throw an exception
            throw std::runtime_error("Unable to open a window");
        }

        // Set default border and background colors
        borderColor_ = WhitePixel(display_, DefaultScreen(display_));
        backgroundColor_ = BlackPixel(display_, DefaultScreen(display_));

        // Create a simple window with specified dimensions and properties
        window_ = XCreateSimpleWindow(display_, DefaultRootWindow(display_),
                                      X_, Y_, width_, height_, borderWidth_, borderColor_, backgroundColor_);

        // Check if window creation is successful
        if (!window_)
        {
            // If window creation fails, release display resource
            XCloseDisplay(display_);
            throw std::runtime_error("Unable to create window");
        }

        // Set standard properties for the window, including title
        XSetStandardProperties(display_, window_, title.c_str(), title.c_str(), None, NULL, 0, NULL);

        // Flush the X server connection
        XFlush(display_);
    }

    // Constructor with title and title color
    QWindow::QWindow(const std::string &title, const Color &titleColor) : X_(100), Y_(100), width_(900), height_(700), borderWidth_(1)
    {
        // Open the X display connection
        display_ = XOpenDisplay(nullptr);

        // Check if the display connection is successful
        if (!display_)
        {
            std::cout << "!displey_\n";

            // If unable to open display, throw an exception
            throw std::runtime_error("Unable to open a window");
        }

        // Set default border and background colors
        borderColor_ = WhitePixel(display_, DefaultScreen(display_));
        backgroundColor_ = BlackPixel(display_, DefaultScreen(display_));

        // Create a simple window with specified dimensions and properties
        window_ = XCreateSimpleWindow(display_, DefaultRootWindow(display_),
                                      X_, Y_, width_, height_, borderWidth_, borderColor_, backgroundColor_);

        // Check if window creation is successful
        if (!window_)
        {
            // If window creation fails, release display resource
            XCloseDisplay(display_);
            throw std::runtime_error("Unable to create window");
        }

        // Allocate color for the title
        XColor xColor;
        xColor.red = titleColor.getRed();
        xColor.green = titleColor.getGreen();
        xColor.blue = titleColor.getBlue();
        XAllocColor(display_, DefaultColormap(display_, DefaultScreen(display_)), &xColor);
        unsigned int color = xColor.pixel;

        // Set window properties, including title, color, and input events
        XSelectInput(display_, window_, ExposureMask | KeyPressMask);
        XSetStandardProperties(display_, window_, title.c_str(), title.c_str(), None, nullptr, 0, nullptr);

        // Map the window to the screen
        XMapWindow(display_, window_);

        // Flush the X server connection
        XFlush(display_);
    }
    // Constructor with width, height, X, Y, Background color, title
    QWindow::QWindow(int width, int height, int Position_X, int Position_Y, Color &background, const std::string &title) : X_(Position_X), Y_(Position_Y), width_(width), height_(height), borderWidth_(1)
    {
        // Open the X display connection
        display_ = XOpenDisplay(nullptr);
        if (!display_)
        {
            std::cout << "!displey_\n";

            // If unable to open display, throw an exception
            throw std::runtime_error("Unable to open a window");
        }

        // Set default border color
        borderColor_ = WhitePixel(display_, DefaultScreen(display_));
        backgroundColor_ = BlackPixel(display_, DefaultScreen(display_));

        // Create a simple window with specified dimensions, properties, and background color
        window_ = XCreateSimpleWindow(display_, DefaultRootWindow(display_),
                                      X_, Y_, width_, height_, borderWidth_, borderColor_, backgroundColor_);

        // Check if window creation is successful
        if (!window_)
        {
            // If window creation fails, release display resource
            XCloseDisplay(display_);
            throw std::runtime_error("Unable to create window");
        }

        // Map the window to the screen, resize it, move it to specified coordinates, set standard properties, and flush
        XMapWindow(display_, window_);
        if (window_)
        {
            XResizeWindow(display_, window_, width, height);
        }
        XMoveWindow(display_, window_, X_, Y_);
        XSetStandardProperties(display_, window_, title.c_str(), title.c_str(), None, NULL, 0, NULL);
        XColor color;
        color.red = background.getRed();
        color.green = background.getGreen();
        color.blue = background.getBlue();
        backgroundColor_ = color.pixel;
        XSetWindowBackground(display_, window_, backgroundColor_); // Function which changes the background color
        XClearWindow(display_, window_);
        XFlush(display_);
    }
    // Constructor with X, Y coordinates
    QWindow::QWindow(int X, int Y) : X_(100), Y_(100), width_(900), height_(700), borderWidth_(1)
    {
        // Open X display
        display_ = XOpenDisplay(nullptr);
        if (!display_)
        {
            std::cout << "!display_\n";

            throw std::runtime_error("Unable to open a window");
        }

        // Set border and background colors
        borderColor_ = WhitePixel(display_, DefaultScreen(display_));
        backgroundColor_ = BlackPixel(display_, DefaultScreen(display_));

        // Create a simple window
        window_ = XCreateSimpleWindow(display_, DefaultRootWindow(display_),
                                      X_, Y_, width_, height_, borderWidth_, borderColor_, backgroundColor_);

        if (!window_)
        {
            // If window creation fails, release display resource
            XCloseDisplay(display_);
            throw std::runtime_error("Unable to create window");
        }

        // Map the window and move it to the specified position
        XMapWindow(display_, window_);
        XFlush(display_);
        XMoveWindow(display_, window_, X, Y);
        XFlush(display_);
    }

    // Constructor with background color and title
    QWindow::QWindow(Color &background, const std::string &title) : X_(100), Y_(100), width_(900), height_(700), borderWidth_(1)
    {
        // Open X display
        display_ = XOpenDisplay(nullptr);
        if (!display_)
        {
            std::cout << "!display_\n";

            throw std::runtime_error("Unable to open a window");
        }

        // Set border and background colors
        borderColor_ = WhitePixel(display_, DefaultScreen(display_));
        backgroundColor_ = BlackPixel(display_, DefaultScreen(display_));

        // Create a simple window
        window_ = XCreateSimpleWindow(display_, DefaultRootWindow(display_),
                                      X_, Y_, width_, height_, borderWidth_, borderColor_, backgroundColor_);

        if (!window_)
        {
            // If window creation fails, release display resource
            XCloseDisplay(display_);
            throw std::runtime_error("Unable to create window");
        }

        // Set window properties, background color, and title
        XSetStandardProperties(display_, window_, title.c_str(), title.c_str(), None, NULL, 0, NULL);
        XColor color;
        color.red = background.getRed();
        color.green = background.getGreen();
        color.blue = background.getBlue();
        backgroundColor_ = color.pixel;
        XSetWindowBackground(display_, window_, backgroundColor_); // Function which changes the background color
        XClearWindow(display_, window_);
        XSetStandardProperties(display_, window_, title.c_str(), title.c_str(), None, NULL, 0, NULL);
        XFlush(display_);
    }
    void QWindow::redraw()
    {
        // Put your drawing logic here
        // For example, you can clear the window and draw a rectangle
        XClearWindow(display_, window_);

        // Draw a rectangle
        XDrawRectangle(display_, window_, DefaultGC(display_, DefaultScreen(display_)), 50, 50, 100, 100);

        // Flush the changes to the display
        XFlush(display_);
    }
    void QWindow::handleEvent(XEvent &event)
    {
        switch (event.type)
        {
        case Expose:
            // Handle expose event, e.g., redraw the window
            redraw();
            break;
        case KeyPress:
            // Handle key press event, if needed
            break;
            // Add more cases to handle other events as necessary
        }
    }

    // Destructor
    QWindow::~QWindow()
    {
        close();
        if (display_)
        {
            // XFreeGC(display_, gc_);
            XCloseDisplay(display_);
        }
        if (eventLoopThread_.joinable())
            eventLoopThread_.join();
  
    }
    // Main Interface Functions

    // Open the window
    void QWindow::open()
    {
        if (window_)
        {
            // Map the window to the screen and flush the display
            XMapWindow(display_, window_);
            XFlush(display_);
        }
    }

    // Close the window
    void QWindow::close()
    {
        if (window_)
        {
            // Unmap the window from the screen and flush the display
            XUnmapWindow(display_, window_);
            XFlush(display_);
        }
    }

    // Set the title of the window
    void QWindow::setTitle(const std::string &title)
    {
        if (window_)
        {
            // Set standard properties of the window with the specified title and flush the display
            XSetStandardProperties(display_, window_, title.c_str(), title.c_str(), None, NULL, 0, NULL);
            XFlush(display_);
        }
    }

    // Move the window to the specified coordinates
    void QWindow::MoveWindow(int to_left, int to_bottom)
    {
        if (window_)
        {
            // Map the window to the screen, move it to the specified coordinates, and flush the display
            XMapWindow(display_, window_);
            XMoveWindow(display_, window_, to_left, to_bottom);
            XFlush(display_);
        }
    }
    // Resize the window to the specified width and height
    void QWindow::resize(int width, int height)
    {
        if (window_)
        {
            // Resize the window and flush the display
            XResizeWindow(display_, window_, width, height);
            XFlush(display_);
        }
    }

    // Set the background color of the window using a Color object
    void QWindow::setBackgroundColor(Color &background)
    {
        if (window_)
        {
            // Extract the RGB values from the Color object
            XColor color;
            color.red = background.getRed();
            color.green = background.getGreen();
            color.blue = background.getBlue();

            // Get the pixel value for the specified color
            backgroundColor_ = color.pixel;

            // Set the window background color and clear the window
            XSetWindowBackground(display_, window_, backgroundColor_);
            XClearWindow(display_, window_);

            // Flush the display
            XFlush(display_);
        }
    }

    // Set the background color of the window using a color name
    void QWindow::setBackgroundColor(const std::string &backgroundcolor)
    {
        if (!display_)
        {
            std::cout << "Nullll" << std::endl;
            throw std::runtime_error("Display NULL");
        }
        // Clear the window
        XClearWindow(display_, window_);

        // Create a Color object based on the provided color name
        Color background;
        if (backgroundcolor == "red")
        {
            background.setAsRed();
        }
        else if (backgroundcolor == "green")
        {
            background.setAsGreen();
        }
        else if (backgroundcolor == "blue")
        {
            background.setAsBlue();
        }
        else if (backgroundcolor == "black")
        {
            background.setAsBlack();
        }
        else if (backgroundcolor == "white")
        {
            background.setAsWhite();
        }
        else
        {
            // If no matching color, set it to white and inform the user
            std::cout << "No matching Color. Color will be white" << std::endl;
            background.setAsWhite();
        }

        if (window_)
        {
            // Clear the window again
            XClearWindow(display_, window_);

            // Get the RGB values from the Color object
            XColor xColor;
            xColor.red = background.getRed();
            xColor.green = background.getGreen();
            xColor.blue = background.getBlue();

            // Allocate the color and get the pixel value
            XAllocColor(display_, DefaultColormap(display_, DefaultScreen(display_)), &xColor);
            backgroundColor_ = xColor.pixel;

            // Set the window background color and clear the window
            XSetWindowBackground(display_, window_, backgroundColor_);
            XClearWindow(display_, window_);

            // Flush the display
            XFlush(display_);
        }
    }
    // Maximize the window to cover the entire screen
    void QWindow::maximize()
    {
        if (window_)
        {
            // Get screen dimensions
            int screenWidth = WidthOfScreen(DefaultScreenOfDisplay(display_));
            int screenHeight = HeightOfScreen(DefaultScreenOfDisplay(display_));

            // Resize the window to cover the entire screen
            resize(screenWidth, screenHeight);
        }
    }

    // Minimize the window
    void QWindow::minimize()
    {
        if (window_)
        {
            // Iconify (minimize) the window and flush the display
            XIconifyWindow(display_, window_, DefaultScreen(display_));
            XFlush(display_);
        }
    }

    // Getter function to check if the window is open
    bool QWindow::isOpen()
    {
        return window_;
    }

    // Restore the window to its previous state
    void QWindow::restore()
    {
        if (window_)
        {
            // Map the window, reset the screen saver, map it raised, and flush the display
            XMapWindow(display_, window_);
            XResetScreenSaver(display_);
            XMapRaised(display_, window_);
            XFlush(display_);
        }
    }
    // Getter function to retrieve the window title
    std::string &QWindow::getTitle() const
    {
        // Note: You should return the title here, but the function is currently returning void.
        // You need to modify the return type and implementation to correctly return the title.
        // Example: return title_;
    }

    // Show a message at the specified position (x, y) using the default font and size
    void QWindow::showMessage(const std::string &message, int x, int y)
    {
        if (window_)
        {
            // Draw the text at the specified position using the default font and size
            XDrawString(display_, window_, DefaultGC(display_, DefaultScreen(display_)), x, y, message.c_str(), message.length());
            XFlush(display_);
        }
    }

    // Show a message at the specified position (x, y) using the specified font
    void QWindow::showMessage(const std::string &message, int x, int y, const std::string &fontName)
    {
        if (window_)
        {
            // Load the specified font
            XFontStruct *fontInfo = XLoadQueryFont(display_, fontName.c_str());
            if (!fontInfo)
            {
                // Handle font loading error
                std::cerr << "Failed to load font: " << fontName << std::endl;
                return;
            }

            // Set the specified font
            XSetFont(display_, DefaultGC(display_, DefaultScreen(display_)), fontInfo->fid);

            // Draw the text at the specified position using the specified font
            XDrawString(display_, window_, DefaultGC(display_, DefaultScreen(display_)), x, y, message.c_str(), message.length());

            // Free the font structure
            XFreeFontInfo(nullptr, fontInfo, 1);

            XFlush(display_);
        }
    }

    // Show a message at the specified position (x, y) using the specified font and size
    void QWindow::showMessage(const std::string &message, int x, int y, const std::string &fontName, int fontSize)
    {
        if (window_)
        {
            // Load the specified font
            XFontStruct *fontInfo = XLoadQueryFont(display_, fontName.c_str());
            if (fontInfo)
            {
                // Scale the font size
                int scaledFontSize = (int)(fontSize * (double)fontInfo->ascent / fontInfo->max_bounds.ascent);

                // Set the font for the graphics context
                GC gc = XCreateGC(display_, window_, 0, nullptr);
                XSetFont(display_, gc, fontInfo->fid);

                // Draw the text at the specified position using the specified font and size
                XDrawString(display_, window_, gc, x, y, message.c_str(), message.length());

                // Free the font structure
                XFreeFontInfo(nullptr, fontInfo, 1);
                XFreeGC(display_, gc);

                XFlush(display_);
            }
            else
            {
                std::cerr << "Failed to load font: " << fontName << std::endl;
            }
        }
    }
    Window QTC::QWindow::getWindow() { return window_; }
    Display *QTC::QWindow::getDisplay() { return display_; }
}