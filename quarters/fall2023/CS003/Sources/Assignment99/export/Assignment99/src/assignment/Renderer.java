package assignment;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Scanner;

public class Renderer extends JFrame {

    public Grid grid;
    private final Timer timer;
    private final Scanner scanner = new Scanner(System.in);

    public Renderer(Grid grid) {
        setTitle("Game of Life");
        setSize(800, 800);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);

        this.grid = grid;

        JPanel gridPanel = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                draw(g);
            }
        };
        gridPanel.setPreferredSize(new Dimension(800, 800));
        gridPanel.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                timer.stop();
                doFileInputOutput();
                timer.start();
            }
        });

        add(gridPanel);
        pack();

        int delay = 200; // milliseconds
        ActionListener taskPerformer = new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
                update();
                repaint();
            }
        };
        timer = new Timer(delay, taskPerformer);
        timer.start();
    }

    public void draw(Graphics g) {
        grid.paint(g);
    }

    public void update() {
        grid.AdvanceGeneration();
    }

    public void doFileInputOutput() {
        boolean validInput = false;

        System.out.println("Saving game state...");
        while (!validInput) {
            System.out.print("Please enter a filename: ");

            String filename = scanner.nextLine();

            if (!filename.isBlank()) {
                validInput = true;
                GameLoader.GridToState(filename, grid);
                System.out.println("Wrote game state to " + filename);
            } else {
                System.out.println("Invalid input. Please try again.");
            }
        }
    }
}
