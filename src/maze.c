/*
http://www.mazeworks.com/mazegen/mazetut/
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLS 21
#define ROWS 21
#define CELL_X 10
#define CELL_Y 10

int map[ROWS][COLS];
void build(int, int, int, int);
int check_wall(int, int, int, int);

int main(int argc, char *argv[])
{
	for(int i = 0; i < ROWS; i++)
		for(int j = 0; j < COLS; j++)
			map[i][j] = (i % 2 && j % 2 ? 0 : 1);

	const int total_cells = CELL_X * CELL_Y;

	srand(time(NULL));
	build(0, 0, CELL_X, CELL_Y);

	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLS; j++)
			printf("%d", map[i][j]);
		printf("\n");
	}

	return 0;
}

void build(int current_x, int current_y, int max_x, int max_y){
	while(1){
		int neighbors = (check_wall(current_x - 1, current_y, max_x, max_y) << 3)
						+ (check_wall(current_x + 1, current_y, max_x, max_y) << 2)
						+ (check_wall(current_x, current_y - 1, max_x, max_y) << 1)
						+ check_wall(current_x, current_y + 1, max_x, max_y);

		// edge check // 1000 up 0100 down 0010 left 0001 right
		if(current_x == 0 || current_x == max_x - 1)
			neighbors &= (current_x ? 11 : 7); // 1011 0111
		if(current_y == 0 || current_y == max_y - 1)
			neighbors &= (current_y ? 14 : 13); // 1110 1101

		if(neighbors){
			int next = 0;
			while(!next)
				next = ((1 << (rand() % 4)) & neighbors);
			/*
			if(next >> 3){
				map[2 * current_x][2 * current_y + 1] = 0;
				build(current_x - 1, current_y, max_x, max_y);
			}
			else if(next >> 2){
				map[2 * current_x + 2][2 * current_y + 1] = 0;
				build(current_x + 1, current_y, max_x, max_y);
			}
			else if(next >> 1){
				map[2 * current_x + 1][2 * current_y] = 0;
				build(current_x, current_y - 1, max_x, max_y);
			}
			else{
				map[2 * current_x + 1][2 * current_y + 2] = 0;
				build(current_x, current_y + 1, max_x, max_y);
			}
			*/
			int delta_x = (next & 8 ? -1 : next & 4 ? 1 : 0);
			int delta_y = (next & 2 ? -1 : next & 1 ? 1 : 0);
			map[2 * current_x + 1 + delta_x][2 * current_y + 1 + delta_y] = 0;
			build(current_x + delta_x, current_y + delta_y, max_x, max_y);
		}
		else 
			break;
	}
}

int check_wall(int current_x, int current_y, int max_x, int max_y){

	if(current_x < 0 || current_x > max_x - 1 || current_y < 0 || current_y > max_y - 1)
		return 0;

	return map[2 * current_x][2 * current_y + 1]
		+ map[2 * current_x + 2][2 * current_y + 1]
		+ map[2 * current_x + 1][2 * current_y]
		+ map[2 * current_x + 1][2 * current_y + 2] == 4 ? 1 : 0;
}