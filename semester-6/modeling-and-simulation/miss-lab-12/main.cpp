#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>

#define N 200
#define BOARD_SIZE 100
#define MAX_AGE 100
#define TURNS 100
#define SPEED 100 // ms per turn
#define BIRTH_RATE 10 // % chance

// colors
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define ORANGE  "\033[38;5;208m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"

// replaced with functions 
// enum class Resistance {
//   LOW,
//   MEDIUM,
//   HIGH
// };

// returns (min, max) allowed resistance for age group
inline void resistance_init_bounds(int age, float& rmin, float& rmax) {
    if (age < 15 || age >= 70) { rmin = 0.01f; rmax = 3.0f; }
    else if (age < 40)         { rmin = 6.0f;  rmax = 10.0f; }
    else                       { rmin = 3.0f;  rmax = 6.0f; }
}

inline float resistance_group_max(int age) {
    if (age < 15 || age >= 70) return 3.0f;
    else if (age < 40)         return 10.0f;
    else                       return 6.0f;
}

// resistance level: 0=low, 1=medium, 2=high (context-dependent)
inline int res_group(float resistance, int age) {
    float max = resistance_group_max(age);
    if (max == 3.0f) return 0; // only low for (0,15) and (70,100)
    if (max == 6.0f) return (resistance < 3.0f ? 0 : 1);        // low/med
    return (resistance < 3.0f ? 0 : (resistance < 6.0f ? 1 : 2)); // low/med/high
}

enum class State {
  C,   // sick
  Z,   // infected
  ZD,  // recovering
  ZZ   // healthy
};

enum class Direction {
  NORTH,
  EAST,
  SOUTH,
  WEST
};

struct Point {
  int x, y;
};

struct Induvidual {
  Point position;
  int speed;
  Direction direction;
  State state;
  int age;
  float resistance;
  int days_in_state = 0;
  bool alive = true;

  Induvidual(std::mt19937 &rng);
  void move(std::mt19937 &rng);
  void update_state();
  void update_resistance();
  void age_and_check();
  void bounce_wall();
  void print() const;
};

int randInt(std::mt19937 &rng, int a, int b) {
  std::uniform_int_distribution<int> dist(a, b);
  return dist(rng);
}

template<typename Enum>
Enum randEnum(std::mt19937 &rng, int numValues) {
  return static_cast<Enum>(randInt(rng, 0, numValues - 1));
}

