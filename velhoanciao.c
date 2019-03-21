#include <ncurses.h>
#include <string.h> 

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
    initscr();

    raw();
    noecho();

    splash(); // Splash screen

    char* groselha = "Oh, grande mestre ancião, compartilhe sua sabedoria";

    move(LINES/2,COLS/3);

    char str[110], ch;
    int i;
    printf("Digite sua pergunta...");
    i = 0;
    ch = getchar ();

    // Pegando a resposta
    while(ch!='\\') {
	str[i] = ch; i++;
	ch = getchar();
	printf("%c", groselha[i]);
    }

    int foo = getch();
    while(foo!='\n') {
	foo = getch();
	printf("%c", foo);
    }

    str[i] ='\0';

    mvprintw(LINES - 2, 0, "You Entered: %s", str);

    refresh();
    getch();
    
    endwin();

    return 0;
}
