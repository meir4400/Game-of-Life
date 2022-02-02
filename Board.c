#include <stdio.h>
#include <stdlib.h>
#include "Cell.h"
#include "Board.h"
#include "Controller.h"
#include "K.h"

//global vars for board data
char **BOARD;
int ROWS = 0, COLS = 0;
Cell *LIVE_CELLS_ARR = NULL;
int LIVE_CELLS_NUM = 0;

/*===================================================================
prepare board, allocate memory and initialize cells values. 
return 1 if preparing was proper, 0 if not
===================================================================*/
void prepare_board(int rows, int cols, Cell *live_cells_arr, int live_cells_num){

    ROWS = rows;
    COLS = cols;
    LIVE_CELLS_ARR = live_cells_arr;
    LIVE_CELLS_NUM = live_cells_num;

    //allocate memory for board rows, each is of char* type
    BOARD = (char**)calloc(ROWS, sizeof(char*));
    if (!BOARD) {
        printf("board rows allocation faild");
        exit(1);
    }
    
    //allocate memory for each row in board, each is char type
    int i;
    for (i = 0; i < ROWS; i++) {
        BOARD[i] = (char*)calloc(COLS, sizeof(char));
        if (!BOARD[i]) {
            printf("row's content allocation faild");
            exit(1);
        }
    }
    
    init_cells();
}

/*===================================================================
initialize cells value, ' ' for dead cell state and '*' for live
===================================================================*/
void init_cells(){

    //set all cells with DEAD value at the beginning
    int r, c, i;
    for (r = 0; r < ROWS; r++){
        for (c = 0; c < COLS; c++) {
            BOARD[r][c] = DEAD;
        }
    }

    //set the live cells with LIVE value
    for (i = 0; i < LIVE_CELLS_NUM; i++) {
        r = LIVE_CELLS_ARR[i].row;
        c = LIVE_CELLS_ARR[i].col;
        BOARD[r][c] = LIVE;
    }
}

/*===================================================================
creates new game state for the next step
===================================================================*/
int move_step(){

    int current_cell, r, c;
    Cell cell;

    //for all live cells, send each cell and his neighbors to set its state 
    for ( current_cell = 0; current_cell < LIVE_CELLS_NUM; current_cell++) {

        //send current cell neighbors to check (skip cell itself)
        for ( r = 0; r < NEIGHBORS_RANGE; r++) {
            for ( c = 0; c < NEIGHBORS_RANGE; c++) {
                
                cell.row = (LIVE_CELLS_ARR[current_cell].row)-1+r;
                cell.col = (LIVE_CELLS_ARR[current_cell].col)-1+c;

                //skip current cell itself untill finish check all its neighbors
                if ( cell.row == LIVE_CELLS_ARR[current_cell].row
                    && cell.col == LIVE_CELLS_ARR[current_cell].col) {
                    continue;
                }

                set_cell_state(cell);
            }
        }
        //after check all current cell neighbor, checl itself
        set_cell_state(LIVE_CELLS_ARR[current_cell]);
    }

    //update_board will return if game should continue or not
    return update_board();
}

/*===================================================================
set state (live or dead) of given cell accordingly his neighbors
===================================================================*/
void set_cell_state(Cell cell) {

    //do nothing if cell is invalid
    if (!is_valid_cell(cell)) {
        return;
    }
    
    int neighbors = 0, r, c;
    Cell cur;

    //check all cell neighbors to set its state 
    for ( r = 0; r < NEIGHBORS_RANGE; r++) {
        for ( c = 0; c < NEIGHBORS_RANGE; c++) {

            //the cell itself should not be checked
            if (r == 1 && c == 1) {
                continue;
            }
            
            cur.row = (cell.row)-1+r; 
            cur.col = (cell.col)-1+c; 

            //check if current neighbor is live. both states LIVE and SHOULD_DEAD indicate cell is live
            if ( is_valid_cell(cur) && ( BOARD[cur.row][cur.col] == LIVE || BOARD[cur.row][cur.col] == SHOULD_DEAD ) ) {
                neighbors++;
            }
        }
    }

    //set cell's state
    if (neighbors <= 1 || neighbors >= 4) {

        //change state to SHOULD_DEAD only if cell is live
        if ( BOARD[cell.row][cell.col] == LIVE ) { 
            BOARD[cell.row][cell.col] = SHOULD_DEAD;
        }

    }
    else if (neighbors == 3) {
        
        //change state to SHOULD_LIVE only if cell is dead
        if ( BOARD[cell.row][cell.col] == DEAD ) { 
            BOARD[cell.row][cell.col] = SHOULD_LIVE;
        }
    }
}

