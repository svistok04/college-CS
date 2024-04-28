// ALGO2 IS1 223A LAB01
// Vladyslav Zosimchuk
// zv53855@zut.edu.pl

#include <iostream>
#include <ctime>
#include <sstream>
#include <random>


struct linked_list {
    std::string name;
    std::string surname;
    int age;
    std::string occupation;
    struct linked_list* next;
    struct linked_list* prev;

    linked_list(std::string name = "John", std::string surname, int age = 18, std::string occupation = "Unknown") :
        name(std::move(name)),
        surname(std::move(surname)),
        age(age),
        occupation(std::move(occupation)),
        next (nullptr),
        prev(nullptr) {}

    ~linked_list() = default;
};


void insertBeginning(linked_list*&, std::string, std::string, int, std::string); // a
void insertEnd(linked_list*&, std::string, std::string, int, std::string); // b
void removeFirst(linked_list*&); // c
void removeEnd(linked_list*&); // d
std::string findByPosition(linked_list*, int); // e
void changeByPosition(linked_list*&, int, std::string, std::string, int, std::string); // f
linked_list* findBySurname(linked_list*, const std::string&); // g
bool findAndRemoveBySurname(linked_list*&, linked_list*&, const std::string&); // h
void addWithEnforcedOrder(linked_list*&, linked_list*&, std::string, std::string, int, std::string); // i
void clearAll(linked_list*&); // j
std::ostream& operator<<(std::ostream&, const linked_list&);
std::string node_toString(linked_list*&);
std::string list_toString(linked_list*&, int); // k
int getRandomInRange(int, int);

std::ostream& operator<< (std::ostream&, linked_list*);

