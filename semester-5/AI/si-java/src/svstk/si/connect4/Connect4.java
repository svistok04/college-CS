package svstk.si.connect4;

import sac.game.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class Connect4 extends GameStateImpl {

    public static final boolean O_PLAYER_AI = false;
    public static final boolean X_PLAYER_AI = true;

    public int emptyCells = m*n; 

    public static final int m = 6; // col
    public static final int n = 7; // row

    protected static final byte O = 1;
    protected static final byte EMPTY = 0;
    protected static final byte X = -1;
    private static final String[] SYMBOLS = new String[] {"X", ".", "O"};


    private byte[][] board;
    private int lastMoveI = -1;
    private int lastMoveJ = -1;

    public Connect4() {
        board = new byte[m][n];
        for (int i = 0; i < board.length; i++) {
            Arrays.fill(board[i], EMPTY);
        }
    }

    public Connect4(Connect4 parent) {
        board = new byte[m][n];
        for (int i = 0; i < board.length; i++) {
            board[i] = Arrays.copyOf(parent.board[i], parent.board[i].length);
        }
        setMaximizingTurnNow(parent.isMaximizingTurnNow());
    }

    public byte getPieceAt(int row, int col) {
        if (row >= 0 && row < m && col >= 0 && col < n) {
            return board[row][col];
        }
        throw new IllegalArgumentException("out of bounds");
    }

    public int countChain(int row, int col, int rowDir, int colDir, byte piece) {
        int length = 0;
        int r = row;
        int c = col;

        while (r >= 0 && r < m && c >= 0 && c < n && board[r][c] == piece) {
            length++;
            r += rowDir;
            c += colDir;
        }

        return length;
    }


    @Override
    public String toString() {
        StringBuilder txt = new StringBuilder();
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                txt.append("|");
                txt.append(SYMBOLS[board[i][j] + 1]);
            }
            txt.append("|\n");
        }
        for (int j = 0; j < n; j++) {
            txt.append(" ");
            txt.append(Integer.toString(j));
        }

        return txt.toString();
    }

    public boolean move(int j) {
        int i = m - 1;
        for (; i >= 0; i--) {
            if (board[i][j] == EMPTY) {
                break;
            }
        }
        if (i >= 0) {
            board[i][j] = (isMaximizingTurnNow()) ? O : X;
            setMaximizingTurnNow(!isMaximizingTurnNow());
            lastMoveI = i;
            lastMoveJ = j;
            return true;
        }
        return false;
    }

    public boolean isWin() {
        if (lastMoveI == -1 || lastMoveJ == -1) {
            return false;
        }
        byte symbol = board[lastMoveI][lastMoveJ];

        //left-right
        int counter = 0;
        for(int k = 1; k <= 3; k++) {
            if ((lastMoveJ + k >= n) || (board[lastMoveI][lastMoveJ + k] != symbol)) {
                break;
            }
            counter++;
        }

        for(int k = 1; k <= 3; k++) {
            if ((lastMoveJ - k < 0) || (board[lastMoveI][lastMoveJ - k] != symbol)) {
                break;
            }
            counter++;
        }

        if (counter >= 3) {
            return true;
        }

        // down-up
        counter = 0;
        for (int k = 1; k <= 3; k++) {
            if ((lastMoveI + k >= m) || (board[lastMoveI + k][lastMoveJ] != symbol)) {
                break;
            }
            counter++;
        }

        for (int k = 1; k <= 3; k++) {
            if ((lastMoveI - k < 0) || (board[lastMoveI - k][lastMoveJ] != symbol)) {
                break;
            }
            counter++;
        }

        if (counter >= 3) {
            return true;
        }

        // SW-NE
        counter = 0;

        for (int k = 1; k <= 3; k++) {
            if ((lastMoveI - k < 0) || (lastMoveJ + k >= n) || (board[lastMoveI - k][lastMoveJ + k] != symbol)) {
                break;
            }
            counter++;
        }

        for (int k = 1; k <= 3; k++) {
            if ((lastMoveI + k >= m)  || (lastMoveJ - k < 0) || (board[lastMoveI + k][lastMoveJ - k] != symbol)) {
                break;
            }
            counter++;
        }

        if (counter >= 3) {
            return true;
        }

        // SE-NW
        counter = 0;
        for (int k = 1; k <= 3; k++) {
            if ((lastMoveI - k < 0)  || (lastMoveJ - k < 0) || (board[lastMoveI - k][lastMoveJ - k] != symbol)) {
                break;
            }
            counter++;
        }

        for (int k = 1; k <= 3; k++) {
            if ((lastMoveI + k >= m) || (lastMoveJ + k >= n) || (board[lastMoveI + k][lastMoveJ + k] != symbol)) {
                break;
            }
            counter++;
        }

        if (counter >= 3) {
            return true;
        }

        return false;

    }

    public boolean isTie() {
        for (int j = 0; j < n; j++) {
            if (board[0][j] == EMPTY) {
                return false;
            }
        }
        return true;
    }

    @Override
    public List<GameState> generateChildren() {
        List<GameState> children = new ArrayList<>();
        for (int j = 0; j < n; j++) {
            Connect4 child = new Connect4(this);
            if (child.move(j)) {
                children.add(child);
                child.setMoveName(Integer.toString(j));
            }
        }
        emptyCells -= 2;
        return children;
    }

    public int hashCode() {
        byte[] flat = new byte[m * n];
        int k = 0;
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                flat[k++] = board[i][j];
            }
        }
        return Arrays.hashCode(flat);
    }

    // regula sufitu

    public static void main(String[] args) {
        Connect4 c4 = new Connect4();
        Connect4.setHFunction(new Connect4Evaluation());
        System.out.println(c4);
        Scanner scanner = new Scanner(System.in);
        int j = 0;
        GameSearchAlgorithm algo = new AlphaBetaPruning(); // new MinMax();
        GameSearchConfigurator conf = new GameSearchConfigurator();
        conf.setDepthLimit(5.5);
        algo.setConfigurator(conf);
        while (true) {
            if (O_PLAYER_AI) {
                System.out.println(c4.emptyCells);
                algo.setInitial(c4);
                algo.execute();
                int bestMove = Integer.valueOf(algo.getFirstBestMove());
                c4.move(bestMove);
                System.out.println("MOVES SCORES: " + algo.getMovesScores());
                System.out.println("STATES: " + algo.getClosedStatesCount());
                System.out.println("TIME [ms]: " + algo.getDurationTime());
                System.out.println("MOVE PLAYED: " + bestMove);
            }
            else {
                boolean moveLegal = false;
                do {
                    System.out.print("O PLAYER YOUR MOVE: ");
                    j = scanner.nextInt();
                    moveLegal = c4.move(j);
                } while (!moveLegal);
            }
            System.out.println(c4);
            if (c4.isWin()) {
                System.out.println("O PLAYER (MAX) WINS!");
                break;
            }
            if (c4.isTie()) {
                System.out.println("GAME TIED.");
                break;
            }

            if (X_PLAYER_AI) {
                algo.setInitial(c4);
                algo.execute();
                int bestMove = Integer.valueOf(algo.getFirstBestMove());
                c4.move(bestMove);
                System.out.println("MOVES SCORES: " + algo.getMovesScores());
                System.out.println("STATES: " + algo.getClosedStatesCount());
                System.out.println("TIME [ms]: " + algo.getDurationTime());
                System.out.println("MOVE PLAYED: " + bestMove);
            }
            else {
                boolean moveLegal = false;
                do {
                    System.out.print("X PLAYER YOUR MOVE: ");
                    j = scanner.nextInt();
                    moveLegal = c4.move(j);
                } while (!moveLegal);
            }
            System.out.println(c4);
            if (c4.isWin()) {
                System.out.println("X PLAYER (MIN) WINS!");
                break;
            }
            if (c4.isTie()) {
                System.out.println("GAME TIED.");
                break;
            }
        }
        scanner.close();
    }
}