#include "raylib.h"
#include <string>
#include <cstdlib>

class Board
{
    public:
        int mines[16][30][3];
        Board(int boardWidth, int boardHeigth, int numberOfMines) {

            // pick random mine locations
            int tempMineCnt = 0;
            int tempMineLoc = 0;
            int maxMines = numberOfMines;
            int mineLocations[boardHeigth*boardWidth]{};
            int cellCnt = 0;

            while (tempMineCnt < maxMines) {
                tempMineLoc = rand() % (boardHeigth * boardWidth);
                if (mineLocations[tempMineLoc] != 1) {
                    mineLocations[tempMineLoc] = 1;
                    tempMineCnt++;
                }
            }

            // place mines on board
            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 30; j++) {
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

            // add number of mines near location
            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 30; j++) {
                    if (mines[i][j][0] != 3) {
                        if (i == 0 && j == 0) {
                            if (mines[i][j+1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i+1][j+1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i+1][j][1] == 1) { mines[i][j][2]++; }
                        } else if (i == 0 && j < boardWidth-1 && j > 0) {
                            if (mines[i][j-1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i+1][j-1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i+1][j][1] == 1) { mines[i][j][2]++; }
                            if (mines[i+1][j+1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i][j+1][1] == 1) { mines[i][j][2]++; }
                        } else if (i == 0 && j == boardWidth-1) {
                            if (mines[i][j-1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i+1][j-1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i+1][j][1] == 1) { mines[i][j][2]++; }
                        } else if (i > 0 && i < boardHeigth-1 && j == 0) {
                            if (mines[i-1][j][1] == 1) { mines[i][j][2]++; }
                            if (mines[i-1][j+1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i][j+1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i+1][j+1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i+1][j][1] == 1) { mines[i][j][2]++; }
                        } else if (i > 0 && i < boardHeigth-1 && j > 0 && j < boardWidth-1) {
                            if (mines[i-1][j-1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i-1][j][1] == 1) { mines[i][j][2]++; }
                            if (mines[i-1][j+1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i][j-1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i][j+1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i+1][j-1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i+1][j][1] == 1) { mines[i][j][2]++; }
                            if (mines[i+1][j+1][1] == 1) { mines[i][j][2]++; }
                        } else if (i > 0 && i < boardHeigth-1 && j == boardWidth-1) {
                            if (mines[i-1][j][1] == 1) { mines[i][j][2]++; }
                            if (mines[i-1][j-1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i][j-1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i+1][j-1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i+1][j][1] == 1) { mines[i][j][2]++; }
                        } else if (i == boardHeigth-1 && j == 0) {
                            if (mines[i-1][j][1] == 1) { mines[i][j][2]++; }
                            if (mines[i-1][j+1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i][j+1][1] == 1) { mines[i][j][2]++; }
                        } else if (i == boardHeigth-1 && j > 0 && j < boardWidth-1) {
                            if (mines[i][j-1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i-1][j-1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i-1][j][1] == 1) { mines[i][j][2]++; }
                            if (mines[i-1][j+1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i][j+1][1] == 1) { mines[i][j][2]++; }
                        } else if (i == boardHeigth-1 && j == boardWidth-1) {
                            if (mines[i][j-1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i-1][j-1][1] == 1) { mines[i][j][2]++; }
                            if (mines[i-1][j][1] == 1) { mines[i][j][2]++; }
                        }
                    }
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
    int boardWidth = 16;
    int boardHeight = 16;
    int numberOfMines = 40;
    Board board{boardWidth, boardHeight, numberOfMines};
    int boxWidth = 40;
    int boxHeight = 40;
    int fontSize = 32;
        

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();

        const float dT { GetFrameTime() };
        runningTime += dT;

        ClearBackground(WHITE);

        // draw board text test
        if (boardWidth > 27) {
            boxWidth = 40;
            boxHeight = 40;
        } else {
            boxWidth = 45;
            boxHeight = 45;
        }
        int xPos = WIN_WIDTH/2 - (boxWidth*boardWidth + boardWidth-1)/2;
        int yPos = WIN_HEIGHT/2 + 30 - (boxHeight*boardHeight + boardHeight-1)/2;
        char tempText[10];
        for (int i = 0; i < 16; i++){
            for (int j = 0; j < 30; j++) {
                if (board.mines[i][j][0] != 3) {
                    DrawRectangle(xPos + j*(boxWidth+1), yPos + i*(boxHeight+1), boxWidth, boxHeight, BLUE);
                    if (board.mines[i][j][1] == 1 && board.mines[i][j][0] == 1) {
                        DrawRectangle(xPos + j*(boxWidth+1)+1, yPos + i*(boxHeight+1)+1, boxWidth-2, boxHeight-2, RED);
                    }
                    if (board.mines[i][j][1] == 0 && board.mines[i][j][0] == 1) {
                        DrawRectangle(xPos + j*(boxWidth+1)+1, yPos + i*(boxHeight+1)+1, boxWidth-2, boxHeight-2, WHITE);
                        if (board.mines[i][j][2] > 0) {
                            std::sprintf(tempText, "%d", board.mines[i][j][2]);
                            DrawText(tempText, xPos + j*(boxWidth+1) + boxWidth/2 - MeasureText(tempText, 32)/2, yPos + i*(boxHeight+1) + boxHeight/2 - fontSize/2, fontSize, GREEN);
                        }
                    }
                }
            }
        }
        EndDrawing();
    }
    CloseWindow();
}