#include <csignal>
#include <iostream>

#include <App.h>

App app;

void signal_handler(int s) { app.Shutdown(); }

int main() {
  signal(SIGINT, signal_handler);

  try {
    app.Init();
    app.NormalOperation();
  } catch (const std::exception &e) {
    std::cout << "An exception was caught: " << e.what() << std::endl;
  }

  app.Shutdown();
  return 0;
}
