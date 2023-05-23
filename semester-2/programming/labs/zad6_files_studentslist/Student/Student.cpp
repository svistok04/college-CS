//
// Created by marling on 5/17/23.
//

#include "Student.hpp"

#include <utility>

std::ifstream& operator>>(std::ifstream& input, Student& student) {
    input >> student.surname >> student.name >> student.id >> student.group >> student.year;
}

std::ofstream& operator<<(std::ofstream& output, Student& student) {
    output << student.getSurname() << std::endl << student.getName() << std::endl << student.getId()
    << std::endl << student.getGroup() << std::endl << student.getYear() << std::endl;
    return output;
}

std::ostream& operator<<(std::ostream& os, Student& student) {
    return os << student.getSurname() << " " << student.getName() << " " << student.getId() << " "
    << student.getGroup() << " " << student.getYear() << std::endl;
}

int Student::getYear() const {
    return year;
}

const std::string &Student::getSurname() const {
    return surname;
}

const std::string &Student::getName() const {
    return name;
}

int Student::getId() const {
    return id;
}

int Student::getGroup() const {
    return group;
}

Student::Student(std::string surname, std::string name, int id, int group, int year) : surname(std::move(surname)),
                                                                                                     name(std::move(name)), id(id),
                                                                                                     group(group),
                                                                                                     year(year) {}
