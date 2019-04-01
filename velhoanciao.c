#include <ncurses.h>
#include <string.h> 

WINDOW *w;
int x,y;

int center(char str[], int col) {
    return (col-strlen(str))/2;
}

void splash()
{
    int row,col;
    char spl[]="Velho Anciao...";
    char press[]="pressione qualquer tecla para fazer uma pergunta...";
    getmaxyx(stdscr, row, col);

    attron(A_BOLD);
    mvprintw(row/2, center(spl, col), "%s", spl);
    mvprintw(row/2 + 1, center(press,col), "%s",press);
    attroff(A_BOLD);

    getch();	
    clear();
    refresh();
}

int main()
{   
    w = initscr();

    raw();
    noecho();

    splash(); // Splash screen

    char groselha[53] = "Oh, grande mestre ancião, compartilhe sua sabedoria";

    move(LINES/2,COLS/3);

    char str[110], ch;
    int i = 0;
    printw("Digite sua pergunta...");
    move((LINES/2)+1,COLS/3);
    refresh();
    // Pegando a resposta
    while(1) {
	ch = getch();

	if(ch == '\\') break; 

	if(ch == 127) {
	    //mvdelch();
	    continue;
	}

	printw("%c", groselha[i]);
	str[i] = ch; i++;
	refresh();
    }

    while(1) {
	ch = getch();
	if(ch == '\n') break; 
	printw("%c", ch);
	refresh();
    }

    clear();

    attron(A_BOLD);
    move((LINES/2)+1,COLS/3);
    printw("Mestre responde: %s", str);
    attroff(A_BOLD);
    refresh();

    getch();
    
    endwin();

    return 0;
}
