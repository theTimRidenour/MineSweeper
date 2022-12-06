#include "raylib.h"
#include <string>
#include <cstdlib>

#define MAX_INPUT_CHARS 3

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

struct player {
    char initials[3];
    int time[3];
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

    // top players
    player leaderBoards[10][3];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                leaderBoards[i][j].initials[k] = '@';
                leaderBoards[i][j].time[k] = 99;
            }
        }
    }
    bool addPlayerScore = false;

    // board
    int boardWidth = 16;
    int boardHeight = 16;
    int numberOfMines = 40;
    Board board(boardWidth, boardHeight, numberOfMines);
    int boxWidth = 40;
    int boxHeight = 40;
    int fontSize = 32;
    bool gameOver = false;
    bool won = false;
    int mineFlags = numberOfMines;
    char flagText[30];

    // mouse
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    // testing text input
    char name[MAX_INPUT_CHARS + 1] = "\0";
    int letterCount = 0;
    Rectangle textBox = {WIN_WIDTH/2 - 75, 180, 150, 50};

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        const float dT { GetFrameTime() };

        // Check if winner
        if (!gameOver && timerIsRunning) {
            int wonByFlags = 0;
            bool wonByClicks = true;

            for (int i = 0; i < boardHeight; i++) {
                for (int j = 0; j < boardWidth; j++) {
                    if (board.mines[i][j][0] == 0 && board.mines[i][j][1] == 0) {
                        wonByClicks = false;
                    } else if (board.mines[i][j][0] == 3 && board.mines[i][j][1] == 1) {
                        wonByFlags++;
                    }
                }
            }

            if (wonByClicks || wonByFlags == numberOfMines) {
                timerIsRunning = false;
                won = true;
            }
        }

        // GAME OVER
        if (gameOver) {
            for (int i = 0; i < boardHeight; i++) {
                for (int j = 0; j < boardWidth; j++) {
                    if (board.mines[i][j][0] != 4 && board.mines[i][j][1] == 1) {
                        board.mines[i][j][0] = 1;
                    }
                }
            }
        }

        if (!playing) {
            board.newBoard(boardWidth, boardHeight, numberOfMines);
            playing = true;
            timerIsRunning = true;
            gameOver = false;
            won = false;
            letterCount = 0;
            name[0] = '\0';
            name[1] = '\0';
            name[2] = '\0';
            boxWidth = (int)((WIN_WIDTH - 20 - 1 * (boardWidth-1)) / boardWidth);
            boxHeight = (int)((WIN_HEIGHT - 70 - 1 * (boardHeight-1)) / boardHeight);
            if (boxWidth < boxHeight) {
                boxHeight = boxWidth;
            } else {
                boxWidth = boxHeight;
            }
        } else if (timerIsRunning) {
            gameTime += dT;
            hours = (int)(gameTime / 60 / 60);
            minutes = (int)(gameTime / 60) - (hours * 60 * 60);
            seconds = (int)(gameTime) - (minutes * 60) - (hours * 60 * 60);
        }

        BeginDrawing();

        ClearBackground(WHITE);

        // player area x and y
        int xPos = WIN_WIDTH/2 - (boxWidth*boardWidth + boardWidth-1)/2;
        int yPos = WIN_HEIGHT/2 + 30 - (boxHeight*boardHeight + boardHeight-1)/2;

        // temp text
        char tempText[10];

        // interaction with game board
        if ((IsMouseButtonPressed(0) || IsMouseButtonPressed(1)) && timerIsRunning) {
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
                                if (board.mines[i][j][1] == 1) {
                                    gameOver = true;
                                    timerIsRunning = false;
                                }
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

        // GAME OVER TEXT
        if (gameOver) DrawText("Game Over", WIN_WIDTH/2 - MeasureText("Game Over", 60)/2, WIN_HEIGHT/2 - 30, 60, DARKGRAY);

        // WINNER
        if (won) {
            if (letterCount == MAX_INPUT_CHARS) {

                int difficulty;
                    if (boardWidth == 9) difficulty = 0;
                    else if (boardWidth == 16) difficulty = 1;
                    else difficulty = 2;
                    
                if (name[0] == '@') {
                    for (int i = 0; i < 10; i++) {
                        int spacer = MeasureText("10. MMM - 00:00:00", 60);
                        spacer = WIN_WIDTH/2 - spacer/2;
                        char currentText[20]{};
                        std::sprintf(currentText, "%d.", i+1);
                        DrawText(currentText, spacer + 65 - MeasureText(currentText, 60), 180 + i*45, 60, RED);
                        if (leaderBoards[i][difficulty].initials[0] != '@') {
                            std::sprintf(currentText, "%C%C%C", leaderBoards[i][difficulty].initials[0], leaderBoards[i][difficulty].initials[1], leaderBoards[i][difficulty].initials[2]);
                            DrawText(currentText, spacer + 75, 180 + i*45, 60, RED);
                            std::sprintf(currentText, "- %02d:%02d:%02d", leaderBoards[i][difficulty].time[0], leaderBoards[i][difficulty].time[1], leaderBoards[i][difficulty].time[2]);
                            DrawText(currentText, spacer + 225, 180 + i*45, 60, RED);
                        }
                    }
                } else {
                    int place = 0;
                    bool cont = true;
                    for (int i = 0; i < 10; i++) {
                        if (cont && (leaderBoards[i][difficulty].initials[0] == '@' || (leaderBoards[i][difficulty].time[0] >= hours &&
                            leaderBoards[i][difficulty].time[1] >= minutes && leaderBoards[i][difficulty].time[2] >= seconds))) {
                                addPlayerScore = true;
                                place = i;
                                cont = false;
                        }
                    }
                    if (addPlayerScore) {
                        for (int i = 8; i >= place; i--) {
                            leaderBoards[i+1][difficulty].initials[0] = leaderBoards[i][difficulty].initials[0];
                            leaderBoards[i+1][difficulty].initials[1] = leaderBoards[i][difficulty].initials[1];
                            leaderBoards[i+1][difficulty].initials[2] = leaderBoards[i][difficulty].initials[2];
                            leaderBoards[i+1][difficulty].time[0] = leaderBoards[i][difficulty].time[0];
                            leaderBoards[i+1][difficulty].time[1] = leaderBoards[i][difficulty].time[1];
                            leaderBoards[i+1][difficulty].time[2] = leaderBoards[i][difficulty].time[2];
                        }
                        leaderBoards[place][difficulty].initials[0] = name[0];
                        leaderBoards[place][difficulty].initials[1] = name[1];
                        leaderBoards[place][difficulty].initials[2] = name[2];
                        leaderBoards[place][difficulty].time[0] = hours;
                        leaderBoards[place][difficulty].time[1] = minutes;
                        leaderBoards[place][difficulty].time[2] = seconds;
                    }
                    addPlayerScore = false;
                }
                name[0] = '@';
            } else {
                DrawRectangle(WIN_WIDTH/2 - MeasureText("WINNER!!!", 60)/2 - 10, WIN_HEIGHT/2 - 40, MeasureText("WINNER!!!", 60) + 20, 80, BLACK);
                DrawText("WINNER!!!", WIN_WIDTH/2 - MeasureText("WINNER!!!", 60)/2, WIN_HEIGHT/2 -30, 60, GREEN);

                int key = GetCharPressed();
                while (key > 0) {
                    if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)) {
                        name[letterCount] = (char)key;
                        name[letterCount+1] = '\0';
                        letterCount++;
                    }
                    key = GetCharPressed();
                }

                if (IsKeyPressed(KEY_BACKSPACE)) {
                    letterCount--;
                    if (letterCount < 0) letterCount = 0;
                    name[letterCount] = '\0';
                }

                DrawText("INITIALS", textBox.x - 150, textBox.y + 10, 32, GRAY);

                DrawRectangleRec(textBox, LIGHTGRAY);
                DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, MAROON);

                DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
            }
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