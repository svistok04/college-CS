package svstk.si.sudoku;

import sac.IdentifierType;
import sac.graph.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

public class Sudoku extends GraphStateImpl {

    public static final int n = 3;
    public static final int n2 = n*n;
    private byte[][] board = null;

    public int getZeros() {
        return zeros;
    }

    private int zeros = n2 * n2;

    public Sudoku() {
        board = new byte[n2][n2];
        for (int i = 0; i < n2; i++) {
            for (int j = 0; j < n2; j++) {
                board[i][j] = 0;
            }
        }
    }

    public Sudoku(Sudoku parent) {
        board = new byte[n2][n2];
        for (int i = 0; i < n2; i++) {
            for (int j = 0; j < n2; j++) {
                board[i][j] = parent.board[i][j];
            }
            zeros = parent.zeros;
        }
    }

    private void refreshZeros() {
        zeros = 0;
        for (int i = 0; i < n2; i++) {
            for (int j = 0; j < n2; j++) {
                if (board[i][j] == 0) {
                    zeros++;
                }
            }
        }
    }

    @Override
    public String toString() {
//        String txt = "";
//
//        for (int i = 0; i < n2; i++) {
//            for (int j = 0; j < n2; j++) {
//                //txt += (j == n2 - 1) ? board[i][j] + "\n" : board[i][j] + ", ";
//                txt += board[i][j] + ", ";
//            }
//            txt += "\n";
//        }
//        return txt;
        StringBuilder txt = new StringBuilder();

        for (int i = 0; i < n2; i++) {
            for (int j = 0; j < n2; j++) {
                //txt.append(board[i][j] + " ");
                txt.append(board[i][j]);
                txt.append(" ");
            }
            txt.append("\n");
        }

        return txt.toString();
    }

    public void fromString(String txt) {
        for (int i = 0; i < txt.length(); i++) {
            board[i / 9][i % 9] = Byte.valueOf(txt.substring(i, i+1));
        }
        refreshZeros();
    }

    public static boolean isGroupLegal(byte[] group) {
        boolean[] visited = new boolean[group.length + 1];
        Arrays.fill(visited, false);
        for (int i = 0; i < n2; i++) {
            if (group[i] == 0) {
                continue;
            }
            if (visited[group[i]]) {
                return false;
            }
            visited[group[i]] = true;
        }
        return true;
    }

    public boolean isLegal() {
        // sprawdzenie wierszy
//        for (int i = 0; i < n; i++) {
//            boolean flag = isGroupLegal(board[i]);
//            if (flag == false) {
//                return false;
//            }
//        }
        byte[] group = new byte[n2];
        for (int i = 0; i < n2; i++) {
//            for (int j = 0; j < n2; j++) {
//                group[j] = board[i][j];
//            }
            if (!Sudoku.isGroupLegal(board[i])) {
                return false;
            }
        }
        // sprawdzenie kolumn
        for (int i = 0; i < n2; i++) {
            for (int j = 0; j < n2; j++) {
                group[j] = board[j][i];
            }
            if (!Sudoku.isGroupLegal(group)) {
                return false;
            }
        }
        // sprawdzenie podkwadratów
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int q = 0;
                for (int k = 0; k < n; k++) {
                    for (int l = 0; l < n; l++) {
                        group[q++] = board[i * n + k][j * n + l];
                    }
                }
                if (!Sudoku.isGroupLegal(group)) {
                    return false;
                }
            }
        }
        return true;
    }

    @Override
    public List<GraphState> generateChildren() {
        List<GraphState> children = new ArrayList<>();
        int i = 0, j = 0;
        zeroFinder:
        for (i = 0; i < n2; i++) {
            for (j = 0; j < n2; j++) {
                if (board[i][j] == 0) {
                    break zeroFinder;
                }
            }
        }
        if (i == n2) { // full list
            return children;
        }
        for (int k = 0; k <= n2; k++) {
            Sudoku child = new Sudoku(this);
            child.board[i][j] = (byte) k;
            if (child.isLegal()) {
                children.add(child);
                child.zeros--;
            }
        }

        return children;
    }

    @Override
    public boolean isSolution() {
        return ((zeros == 0) && (isLegal()));
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Sudoku sudoku)) return false;
        if (!super.equals(o)) return false;
        return zeros == sudoku.zeros && Objects.deepEquals(board, sudoku.board);
    }

    @Override
    public int hashCode() {
        byte[] flatSudoku = new byte[n2 * n2];
        int k = 0;
        for (int i = 0; i < n2; i++) {
            for (int j = 0; j < n2; j++) {
                flatSudoku[k++] = board[i][j];
            }
        }
        return Arrays.hashCode(flatSudoku);

//        return Arrays.deepHashCode(board);

        //return toString().hashCode();
        //return Objects.hash(Arrays.deepHashCode(board), zeros);
    }

    public static void main(String[] args) {
        Sudoku sudoku = new Sudoku();
        String sudokuTxt = "003020600900305001001806400008102900700000008006708200002609500800203009005010300";
        //String sudokuTxt = "000000000000005001001806400008102900700000008006708200002609500800203009005010300";
        sudoku.fromString(sudokuTxt);
        System.out.println(sudoku);
//        System.out.println(sudoku.isLegal());
//        System.out.println(sudoku.zeros);
        GraphSearchConfigurator conf = new GraphSearchConfigurator();
        conf.setWantedNumberOfSolutions(Integer.MAX_VALUE);
        conf.setIdentifierType(IdentifierType.HASH_CODE);
        GraphSearchAlgorithm algo = new BestFirstSearch(sudoku, conf);
        Sudoku.setHFunction(new EmptyCellsHeuristic());
//        algo.setConfigurator(conf);
        algo.execute();
        List<GraphState> solutions = algo.getSolutions();
        for (GraphState solution : solutions) {
            System.out.println(solution);
        }
        System.out.println("Time [ms]: " + algo.getDurationTime());
        System.out.println("Closed: " + algo.getClosedStatesCount());
        System.out.println("Open: " + algo.getOpenSet().size());
        System.out.println("Solutions: " + solutions.size());
    }
}
