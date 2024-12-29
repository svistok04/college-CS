package svstk.si.puzzle;

import sac.State;
import sac.StateFunction;

public class ManhattanHeuristic extends StateFunction {
    @Override
    public double calculate(State state) {
        SlidingPuzzle puzzle = (SlidingPuzzle) state;
        int distance = 0;
        for (int i = 0; i < puzzle.n; i++) {
            for (int j = 0; j < puzzle.n; j++) {
                int value = puzzle.board[i][j];
                if (value != 0) {
                    int goalRow = value / puzzle.n;
                    int goalCol = value % puzzle.n;
                    distance += Math.abs(i - goalRow) + Math.abs(j - goalCol);
                }
            }
        }
        return distance;
    }
}
