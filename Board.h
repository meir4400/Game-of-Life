#ifndef BOARD_H
#define BOARD_H

typedef struct Cell Cell;

void prepare_board(int, int, Cell*, int);
void init_cells();
int move_step();
void print_board();
void free_board();
void set_cell_state(Cell cell);
int is_valid_cell(Cell cell);
int update_board();

#endif