/*========================================================================
check if cell is valid (inside board borders), return 1 if valid, 0 if not
========================================================================*/
int is_valid_cell(Cell cell) {

    return cell.row >= 0 && cell.row < ROWS && cell.col >= 0 && cell.col < COLS ;
}

/*========================================================================
re-build array of current live cells after change in game state
return 1 if game is on or 0 if game is over (no more live cells)
========================================================================*/
int update_board(){

    int r, c;
    LIVE_CELLS_NUM = 0;

    //give value to pendent cells and count live cells
    for ( r = 0; r < ROWS; r++) {
        for ( c = 0; c < COLS; c++) {

            if ( BOARD[r][c] == SHOULD_LIVE || BOARD[r][c] == LIVE ) {
                BOARD[r][c] = LIVE;
                LIVE_CELLS_NUM++;
            }
            else if ( BOARD[r][c] == SHOULD_DEAD ) {
                BOARD[r][c] = DEAD;
            }
        }
    }

    //free previous arr memory and allocate memory for the new arr
    free(LIVE_CELLS_ARR);
    LIVE_CELLS_ARR = (Cell*)calloc(LIVE_CELLS_NUM, sizeof(Cell));
    if ( !LIVE_CELLS_ARR ) {
        printf("allocation of live cells array faild\n");
        exit(1);
    }

    //build new live cells arr and save its size
    int current = 0;
    for ( r = 0; r < ROWS; r++) {
        for ( c = 0; c < COLS; c++) {
            if ( BOARD[r][c] == LIVE ) {
                LIVE_CELLS_ARR[current].row = r;
                LIVE_CELLS_ARR[current].col = c;
                current++;
            }
        }
    }

    // return if game is on or not (no more live cells)
    return LIVE_CELLS_NUM;
}

/*===================================================================
print the board
===================================================================*/
void print_board(){

    int r, c;

    // //print upper indexes
    // printf("\n%5c", ' ');
    // for(c = 0; c < COLS; c++){
    //     printf("%3d",c);
    // }
    // printf("\n");

    //print upper border
    printf("%5c", ' ');
    for(c = 0; c < COLS; c++){
        printf("%c%c%c",HORIZONTAL_BORDER,HORIZONTAL_BORDER, HORIZONTAL_BORDER);
    }
    printf("\n");

    //print board
    for (r = 0; r < ROWS; r++){
        //printf("%3d ",r);      //left indexes
        printf("%c", VERTICAL_BORDER);
        for (c = 0; c < COLS; c++){
            printf("%3c", BOARD[r][c]);
        }
        printf("%2c", VERTICAL_BORDER);
        printf("\n");
    }

    //print lower border
    printf("%5c", ' ');
    for(c = 0; c < COLS; c++){
        printf("%c%c%c",HORIZONTAL_BORDER, HORIZONTAL_BORDER, HORIZONTAL_BORDER);
    }
    printf("-\n");
}

/*===================================================================
free board memory
===================================================================*/
void free_board(){
    
    //free content of each row in board
    int i;
    for (i = 0; i < ROWS; i++){
        free(BOARD[i]);
    } 

    //free the rows array
    free(BOARD);
}