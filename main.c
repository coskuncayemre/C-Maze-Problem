#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* Emre Coskuncay 21526806 */

char key_list[30];
int start_index;
int end_index;
int row_counter;
int column_counter;
int finish_key=1;
int access_mode=0;
int lastX;
int lastY;
int moveX;
int moveY;
int posX;
int posY;
int check_pointX;
int step_counter;
int check_pointY;
int cp_counter;
int key_counter;
char real_path[1500];
int real_counter;
char maze[30][30];
char copy_maze[30][30];


int find_rower(){ /* determine our dimensions */
	
/*   	char const* const fileName = argv[1]; */
	FILE *fp = fopen("maze.txt", "r");
   	int x;
   	char ch;
   	while(!feof(fp)){
   		ch = fgetc(fp);
  		if(ch == '\n' ){
			    x++; 
		}
	}
	row_counter=x+1;
	column_counter=x+1;
	return x+1;
}

void start(){ /* reads the file and assigns the array  */
	int x=0;
	int y=0;
   	FILE *p;
   	p = fopen("maze.txt","r");
   	char ch;
   	find_rower();
   	for(x=0;x<row_counter;x++){
   			for(y=0;y<column_counter;y++){
   				ch=getc(p);
   				if(ch == '\n' ){
   				ch=getc(p);
				}
   				maze[x][y]=ch;
   				copy_maze[x][y]='1';
			}
	}
}

int find_start_index(){ /*find the initial index */
	int counter=0;
	int i;
	for(i=0;i<column_counter;i++){
		if(maze[0][i]=='S'){
			start_index=counter;
			posX=start_index;
			copy_maze[0][posX]='0';
		}
	counter++;
	}
	
	return start_index;
}


int find_end_index(){ /*find the ending index */
	int counter=0;
	int i;
	for(i=0;i<column_counter;i++){
		if(maze[row_counter-1][i]=='E'){
			end_index=counter;
		}
	counter++;
	}
	return end_index;
}

void writer(char path){ /*prints directions*/
	real_path[real_counter]=path;
	real_counter++;
}

void moveS(int y,int x){ /* when move towards the south,change the location */
	lastY=y;
	lastX=x;
	step_counter++;
	writer('S');
	posY=y+1;
	moveY++;
	copy_maze[posY][posX]='0';
}

void moveN(int y,int x){ /* when move towards the north,change the location */
	lastY=y;
	lastX=x;
	step_counter++;
	writer('N');
	posY=y-1;
	moveY--;
	copy_maze[posY][posX]='0';
}

void moveW(int y,int x){ /* when move towards the East,change the location */
	lastY=y;
	lastX=x;
	step_counter++;
	writer('E');
	moveX++;
	posX=x+1;
	copy_maze[posY][posX]='0';
}

void moveE(int y,int x){ /* when move towards the West,change the location */
	lastY=y;
	lastX=x;
	step_counter++;
	writer('W');
	moveX--;
	posX=x-1;
	copy_maze[posY][posX]='0';
}

void get_key(char key){ /* when found the key,we getting by this function */
	key_list[key_counter]= key;
	key_counter++;
}

void reset_copy_maze(int a,int b){ /* to reset the paths we pass */
	int x=0;
	int y=0;
	for(x=0;x<row_counter;x++){
   			for(y=0;y<column_counter;y++){
   				copy_maze[x][y]='1';
			}
	}
	copy_maze[a][b]='0';
}


