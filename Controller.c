#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Cell.h"
#include "Controller.h"
#include "Board.h"
#include "K.h"

//for sleep()
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

/*===================================================================
//the game run function. prepares the game and manage it
===================================================================*/
void run(){

    int rows , cols, max_live_cells, live_cells_num;
    Cell *live_cells_arr = NULL;

    printf("enter number of rows, columns and max number of live cells (seperated with space)\n\n");
    scanf("%d %d %d", &rows, &cols, &max_live_cells);

    initialize_live_cells(rows, cols, max_live_cells, &live_cells_num, &live_cells_arr);    
    prepare_board(rows, cols, live_cells_arr, live_cells_num);

    //game loop. run while there are live cells in board (move_step return number of live cells)
    do
    {
        print_board();
        Sleep(STEP_DELAY);
    } while (move_step());

    printf("\n no more live cells \n");
    free_board();
}

/*===========================================================================
//the function creates random number of live cells, each has random location.
parameter: rows number, cols number, max of live cells, variable to have the
number of live cells, pointer to have the list of live cells
===========================================================================*/
void initialize_live_cells(int rows, int cols, 
    int max_live_cells, int *live_cells_num, Cell **live_cells_arr) {

    srand(time(NULL));

    //initialize random number (bigger than 0) of live cells. 
    *live_cells_num = (rand()%(max_live_cells-1))+1;

    //allocate memory for live cells array
    *live_cells_arr = (Cell*)calloc(*live_cells_num, sizeof(Cell));
    if (!(*live_cells_arr)){
        printf("live cells list allocation faild\n");
        exit(1);
    }

    //set random location to each live cell
    int index;
    Cell cell;
    for ( index = 0; index < *live_cells_num; index++) {

        cell.row = rand()%rows;
        cell.col = rand()%cols;

        //send new cell to insert. decrease index if exist cell in this location
        if ( !insert_cell( cell, *live_cells_arr, index) ) {
            index--;
        }
    }
}
/*===========================================================================
insert given cell to given arr, return 0 if exist cell in this location
parameters: cell, array of cells, limit index to run untill it
===========================================================================*/
int insert_cell( Cell cell, Cell *arr, int limit) {

    int i = 0;
    while ( i < limit){

        if ( arr[i].row == cell.row && arr[i].col == cell.col ) {
            return 0;
        }
        i++;
    }

    //insert cell to arr if not found cell in this location
    arr[limit].row = cell.row;
    arr[limit].col = cell.col;

    return 1;
}
