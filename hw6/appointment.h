// appointment.h

#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <iostream>

class Appointment {
private:
  std::string description;
  int start_hour, start_minute;

public:
  Appointment(const std::string &desc, int start_hr, int start_min)
    : description(desc), start_hour(start_hr), start_minute(start_min)
  {
  }

  std::string get_description() const { return description; }
  int get_start_hour() const { return start_hour; }
  int get_start_minute() const { return start_minute; }

  // Print to std::cout in form "hour:minute: description"
  void print() const;
};

// Return negative value if left appointment starts earlier
// than right appointment, positive if left appointment starts later
// than right appointment, 0 if they start at the same time.
int compare_appt(const Appointment &left, const Appointment &right);

#endif // APPOINTMENT_H