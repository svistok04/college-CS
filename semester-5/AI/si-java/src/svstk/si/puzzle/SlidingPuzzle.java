package svstk.si.puzzle;

import sac.IdentifierType;
import sac.graph.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.io.FileWriter;
import java.io.IOException;

import sac.StateFunction;

public class SlidingPuzzle extends GraphStateImpl {
    static int numTests = 100;
    static int numShuffles = 1000;
    int n = 3;
    byte[][] board = new byte[n][n];
    int zeroRow, zeroCol;
    StringBuilder path;

    public StringBuilder getPathString() {
        return path;
    }

    public SlidingPuzzle(int nShuffles) {
        int tile = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) {
                    board[i][j] = 0;
                    zeroRow = i;
                    zeroCol = j;
                } else {
                    board[i][j] = (byte) tile++;
                }
            }
        }
        path = new StringBuilder();
        shuffle(nShuffles);
    }

    public SlidingPuzzle(SlidingPuzzle parent) {
        this.board = new byte[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                this.board[i][j] = parent.board[i][j];
            }
        }
        this.zeroRow = parent.zeroRow;
        this.zeroCol = parent.zeroCol;
        this.path = parent.path;
    }

    private void shuffle(int moves) {
        Random rnd = new Random();
        int previousDirection = -1;

        for (int i = 0; i < moves; i++) {
            boolean validMove = false;

            while (!validMove) {
                int direction = rnd.nextInt(4);
                if (direction == (previousDirection + 2) % 4) {
                    continue;
                }

                int newRow = zeroRow, newCol = zeroCol;

                switch (direction) {
                    case 0:  // Up
                        newRow = zeroRow - 1;
                        break;
                    case 1:  // Down
                        newRow = zeroRow + 1;
                        break;
                    case 2:  // Left
                        newCol = zeroCol - 1;
                        break;
                    case 3:  // Right
                        newCol = zeroCol + 1;
                        break;
                }

                if (isValid(newRow, newCol)) {
                    board[zeroRow][zeroCol] = board[newRow][newCol];
                    board[newRow][newCol] = 0;
                    zeroRow = newRow;
                    zeroCol = newCol;

                    previousDirection = direction;
                    validMove = true;
                }
            }
        }
    }

    @Override
    public List<GraphState> generateChildren() {
        List<GraphState> children = new ArrayList<>();
        int[][] moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        char[] moveNames = {'U', 'D', 'L', 'R'};
        for (int i = 0; i < moves.length; i++) {
            int newRow = zeroRow + moves[i][0];
            int newCol = zeroCol + moves[i][1];

            if (isValid(newRow, newCol)) {
                SlidingPuzzle child = new SlidingPuzzle(this);
                child.board[zeroRow][zeroCol] = child.board[newRow][newCol];
                child.board[newRow][newCol] = 0;
                child.zeroRow = newRow;
                child.zeroCol = newCol;
                child.path.append(moveNames[i]);
                children.add(child);
            }
        }
        return children;
    }


    @Override
    public int hashCode() {
        byte[] flatPuzzle = new byte[n * n];
        int k = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                flatPuzzle[k++] = board[i][j];
            }
        }
        return Arrays.hashCode(flatPuzzle);
    }

    public void fromString(String txt) {
        int index = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] = Byte.parseByte(txt.substring(index, index + 1));
                if (board[i][j] == 0) {
                    zeroRow = i;
                    zeroCol = j;
                }
                index++;
            }
        }
    }


    private boolean isValid(int row, int col) {
        return row >= 0 && row < n && col >= 0 && col < n;
    }

    @Override
    public boolean isSolution() {
        int tile = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] != tile++) {
                    return false;
                }
            }
        }
        return true;
    }


    @Override
    public String toString() {
        StringBuilder txt = new StringBuilder();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                txt.append(board[i][j]);
                txt.append(" ");
            }
            txt.append("\n");
        }

        return txt.toString();
    }
    public static void main(String[] args) {
//        singleTest();
        multipleTest();
    }

    private static void singleTest() {
        SlidingPuzzle puzzle = new SlidingPuzzle(numShuffles);
        GraphSearchConfigurator conf = new GraphSearchConfigurator();
        conf.setWantedNumberOfSolutions(1);
        conf.setIdentifierType(IdentifierType.HASH_CODE);
        puzzle.setHFunction(new ManhattanHeuristic());
        GraphSearchAlgorithm algo = new BestFirstSearch(puzzle, conf);

        System.out.println(puzzle.toString());
        algo.execute();
        List<GraphState> solutions = algo.getSolutions();
        System.out.println("Manhattan");
        System.out.println();
        System.out.println(solutions.isEmpty() ? "" : ((SlidingPuzzle) solutions.get(0)).getPathString().toString()); // Use custom path);
        System.out.println(solutions.isEmpty() ? "" : ((SlidingPuzzle) solutions.get(0)).getPathString().length());
        System.out.println(solutions.get(0).toString());

        puzzle.setHFunction(new MisplacedTilesHeuristic());
        GraphSearchAlgorithm algo2 = new BestFirstSearch(puzzle, conf);
        System.out.println(puzzle.toString());
        algo2.execute();
        List<GraphState> solutions2 = algo2.getSolutions();
        System.out.println("Misplaced Tiles");
        System.out.println();
        System.out.println(solutions2.isEmpty() ? "" : ((SlidingPuzzle) solutions.get(0)).getPathString().toString()); // Use custom path);
        System.out.println(solutions2.isEmpty() ? "" : ((SlidingPuzzle) solutions2.get(0)).getPathString().length());
        System.out.println(solutions2.get(0).toString());
    }

    private static void multipleTest() {
        List<String[]> results = new ArrayList<>();
        results.add(new String[]{"Test Number", "Heuristic", "Execution Time [ms]", "Closed States", "Open States", "Path Length", "Path"});

        long totalManhattanTime = 0;
        long totalManhattanClosed = 0;
        long totalManhattanOpen = 0;
        long totalManhattanPathLength = 0;

        long totalMisplacedTime = 0;
        long totalMisplacedClosed = 0;
        long totalMisplacedOpen = 0;
        long totalMisplacedPathLength = 0;

        for (int i = 0; i < numTests; i++) {
            SlidingPuzzle puzzle = new SlidingPuzzle(numShuffles);

            long[] manhattanResults = runExperiment(puzzle, new ManhattanHeuristic(), results, i + 1);
            totalManhattanTime += manhattanResults[0];
            totalManhattanClosed += manhattanResults[1];
            totalManhattanOpen += manhattanResults[2];
            totalManhattanPathLength += manhattanResults[3];

            long[] misplacedResults = runExperiment(puzzle, new MisplacedTilesHeuristic(), results, i + 1);
            totalMisplacedTime += misplacedResults[0];
            totalMisplacedClosed += misplacedResults[1];
            totalMisplacedOpen += misplacedResults[2];
            totalMisplacedPathLength += misplacedResults[3];
        }

        results.add(new String[]{"", "Manhattan Summary",
                String.valueOf(Float.valueOf(totalManhattanTime) / numTests),
                String.valueOf(Float.valueOf(totalManhattanClosed) / numTests),
                String.valueOf(Float.valueOf(totalManhattanOpen) / numTests),
                String.valueOf(Float.valueOf(totalManhattanPathLength) / numTests),
                ""
        });

        results.add(new String[]{"", "Misplaced Tiles Summary",
                String.valueOf(Float.valueOf(totalMisplacedTime) / numTests),
                String.valueOf(Float.valueOf(totalMisplacedClosed) / numTests),
                String.valueOf(Float.valueOf(totalMisplacedOpen) / numTests),
                String.valueOf(Float.valueOf(totalMisplacedPathLength) / numTests),
                ""
        });

        System.out.println("Manhattan");
        System.out.println("Total time [s]: " + Float.valueOf(totalManhattanTime) / 1000);
        System.out.println("Total closed: " + totalManhattanClosed);
        System.out.println("Total open: " + totalManhattanOpen);
        System.out.println("Total path length: " + totalManhattanPathLength + "\n");

        System.out.println("Misplaced Tiles");
        System.out.println("Total time [s]: " + Float.valueOf(totalMisplacedTime) / 1000);
        System.out.println("Total closed: " + totalMisplacedClosed);
        System.out.println("Total open: " + totalMisplacedOpen);
        System.out.println("Total path length: " + totalMisplacedPathLength );

        try (FileWriter writer = new FileWriter("heuristics_comparison_grouped.csv")) {
            for (String[] row : results) {
                writer.append(String.join(",", row)).append("\n");
            }
            System.out.println("successfully written to files");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static long[] runExperiment(SlidingPuzzle puzzle, StateFunction heuristic, List<String[]> results, int testNumber) {
        GraphSearchConfigurator conf = new GraphSearchConfigurator();
        conf.setWantedNumberOfSolutions(1);
        conf.setIdentifierType(IdentifierType.HASH_CODE);

        GraphSearchAlgorithm algo = new BestFirstSearch(puzzle, conf);
        puzzle.setHFunction(heuristic);

        algo.execute();

        List<GraphState> solutions = algo.getSolutions();
        int pathLength = solutions.isEmpty() ? 0 : ((SlidingPuzzle) solutions.get(0)).getPathString().length();
        String path = solutions.isEmpty() ? "" : ((SlidingPuzzle) solutions.get(0)).getPathString().toString(); // Use custom path

        results.add(new String[]{
                String.valueOf(testNumber),
                heuristic.getClass().getSimpleName(),
                String.valueOf(algo.getDurationTime()),
                String.valueOf(algo.getClosedStatesCount()),
                String.valueOf(algo.getOpenSet().size()),
                String.valueOf(pathLength),
                "\"" + path + "\""
        });

        return new long[]{
                algo.getDurationTime(),
                algo.getClosedStatesCount(),
                algo.getOpenSet().size(),
                pathLength
        };
    }
}