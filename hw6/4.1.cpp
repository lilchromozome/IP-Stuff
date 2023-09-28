#include "appointment.h"
#include <iostream>

// Print to std::cout in form "hour:minute: description"
void Appointment::print() const{
    std::cout << this->get_start_hour() << ":" << this->get_start_minute() << ": " << this->get_description() << '\n';
}
    

// Return negative value if left appointment starts earlier
// than right appointment, positive if left appointment starts later
// than right appointment, 0 if they start at the same time.
int compare_appt(const Appointment &left, const Appointment &right){
    if(left.get_start_hour() !=  right.get_start_hour())
        return left.get_start_hour() - right.get_start_hour();
    if(left.get_start_minute() != right.get_start_minute())
        return left.get_start_minute() - right.get_start_minute();
    return 0;
}

int main(){
    Appointment a1("ballllllllls", 6, 235);
    Appointment a2("ballllllllls", 6, 23);

    a1.print();
    a2.print();

    std::cout << compare_appt(a1, a2) << '\n';
}