void check_arround(int y , int x){ /* most important function, check the road or the key or the door */
	 cp_counter=0;
	 if(protect_array(y+1,x) && maze[y+1][x]!= '1' && finish_key==1 ){
		int a=posY+1;
		int b=posX;
		int cpy=y;
		int cpx=x;
		cp_counter++;
		if(protect_array(a,b)){
			if(check_path(a,b) && been_here(a,b)){
				if(check_path_down(a,b) ){
					moveS(posY,posX);
					check_arround(posY,posX);
				}
			}
			
			if(check_point(cpy,cpx)){
				cp_counter=0;
				copy_maze[cpy][cpx]='1';
				posY=cpy;
				posX=cpx;
			}
			
			if(is_it_key(a,b) && been_here(a,b)){
				
				moveS(posY,posX);
				get_key(maze[a][b]);
				step_counter++;
				writer(maze[a][b]);
				reset_copy_maze(a,b);
				check_arround(posY,posX);
			}
			
			if(is_it_door(a,b)){
				
				if(check_end(a,b)){
					moveS(posY,posX);
				}
					
				if(check_s(a,b)){
					moveS(posY,posX);
					check_arround(posY,posX);
				}
				
				else if (finish_key==1){ 
					if(been_here(a,b) ){
						char c;
						int i=0;
						for(i=0;i<30;i++){
							c=key_list[i];
							if(toupper(c) == maze[a][b]){
								moveS(posY,posX);
								step_counter++;
								writer(maze[a][b]);
								check_arround(posY,posX);		
							}
						}
					}
					
					else{
						if(check_point(cpy,cpx)){
							cp_counter=0;
							copy_maze[cpy][cpx]='1';
							posY=cpy;
							posX=cpx;
						}
					}
				}
			}
		}
	}
	
	
	if(protect_array(y,x+1) && maze[y][x+1]!= '1' && finish_key==1){
		int a=posY;
		int b=posX+1;
		int cpy=y;
		int cpx=x;
		cp_counter++;
		if(protect_array(a,b)){
			if(check_path(a,b) && been_here(a,b)){
				if(check_path_right(a,b) ){
					moveW(posY,posX);
					check_arround(posY,posX);
				}
			}
			
			if(check_point(cpy,cpx)){
				cp_counter=0;
				copy_maze[cpy][cpx]='1';
				posY=cpy;
				posX=cpx;
			}
			
			if(is_it_key(a,b) && been_here(a,b) && check_duplicate()){
				moveW(posY,posX);
				step_counter++;
				writer(maze[a][b]);
				get_key(maze[a][b]);
				reset_copy_maze(a,b);
				check_arround(posY,posX);
			}
			
			if(is_it_door(a,b)){
				
				if(check_end(a,b)){
					moveW(posY,posX);
					
				}
					
				if(check_s(a,b)){
					moveW(posY,posX);
					check_arround(posY,posX);
				}
				
				else if (finish_key==1){ 
					if(been_here(a,b) ){
						char c;
						int i=0;
						for(i=0;i<30;i++){
							c=key_list[i];
							if(toupper(c) == maze[a][b]){
								moveW(posY,posX);
								step_counter++;
								writer(maze[a][b]);
								check_arround(posY,posX);		
							}
						}
					}
					
					else{
						if(check_point(cpy,cpx)){
							cp_counter=0;
							copy_maze[cpy][cpx]='1';
							posY=cpy;
							posX=cpx;
						}
					}
				}
				
			}
			
		}			
	}
	
	
	
	if(protect_array(y,x-1) && maze[y][x-1]!= '1' && finish_key==1){
		int a=posY;
		int b=posX-1;
		int cpy=y;
		int cpx=x;
		cp_counter++;
		if(protect_array(a,b)){
			if(check_path(a,b) && been_here(a,b)){
				if(check_path_left(a,b)){
					moveE(posY,posX);
					check_arround(posY,posX);
				}
			}
			
			if(check_point(cpy,cpx)){
				cp_counter=0;
				copy_maze[cpy][cpx]='1';
				posY=cpy;
				posX=cpx;
			}
			
			if(is_it_key(a,b) && check_duplicate()){
				moveE(posY,posX);
				step_counter++;
				writer(maze[a][b]);
				get_key(maze[a][b]);
				reset_copy_maze(a,b);
				check_arround(posY,posX);
			}
			
			if(is_it_door(a,b)){
				if(check_end(a,b)){
					moveE(posY,posX);
					
				}
					
				if(check_s(a,b)){
					moveE(posY,posX);
					check_arround(posY,posX);
				}
				
				else if (finish_key==1){ 
					if(been_here(a,b) ){
						char c;
						int i=0;
						for(i=0;i<30;i++){
							c=key_list[i];
							if(toupper(c) == maze[a][b]){
								moveE(posY,posX);
								step_counter++;
								writer(maze[a][b]);
								check_arround(posY,posX);		
							}
						}
					}
					
					else{
						if(check_point(cpy,cpx)){
							cp_counter=0;
							copy_maze[cpy][cpx]='1';
							posY=cpy;
							posX=cpx;
						}
						
					}
				}
				
			}
			
		}	
		
	}
	
	
	if(protect_array(y-1,x) && maze[y-1][x]!= '1' && finish_key==1){
		int a=posY-1;
		int b=posX;
		int cpy=y;
		int cpx=x;
		cp_counter++;
		if(protect_array(a,b)){
			if(check_path(a,b) && been_here(a,b)){
				if(check_path_up(a,b)){
					moveN(posY,posX);
					check_arround(posY,posX);
				}
			}
			
			if(check_point(cpy,cpx)){
				copy_maze[cpy][cpx]='1';
				posY=cpy;
				posX=cpx;
			}
			
			if(is_it_key(a,b) && been_here(a,b) && check_duplicate()){
				moveN(posY,posX);
				step_counter++;
				writer(maze[a][b]);
				get_key(maze[a][b]);
				reset_copy_maze(a,b);
				copy_maze[a+1][b]='0';
				check_arround(posY,posX);
			}
			
			
			if(is_it_door(a,b)){
				
				if(check_end(a,b)){
					moveN(posY,posX);
					
				}
					
				if(check_s(a,b) && been_here(a,b)){
					moveN(posY,posX);	
					check_arround(posY,posX);
				}
				
				else if (finish_key==1 && been_here(a,b)){
					if(been_here(a,b) ){
						char c;
						int i=0;
						for(i=0;i<30;i++){
							c=key_list[i];
							if(toupper(c) == maze[a][b]){
								moveN(posY,posX);
								step_counter++;
								writer(maze[a][b]);
								check_arround(posY,posX);		
							}
						}
					}
					
					else{
						if(check_point(cpy,cpx)){
							cp_counter=0;
							copy_maze[cpy][cpx]='1';
							posY=cpy;
							posX=cpx;
						}
					}
				}
				
			}
		}		
	}	
	
	
}


