package assignment;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class GameLoader {
    public static void StateToGrid(String file_path, Grid grid) {
        try {
            BufferedReader reader = Files.newBufferedReader(Paths.get(file_path), StandardCharsets.UTF_8);

            String[] header = reader.readLine().split(" X ");
            int width = Integer.parseInt(header[0]);
            int height = Integer.parseInt(header[1]);

            for (int j = 0; j < height; ++j) {
                String[] row = reader.readLine().split(" ");
                for (int i = 0; i < width; ++i) {
                    grid.previous_generation[i][j] = Integer.parseInt(row[i]);
                }
            }

        } catch (Exception e) {
            System.out.println("Unable to read game state from file into grid");
        }
    }

    public static void GridToState(String file_path, Grid grid) {
        try {
            BufferedWriter writer = Files.newBufferedWriter(Paths.get(file_path), StandardCharsets.UTF_8,
                    StandardOpenOption.WRITE, StandardOpenOption.CREATE, StandardOpenOption.TRUNCATE_EXISTING);

            writer.write(String.format("%d X %d\n", grid.grid_count, grid.grid_count));

            for (int i = 0; i < grid.grid_count; ++i) {
                for (int j = 0; j < grid.grid_count; ++j) {
                    writer.write(grid.current_generation[j][i] == 1 ? "1 " : "0 ");
                }
                writer.write('\n');
            }

            writer.close();
        } catch (Exception e) {
            System.out.println("Unable to write game state from grid into file");
        }
    }
}