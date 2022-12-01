#include "raylib.h"
#include <string>
#include <cstdlib>

class Board
{
    public:
        int mines[30][16][3];
        Board(int boardWidth, int boardHeigth, int numberOfMines) {

            // pick random mine locations
            int tempMineCnt = 0;
            int tempMineLoc = 0;
            int maxMines = numberOfMines;
            int mineLocations[99]{};
            int cellCnt = 0;

            while (tempMineCnt < maxMines) {
                tempMineLoc = rand() % (boardHeigth * boardWidth);
                if (mineLocations[tempMineLoc] != 1) {
                    mineLocations[tempMineLoc] = 1;
                    tempMineCnt++;
                }
            }

            for (int i = 0; i < 30; i++) {
                for (int j = 0; j < 16; j++) {
                    if (mineLocations[cellCnt] == 1 && i < boardHeigth && j < boardWidth) {
                        mines[i][j][0] = 0;
                        mines[i][j][1] = 1;
                        cellCnt++;
                    } else if (i < boardHeigth && j < boardWidth) {
                        mines[i][j][0] = 0;
                        mines[i][j][1] = 0;
                        cellCnt++;
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
    int boardWidth = 9;
    int boardHeight = 9;
    int numberOfMines = 10;
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