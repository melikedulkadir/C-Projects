//
// Created by Melike on 26.11.2021.
//

#ifndef ASSIG2_DATE_H
#define ASSIG2_DATE_H
#include <iostream>
#include <sstream>

using namespace std;
class Date {
    public:
    // Special constructor with splitting data functionality. It splits the given data and sets the attributes.
        Date(string& date){
    istringstream ss(date);
    string token;
    int count  = 0;
    while(std::getline(ss, token, '-')) {
        if(count==0){
            day = stoi(token);
            count++;
        }else if(count == 1){
            month = stoi(token);
            count++;
        } else year = stoi(token);
    }

}

Date() {

}

private:
    //attributes
        int day;
        int month;
        int year;
    public:
    //get-sets
    void setDay(int day) {
              day = day;

    }

    int getDay() const {
        return day;
    }

    void setMonth(int month) {
        month= month;
    }

    int getMonth() const {
        return month;
    }

    void setYear(int year) {
        year  = year;
    }
    int getYear() const {
        return year;
    }

       // prototype of operator overload
     friend ostream& operator<<(ostream& output, Date date);       
};

// Operator overload for << sign. Prints date info

inline ostream &operator<<( ostream &output, Date date){
    output <<  date.getDay() <<"-"<< date.getMonth() << "-"<< date.getYear();
    return output;
}

// Operator overload for comparison operators. Specialized for date attributes.
inline bool operator>(Date a, Date b){
           if (a.getYear()>b.getYear()){
               return true;
           }else if(a.getYear()==b.getYear()){
               if (a.getMonth()>b.getMonth())
                   return true;
               else if (a.getMonth()<b.getMonth())
                   return false;
               else if (a.getMonth()==b.getMonth()){
                   if (a.getDay()>b.getDay())
                       return true;
                   else if(a.getDay()<b.getDay())
                       return false;
                   else if (a.getDay()==b.getDay()){
                       cout<<"These are the same dates!";
                       return false;
                   }
               }
           }return false;

      }
   inline bool operator<(Date a, Date b){
          if(a.getYear()< b.getYear()){
              return true;
          }else if(a.getYear()==b.getYear()){
              if (a.getMonth()>b.getMonth())
                  return false;
              else if (a.getMonth()<b.getMonth())
                  return true;
              else if (a.getMonth()==b.getMonth()){
                  if (a.getDay()>b.getDay())
                      return false;
                  else if(a.getDay()<b.getDay())
                      return true;
                  else if (a.getDay()==b.getDay()){
                      cout<<"These are the same dates!";
                      return false;
                  }
              }
          }return false;
      }
    inline bool operator<=(Date a, Date b){
         if(a.getYear()< b.getYear()){
            return true;
        }else if(a.getYear()==b.getYear()){
            if (a.getMonth()>b.getMonth())
                return false;
            else if (a.getMonth()<b.getMonth())
                return true;
            else if (a.getMonth()==b.getMonth()){
                if (a.getDay()>b.getDay())
                    return false;
                else if(a.getDay()<b.getDay())
                    return true;
                else if (a.getDay()==b.getDay()){
                    return true;
                }
            }
        }return false;

    }
   inline bool operator>=(Date a, Date b){
        if (a.getYear()>b.getYear()){
            return true;
        }else if(a.getYear()==b.getYear()){
            if (a.getMonth()>b.getMonth())
                return true;
            else if (a.getMonth()<b.getMonth())
                return false;
            else if (a.getMonth()==b.getMonth()){
                if (a.getDay()>b.getDay())
                    return true;
                else if(a.getDay()<b.getDay())
                    return false;
                else if (a.getDay()==b.getDay()){
                    return true;
                }
            }

        }return false;

    }
   inline bool operator==(Date a, Date b){
           if(a.getYear()==b.getYear()){
               if (a.getMonth()==b.getMonth()){
                   if (a.getDay()== b.getDay())
                       return true;
               }
           }return false;
       }


#endif //ASSIG2_DATE_H