int been_here(int y,int x){ /* check whether we are here before */ 
	if(copy_maze[y][x]=='0'){
		return 0;
	}
	return 1;
}

void finish(){ /* function that finishes the program and the maze */
	finish_key=0;
}

int check_end(int y,int x){ /* check whether the exit is not */
	if(y==row_counter-1 && x==end_index){
		finish();
		return 1;
	}
	return 0;
}

int check_path(int y,int x){ /* checks whether there is a route  , possible way */
	if(maze[y][x] == '0'){
		return 1;
	}
	return 0;
}

int check_path_down(int y,int x){ /* check if there is a road down */
	if(maze[y][x-1] != '1'){
		if(protect_array(y,x-1)){
			return 1;
		}
	}
	
	if(maze[y+1][x] != '1'){
		if(protect_array(y+1,x)){
			return 1;
		}
	}
	
	if(maze[y][x+1] != '1'   ){
		if(protect_array(y,x+1)){
			return 1;
		}
	}
	return 0;
}

int check_path_right(int y,int x){ /* check if there is a road right */
	if(maze[y+1][x] != '1'){
		if(protect_array(y+1,x)){
			return 1;
		}
	}
	
	if(maze[y-1][x] != '1'){
		if(protect_array(y-1,x)){
			return 1;
		}
	}
	
	if(maze[y][x+1] != '1'   ){
		if(protect_array(y,x+1)){
			return 1;
		}
	}
	return 0;
}


int check_path_left(int y,int x){ /* check if there is a road left */
	if(maze[y][x-1] != '1'){
		if(protect_array(y,x-1)){
			return 1;
		}
	}
	
	if(maze[y+1][x] != '1'){
		if(protect_array(y+1,x)){
			return 1;
		}
	}
	
	if(maze[y-1][x] != '1'   ){
		if(protect_array(y-1,x)){
			return 1;
		}
	}
	return 0;
}

int check_path_up(int y,int x){ /* check if there is a road up */
	if(maze[y][x-1] != '1'){
		if(protect_array(y,x-1)){
			return 1;
		}
	}
	
	if(maze[y-1][x] != '1'){
		if(protect_array(y-1,x)){
			return 1;
		}
	}
	
	if(maze[y][x+1] != '1'   ){
		if(protect_array(y,x+1)){
			return 1;
		}
	}
	return 0;
}

int check_s(int y,int x){ /* check whether the location is the starting point */
	if(maze[y][x] == 'S'){
		return 1;
	}
	return 0;
}


int is_it_key(int y,int x){ /* it looks at the letter size and decides whether it is a door or a key */
	if(maze[y][x] >= 'a' && maze[y][x] <= 'z'){
		return 1;
	}
	return 0;
}

int is_it_door(int y,int x){ /* it looks at the letter size and decides whether it is a door or a key */
	if(maze[y][x] >= 'A' && maze[y][x] <= 'Z'){
		return 1;
	}
	return 0;
}

int protect_array(int y,int x){ /* allows us to stay in the maze */
	if(y<column_counter && x<row_counter && y>=0 && x>=0){
		return 1;
	}
	return 0;
}

int check_point(int y,int x){ /*dead-end road control function */
	if(cp_counter>1){
		check_pointY=y;
		check_pointX=x;
		return 1;
	}
	return 0;
}


int check_duplicate(int y,int x){ /* function used to avoid receiving the same key twice */
  	
}     

void write_to_file(){ /* writes the path leading to the solution to the file */
	FILE *f = fopen("path.txt", "w");
	if (f == NULL){
	    printf("Error opening file!\n");
	    exit(1);
	}
	int i=0;
	fprintf(f,"Start ");
	for(i=0;i<step_counter;i++){
		char b= real_path[i];
		fprintf(f, "%c ", b);
	}
	if(finish_key==0){
		fprintf(f,"Exit");
	}
	fclose(f);
}


void main(){
	start(); /* reads the file and assigns the array  */
	find_start_index(); /*find the initial index */
	find_end_index();/*find the ending index */
	check_arround(0,start_index); /* control the paths around helps with recursion */
	write_to_file(); /* writes the path leading to the solution to the file */
	if(finish_key==1){ /* if there is no solution */
		FILE	*pFile2 = fopen("path.txt", "a");
		fprintf(pFile2,"There is no solution.");
	}
}