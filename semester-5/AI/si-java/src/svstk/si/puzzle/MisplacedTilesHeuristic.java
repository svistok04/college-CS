package svstk.si.puzzle;

import sac.State;
import sac.StateFunction;

public class MisplacedTilesHeuristic extends StateFunction {
    @Override
    public double calculate(State state) {
        SlidingPuzzle puzzle = (SlidingPuzzle) state;
        int misplacedCount = 0;

        for (int i = 0; i < puzzle.n; i++) {
            for (int j = 0; j < puzzle.n; j++) {
                int value = puzzle.board[i][j];
                if (value != 0) {
                    int goalRow = value / puzzle.n;
                    int goalCol = value % puzzle.n;

                    if (i != goalRow || j != goalCol) {
                        misplacedCount++;
                    }
                }
            }
        }
        return misplacedCount;
    }
}
