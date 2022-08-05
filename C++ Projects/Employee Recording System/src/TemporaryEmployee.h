//
// Created by Melike on 26.11.2021.
//

#ifndef ASSIG2_TEMPORARYEMPLOYEE_H
#define ASSIG2_TEMPORARYEMPLOYEE_H


#include "Employee.h"

using namespace std;

class TemporaryEmployee : public Employee {
    //overridden constructors
public:
    TemporaryEmployee(int employeeNumber, int employeeType, string &name,
                      string &surname, string &title, float salaryCoefficient,
                      Date &dateOfBirth, Date &dateOfAppointment)
                      : Employee(employeeNumber,employeeType,name, surname,title,salaryCoefficient,dateOfBirth,dateOfAppointment) {}


    TemporaryEmployee(int employeeNumber, int employeeType, string &name, string &surname,
                      string &title, float salaryCoefficient, Date &dateOfBirth, Date &dateOfAppointment,int lengthOfService)
            : Employee(employeeNumber, employeeType, name, surname,title,salaryCoefficient, dateOfBirth, dateOfAppointment, lengthOfService){};

    TemporaryEmployee() = default;



};



#endif //ASSIG2_TEMPORARYEMPLOYEE_H
