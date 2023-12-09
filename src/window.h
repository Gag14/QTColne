#ifndef __QTCWINDOW__
#define __QTCWINDOW__

#include "color.h" // This is a header for Color class

#include <iostream>
#include <string>
#include <thread>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace QTC
{
    class QWindow
    {
    public:
        // Constructors and Destructor
        QWindow();                                                                                                   // Default constructor
        QWindow(const std::string &title);                                                                           // Constructor with title
        QWindow(int Position_X, int Position_Y);                                                                     // Constructor with initial position
        QWindow(Color &background, const std::string &title);                                                        // Constructor with background color and title
        QWindow(const std::string &title, const Color &color);                                                       // Constructor with title and background color
        QWindow(int width, int height, int Position_X, int Position_Y, Color &background, const std::string &title); // Constructor with size, position, background color, and title
        ~QWindow();                                                                                                  // Destructor

        // Main Interface Functions
        void open();  // Open the window
        void close(); // Close the window

        // Modifiers
        void setTitle(const std::string &title);                                                       // Set the window title
        void setBackgroundColor(Color &color);                                                         // Set the background color using a Color object
        void setBackgroundColor(const std::string &colorname);                                         // Set the background color using a color name
        void MoveWindow(int to_right, int to_bottom);                                                  // Move the window to a new position
        void resize(int width, int height);                                                            // Resize the window
        void maximize();                                                                               // Maximize the window
        void minimize();                                                                               // Minimize the window
        void restore();                                                                                // Restore the window to its original state
        void showMessage(const std::string &message, int X, int Y, const std::string &font, int size); // Display a message with specified position, font, and size
        void showMessage(const std::string &message, int X, int Y, const std::string &font);           // Display a message with specified position and font
        void showMessage(const std::string &message, int X, int Y);                                    // Display a message with specified position
        void setTitleColor(const Color &titleColor);                                                   // Set the color of the window title
        void handleEvent(XEvent &event);
        void redraw();

        // Getters
        std::string &getTitle() const; // Get the window title
        bool isOpen();                 // Check if the window is open
        Window getWindow();
        Display *getDisplay();

    private:
        // Helper Functions

        int X_;                         // X-coordinate of the window
        int Y_;                         // Y-coordinate of the window
        int width_;                     // Width of the window
        int height_;                    // Height of the window
        int borderWidth_;               // Border width of the window
        std::thread eventLoopThread_;
        const char *title_;             // Title of the window
        unsigned long borderColor_;     // Border color of the window
        unsigned long backgroundColor_; // Background color of the window
        Window window_;                 // X11 window handle
        Display *display_;              // X11 display handle
    };
} // namespace QTC

#endif
