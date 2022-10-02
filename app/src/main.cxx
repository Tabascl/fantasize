#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/value_semantic.hpp>
#include <boost/program_options/variables_map.hpp>
#include <csignal>
#include <iostream>

#include <boost/program_options.hpp>

#include <App.h>

namespace po = boost::program_options;

App app;

static int doInitialSetup = 0;

void signal_handler(int s) { app.Shutdown(); }

int main(int argc, char **argv) {
  signal(SIGINT, signal_handler);

  po::options_description desc("Allowed options");
  desc.add_options()("help", "produce help message")("setup", po::bool_switch(),
                                                     "run initial setup");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  try {
    if (vm.count("help")) {
      std::cout << desc << "\n";
      return 0;
    }

    if (vm.count("setup") && vm["setup"].as<bool>()) {
      app.InitialSetup();
    } else {
      app.Init();
      app.NormalOperation();
    }
  } catch (const std::exception &e) {
    std::cout << "An exception was caught: " << e.what() << std::endl;
  }

  app.Shutdown();
  return 0;
}
