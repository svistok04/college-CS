//
// Created by marling on 5/17/23.
//

#ifndef ZAD6_FILES_STUDENTSLIST_STUDENT_HPP
#define ZAD6_FILES_STUDENTSLIST_STUDENT_HPP

#include <iostream>
#include <fstream>

class Student {
    std::string surname;
    std::string name;
    int id;
    int group;
    int year;

public:
    Student(std::string surname, std::string name, int id, int group, int year);

//  friend std::istream& operator>>(std::istream&, Student&);
    friend std::ostream& operator<<(std::ostream&, Student&);
    friend std::ifstream& operator>>(std::ifstream&, Student&);
    friend std::ofstream& operator<<(std::ofstream&, Student&);

    int getYear() const;

    const std::string &getSurname() const;

    const std::string &getName() const;

    int getId() const;

    int getGroup() const;
};


#endif //ZAD6_FILES_STUDENTSLIST_STUDENT_HPP
