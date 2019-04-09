#include <ncurses.h>
#include <string.h> 
#include <unistd.h>

WINDOW *w;
int x,y;

char groselha[100], resposta[100], buffer;

int center(char str[], int col) {
    return (col-strlen(str))/2;
}

void splash()
{
    int row,col;
    FILE* f;

    f = fopen("mestre.txt", "r");

    char foo[1000];
    getmaxyx(stdscr, row, col);

    for (int i = 0; i<6; i++) {
	fgets( foo, 150, f);
	mvprintw( 3+i, center(foo, col), "%s", foo);
    }

    fclose(f);

    char press[]="pressione qualquer tecla para fazer uma pergunta...";

    mvprintw(row/2 + 1, center(press,col), "%s",press);

    getch();
    clear();
    refresh();
}

void pegarResposta() {
    int i = 0;
    while(1) {
	buffer = getch();

	if(buffer == '\\') break; 

	if(buffer == 127) {
	    i--;
	    continue;
	}

	printw("%c", groselha[i]);
	resposta[i] = buffer; i++;
	refresh();
    }
    
}

void responder() {
    clear();
    int linha = LINES/2;

    char resp[] = "Mestre responde:";
    mvprintw( linha-1, center(resp, COLS), "%s", resp);
    box(w, '|', '-');

    refresh();

    move(linha+1, center(resposta, COLS));
    attron(A_BOLD);
    for (int i = 0;i < strlen(resposta);i++) {
	printw( "%c", resposta[i]);
	usleep(100000); refresh();
    }
    attroff(A_BOLD);
    refresh();
}

int main()
{   
    w = initscr();

    raw();
    noecho();

    splash(); // Splash screen

    sprintf(groselha, "%s", "Oh, grande mestre ancião, compartilhe sua sabedoria" );

    move(LINES/2,COLS/3);

    printw("Digite sua pergunta...");
    move((LINES/2)+1,COLS/3);
    refresh();

    pegarResposta();

    while(1) {
    	buffer = getch();
    	if(buffer == '\n') break;

	if(buffer == 127) {
	    mvdelch(1,2);
	    continue;
	}

    	printw("%c", buffer);
    	refresh();
    }

    responder();

    getch();
    
    endwin();

    return 0;
}
