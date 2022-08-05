//
// Created by Melike on 26.11.2021.
//

#ifndef ASSIG2_PERMANENTEMPLOYEE_H
#define ASSIG2_PERMANENTEMPLOYEE_H


class PermanentEmployee: public Employee{
    //overridden constructors
public:
    PermanentEmployee(int employeeNumber, int employeeType, string &name,string &surname, string &title, float salaryCoefficient,Date &dateOfBirth, Date &dateOfAppointment)
            : Employee(employeeNumber, employeeType, name, surname, title,salaryCoefficient, dateOfBirth, dateOfAppointment) {};

    PermanentEmployee(int employeeNumber, int employeeType, string &name,string &surname, string &title, float salaryCoefficient,Date &dateOfBirth, Date &dateOfAppointment, int lengthOfService)
            : Employee(employeeNumber, employeeType, name, surname,title,salaryCoefficient, dateOfBirth, dateOfAppointment, lengthOfService) {

    };

    PermanentEmployee() = default;

};


#endif //ASSIG2_PERMANENTEMPLOYEE_H
