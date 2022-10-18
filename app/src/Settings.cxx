#include <iostream>

#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/trivial.hpp>

#include <Settings.h>

Settings::Settings(int frequency) : mFrequency(frequency) { LogSettings(); }

int Settings::Frequency() const { return mFrequency; }

void Settings::LogSettings() {
  BOOST_LOG_FUNCTION();

  BOOST_LOG_TRIVIAL(info) << "### Settings";
  BOOST_LOG_TRIVIAL(info) << "Frequency: " << mFrequency << "Hz";
}