int main() {
//    std::string names[100] = {
//            "Emma", "Liam", "Olivia", "Noah", "Ava", "Isabella", "Sophia", "Mia",
//            "Charlotte", "Amelia","Harper", "Evelyn", "Abigail", "Emily", "Elizabeth",
//            "Sofia", "Madison", "Scarlett", "Grace", "Lily","Avery", "Ella",
//            "Madison", "Riley", "Ellie", "Aria", "Chloe", "Natalie", "Layla",
//            "Hannah","Lucy", "Zoey", "Victoria", "Penelope", "Aubrey", "Claire",
//            "Lillian", "Paisley", "Savannah", "Alice","Jasmine", "Naomi", "Ariana",
//            "Kaylee", "Stella", "Sarah", "Gabriella", "Zoe", "Alexa", "Bella",
//            "Violet", "Luna", "Savannah", "Natalie", "Brooklyn", "Leah", "Madelyn",
//            "Hazel", "Skylar", "Aurora","Aaliyah", "Samantha", "Addison", "Eleanor",
//            "Stella", "Nora", "Scarlett", "Grace", "Ellie", "Riley","Victoria",
//            "Madison", "Bella", "Hannah", "Zoe", "Aurora", "Emilia", "Lily",
//            "Hannah", "Penelope","Scarlett", "Elizabeth", "Zoey", "Nora", "Grace",
//            "Avery", "Zoey", "Emily", "Scarlett", "Evelyn","Harper", "Sofia",
//            "Lily", "Victoria", "Aria", "Zoey", "Aurora", "Addison", "Grace",
//            "Emily"
//    };
//
//    std::string surnames[100] = {
//            "Smith", "Johnson", "Brown", "Taylor", "Anderson", "Thomas", "Jackson",
//            "White", "Harris", "Martin","Thompson", "Garcia", "Martinez", "Robinson",
//            "Clark", "Rodriguez", "Lewis", "Lee", "Walker", "Hall","Allen",
//            "Young", "Hernandez", "King", "Wright", "Lopez", "Hill", "Scott",
//            "Green", "Adams","Baker", "Gonzalez", "Nelson", "Carter", "Mitchell",
//            "Perez", "Roberts", "Turner", "Phillips", "Campbell","Parker", "Evans",
//            "Edwards", "Collins", "Stewart", "Sanchez", "Morris", "Rogers", "Reed",
//            "Cook","Murphy", "Bailey", "Rivera", "Cooper", "Cox", "Diaz",
//            "Richardson", "Wood", "Watson", "Brooks","Gray", "James", "Bennett",
//            "Kim", "Kelly", "Morgan", "Murphy", "Mitchell", "Adams", "Jenkins",
//            "Wright", "Bell", "Foster", "Gonzales", "Wood", "Ward", "Powell",
//            "Long", "Flores", "Hansen","Reed", "Reed", "Turner", "Long",
//            "Jenkins", "Perry", "Miller", "Coleman", "Ross", "Hayes","Cox",
//            "Mitchell", "Morgan", "Cooper", "Butler", "Watson", "Pierce", "Parker",
//            "James", "Brooks"
//    };
//
//    std::string occupations[100] = {
//            "Accountant", "Actor", "Architect", "Artist", "Baker", "Barista","Carpenter",
//            "Chef", "Dentist", "Doctor", "Electrician", "Engineer","Farmer",
//            "Firefighter", "Graphic Designer", "Hairdresser", "Judge", "Lawyer",
//            "Librarian", "Mechanic", "Nurse", "Pharmacist", "Photographer", "Pilot",
//            "Plumber", "Police Officer", "Professor", "Programmer", "Psychologist",
//            "Real Estate Agent","Scientist", "Social Worker", "Software Developer", "Teacher",
//            "Truck Driver", "Veterinarian","Waiter", "Writer", "Account Manager",
//            "Acupuncturist", "Aerospace Engineer","Air Traffic Controller", "Animal Trainer",
//            "Archaeologist", "Astronomer", "Ballet Dancer","Biomedical Engineer", "Botanist",
//            "Chaplain", "Chiropractor", "Civil Engineer", "Clinical Psychologist","Curator",
//            "Data Analyst", "Detective", "Dietitian", "Ecologist", "Economist",
//            "Electrician","Event Planner", "Fashion Designer", "Filmmaker",
//            "Flight Attendant", "Forensic Scientist", "Game Developer","Geologist",
//            "Glassblower", "Herbalist", "Historian", "Interior Designer", "Journalist",
//            "Landscaper","Magician", "Marine Biologist", "Meteorologist", "Music Therapist",
//            "Neonatal Nurse", "Oceanographer", "Optometrist","Paleontologist", "Paramedic",
//            "Park Ranger", "Perfumer", "Physical Therapist", "Political Scientist",
//            "Radiologist","Robotics Engineer", "Sales Engineer", "Search and Rescue Officer",
//            "Sign Language Interpreter", "Snake Milker", "Space Physicist","Sports Agent",
//            "Taxidermist", "Textile Designer", "Tour Guide", "Underwater Welder",
//            "Urban Planner", "Video Game Tester", "Wildlife Biologist"
//    };
//
//    const int MAX_ORDER = 6;
//
//    linked_list* head = new linked_list();
//    linked_list* tail = new linked_list();
//    head->next = tail;
//    tail->prev = head;
//
//
//    for (int o = 1; o < MAX_ORDER; ++o)
//    {
//        const int n = pow(10, o);
//
//        clock_t t1 = clock();
//        for (int i = 0; i < n; ++i)
//        {
//            int randomIndex = getRandomInRange(0, 99);
//            int randomAge = getRandomInRange(18, 60);
//
//            addWithEnforcedOrder(
//                    head,
//                    tail,
//                    names[randomIndex],
//                    surnames[randomIndex],
//                    randomAge,
//                    occupations[randomIndex]
//                    );
//        }
//
//        clock_t t2 = clock();
//
//        std::cout << list_toString(head, n);
//
//        std::cout << "It took " << float(t2 - t1) / CLOCKS_PER_SEC << " seconds to add " << n << " objects" << std::endl;
//
//
//        const int m = pow(10,4);
//
//        t1 = clock();
//
//        for (int i = 0; i < m; ++i)
//        {
//            int randomIndex = getRandomInRange(0, 99);
//            findAndRemoveBySurname(head, tail, surnames[randomIndex]);
//        }
//
//        t2 = clock();
//
//         std::cout << list_toString(head, n);
//
//        std::cout << "It took " << float(t2 - t1) / CLOCKS_PER_SEC << " seconds to make " << m
//        << " attempts to remove objects" << std::endl;
//
//        std::string str;
//        std::cin >> str;
//    }
//
//    delete head;
//    delete tail;



    linked_list* head = new linked_list("John", "Doe", 21, "Plumber");
    linked_list* tail = new linked_list("Alex", "Smith", 25, "Clerk");
    linked_list* random = new linked_list("John");

    head->next = tail;
    tail->prev = head;

    addWithEnforcedOrder(head, tail, "Johny", "Muller", 32, "Soldier");
    addWithEnforcedOrder(head, tail, "Johny", "Muller", 33, "Soldier");

    addWithEnforcedOrder(head, tail, "Johny", "Muller", 31, "Soldier");
    addWithEnforcedOrder(head, tail, "Johny", "Muller", 84, "Soldier");
    addWithEnforcedOrder(head, tail, "Johny", "Muller", 55, "Soldier");
    addWithEnforcedOrder(head, tail, "Johny", "Muller", 39, "Soldier");
//    changeByPosition(head, 2, "J", "Zucker", 100, "Entrepreneur");

//    (findAndRemoveBySurname(head, tail, "Smith")) ?
//    std::cout << "Successfully removed Smith" << std::endl :
//    std::cout << "Couldn't find Smith" << std::endl;

//    linked_list* someNode = findBySurname(head, "Smith");
//
//    std::cout << &someNode << std::endl;

//    std::cout << &head << std::endl;
//
//    std::cout << findByPosition(head, 1);

    std::cout << list_toString(head, 8);


    clearAll(head);

    std::cout << list_toString(head, 2);



    return 0;
}

void insertBeginning(linked_list*& head, std::string name, std::string surname, int age, std::string occupation) {
    linked_list* newNode = new linked_list(std::move(name), std::move(surname), age, std::move(occupation));
    if (head == nullptr) {
        head = newNode;
        return;
    }
    newNode->next = head;
    head->prev = newNode;

    head = newNode;
} // a

