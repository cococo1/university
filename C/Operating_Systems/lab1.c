#include "lib/video.c"
#include "lib/io.c"
#include "lib/kbd.c"

int cursorPosition=0;
char* vidmem = (char *) 0xb8000;


void putc(char c);
void puts(char* string);
char* gets(char *string);
void clrscr();

int main( void )
{
    char s[256],c;
 /*putc('a');
    putc('b');
    putc('c');
    puts("Aha!");
    getchar();
    clrscr();
    puts("No way.");
    putc('a');
    clrscr();
  
    
    */
    gets(s);
    cursorPosition=10;
    puts(s);
   // c=getchar();
    
  for(;;);
}

void putc(char c){
    vidmem[cursorPosition*2]=c;
    vidmem[cursorPosition*2+1]=0x7;
    cursorPosition++;
}

void puts(char* string){
    int i=0;
    while (string[i]!='\0') {
        putc(string[i]);
        i++;
    }
}

char* gets(char *string){
    int i=0;
    while ((string[i]=getchar())!='\n') {
        putc(string[i]);
        i++;
    }
    string[i]='\n\r';
    i++;
    //putc(string[i]);
    string[i]='\0';
    //clrscr();
    return string;
}

void clrscr(){
    int i=0;
    for (i; i<cursorPosition; i++) {
        vidmem[i*2]=' ';
        vidmem[i*2+1]=0x0;
    }
    cursorPosition=0;
}