#include <iostream>
#include "window.h"
#include "color.h"
#include "button.h"

#include <thread>
#include <chrono>

void green(QTC::QWindow *w)
{
  std::cout << "green" << std::endl;
  w->setBackgroundColor("green");
  // w->setTitle("Artur");
}

void red(QTC::QWindow *w)
{
  std::cout << "red" << std::endl;
  w->setBackgroundColor("red");
  // w->setTitle("");
}

int main()
{

  QTC::QWindow w;
  QTC::QWindow *wp = &w;
  QTC::Button b(wp, 100, 0, "red");
  QTC::Color c;
  c.setAsRed();
  b.setColor(c);
  b.setClickFunction(&red, wp);
  QTC::Button b2(wp, 0, 0, "green");
  c.setAsGreen();
  b2.setColor(c);
  c.setAsGreen();
  b.serBorderColor(c);
  b2.setClickFunction(&green, wp);
  wp->open();

  XEvent event;
  while (true)
  {
    XNextEvent(wp->getDisplay(), &event);
    b.draw();
    b2.draw();

    b.handleClick(event);
    b2.handleClick(event);
  }
}