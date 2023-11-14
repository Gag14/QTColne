#include <iostream>
#include "window.h"
#include "color.h"

#include <thread>
#include <chrono>

void sleep(int seconds)
{
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
}
int main()
 {
//   QTC::Color c;
//   c.setAsRed();
//   QTC::QWindow x("Title", c);
//   sleep(7);
  QTC::QWindow w;
  // QTC::QWindow* t = new QTC::QWindow();
  sleep(1);
  w.close();
  sleep(4);
  w.open();
  w.resize(200, 300);
  sleep(4);
  // w.minimize();
  // sleep(4);
  // w.restore();
  // sleep(1);
  w.MoveWindow(500, 0);
  sleep(1);
  w.MoveWindow(0, 500);
  sleep(1);
  w.MoveWindow(-500, 0);
  sleep(1);
  w.MoveWindow(0, 500);
  sleep(1);
  w.maximize();
  w.setBackgroundColor("red");
  std::cout << "Now red\n";
  sleep(2);
  w.setBackgroundColor("green");
  std::cout << "Now green\n";
  sleep(2);
  w.setBackgroundColor("blue");
  std::cout << "Now green\n";
  sleep(2);
  w.setTitle("Window m");
  QTC::Color c(65000, 0, 0);
  c.setAsRed();
 // w.setTitleColor(c);
  sleep(2);
  w.setBackgroundColor("black");
  // w.showMessage("BYE", 100, 100);
  //w.showMessage("Hello, X11!", 50, 50, "fixed", 70);
  sleep(5);
}