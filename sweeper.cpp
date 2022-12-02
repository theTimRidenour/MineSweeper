#include "raylib.h"
#include <string>
#include <cstdlib>

class Board
{
    public:
        int mines[16][30][3];
        Board(int boardWidth, int boardHeigth, int numberOfMines) {
            newBoard(boardWidth, boardHeigth, numberOfMines);
        }

        void newBoard(int boardWidth, int boardHeigth, int numberOfMines) {
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
                        mines[i][j][0] = 4;
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

Board checkSuroundingBlocks(int, int, int, int, Board);

int main(int argc, char const *argv[])
{
    // initialize window
    const int WIN_WIDTH = 1280;
    const int WIN_HEIGHT = 800;
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Mine Sweeper");

    // universal timer
    float gameTime = 0;
    bool playing = false;
    bool timerIsRunning = false;
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    char timerText[20];

    // board
    int boardWidth = 16;
    int boardHeight = 16;
    int numberOfMines = 40;
    Board board(boardWidth, boardHeight, numberOfMines);
    int boxWidth = 40;
    int boxHeight = 40;
    int fontSize = 32;
    bool gameOver = false;
    int mineFlags = numberOfMines;
    char flagText[30];

    // mouse
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        const float dT { GetFrameTime() };

        if (!playing) {
            board.newBoard(boardWidth, boardHeight, numberOfMines);
            playing = true;
            timerIsRunning = true;
        } else {
            gameTime += dT;
            hours = (int)(gameTime / 60 / 60);
            minutes = (int)(gameTime / 60) - (hours * 60 * 60);
            seconds = (int)(gameTime) - (minutes * 60) - (hours * 60 * 60);
        }

        BeginDrawing();

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

        if (IsMouseButtonPressed(0) || IsMouseButtonPressed(1)) {
            mouseX = GetMouseX();
            mouseY = GetMouseY();
            for (int i = 0; i < boardHeight; i++) {
                for (int j = 0; j < boardWidth; j++) {
                    if (mouseX >= xPos + j*(boxWidth+1) &&
                        mouseX <= xPos + j*(boxWidth+1) + boxWidth &&
                        mouseY >= yPos + i*(boxHeight+1) &&
                        mouseY <= yPos + i*(boxHeight+1) + boxHeight) {
                            if (IsMouseButtonPressed(0) && board.mines[i][j][0] == 0) {
                                board.mines[i][j][0] = 1;
                                if (board.mines[i][j][1] == 1) { gameOver = true; }
                                if (board.mines[i][j][2] == 0 && board.mines[i][j][1] != 1) {
                                    board = checkSuroundingBlocks(i, j, boardWidth-1, boardHeight-1, board);
                                }
                            } else if (IsMouseButtonPressed(1) && (board.mines[i][j][0] == 0 || board.mines[i][j][0] == 3)) {
                                if (board.mines[i][j][0] == 0 && mineFlags > 0) {
                                    board.mines[i][j][0] = 3;
                                    mineFlags--;
                                } else if (board.mines[i][j][0] == 3) { 
                                    board.mines[i][j][0] = 0;
                                    mineFlags++;
                                }
                            }
                        }
                }
            }
        }
        for (int i = 0; i < boardHeight; i++){
            for (int j = 0; j < boardWidth; j++) {
                if (board.mines[i][j][0] != 4) {
                    DrawRectangle(xPos + j*(boxWidth+1), yPos + i*(boxHeight+1), boxWidth, boxHeight, BLUE);
                    if (board.mines[i][j][1] == 1 && board.mines[i][j][0] == 1) {
                        DrawRectangle(xPos + j*(boxWidth+1)+1, yPos + i*(boxHeight+1)+1, boxWidth-2, boxHeight-2, RED);
                    }
                    if (board.mines[i][j][1] == 0 && board.mines[i][j][0] == 1) {
                        DrawRectangle(xPos + j*(boxWidth+1)+1, yPos + i*(boxHeight+1)+1, boxWidth-2, boxHeight-2, WHITE);
                        if (board.mines[i][j][2] > 0) {
                            std::sprintf(tempText, "%d", board.mines[i][j][2]);
                            DrawText(tempText, xPos + j*(boxWidth+1) + boxWidth/2 - MeasureText(tempText, fontSize)/2, yPos + i*(boxHeight+1) + boxHeight/2 - fontSize/2, fontSize, GREEN);
                        }
                    }
                    if (board.mines[i][j][0] == 3) {
                        DrawText("Q", xPos + j*(boxWidth+1) + boxWidth/2 - MeasureText("Q", fontSize)/2, yPos + i*(boxHeight+1) + boxHeight/2 - fontSize/2, fontSize, LIGHTGRAY);
                    }
                }
            }
        }

        // draw flag counter
        std::sprintf(flagText, "Mines: %d", mineFlags);
        DrawText(flagText, WIN_WIDTH - 200, 20, 32, BLACK);

        // draw timer
        std::sprintf(timerText, "%d:%02d:%02d", hours, minutes, seconds);
        DrawText(timerText, WIN_WIDTH/2 - MeasureText(timerText, 32)/2, 20, 32, BLACK);

        // draw buttons
        mouseX = GetMouseX();
        mouseY = GetMouseY();

        int smB = MeasureText("SMALL", 32) + 20;
        int mdB = MeasureText("MEDIUM", 32) + 20;
        int lgB = MeasureText("LARGE", 32) + 20;

        DrawRectangle(10, 6, smB, 38, DARKBLUE);
        DrawRectangle(10 + smB + 5, 6, mdB, 38, DARKBLUE);
        DrawRectangle(10 + smB + mdB + 10, 6, lgB, 38, DARKBLUE);

        if (mouseX >= 10 && mouseX <= 20 + smB + mdB + lgB && mouseY >= 6 && mouseY <= 6 + 38) {
            // small button interaction
            if (mouseX >= 10 && mouseX <= 10 + smB && IsMouseButtonPressed(0)) {
                playing = false;
                gameTime = 0.0;
                boardWidth = 9;
                boardHeight = 9;
                numberOfMines = 10;
                mineFlags = numberOfMines;
            } else if (mouseX >= 10 && mouseX <= 10 + smB) {
                DrawRectangle(12, 8, smB - 4, 34, BLUE);
                DrawText("SMALL", 20, 10, 32, DARKGRAY);
            } else {
                DrawText("SMALL", 20, 10, 32, BLACK);
            }

            // medium button interaction
            if (mouseX >= 15 + smB && mouseX <= 15 + smB + mdB && IsMouseButtonPressed(0)) {
                playing = false;
                gameTime = 0.0;
                boardWidth = 16;
                boardHeight = 16;
                numberOfMines = 40;
                mineFlags = numberOfMines;
            } else if (mouseX >= 15 + smB && mouseX <= 15 + smB + mdB) {
                DrawRectangle(12 + smB + 5, 8, mdB - 4, 34, BLUE);
                DrawText("MEDIUM", 20 + smB + 5, 10, 32, DARKGRAY);
            } else {
                DrawText("MEDIUM", 20 + smB + 5, 10, 32, BLACK);
            }

            // large button interaction
            if (mouseX >= 20 + smB + mdB && mouseX <= 20 + smB + mdB + lgB && IsMouseButtonPressed(0)) {
                playing = false;
                gameTime = 0.0;
                boardWidth = 30;
                boardHeight = 16;
                numberOfMines = 99;
                mineFlags = numberOfMines;
            } else if (mouseX >= 20 + smB + mdB && mouseX <= 20 + smB + mdB + lgB) {
                DrawRectangle(12 + smB + mdB + 10, 8, lgB - 4, 34, BLUE);
                DrawText("LARGE", 20 + smB + mdB + 10, 10, 32, DARKGRAY);
            } else {
                DrawText("LARGE", 20 + smB + mdB + 10, 10, 32, BLACK);
            }
        } else {
            DrawText("SMALL", 20, 10, 32, BLACK);
            DrawText("MEDIUM", 20 + smB + 5, 10, 32, BLACK);
            DrawText("LARGE", 20 + smB + mdB + 10, 10, 32, BLACK);
        }

        EndDrawing();
    }
    CloseWindow();
}

Board checkSuroundingBlocks(int i, int j, int boardWidth, int boardHeight, Board board) {
    if (board.mines[i][j][1] == 0 && board.mines[i][j][2] == 0) {
        if (i == 0 && j == 0) {
            if (board.mines[i][j+1][0] == 0) {
                board.mines[i][j+1][0] = 1;
                if (board.mines[i][j+1][2] == 0) {
                    board = checkSuroundingBlocks(i, j+1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i+1][j+1][0] == 0) {
                board.mines[i+1][j+1][0] = 1;
                if (board.mines[i+1][j+1][2] == 0) {
                    board = checkSuroundingBlocks(i+1, j+1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i+1][j][0] == 0) {
                board.mines[i+1][j][0] = 1;
                if (board.mines[i+1][j][2] == 0) {
                    board = checkSuroundingBlocks(i+1, j, boardWidth, boardHeight, board);
                }
            }
        } else if (i == 0 && j > 0 && j < boardWidth) {
            if (board.mines[i][j+1][0] == 0) {
                board.mines[i][j+1][0] = 1;
                if (board.mines[i][j+1][2] == 0) {
                    board = checkSuroundingBlocks(i, j+1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i+1][j+1][0] == 0) {
                board.mines[i+1][j+1][0] = 1;
                if (board.mines[i+1][j+1][2] == 0) {
                    board = checkSuroundingBlocks(i+1, j+1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i+1][j][0] == 0) {
                board.mines[i+1][j][0] = 1;
                if (board.mines[i+1][j][2] == 0) {
                    board = checkSuroundingBlocks(i+1, j, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i+1][j-1][0] == 0) {
                board.mines[i+1][j-1][0] = 1;
                if (board.mines[i+1][j-1][2] == 0) {
                    board = checkSuroundingBlocks(i+1, j-1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i][j-1][0] == 0) {
                board.mines[i][j-1][0] = 1;
                if (board.mines[i][j-1][2] == 0) {
                    board = checkSuroundingBlocks(i, j-1, boardWidth, boardHeight, board);
                }
            }
        } else if (i == 0 && j == boardWidth) {
            if (board.mines[i][j-1][0] == 0) {
                board.mines[i][j-1][0] = 1;
                if (board.mines[i][j-1][2] == 0) {
                    board = checkSuroundingBlocks(i, j-1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i+1][j-1][0] == 0) {
                board.mines[i+1][j-1][0] = 1;
                if (board.mines[i+1][j-1][2] == 0) {
                    board = checkSuroundingBlocks(i+1, j-1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i+1][j][0] == 0) {
                board.mines[i+1][j][0] = 1;
                if (board.mines[i+1][j][2] == 0) {
                    board = checkSuroundingBlocks(i+1, j, boardWidth, boardHeight, board);
                }
            }
        } else if (i > 0 && i < boardHeight && j == 0) {
            if (board.mines[i-1][j][0] == 0) {
                board.mines[i-1][j][0] = 1;
                if (board.mines[i-1][j][2] == 0) {
                    board = checkSuroundingBlocks(i-1, j, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i-1][j+1][0] == 0) {
                board.mines[i-1][j+1][0] = 1;
                if (board.mines[i-1][j+1][2] == 0) {
                    board = checkSuroundingBlocks(i-1, j+1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i][j+1][0] == 0) {
                board.mines[i][j+1][0] = 1;
                if (board.mines[i][j+1][2] == 0) {
                    board = checkSuroundingBlocks(i, j+1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i+1][j+1][0] == 0) {
                board.mines[i+1][j+1][0] = 1;
                if (board.mines[i+1][j+1][2] == 0) {
                    board = checkSuroundingBlocks(i+1, j+1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i+1][j][0] == 0) {
                board.mines[i+1][j][0] = 1;
                if (board.mines[i+1][j][2] == 0) {
                    board = checkSuroundingBlocks(i+1, j, boardWidth, boardHeight, board);
                }
            }
        } else if (i > 0 && i < boardHeight && j > 0 && j < boardWidth) {
            if (board.mines[i][j-1][0] == 0) {
                board.mines[i][j-1][0] = 1;
                if (board.mines[i][j-1][2] == 0) {
                    board = checkSuroundingBlocks(i, j-1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i-1][j-1][0] == 0) {
                board.mines[i-1][j-1][0] = 1;
                if (board.mines[i-1][j-1][2] == 0) {
                    board = checkSuroundingBlocks(i-1, j-1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i-1][j][0] == 0) {
                board.mines[i-1][j][0] = 1;
                if (board.mines[i-1][j][2] == 0) {
                    board = checkSuroundingBlocks(i-1, j, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i-1][j+1][0] == 0) {
                board.mines[i-1][j+1][0] = 1;
                if (board.mines[i-1][j+1][2] == 0) {
                    board = checkSuroundingBlocks(i-1, j+1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i][j+1][0] == 0) {
                board.mines[i][j+1][0] = 1;
                if (board.mines[i][j+1][2] == 0) {
                    board = checkSuroundingBlocks(i, j+1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i+1][j+1][0] == 0) {
                board.mines[i+1][j+1][0] = 1;
                if (board.mines[i+1][j+1][2] == 0) {
                    board = checkSuroundingBlocks(i+1, j+1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i+1][j][0] == 0) {
                board.mines[i+1][j][0] = 1;
                if (board.mines[i+1][j][2] == 0) {
                    board = checkSuroundingBlocks(i+1, j, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i+1][j-1][0] == 0) {
                board.mines[i+1][j-1][0] = 1;
                if (board.mines[i+1][j-1][2] == 0) {
                    board = checkSuroundingBlocks(i+1, j-1, boardWidth, boardHeight, board);
                }
            }
        } else if (i > 0 && i < boardHeight && j == boardWidth) {
            if (board.mines[i+1][j][0] == 0) {
                board.mines[i+1][j][0] = 1;
                if (board.mines[i+1][j][2] == 0) {
                    board = checkSuroundingBlocks(i+1, j, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i+1][j-1][0] == 0) {
                board.mines[i+1][j-1][0] = 1;
                if (board.mines[i+1][j-1][2] == 0) {
                    board = checkSuroundingBlocks(i+1, j-1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i][j-1][0] == 0) {
                board.mines[i][j-1][0] = 1;
                if (board.mines[i][j-1][2] == 0) {
                    board = checkSuroundingBlocks(i, j-1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i-1][j-1][0] == 0) {
                board.mines[i-1][j-1][0] = 1;
                if (board.mines[i-1][j-1][2] == 0) {
                    board = checkSuroundingBlocks(i-1, j-1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i-1][j][0] == 0) {
                board.mines[i-1][j][0] = 1;
                if (board.mines[i-1][j][2] == 0) {
                    board = checkSuroundingBlocks(i-1, j, boardWidth, boardHeight, board);
                }
            }
        } else if (i == boardHeight && j == 0) {
            if (board.mines[i-1][j][0] == 0) {
                board.mines[i-1][j][0] = 1;
                if (board.mines[i-1][j][2] == 0) {
                    board = checkSuroundingBlocks(i-1, j, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i-1][j+1][0] == 0) {
                board.mines[i-1][j+1][0] = 1;
                if (board.mines[i-1][j+1][2] == 0) {
                    board = checkSuroundingBlocks(i-1, j+1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i][j+1][0] == 0) {
                board.mines[i][j+1][0] = 1;
                if (board.mines[i][j+1][2] == 0) {
                    board = checkSuroundingBlocks(i, j+1, boardWidth, boardHeight, board);
                }
            }
        } else if (i == boardHeight && j > 0 && j < boardWidth) {
            if (board.mines[i][j-1][0] == 0) {
                board.mines[i][j-1][0] = 1;
                if (board.mines[i][j-1][2] == 0) {
                    board = checkSuroundingBlocks(i, j-1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i-1][j-1][0] == 0) {
                board.mines[i-1][j-1][0] = 1;
                if (board.mines[i-1][j-1][2] == 0) {
                    board = checkSuroundingBlocks(i-1, j-1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i-1][j][0] == 0) {
                board.mines[i-1][j][0] = 1;
                if (board.mines[i-1][j][2] == 0) {
                    board = checkSuroundingBlocks(i-1, j, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i-1][j+1][0] == 0) {
                board.mines[i-1][j+1][0] = 1;
                if (board.mines[i-1][j+1][2] == 0) {
                    board = checkSuroundingBlocks(i-1, j+1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i][j+1][0] == 0) {
                board.mines[i][j+1][0] = 1;
                if (board.mines[i][j+1][2] == 0) {
                    board = checkSuroundingBlocks(i, j+1, boardWidth, boardHeight, board);
                }
            }
        } else if (i == boardHeight && j == boardWidth) {
            if (board.mines[i][j-1][0] == 0) {
                board.mines[i][j-1][0] = 1;
                if (board.mines[i][j-1][2] == 0) {
                    board = checkSuroundingBlocks(i, j-1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i-1][j-1][0] == 0) {
                board.mines[i-1][j-1][0] = 1;
                if (board.mines[i-1][j-1][2] == 0) {
                    board = checkSuroundingBlocks(i-1, j-1, boardWidth, boardHeight, board);
                }
            }
            if (board.mines[i-1][j][0] == 0) {
                board.mines[i-1][j][0] = 1;
                if (board.mines[i-1][j][2] == 0) {
                    board = checkSuroundingBlocks(i-1, j, boardWidth, boardHeight, board);
                }
            }
        }
    }
    return board;
}