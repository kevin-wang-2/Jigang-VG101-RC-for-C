#include <stdio.h>

FILE* fp;
int board[15][15][50] = {0};
int finalboard[15][15] = {0};
int border, step = 1;
float komi;

int eat(int x, int y, int player);
void fill(int x, int y);

int main() {
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d %f", &border, &komi);
	fgetc(fp);
	
	int resign = 0;

	while(!feof(fp)) {
		step++;

		fprintf(stderr, "Round %d\n", step - 1);

		char x_char = fgetc(fp);
		if(x_char == 'r') { // Resign
			step--;
			resign = 1;
			break;
		}

		if(x_char == 'u') { // Undo
			fgetc(fp);
			if(fgetc(fp) == 'a') {
				step -= 2;
				printf("Undo successfully.\n");
			} else {
				printf("Undo denied.\n");
			}
			fgetc(fp);
			continue;
		}
		if(x_char == 'p'){
			step--;
			fgetc(fp);
			printf("Pass successfully.\n");
			continue;
		}

		if(feof(fp)) break;

		int x = x_char - 'a', y;
		fscanf(fp, "%d", &y);
		fgetc(fp);
		y--;

		if(board[x][y][step - 2] != 0) {
			step--;
			printf("There's already a stone here, please input again.\n");
			continue;
		}

		fprintf(stderr, "%c on (%d, %d)\n", step%2?'0':'@', x, y);

		for(int i=0;i<border;i++)
			for(int j=0;j<border;j++)
				board[i][j][step - 1] = board[i][j][step - 2];
		board[x][y][step - 1] = step%2 + 1;

		if(x > 0) { // left
			if(board[x-1][y][step-1] == ((step+1) % 2 + 1)) eat(x-1, y, (step+1) % 2 + 1);
		}
		if(y > 0) { // top
			if(board[x][y-1][step-1] == ((step+1) % 2 + 1)) eat(x, y-1, (step+1) % 2 + 1);
		}
		if(x < border - 1) { // right
			if(board[x+1][y][step-1] == ((step+1) % 2 + 1)) eat(x+1, y, (step+1) % 2 + 1);
		}
		if(y < border - 1) { // bottom
			if(board[x][y+1][step-1] == ((step+1) % 2 + 1)) eat(x, y+1, (step+1) % 2 + 1);
		}

		if(eat(x, y, step % 2 + 1)) {
			step--;
			printf("Forbidden point, please input again.\n");
			continue;
		}

		int same = 1;
		for(int i=0;i<border;i++) {
			for(int j=0;j<border;j++) {
				if(board[i][j][step - 1] != board[i][j][step - 2]) {
					same = 0;
					break;
				}
			}
			if(!same) break;
		}
		if(same) {
			printf("Same situation as before, please input again.\n");
			step--;
		}
		for(int i=0;i<border;i++) {
			for(int j=0;j<border;j++) putc((board[i][j][step-1]==0?'+':
												(board[i][j][step-1]==1?'@':'0')), stderr);
			putc('\n', stderr);
		}
		fprintf(stderr, "-----\n");
	}
	
	if(resign) {
		printf("%s wins by resignation.", step%2?"White":"Black");
	} else {
		int black = 0, white = 0;
		for(int i=0;i<border;i++) {
			for(int j=0;j<border;j++) {
				finalboard[i][j] = board[i][j][step-2];
			}
		}
		for(int i=0;i<border;i++) {
			for(int j=0;j<border;j++) {
				if(finalboard[i][j] == 0) fill(i, j);
				if(finalboard[i][j] == 1) black++;
				if(finalboard[i][j] == 2) white++;
			}
		}
		float score = black - white - komi;
		if(score > 0) {
			printf("Black wins by %f points.\n", score);
		} else {
			printf("White wins by %f points.\n", -score);
		}
	}

	for(int i=0;i<border;i++) {
		for(int j=0;j<border;j++) putchar((board[i][j][step-2]==0?'+':
											(board[i][j][step-2]==1?'@':'0')));
		putchar('\n');
	}
}

