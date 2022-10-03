#include <boost/log/expressions/formatters/named_scope.hpp>
#include <csignal>
#include <iostream>

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/message.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/value_semantic.hpp>
#include <boost/program_options/variables_map.hpp>

#include <App.h>

namespace po = boost::program_options;
namespace logging = boost::log;

App app;

static int doInitialSetup = 0;

void signal_handler(int s) { app.Shutdown(); }

void InitLogging(bool verbose) {
  logging::add_console_log(
      std::clog,
      logging::keywords::format =
          (logging::expressions::stream
           << "["
           << logging::expressions::format_date_time<boost::posix_time::ptime>(
                  "TimeStamp", "%Y-%m-%d %H:%M:%S")
           << "]["
           << logging::expressions::format_named_scope(
                  "Scope", logging::keywords::format = "%c")
           << "]"
           << "[" << logging::trivial::severity << "] "
           << logging::expressions::smessage));

  logging::add_common_attributes();
  logging::core::get()->add_global_attribute(
      "Scope", logging::attributes::named_scope());

  BOOST_LOG_FUNCTION();

  if (!verbose) {
    logging::core::get()->set_filter(logging::trivial::severity >=
                                     logging::trivial::info);
  } else {
    BOOST_LOG_TRIVIAL(info) << "Verbose logging enabled";
  }
}

int main(int argc, char **argv) {
  signal(SIGINT, signal_handler);

  po::options_description desc("Allowed options");
  desc.add_options()("help,h", "produce help message")(
      "setup,s", po::bool_switch(),
      "run initial setup")("verbose,v", po::bool_switch(), "print debug info");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  try {
    InitLogging(vm["verbose"].as<bool>());

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
