package svstk.si.connect4;

import sac.State;
import sac.StateFunction;

public class Connect4Evaluation extends StateFunction {

    @Override
    public double calculate(State state) {
        Connect4 connect4 = (Connect4) state;

        // check if the game is in a win state
        if (connect4.isWin()) {
            return connect4.isMaximizingTurnNow() ? Double.NEGATIVE_INFINITY : Double.POSITIVE_INFINITY;
        }

        // set endgame mode based on the number of empty cells
        boolean endgameMode = (connect4.emptyCells < connect4.m * connect4.n / 3);

        double score = 0.0;
        // for each cell
        for (int row = 0; row < connect4.m; row++) {
            for (int col = 0; col < connect4.n; col++) {
                byte piece = connect4.getPieceAt(row, col);

                // skip empty cells
                if (piece == Connect4.EMPTY) continue;

                // center control scoring only in early game
                if (!endgameMode) {
                    int centerDistance = Math.abs(col - connect4.n / 2);
                    score += (piece == Connect4.O ? 3 - centerDistance : -(3 - centerDistance));
                }
                // chain scoring with adjusted weights if in endgame mode
                score += evaluateChain(connect4, row, col, piece, endgameMode);
            }
        }

        return score;
    }

    // chain length and orientation scoring; adjusts scoring based on endgame mode
    private double evaluateChain(Connect4 connect4, int row, int col, byte piece, boolean endgameMode) {
        double chainScore = 0.0;
        // prioritizes aggressive chain-building in early game, shifts to blocking opponent chains in late game
        double agressiveMultiplier = endgameMode ? 1.7 : 1.5;
        double blockMultiplier = endgameMode ? 2.0 : 1.0;
        // horizontal chain scoring
        int horizontalLength = connect4.countChain(row, col, 0, 1, piece);
        if (piece == Connect4.O) {
            // prioritize AI's own chains
            chainScore += (horizontalLength == 3 ? 4 * agressiveMultiplier : (horizontalLength == 2 ? 2 : (horizontalLength == 1 ? 1 : 0)));
        } else {
            // prioritize blocking opponent's chains in endgame mode
            chainScore -= (horizontalLength == 3 ? 4 * blockMultiplier : (horizontalLength == 2 ? 2 : (horizontalLength == 1 ? 1 : 0)));
        }

        // vertical chain scoring
        int verticalLength = connect4.countChain(row, col, 1, 0, piece);
        if (piece == Connect4.O) {
            // prioritize AI's own chains
            chainScore += (verticalLength == 3 ? 4 * agressiveMultiplier : (verticalLength == 2 ? 2 : (verticalLength == 1 ? 1 : 0)));
        } else {
            // prioritize blocking opponent's chains in endgame mode
            chainScore -= (verticalLength == 3 ? 4 * blockMultiplier : (verticalLength == 2 ? 2 : (verticalLength == 1 ? 1 : 0)));
        }

        // diagonal chains scoring
        int diag1Length = connect4.countChain(row, col, 1, 1, piece);
        int diag2Length = connect4.countChain(row, col, 1, -1, piece);
        if (piece == Connect4.O) {
            // prioritize AI's own chains
            chainScore += (diag1Length == 3 ? 3 * agressiveMultiplier : (diag1Length == 2 ? 1.5 : (diag1Length == 1 ? 0.5 : 0)));
            chainScore += (diag2Length == 3 ? 3 * agressiveMultiplier : (diag2Length == 2 ? 1.5 : (diag2Length == 1 ? 0.5 : 0)));
        } else {
            // prioritize blocking opponent's chains in endgame mode
            chainScore -= (diag1Length == 3 ? 3 * blockMultiplier : (diag1Length == 2 ? 1.5 : (diag1Length == 1 ? 0.5 : 0)));
            chainScore -= (diag2Length == 3 ? 3 * blockMultiplier : (diag2Length == 2 ? 1.5 : (diag2Length == 1 ? 0.5 : 0)));
        }

        return chainScore;
    }

}
