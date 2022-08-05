#include <iostream>
#include "Date.h"
#include "TemporaryEmployee.h"
#include "PermanentEmployee.h"
#include "Node.h"
#include "CircularArrayLinkedList.h"
#include "DynamicDoubleLinkedList.h"
#include <algorithm>
using namespace std;

// console showing
void showConsol(){
    cout<<"-------------------Employee Recording System-------------------"<<endl;
    cout<<"1) Appointment of a new employee"<<endl;
    cout<<"2) Appointment of a transferred employee"<<endl;
    cout<<"3) Updating the title and salary coefficient of an employee"<<endl;
    cout<<"4) Deletion of an employee"<<endl;
    cout<<"5) Listing the information of an employee"<<endl;
    cout<<"6) Listing employees ordered by employee number"<<endl;
    cout<<"7) Listing employees ordered by appointment day"<<endl;
    cout<<"8) Listing appointed after a certain date"<<endl;
    cout<<"9) Listing employees assigned in a given year"<<endl;
    cout<<"10) Listing employees born before a certain date"<<endl;
    cout<<"11) Listing employees born in a particular month"<<endl;
    cout<<"12) Listing the information of the last assigned employee with a given title"<<endl;
}

int main() {
    string choice;
    CircularArrayLinkedList circularArrayLinkedList;
    DynamicDoubleLinkedList doubleLinkedList;
    bool flag = true; // if flag is false, terminate
    while (flag){
        showConsol();
        cin>>choice;
        //choice 1 and 2
        if(stoi(choice)==1 || stoi(choice)==2){
            string employee_num,employee_type,name,surname,title,salary_coef,date_birth,date_appointment,service_lenght;
            cout<<"Please type the employee number:"<<endl;
            cin>>employee_num;
            if(circularArrayLinkedList.isExist(stoi(employee_num)) || doubleLinkedList.isExist(stoi(employee_num))){
                cout<<"This employee already works here"<<endl;
                continue;
            }
            cout<<"Please type the employee type:"<<endl;
            cin>>employee_type;
            cout<<"Please type the employee name: "<<endl;
            cin.ignore();
            getline (cin, name);
            cout<<"Please type the employee surname:"<<endl;
            getline (cin, surname);
            cout<<"Please type the employee title:"<<endl;
            getline (cin, title);
            cout<<"Please type the employee salarycoefficient:"<<endl;
            cin>>salary_coef;
            cout<<"Please type the employee date of birth:"<<endl;
            cin>>date_birth;
            cout<<"Please type the employee date of appointment:"<<endl;
            cin>>date_appointment;
            if(stoi(choice)==2){
                cout<<"Please type the lenght of service:"<<endl;
                cin>>service_lenght;
            }
            Date birthday(date_birth);
            Date appointment_day(date_appointment);

            if(stoi(employee_type)==0){
                if(choice=="2"){
                    TemporaryEmployee temporaryEmployee(stoi(employee_num), stoi(employee_type),name,surname,title, stod(salary_coef),birthday,appointment_day,stoi(service_lenght));
                    circularArrayLinkedList.insert(temporaryEmployee);
                    continue;
                }else{
                    TemporaryEmployee temporaryEmployee(stoi(employee_num), stoi(employee_type),name,surname,title, stod(salary_coef),birthday,appointment_day);
                    circularArrayLinkedList.insert(temporaryEmployee);
                    continue;
                }

            } else if(stoi(employee_type)==1){
                if(choice=="2"){
                    PermanentEmployee permanentEmployee(stoi(employee_num), stoi(employee_type),name,surname,title, stod(salary_coef),birthday,appointment_day,stoi(service_lenght));
                    doubleLinkedList.insert(permanentEmployee);
                    continue;
                }else{
                    PermanentEmployee permanentEmployee(stoi(employee_num), stoi(employee_type),name,surname,title, stod(salary_coef),birthday,appointment_day);
                    doubleLinkedList.insert(permanentEmployee);
                    continue;
                }

            }

        //choice 3
        }else if(stoi(choice)==3){
            string employee_num,newTitle,newSalaryCoef;
            cout<<"Please type the employee number:"<<endl;
            cin>>employee_num;
            if(circularArrayLinkedList.isExist(stoi(employee_num))){
                cout<<"Please type the new title:"<<endl;
                cin.ignore();
                getline (cin, newTitle);
                cout<<"Please type the new salary coefficient:"<<endl;
                getline (cin, newSalaryCoef);
                circularArrayLinkedList.update(circularArrayLinkedList.findEmployee(stoi(employee_num)),newTitle,stod(newSalaryCoef));
                continue;
            }else if(doubleLinkedList.isExist(stoi(employee_num))){
                cout<<"Please type the new title:"<<endl;
                cin.ignore();
                getline (cin, newTitle);
                cout<<"Please type the new salary coefficient:"<<endl;
                getline (cin, newSalaryCoef);
                doubleLinkedList.update(doubleLinkedList.findEmployee(stoi(employee_num)),newTitle, stod(newSalaryCoef));
                continue;
            }
            else{
                cout<<"There is no such employee"<<endl;
                continue;
            }

        //choice 4
        } else if(stoi(choice)==4){
            string employee_num;
            cout<<"Please type the employee number:"<<endl;
            cin>>employee_num;
            if(circularArrayLinkedList.isExist(stoi(employee_num))){
                circularArrayLinkedList.deleteTemployee(circularArrayLinkedList.findEmployee(stoi(employee_num)));
                continue;
            }else if(doubleLinkedList.isExist(stoi(employee_num))){
                doubleLinkedList.remove(doubleLinkedList.findEmployee(stoi(employee_num)));
                continue;
            }
            else{
                cout<<"There is no such employee"<<endl;
                continue;
            }

        //choice 5
        }else if(stoi(choice)==5){
            string employee_num;
            cout<<"Please type the employee number:"<<endl;
            cin>>employee_num;
            if(circularArrayLinkedList.isExist(stoi(employee_num))){
                cout<<circularArrayLinkedList.findEmployee(stoi(employee_num));
                continue;
            }else if(doubleLinkedList.isExist(stoi(employee_num))){
                cout<<doubleLinkedList.findEmployee(stoi(employee_num));
                continue;
            }else{
                cout<<"There is no such employee"<<endl;
                continue;
            }

        //choice 6
        }else if(stoi(choice)==6){
            vector<Employee> employeeList;
            circularArrayLinkedList.addEmployee(employeeList);
            doubleLinkedList.addEmployee(employeeList);
            sort(employeeList.begin(), employeeList.end(), [](const Employee& employee1, const Employee& employee2) -> bool
            {
                return employee1.getEmployeeNumber() < employee2.getEmployeeNumber();
            });
            for (int i = 0; i < employeeList.size(); ++i) {
                cout<<employeeList[i];
            }
            continue;

        //choice 7
        }else if(stoi(choice)==7){
            vector<Employee> employeeList;
            circularArrayLinkedList.addEmployee(employeeList);
            doubleLinkedList.addEmployee(employeeList);
            sort(employeeList.begin(), employeeList.end(), [](const Employee& employee1, const Employee& employee2) -> bool
            {
                return employee1.getDateOfAppointment() < employee2.getDateOfAppointment();
            });
            for (int i = 0; i < employeeList.size(); ++i) {
                cout<<employeeList[i];
            }


        //choice 8
        }else if(stoi(choice)==8){
            string newDate;
            cout<<"Type the date: "<<endl;
            cin>>newDate;
            Date afterDate(newDate);
            vector<Employee> employeeList;
            circularArrayLinkedList.addEmployee(employeeList);
            doubleLinkedList.addEmployee(employeeList);
            sort(employeeList.begin(), employeeList.end(), [](const Employee& employee1, const Employee& employee2) -> bool
            {
                return employee1.getDateOfAppointment() > employee2.getDateOfAppointment();
            });
            for (int i = 0; i < employeeList.size(); ++i) {
                if(employeeList[i].getDateOfAppointment()>afterDate){
                    cout<<employeeList[i];
                }
            }

        //choice 9
        }else if(stoi(choice)==9){
            string year;
            cout<<"Type the year: "<<endl;
            cin>>year;
            vector<Employee> employeeList;
            circularArrayLinkedList.addEmployee(employeeList);
            doubleLinkedList.addEmployee(employeeList);
            sort(employeeList.begin(), employeeList.end(), [](const Employee& employee1, const Employee& employee2) -> bool
            {
                return employee1.getDateOfAppointment() < employee2.getDateOfAppointment();
            });
            for (int i = 0; i < employeeList.size(); ++i) {
                if((employeeList[i].getDateOfAppointment()).getYear()==stoi(year)){
                    cout<<employeeList[i];
                }
            }


        //choice 10
        }else if(stoi(choice)==10){
            string bornDate;
            cout<<"Type the date: "<<endl;
            cin>>bornDate;
            Date birthDay(bornDate);
            vector<Employee> employeeList;
            circularArrayLinkedList.addEmployee(employeeList);
            doubleLinkedList.addEmployee(employeeList);
            sort(employeeList.begin(), employeeList.end(), [](const Employee& employee1,const  Employee& employee2) -> bool
            {
                return employee1.getEmployeeNumber() < employee2.getEmployeeNumber();
            });
            for (int i = 0; i < employeeList.size(); ++i) {
                if(employeeList[i].getDateOfBirth()<birthDay){
                    cout<<employeeList[i];
                }
            }

        //choice 11
        }else if(stoi(choice)==11){
            string bornMonth;
            cout<<"Type the month: "<<endl;
            cin>>bornMonth;
            vector<Employee> employeeList;
            circularArrayLinkedList.addEmployee(employeeList);
            doubleLinkedList.addEmployee(employeeList);
            sort(employeeList.begin(), employeeList.end(), [](const Employee& employee1,const  Employee& employee2) -> bool
            {
                return employee1.getEmployeeNumber() < employee2.getEmployeeNumber();
            });
            for (int i = 0; i < employeeList.size(); ++i) {
                if(employeeList[i].getDateOfBirth().getMonth()== stoi(bornMonth)){
                    cout<<employeeList[i];
                }
            }

        //choice 12
        }else if(stoi(choice)==12){
            string searchTitle;
            cout<<"Type the title: "<<endl;
            cin.ignore();
            getline (cin, searchTitle);
            vector<Employee> employeeList;
            circularArrayLinkedList.addEmployee(employeeList);
            doubleLinkedList.addEmployee(employeeList);
            sort(employeeList.begin(), employeeList.end(), [](const Employee& employee1,const  Employee& employee2) -> bool
            {
                return employee1.getDateOfAppointment() > employee2.getDateOfAppointment();
            });
            for (int i = 0; i < employeeList.size(); ++i) {
                if(employeeList[i].getTitle()==searchTitle){
                    cout<<employeeList[i];
                    break;
                }
            }
        }
        else
            flag= false;
    }

    return 0;
}
