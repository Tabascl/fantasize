#ifndef SETTINGS_H_
#define SETTINGS_H_

#define FREQUENCY_DEFAULT 1

class Settings {
public:
  Settings(int frequency);

  int Frequency() const;

private:
  void LogSettings();
  int mFrequency;
};

#endif // SETTINGS_H_
