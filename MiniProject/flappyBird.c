#include "pic32mx.h"
#include "io.h"

int bird_x = 16;
int bird_y = 16;

void play() {
    // Clear canvas 
    
    while (1)
    {
        // Movement functions 
        // Display functions
        
        gravity();
        collisiondetection();
    }
    
}

void collisiondetection(){
    if (bird_x < 0 || bird_x > 128)
    {
        gameOver();
    }

    if (bird_y < 0 || bird_y > 32)
    {
        gameOver();
    }
    
    // matrixOverlap()
    
}

void gameOver(){
    //Clear canvas

    printText("GAME OVER", {1, 12}, {1, 1}, "CENTER", "BORDER", "NO_INVERT");
    printText("Retry", {32, 20}, {1, 1}, "CENTER", "BORDER", "NO_INVERT");
    printText("Menu", {96, 20}, {1, 1}, "CENTER", "BORDER", "NO_INVERT");

    if ((getbtns() & 8) == 8) {   // Gå upp och ner i menyn med knappar (2 knappar)
        if (gameOverOption > 1){
            gameOverOption--;
        }

        switch (gameOverOption){
            case 1:
                printText("Retry", {32, 20}, {1, 1}, "CENTER", "BORDER", "INVERT");
                printText("Menu", {96, 20}, {1, 1}, "CENTER", "BORDER", "NO_INVERT");
                break;
            case 2: 
                printText("Retry", {32, 20}, {1, 1}, "CENTER", "BORDER", "NO_INVERT");
                printText("Menu", {96, 20}, {1, 1}, "CENTER", "BORDER", "INVERT");
                break;
            default:
                break;
        }
        displayUpdate();

    }    
	if ((getbtns() & 4) == 4) {   // Gå upp och ner i menyn med knappar (2 knappar)
        if (gameOverOption < 2){
            gameOverOption++;
        }

        switch (gameOverOption){
            case 1:
                printText("Retry", {32, 20}, {1, 1}, "CENTER", "BORDER", "INVERT");
                printText("Menu", {96, 20}, {1, 1}, "CENTER", "BORDER", "NO_INVERT");
                break;
            case 2: 
                printText("Retry", {32, 20}, {1, 1}, "CENTER", "BORDER", "NO_INVERT");
                printText("Menu", {96, 20}, {1, 1}, "CENTER", "BORDER", "INVERT");
                break;
            default:
                break;
        }
        displayUpdate();

    }  
	if ((getbtns() & 2) == 2) { // Select knapp som går in i vald alternativ (1 knapp)
        switch (gameOverOption){
            case 1:
                play();
                break;
            case 2: 
                menu();
                break;
            default:
                break;
        }
    }
}