void insertEnd(linked_list*& tail, std::string name, std::string surname, int age, std::string occupation) {
        linked_list* newNode = new linked_list(std::move(name), std::move(surname), age, std::move(occupation));
        if (tail == nullptr) {
            tail = newNode;
            return;
        }
        newNode->prev = tail;
        tail->next = newNode;

        tail = newNode;
} // b

void removeFirst(linked_list*& head) {
    if (head == nullptr) {
        return;
    }

    head = head->next;

    delete head->prev;

    if (head) {
        head->prev = nullptr;
    }
} // c

void removeEnd(linked_list*& tail) {
    if (tail == nullptr) {
        return;
    }

    tail = tail->prev;

    delete tail->next;

    if (tail) {
        tail->next = nullptr;
    }
} // d

std::string findByPosition(linked_list* head, int id) {
    if(head == nullptr || id < 0) {
        return "nullptr";
    }
    linked_list* traverser = head;
    for (int i = 0; i < id && traverser != nullptr; i++) {
        traverser = traverser->next;
    }

    return (traverser) ? "The " + std::to_string(id) + "th node is: " + node_toString(traverser) : "nullptr\n";
} // e

void changeByPosition(linked_list*& head, int id, std::string name, std::string surname, int age, std::string occupation) {
    if (head == nullptr || id < 0) {
        return;
    }

    linked_list* traverser = head;

    for (int i = 0; i < id && traverser != nullptr; i++) {
        traverser = traverser->next;
    }

    if (!traverser) {
        return;
    }

    linked_list* newNode = new linked_list(std::move(name), std::move(surname), age, std::move(occupation));


    newNode->prev = traverser->prev;
    newNode->next = traverser->next;

    if (traverser->next) traverser->next->prev = newNode;
    if (traverser->prev) traverser->prev->next = newNode;

    delete traverser;
} // f

linked_list* findBySurname(linked_list* head, const std::string& surname) {
    if (head == nullptr) {
        return nullptr;
    }


    linked_list* traverser = head;

    while(traverser != nullptr) {
        if (traverser->surname == surname) return traverser;
        traverser = traverser->next;
    }

    return nullptr;
}// g

bool findAndRemoveBySurname(linked_list*& head, linked_list*& tail, const std::string& surname) {
    if (head == nullptr) {
        return false;
    }

    if (head->surname == surname) {
        head = head->next;
        delete head->prev;

        if (head) {
            head->prev = nullptr;
        }

        return true;
    }

    if (tail->surname == surname) {
        tail = tail->prev;

        delete tail->next;

        if (tail) {
            tail->next = nullptr;
        }

        return true;
    }

    linked_list* traverser = head;

    while(traverser != nullptr && traverser->surname != surname) {
        traverser = traverser->next;
    }

    if (traverser) {
        if (traverser->prev) {
            traverser->prev->next = traverser->next;
        }

        if (traverser->next) {
            traverser->next->prev = traverser->prev;
        }

        delete traverser;

        return true;
    }

    return false;
} // h

void addWithEnforcedOrder(linked_list*& head, linked_list*& tail, std::string name, std::string surname, int age, std::string occupation) {
    linked_list* newNode = new linked_list(std::move(name), std::move(surname), age, std::move(occupation));

    if (head == nullptr) {
        head = newNode;
        return;
    }

    if (age < head->age) {
        if (head->next) head->next->prev = newNode;
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }

    linked_list* traverser = head;

    while(traverser->next) {
        if (age < traverser->next->age) {
            newNode->prev = traverser;
            newNode->next = traverser->next;
            traverser->next->prev = newNode;
            traverser->next = newNode;
            return;
        } else {
            traverser = traverser->next;
        }
    }

    newNode->prev = traverser;
    traverser->next = newNode;
    tail = newNode;
} // i

void clearAll(linked_list*& head) {

    linked_list* tmpNode = head;

    while (head) {
        tmpNode = head;
        head = head->next;
        delete tmpNode;
    }

    head = nullptr;
} // j

std::string node_toString(linked_list*& node) {

    std::stringstream output;

    output << node->name << " " << node->surname << "\t" << node->age << "\t" << node->occupation << std::endl;

    return output.str();
}

//std::ostream& operator<<(std::ostream& os, const linked_list& node) {
//
//    os << node.name << " " << node.surname << "\t" << node.age << "\t" << node.occupation << std::endl;
//
//    return os;
//}

std::string list_toString(linked_list*& head, int amount) {
    std::stringstream output;

    output << "The first node's address: " << &head << std::endl;

    linked_list* traverser = head;

    for (int i = 0; i < amount && traverser != nullptr; i++) {
    output << *traverser;
    traverser = traverser->next;
    }

    traverser = head;

    size_t i = 0;

    while(traverser) {
        i++;
        traverser = traverser->next;
    }

    output << "List's size is: " << i << std::endl;

    return output.str();
} // k

int getRandomInRange(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

