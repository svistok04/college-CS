A C++ program to sort a vector of football teams based on weighted parameters, including score, wins, losses, goals scored, and goals missed:
Score (the higher, the better);
Wins  (the higher, the better);
Losses  (the lower, the better);
Goals scored  (the higher, the better);
Goals Missed (the lower, the better).

The sorting function utilizes the <code>std::greater&lt;T&gt;</code> function object from the C++ Standard Library to sort the teams according to the specified rule of weights. The program also overloads the ostream operator to display the league table, providing rankings and statistics for each team.