float randFloat(std::mt19937 &rng, float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

Induvidual::Induvidual(std::mt19937 &rng)
  : position{randInt(rng, 1, BOARD_SIZE), randInt(rng, 1, BOARD_SIZE)},
  speed(randInt(rng, 1, 3)),
  direction(randEnum<Direction>(rng, 4)),
  state(randEnum<State>(rng, 4)),
  age(randInt(rng, 0, 59))
{
  // init resistance based on age
  // if (age < 15 || age >= 70) {
  //   resistance = randInt(rng, 0, 29) / 10.0f + 0.01f; // (0,3]
  // } else if (age < 40) {
  //   resistance = randInt(rng, 61, 99) / 10.0f; // (6,10)
  // } else { // 40 <= age < 70
  //   resistance = randInt(rng, 31, 59) / 10.0f; // (3,6)
  // }
    float rmin, rmax;
    resistance_init_bounds(age, rmin, rmax);
    resistance = randFloat(rng, rmin, rmax);
}

// movement
void Induvidual::move(std::mt19937 &rng) {
  switch (direction) {
    case Direction::NORTH: position.y -= speed; break;
    case Direction::EAST:  position.x += speed; break;
    case Direction::SOUTH: position.y += speed; break;
    case Direction::WEST:  position.x -= speed; break;
  }
  bounce_wall();
  direction = randEnum<Direction>(rng, 4);
}

// wall bounce
void Induvidual::bounce_wall() {
  if (position.x < 1) { position.x = 1; direction = Direction::EAST; }
  if (position.x > BOARD_SIZE) { position.x = BOARD_SIZE; direction = Direction::WEST; }
  if (position.y < 1) { position.y = 1; direction = Direction::SOUTH; }
  if (position.y > BOARD_SIZE) { position.y = BOARD_SIZE; direction = Direction::NORTH; }
}

// state transitions
void Induvidual::update_state() {
  days_in_state++;
  switch(state) {
    case State::Z:  // Z -> C after 2 days
      if (days_in_state >= 2) { state = State::C; days_in_state = 0; }
      break;
    case State::C:  // C -> ZD after 7 days
      if (days_in_state >= 7) { state = State::ZD; days_in_state = 0; }
      break;
    case State::ZD: // ZD -> ZZ after 5 days
      if (days_in_state >= 5) { state = State::ZZ; days_in_state = 0; }
      break;
    default: break;
  }
}

// changes resistance per state
void Induvidual::update_resistance() {
  switch(state) {
    case State::Z:  resistance -= 0.10f; break;
    case State::C:  resistance -= 0.50f; break;
    case State::ZD: resistance += 0.10f; break;
    case State::ZZ: resistance += 0.05f; break;
  }
  // bounds resistance to [0, group_max] after updates
  float max_r = resistance_group_max(age);
  if (resistance > max_r) resistance = max_r;
  if (resistance < 0.0f) resistance = 0.0f;
}

// aging and death check
void Induvidual::age_and_check() {
  age++;
  if (age >= MAX_AGE || resistance <= 0.0f)
    alive = false;
}

// prints with color
void Induvidual::print() const {
  switch(state) {
    case State::C:  std::cout << RED << "C" << RESET; break;
    case State::Z:  std::cout << YELLOW << "Z" << RESET; break;
    case State::ZD: std::cout << ORANGE << "D" << RESET; break;
    case State::ZZ: std::cout << GREEN << "S" << RESET; break;
  }
}

void interact(Induvidual &a, Induvidual &b) {
  // REPLACED helper lambda funcs for retrieving resistance group (low/med/high) 
  // auto group = [](const Induvidual &x) -> int {
  //   if (x.age < 15 || x.age >= 70) return 0; // low (max 3.0)
  //   if (x.age < 40) return 2; // high (max 10.0)
  //   return 1; // medium (max 6.0)
  // };
  // auto res_group = [&](const Induvidual &x) -> int {
  //   float r = x.resistance;
  //   if (group(x) == 0) return 0; // only low group possible
  //   if (group(x) == 1) return (r < 3.0f ? 0 : 1); // low/med
  //   return (r < 3.0f ? 0 : (r < 6.0f ? 1 : 2)); // low/med/high
  // };

  // ZZ and Z
  if (a.state == State::ZZ && b.state == State::Z) {
    if (res_group(a.resistance, a.age) == 0) { // low
      a.state = State::Z; a.days_in_state = 0;
    }
  }
  if (a.state == State::Z && b.state == State::ZZ) {
    if (res_group(b.resistance, b.age) == 0) {
      b.state = State::Z; b.days_in_state = 0;
    }
  }
  // ZZ and C
  if (a.state == State::ZZ && b.state == State::C) {
    int rg = res_group(a.resistance, a.age);
    if (rg == 0 || rg == 1) { // low or medium
      a.state = State::Z; a.days_in_state = 0;
    } else if (rg == 2) { // high
      a.resistance -= 3.0f;
      if (a.resistance < 0.0f) a.resistance = 0.0f;
    }
  }
  if (a.state == State::C && b.state == State::ZZ) {
    int rg = res_group(b.resistance, b.age);
    if (rg == 0 || rg == 1) {
      b.state = State::Z; b.days_in_state = 0;
    } else if (rg == 2) {
      b.resistance -= 3.0f;
      if (b.resistance < 0.0f) b.resistance = 0.0f;
    }
  }
  // ZZ and ZD
  if (a.state == State::ZZ && b.state == State::ZD) {
    b.resistance += 1.0f;
    float max_b = (b.age < 15 || b.age >= 70) ? 3.0f : (b.age < 40 ? 10.0f : 6.0f);
    if (b.resistance > max_b) b.resistance = max_b;
  }
  if (a.state == State::ZD && b.state == State::ZZ) {
    a.resistance += 1.0f;
    float max_a = (a.age < 15 || a.age >= 70) ? 3.0f : (a.age < 40 ? 10.0f : 6.0f);
    if (a.resistance > max_a) a.resistance = max_a;
  }
  // ZZ and ZZ
  if (a.state == State::ZZ && b.state == State::ZZ) {
    float max_a = (a.age < 15 || a.age >= 70) ? 3.0f : (a.age < 40 ? 10.0f : 6.0f);
    float max_b = (b.age < 15 || b.age >= 70) ? 3.0f : (b.age < 40 ? 10.0f : 6.0f);
    float new_r = std::min(std::max(a.resistance, b.resistance), std::min(max_a, max_b));
    a.resistance = b.resistance = new_r;
  }
  // C and Z
  if (a.state == State::C && b.state == State::Z) {
    int rg = res_group(b.resistance, b.age);
    if (rg == 0 || rg == 1) { b.state = State::C; b.days_in_state = 0; }
    a.days_in_state = 0;
  }
  if (a.state == State::Z && b.state == State::C) {
    int rg = res_group(a.resistance, a.age);
    if (rg == 0 || rg == 1) { a.state = State::C; a.days_in_state = 0; }
    b.days_in_state = 0;
  }
  // C and ZD
  if (a.state == State::C && b.state == State::ZD) {
    int rg = res_group(b.resistance, b.age);
    if (rg == 0 || rg == 1) { b.state = State::Z; b.days_in_state = 0; }
  }
  if (a.state == State::ZD && b.state == State::C) {
    int rg = res_group(a.resistance, a.age);
    if (rg == 0 || rg == 1) { a.state = State::Z; a.days_in_state = 0; }
  }
  // C and C
  if (a.state == State::C && b.state == State::C) {
    float min_r = std::min(a.resistance, b.resistance);
    a.resistance = b.resistance = min_r;
    a.days_in_state = b.days_in_state = 0;
  }
  // Z and ZD
  if (a.state == State::Z && b.state == State::ZD) {
    b.resistance -= 1.0f;
    if (b.resistance < 0.0f) b.resistance = 0.0f;
  }
  if (a.state == State::ZD && b.state == State::Z) {
    a.resistance -= 1.0f;
    if (a.resistance < 0.0f) a.resistance = 0.0f;
  }
  // Z and Z
  if (a.state == State::Z && b.state == State::Z) {
    a.resistance -= 1.0f;
    b.resistance -= 1.0f;
    if (a.resistance < 0.0f) a.resistance = 0.0f;
    if (b.resistance < 0.0f) b.resistance = 0.0f;
  }
  // ZD and ZD: nothing happens
}

// Chessboard distance
int chess_distance(const Induvidual& a, const Induvidual& b) {
  return std::max(std::abs(a.position.x - b.position.x), std::abs(a.position.y - b.position.y));
}


void clear_screen() {
  std::cout << "\033[2J\033[H"; // Clear screen and move cursor home
}

void print_grid(const std::vector<Induvidual>& population, int turn) {
  char board[BOARD_SIZE+1][BOARD_SIZE+1] = {};

  // Place individuals
  for (const auto& ind : population) {
    if (!ind.alive) continue;
    char symbol = ' ';
    switch(ind.state) {
      case State::C:  symbol = 'C'; break;
      case State::Z:  symbol = 'Z'; break;
      case State::ZD: symbol = 'D'; break;
      case State::ZZ: symbol = 'S'; break;
    }
    board[ind.position.y][ind.position.x] = symbol;
  }

  for (int y = 1; y <= BOARD_SIZE; ++y) {
    for (int x = 1; x <= BOARD_SIZE; ++x) {
      char ch = board[y][x];
      if (ch == 0) std::cout << ".";
      else if (ch == 'C') std::cout << RED << "C" << RESET;
      else if (ch == 'Z') std::cout << YELLOW << "Z" << RESET;
      else if (ch == 'D') std::cout << ORANGE << "D" << RESET;
      else if (ch == 'S') std::cout << GREEN << "S" << RESET;
      else std::cout << ch;
    }
    std::cout << "\n";
  }
}

int count_alive(const std::vector<Induvidual>& pop) {
  int c = 0;
  for (const auto& ind : pop) if (ind.alive) ++c;
  return c;
}

int main() {
  std::mt19937 rng(time(nullptr));
  std::vector<Induvidual> population;
  for (int i = 0; i < N; ++i)
    population.emplace_back(rng);


  for (int t = 0; t < TURNS; ++t) {
    for (auto &ind : population)
      if (ind.alive) ind.move(rng);


    for (size_t i = 0; i < population.size(); ++i) {
      for (size_t j = i+1; j < population.size(); ++j) {
        if (!population[i].alive || !population[j].alive) continue;
        if (chess_distance(population[i], population[j]) > 2) continue;

        interact(population[i], population[j]);

        if (population[i].alive && population[j].alive &&
          population[i].age >= 20 && population[i].age < 40 &&
          population[j].age >= 20 && population[j].age < 40) 
        {
          // 10% chance of birth
          if (randInt(rng, 0, 99) < BIRTH_RATE) { 
            int num_newborns = randInt(rng, 1, 2);
            for (int b = 0; b < num_newborns; ++b) {
              Induvidual baby(rng);
              baby.state = State::ZZ;
              baby.age = 0;
              baby.resistance = 3.0f;
              baby.days_in_state = 0;
              baby.position = population[i].position;
              population.push_back(baby);
            }
          }
        }
      }
    }

    // update state, resistance, age, death
    for (auto &ind : population) {
      if (!ind.alive) continue;
      ind.update_state();
      ind.update_resistance();
      ind.age_and_check();
    }

    clear_screen();
    print_grid(population, t);
    std::cout << "Turn: " << t << " | Alive: " << count_alive(population) << "\n";
    std::cout << "Legend: " << RED << "C" << RESET << "=sick, "
      << YELLOW << "Z" << RESET << "=infected, "
      << ORANGE << "D" << RESET << "=recovering, "
      << GREEN << "S" << RESET << "=healthy\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(SPEED));
  }

  std::cout << "Simulation finished.\n";

  //   for (auto &ind : population) {
  //     if (ind.alive) {
  //       std::cout << "(" << ind.position.x << "," << ind.position.y << ") " << std::endl;
  //     }
  //   }
  //
  // int off_grid = 0;
  // for (const auto& ind : population) {
  //     if (ind.alive && (ind.position.x < 1 || ind.position.x > BOARD_SIZE || ind.position.y < 1 || ind.position.y > BOARD_SIZE)) {
  //         ++off_grid;
  //     }
  // }
  // std::cout << "Number off-grid: " << off_grid << std::endl;
  char board[BOARD_SIZE+1][BOARD_SIZE+1] = {};

  for (const auto& ind : population) {
    if (!ind.alive) continue;
    char symbol = ' ';
    switch(ind.state) {
      case State::C:  symbol = 'C'; break;
      case State::Z:  symbol = 'Z'; break;
      case State::ZD: symbol = 'D'; break;
      case State::ZZ: symbol = 'S'; break;
    }
    board[ind.position.y][ind.position.x] = symbol;
  }

  std::ofstream fout("final_board.txt");
  for (int y = 1; y <= BOARD_SIZE; ++y) {
    for (int x = 1; x <= BOARD_SIZE; ++x) {
      char ch = board[y][x];
      if (ch == 0) fout << ".";
      else if (ch == 'C') fout << "\033[31mC\033[0m";
      else if (ch == 'Z') fout << "\033[33mZ\033[0m";
      else if (ch == 'D') fout << "\033[38;5;208mD\033[0m";
      else if (ch == 'S') fout << "\033[32mS\033[0m";
      else fout << ch;
    }
    fout << "\n";
  }
  fout << "Turn: " << TURNS-1 << " | Alive: " << count_alive(population) << "\n";
  fout << "Legend: " << RED << "C" << RESET << "=sick, "
    << YELLOW << "Z" << RESET << "=infected, "
    << ORANGE << "D" << RESET << "=recovering, "
    << GREEN << "S" << RESET << "=healthy\n";
  fout << "Simulation finished.\n";
  fout.close();
  return 0;
}
