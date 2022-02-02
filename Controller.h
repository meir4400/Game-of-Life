#ifndef CONTROLLER_H
#define CONTROLLER_H

typedef struct Cell Cell;

void run();
void initialize_live_cells(int, int, int, int*, Cell**);
int insert_cell( Cell cell, Cell *arr, int limit);

#endif