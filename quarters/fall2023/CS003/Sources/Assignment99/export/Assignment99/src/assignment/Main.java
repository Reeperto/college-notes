package assignment;

import javax.swing.*;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        var scan = new Scanner(System.in);
        scan.useDelimiter(System.lineSeparator());

        System.out.println("""
                1. Task 1
                2. Task 2
                3. Task 3
                4. Task 4
                -1 to quit.""");

        int userChoice = scan.nextInt();

        if (userChoice == -1) {
            System.out.println("Quitting. Thank you.");
            scan.close();
            return;
        }

        if (userChoice == 1) {
            System.out.println(
                    "Please choose the file for the game pattern you would like to start with."
                    + "\n"
                    + "The file must be in the project directory of this programming assignment"
            );
            String file = scan.next();

            System.out.println("What would you like the size of the Game of Life grid to be? (must be larger than the game pattern you selected):");
            Grid grid = new Grid(scan.nextInt());

            if (!file.isBlank()) {
                GameLoader.StateToGrid(file, grid);
            }

            System.out.println("Click the grid to save the current game state to a file");

            SwingUtilities.invokeLater(new Runnable() {
                public void run() {
                    new Renderer(grid).setVisible(true);
                }
            });
        }
    }
}
