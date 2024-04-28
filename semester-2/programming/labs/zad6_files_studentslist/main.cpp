#include <iostream>
#include <vector>
#include <algorithm>
#include "Student/Student.hpp"

void print(Student);

int main() {

    Student student("Wozniak", "Hubert", 13412, 112, 3);

    std::vector<Student> list;
    list.push_back(student);

    std::ifstream fileInput("data.txt");

    while (fileInput >> student) {
        list.push_back(student);
    }

    fileInput.close();

    //for_each(list.begin(), list.end(), print);
    std::cout << "Surname, name, ID, group, year" << std::endl;
    for_each(list.begin(), list.end(), [](Student st) {std::cout << st;});


    std::ofstream fileOutput("output.txt");

    for (Student st : list) {
        fileOutput << st;
    }

    fileOutput.close();

    std::cout << "Number of students enrolled in the 3rd year: " << std::count_if(list.begin(), list.end(), [=](Student const& st)
    {return st.getYear() == 3; });

    // for_each(list.begin(), list.end(), [&fileOutput](Student st) -> void {fileOutput << st})

    return 0;
}

void print(Student student) {
    std::cout << student;
}
