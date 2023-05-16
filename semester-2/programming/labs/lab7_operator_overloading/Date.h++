//
// Created by marling on 4/19/23.
//

#ifndef LAB7_DATE_H
#define LAB7_DATE_H
#include <iostream>

class Date {
    int d, m, y;

public:
    Date(int, int, int);
    ~Date();

    bool operator==(Date d2){

        return ((d = d2.d) && (m == d2.m) && (y==d2.y));
    }

    bool operator!=(Date d2){

        return !(*this==d2);
    }

   /* bool operator>(Date d2) {
        return (y > d2.y) ? true : (m > d2.m) ? true : (d > d2.d) ? true : false;
    }*/

    bool operator>(Date d2) {
        return (y > d2.y) || (m > d2.m) || (d > d2.d);
    }

    bool operator<(Date d2){
        return !((*this==d2) || (*this>d2));
    }

    bool operator>=(Date d2) {
        return ((*this==d2) || (*this>d2));
    }

    bool operator<=(Date d2) {
        return ((*this==d2)) || (*this<d2);
    }

  /*  Date operator++(){
        return (d++ < 31) ? *this : (d=1 && m++ && m<12) ? *this : (m=1 && y++) ? *this : *this;
    }*/

  Date operator++(){
      d++;
      return *this;
  }
 /* Date operator++(int){
        d++;
        return *this;
    }*/

    Date operator++(int){
        Date tmp = *this;
        d++;
        return tmp;
    }

    /*
      friend std::ostream& operator<<(std::ostream& os, const Date d1) {
        os << d1.d << "-" << d1.m << "-" << d1.y << endl;
        return os;
    }
     */

    friend std::ostream& operator<<(std::ostream& os, const Date d1) {
        os << d1.d << "-" << d1.m << "-" << d1.y << std::endl;
        return os;
    }
};


#endif //LAB7_DATE_H
