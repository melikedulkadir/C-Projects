#include "Utils.h"

int main(int argc, char** argv) {
    int **grid;                                 // Creating 2D array with name grid
    int size;
    ofstream output;
    output.open(argv[3], ios::out);           // Creating an output file for output.txt
    if (!output) {
        cout << "File creation failed";
    } else {
        fstream file_1;                          // Reading input1.txt file
        file_1.open(argv[1], ios::in);
        string line;

        if (!file_1) {
            cout << "No such file";
        } else {

            while (getline(file_1, line)) {
                std::stringstream lineStream(line);
                string size_current;
                string grid_row;
                string grid_column;
                lineStream >> size_current >> grid_row >> grid_column;

                if (line.size() < 4) {
                    size = stoi(size_current);
                    grid = new int *[size];
                    initialGrid(grid, size);

                } else {
                    int row = stoi(grid_row);
                    int column = stoi(grid_column);
                    int current = stoi(size_current);

                    place(row, column, size, current, grid);
                    recursive(row, column, size, current, grid);
                }
            }
            file_1.close();
        }
        output << "PART 1:" << endl;
        show(grid, size,output);
        output << endl;

        fstream file_2;
        file_2.open(argv[2], ios::in);                // Reading input2.txt file
        string input_line;
        int **new_grid;                                 // Creating 2D array for part2 with name new_grid
        int grid_size;

        if (!file_2) {
            cout << "No such file";
        } else {
            vector<vector<string>> allTokens;           // Creating vector for reading input2.txt
            while (getline(file_2, line)) {
                vector<string> tokens;
                stringstream mySstream(line);
                string temp;
                while (getline(mySstream, temp, ' ')) {  // Split line form space
                    tokens.push_back(temp);                          // Append in tokens vector
                }
                allTokens.push_back(tokens);                        // Append in allTokens vector
            }

            grid_size = stoi(allTokens[0][0]);
            new_grid = new int *[grid_size];
            int score = 0;
            initialNewGrid(new_grid, grid_size, allTokens);

            for (int i = grid_size + 1; i < allTokens.size(); ++i) {
                int row = stoi(allTokens[i][0]);
                int column = stoi(allTokens[i][1]);
                int current = new_grid[row][column];
                new_grid[row][column] = 0;
                score += current;
                bomb(row, column, current, grid_size, score, "up", new_grid);
                bomb(row, column, current, grid_size, score, "upper left cross", new_grid);
                bomb(row, column, current, grid_size, score, "left", new_grid);
                bomb(row, column, current, grid_size, score, "lower left cross", new_grid);
                bomb(row, column, current, grid_size, score, "down", new_grid);
                bomb(row, column, current, grid_size, score, "lower right cross", new_grid);
                bomb(row, column, current, grid_size, score, "right", new_grid);
                bomb(row, column, current, grid_size, score, "upper right cross", new_grid);
            }
            output << "PART 2:" << endl;
            show(new_grid, grid_size, output);
            output << "Final Point: " << score << "p" << endl;

        }
        file_2.close();
        output.close();
        return 0;
    }
}