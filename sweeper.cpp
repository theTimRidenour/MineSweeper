#include "raylib.h"
#include <string>
#include <map>

class Board
{
    public:
        int mines[20][20][3];
        Board(int boardWidth, int boardHeigth, int numberOfMines) {
            int numOfMines = numberOfMines;
            for (int i = 0; i < 20; i++) {
                for (int j = 0; j < 20; j++) {
                    if (numOfMines > 0 && i < boardHeigth && j < boardWidth) {
                        mines[i][j][0] = 0;
                        mines[i][j][1] = 1;
                        numOfMines--;
                    } else if (numOfMines <= 0 && i < boardHeigth && j < boardWidth) {
                        mines[i][j][0] = 0;
                        mines[i][j][1] = 0;
                    } else {
                        mines[i][j][0] = 3;
                        mines[i][j][1] = 0;
                    }
                    mines[i][j][2] = 0;
                }
            }
        }
};

int main(int argc, char const *argv[])
{
    // initialize window
    const int WIN_WIDTH = 1280;
    const int WIN_HEIGHT = 800;
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Mine Sweeper");

    // universal timer
    const float updateTime = 1.0/60.0;
    float runningTime = 0.0;

    // board
    int boardWidth = 10;
    int boardHeight = 10;
    int numberOfMines = 40;
    Board board{boardWidth, boardHeight, numberOfMines};

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();

        const float dT { GetFrameTime() };
        runningTime += dT;

        ClearBackground(WHITE);

        // draw board text test
        int tempWidth = 100;
        int tempHeight = 30;
        char tempText[10];
        for (int i = 0; i < 20; i++){
            for (int j = 0; j < 20; j++) {
                if (board.mines[i][j][0] != 3) {
                    std::sprintf(tempText, "(%d, %d, %d)", board.mines[i][j][0], board.mines[i][j][1], board.mines[i][j][2]);
                    DrawText(tempText, 10 + j * tempWidth, 10 + i * tempHeight, 20, BLACK);
                }
            }
        }

        EndDrawing();
    }
    CloseWindow();
}