#include "race.h"

int main(int argc, char *argv[]) {
	if (argc != 6) {
		mx_printerr("usage: ./race04 [file_name] [x1] [y1] [x2] [y2]\n");
		exit(1);
	}
	char buff;
	int commas = 0;
	int newline = 0;
	int temp_commas = 0;
	int maze_in = open(argv[1], O_RDONLY);
	if(maze_in == -1) {
		mx_printerr("map does not exist\n");
		exit(1);
	}
	while(read(maze_in, &buff, 1)) {
		if(buff == '#' || buff == ',' || buff == '.' || buff == '\n') {
			if(buff != '\n') {
				if(buff == ',') {
                        		commas++;
				}
                	}
			else {
				newline++;
				if (newline == 1) {
					temp_commas = commas;
				}
				else {
					if(commas != temp_commas) {
						mx_printerr("map error\n");
						exit(1);
					}
				}
				commas = 0;
			}
		}
		else {	
			mx_printerr("map error\n");
                        exit(1);
		}
	}
	close(maze_in);
	int height = newline;
	int width = temp_commas + 1;
	
	for(int i = 2; i < 6; i++) {
		int j1 = 0;
		while(argv[i][j1] != '\0') {
			if(!mx_isdigit(argv[i][j1])) {
				mx_printerr("usage: ./race04 [file_name] [x1] [y1] [x2] [y2]\n");
				exit(1);
			}
			j1++;
		}
	}
	int x1 = mx_atoi(argv[2]);
	int y1 = mx_atoi(argv[3]);
	int x2 = mx_atoi(argv[4]);
	int x2_temp = x2;
	int y2 = mx_atoi(argv[5]);
	int y2_temp = y2;
	if((x1 < 0 || x1 > width) || (x2 < 0 || x2 > width) || (y1 < 0 || y1 > height) || (y2 < 0 || y2 > height)) {
		mx_printerr("points are out of map range\n");
		exit(1);
	}
	if(x1 == x2 && y1 == y2) {
		mx_printerr("error\n");
                exit(1);
        }
	int maze_work[height][width];
	
	maze_in = open(argv[1], O_RDONLY);
		int ii = 0;
                int jj = 0;

	while(read(maze_in, &buff, 1)) {
		if(buff != '\n') {
 			if(buff == '.') {
				maze_work[ii][jj] = -2;
				jj++;
			}
			if(buff == '#') {
				maze_work[ii][jj] = -1;
				jj++;
			}
		}
		else {
			jj = 0;
			ii++;
		}
	}

	if(maze_work[y1][x1] == -1) {
		mx_printerr("entry point cannot be an obstacle\n");
		exit(1);
	}
   	if(maze_work[y2][x2] == -1) {
		mx_printerr("exit point cannot be an obstacle\n");
		exit(1);
	}

// path finder ************************************************************

	maze_work[y1][x1] = 0;
	int dist = 0;
        int exit = 0;
        int z = 1;
        int sch_x[] = {1, 0, -1, 0};
        int sch_y[] = {0, 1, 0, -1};
        while(z == 1) {
        	z = 0;
        //	dist++;
        	if(maze_work[y2][x2] == -2) {
            		exit++;
        	}
        	for(int i = 0; i < height; i++) {   
            		for(int j =0; j < width; j++) { 
                		if(maze_work[i][j] == dist) { 
                    			for(int k = 0; k < 4; k++) {
                        			if((maze_work[i + sch_y[k]][j + sch_x[k]]) == -2) {
                            				maze_work[i + sch_y[k]][j + sch_x[k]] = dist + 1;  
                            				z = 1;
                        			}
                    			}
                		}                           
            		}
        	}	    
        	if(z == 0){
            		if(maze_work[y2][x2] == -2) {
                		mx_printerr("route not found\n");
				return 0;
            		}
            		else {
                		mx_printstr("dist: ");
				mx_printint(dist);
				mx_printchar('\n');
				mx_printstr("exit: ");
                                mx_printint(exit);
                                mx_printchar('\n');
            		} 
        	}
		dist++;
    	}

//    *************************************************************************
//   BACK TO HOME WAY

//	maze_work[y2][x2] = -3;
    	int way = exit;
    	while(maze_work[y1][x1] == 0) {
        	way--;
        //	printf("%d\n",way);
        	if (maze_work[y2][x2 + 1] == way) {
            		maze_work[y2][x2 + 1] = -3;
            		x2 += 1;
        	}
        	else {
            		if (maze_work[y2 + 1][x2] == way) {
                		maze_work[y2 + 1][x2] = -3;
                		y2 += 1;
            		}
            		else {
                		if (maze_work[y2][x2 - 1] == way) {
                    			maze_work[y2][x2 - 1] = -3;
                    			x2 -= 1;
                		}
                		else {
                    			if (maze_work[y2 - 1][x2] == way) {
                        			maze_work[y2 - 1][x2] = -3;
                        			y2 -= 1;
                    			}
                		}
            		}
        	}
	}


//    file creating, filling it and so on	***************************************
		
	char maze_print[height][width];
	for(int i = 0; i < height; i++) {
                for(int j = 0; j < width; j++) {
			if(maze_work[i][j] == -1) {
				maze_print[i][j] = '#';
			}
			if(maze_work[i][j] == dist - 1) {
					maze_print[i][j] = 'D';

			}
			if(maze_work[i][j] == -3) {
                                maze_print[i][j] = '*';
                        }
			if((maze_work[i][j] != dist - 1) &&  (maze_work[i][j] == -2 || maze_work[i][j] > -1)) {
                               maze_print[i][j] = '.';
                        }
		}
	}
	maze_print[y2_temp][x2_temp] = '*';

	if(maze_work[y2_temp][x2_temp] == dist - 1) {
		maze_print[y2_temp][x2_temp] = 'X';
	}

// PRINT ARRAY *********************************************

	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			printf("%2c", maze_print[i][j]);
		//	printf("%3d", maze_work[i][j]);
		}
		printf("\n");
	}
		
	return 0;
}

