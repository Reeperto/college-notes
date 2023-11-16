package assignment;

import java.awt.Color;
import java.awt.Graphics;
import javax.swing.JFrame;

public class Grid {
    int window_padding = 50;
    int window_width = 800 - 2 * window_padding;
    int window_height = 800 - 2 * window_padding;

    int spacing;
    int grid_count;

    int[][] previous_generation;
    int[][] current_generation;

    Grid(int size) {
        SetGrid(size);
    }

    private int Mod(int pos) {
        return ((pos % grid_count) + grid_count) % grid_count;
    }

    public void SetGrid(int size) {
        previous_generation = new int[size][size];
        current_generation = new int[size][size];
        grid_count = size;
        spacing = window_width / size;
    }


    public void AdvanceGeneration() {
        int neighbors;
        int current_cell;

        for (int i = 0; i < grid_count; ++i) {
            for (int j = 0; j < grid_count; ++j) {
                current_cell = previous_generation[i][j];
                neighbors = 0;

                neighbors += previous_generation[Mod(i - 1)][Mod(j - 1)];
                neighbors += previous_generation[Mod(i - 1)][Mod(j)];
                neighbors += previous_generation[Mod(i - 1)][Mod(j + 1)];

                neighbors += previous_generation[Mod(i)][Mod(j - 1)];
                neighbors += previous_generation[Mod(i)][Mod(j + 1)];

                neighbors += previous_generation[Mod(i + 1)][Mod(j - 1)];
                neighbors += previous_generation[Mod(i + 1)][Mod(j)];
                neighbors += previous_generation[Mod(i + 1)][Mod(j + 1)];


                if (current_cell == 1) {
                    if (neighbors == 2 || neighbors == 3) {
                        current_generation[i][j] = 1;
                    } else {
                        current_generation[i][j] = 0;
                    }
                } else {
                    if (neighbors == 3) {
                        current_generation[i][j] = 1;
                    } else {
                        current_generation[i][j] = 0;
                    }
                }

            }
        }

        for (int i = 0; i < grid_count; ++i) {
            for (int j = 0; j < grid_count; ++j) {
                previous_generation[i][j] = current_generation[i][j];
            }
        }
    }

    public void paint(Graphics g) {
        g.setColor(Color.WHITE);
        g.clearRect(window_padding, window_padding, window_width, window_height);
        g.setColor(Color.BLACK);
        g.drawRect(window_padding, window_padding, window_width, window_height);
        for (int i = 0; i < grid_count; i++) {
            for (int j = 0; j < grid_count; j++) {
                if (previous_generation[i][j] == 1) {
                    g.fillRect(i * spacing + window_padding, j * spacing + window_padding, spacing, spacing);
                } else {
                    g.drawRect(i * spacing + window_padding, j * spacing + window_padding, spacing, spacing);
                }
            }
        }
    }
}