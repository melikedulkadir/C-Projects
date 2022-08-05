//
// Created by Melike on 26.11.2021.
//

#ifndef ASSIG2_EMPLOYEE_H
#define ASSIG2_EMPLOYEE_H

#include <string>
#include "Date.h"

using namespace std;

class Employee {
private:
    int employee_number = 0;
    int employee_type; // 0 -> temp, 1 -> perm
    string name;
    string surname;
    string title;
    float salary_coefficient;
    Date date_of_birth;
    Date date_of_appointment;
    int length_of_service = 0;

public:
    Employee(int employeeNumber, int employeeType, string &name, string &surname,
             string &title, float salaryCoefficient, Date &dateOfBirth, Date &dateOfAppointment)
            : employee_number(employeeNumber), employee_type(employeeType), name(name), surname(surname), title(title),
              salary_coefficient(salaryCoefficient), date_of_birth(dateOfBirth),
              date_of_appointment(dateOfAppointment) {}

    Employee(int employeeNumber, int employeeType, string &name, string &surname,
             string &title, float salaryCoefficient, Date &dateOfBirth, Date &dateOfAppointment,
             int lengthOfService) : employee_number(employeeNumber), employee_type(employeeType),
                                    name(name), surname(surname), title(title),
                                    salary_coefficient(salaryCoefficient), date_of_birth(dateOfBirth),
                                    date_of_appointment(dateOfAppointment),
                                    length_of_service(lengthOfService) {}

    Employee() {}
    friend ostream& operator<<(ostream &output,const Employee& employee);

public:
   int getEmployeeNumber() const{
    return employee_number;
}

void setEmployeeNumber(int employeeNumber){
    employee_number = employeeNumber;
}

int getEmployeeType() const{
    return employee_type;
}

void setEmployeeType(int employeeType){
    employee_type = employeeType;
}

string getName() const{
    return name;
}

void setName(const string &name){
    Employee::name = name;
}

string getSurname() const{
    return surname;
}

void setSurname(const string &surname){
    Employee::surname = surname;
}

string getTitle() const{
    return title;
}

void setTitle(const string &title){
    Employee::title = title;
}

float getSalaryCoefficient() const{
    return salary_coefficient;
}

void setSalaryCoefficient(float salaryCoefficient){
    salary_coefficient = salaryCoefficient;
}

Date getDateOfBirth() const{
    return date_of_birth;
}

void setDateOfBirth(const Date &dateOfBirth){
    date_of_birth = dateOfBirth;
}

Date getDateOfAppointment() const{
    return date_of_appointment;
}

void setDateOfAppointment(const Date &dateOfAppointment){
    date_of_appointment = dateOfAppointment;
}

int getLengthOfService() const{
    return length_of_service;
}

void setLengthOfService(int lengthOfService){
    length_of_service = lengthOfService;
}
// appointment date comparer function
bool compareByAppointment(Employee* emp1, Employee* emp2)
    {
        return emp1->getDateOfAppointment() < emp2->getDateOfAppointment();
    }

};
// overload of << operator for employee toString
ostream& operator<<(ostream &output,const Employee& employee) {
           output << "Employee number: " << employee.getEmployeeNumber() << endl 
           <<"Employee type: " << employee.getEmployeeType() << endl 
           <<"Employee name: " << employee.getName() << endl 
           <<"Employee surname: " << employee.getSurname() << endl 
           <<"Employee title: " << employee.getTitle() << endl 
           <<"Employee salary coefficient: "<<employee.getSalaryCoefficient()<< endl 
           <<"Employee date of birth: " << employee.getDateOfBirth() << endl 
           <<"Employee date of appointment: " << employee.getDateOfAppointment() << endl 
           <<"Employee length of service: " << employee.getLengthOfService() << endl;
    return output;
}

#endif //ASSIG2_EMPLOYEE_H