int eat(int x, int y, int player) {
	int temp[15][15];
	for(int i=0;i<border;i++)
		for(int j=0;j<border;j++)
			temp[i][j] = board[i][j][step - 1];
	
	int queue[100][2];
	int top = 1;
	queue[0][0] = x;
	queue[0][1] = y;
	
	temp[x][y] = 3;

	while(top) {
		//Dequeue
		int curx = queue[0][0], cury = queue[0][1];
		for(int i=0;i<top - 1;i++) {
			queue[i][0] = queue[i+1][0];
			queue[i][1] = queue[i+1][1];
		}
		top--;

		if(curx > 0) { // left
			if(temp[curx-1][cury] == 0) return 0; // Lives
			if(temp[curx-1][cury] == player) { // Border Expansion
				queue[top++][0] = curx - 1; // Enqueue
				queue[top - 1][1] = cury;
				temp[curx-1][cury] = 3;
			}
		}
		if(cury > 0) { // top
			if(temp[curx][cury-1] == 0) return 0; // Lives
			if(temp[curx][cury-1] == player) { // Border Expansion
				queue[top++][0] = curx; // Enqueue
				queue[top - 1][1] = cury - 1;
				temp[curx][cury-1] = 3;
			}
		}
		if(curx < border - 1) { // right
			if(temp[curx+1][cury] == 0) return 0; // Lives
			if(temp[curx+1][cury] == player) { // Border Expansion
				queue[top++][0] = curx + 1; // Enqueue
				queue[top - 1][1] = cury;
				temp[curx+1][cury] = 3;
			}
		}
		if(cury < border - 1) { // bottom
			if(temp[curx][cury+1] == 0) return 0; // Lives
			if(temp[curx][cury+1] == player) { // Border Expansion
				queue[top++][0] = curx; // Enqueue
				queue[top - 1][1] = cury + 1;
				temp[curx][cury+1] = 3;
			}
		}
	}
	
	// eat
	for(int i=0;i<border;i++)
		for(int j=0;j<border;j++)
			if(temp[i][j] == 3) board[i][j][step-1] = 0;
	
	return 1;
}

void fill(int x, int y) {
	int temp[15][15];
	for(int i=0;i<border;i++)
		for(int j=0;j<border;j++)
			temp[i][j] = finalboard[i][j];
	
	int queue[100][2];
	int top = 1;
	int whiteflag = 0, blackflag = 0;
	queue[0][0] = x;
	queue[0][1] = y;
	
	temp[x][y] = 3;

	while(top) {
		//Dequeue
		int curx = queue[0][0], cury = queue[0][1];
		for(int i=0;i<top - 1;i++) {
			queue[i][0] = queue[i+1][0];
			queue[i][1] = queue[i+1][1];
		}
		top--;

		if(curx > 0) { // left
			if(temp[curx-1][cury] == 0) { // Border Expansion
				queue[top++][0] = curx - 1; // Enqueue
				queue[top - 1][1] = cury;
				temp[curx-1][cury] = 3;
			} else if(temp[curx-1][cury] == 1) {
				blackflag = 1;
			} else if(temp[curx-1][cury] == 2) {
				whiteflag = 1;
			}
		}
		if(cury > 0) { // top
			if(temp[curx][cury-1] == 0) { // Border Expansion
				queue[top++][0] = curx; // Enqueue
				queue[top - 1][1] = cury - 1;
				temp[curx][cury-1] = 3;
			} else if(temp[curx][cury-1] == 1) {
				blackflag = 1;
			} else if(temp[curx][cury-1] == 2) {
				whiteflag = 1;
			}
		}
		if(curx < border - 1) { // right
			if(temp[curx+1][cury] == 0) { // Border Expansion
				queue[top++][0] = curx + 1; // Enqueue
				queue[top - 1][1] = cury;
			} else if(temp[curx+1][cury] == 1) {
				blackflag = 1;
			} else if(temp[curx+1][cury] == 2) {
				whiteflag = 1;
			}
		}
		if(cury < border - 1) { // bottom
			if(temp[curx][cury+1] == 0) { // Border Expansion
				queue[top++][0] = curx; // Enqueue
				queue[top - 1][1] = cury + 1;
			} else if(temp[curx][cury+1] == 1) {
				blackflag = 1;
			} else if(temp[curx][cury+1] == 2) {
				whiteflag = 1;
			}
		}
	}
	
	// change color
	for(int i=0;i<border;i++)
		for(int j=0;j<border;j++)
			if(temp[i][j] == 3) finalboard[i][j] = (blackflag&&!whiteflag)?1:
												(whiteflag&&!blackflag)?2:0;
}
