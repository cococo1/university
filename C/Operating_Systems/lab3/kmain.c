#include "lib/video.c"
//Commands:
void cmd_clrscr(void);
void cmd_privet(char** args);
void cmd_senseOfLife(void);
void cmd_whatIs(char *arg);


#define MAX_LENGTH_OF_STRING_TO_READ 256
#define MAX_NUMBER_OF_ARGS 5
#define MAX_LENGTH_OF_ARG 40
#define MAX_INDEX_FOR_FUNCTIONS_ARRAY 1000



//returns an "unique" integer for a given string
int getIndexForString(char *string);

//calls a function represented by a pointer, passing the corresponding arguments, stored in an array of words
//returns 1 if call successful, 0 otherwise
int callFunctionWithPointerAndArgs(void (*pointer)(),char args[MAX_NUMBER_OF_ARGS][MAX_LENGTH_OF_ARG]);

//adds a pointer function to functions array, generating an unique indef for a given name
void addCmdFunction(void (**functions)(),char* name,void (*function)());

//initialize all existent cmd functions calling addCmdFunction
void initializeFunctions(void (**functions)());

//parse the string and detect all the words which come after the first one, store them into args
int collectArguments(char* stringContainingArguments,char args[MAX_NUMBER_OF_ARGS][MAX_LENGTH_OF_ARG]);

//erease the existing arguments from the args
void resetArguments(char args[MAX_NUMBER_OF_ARGS][MAX_LENGTH_OF_ARG]);


int main( void )
{
    char s[MAX_LENGTH_OF_STRING_TO_READ];
    int index,i;
    void (*functions[MAX_INDEX_FOR_FUNCTIONS_ARRAY])(); 
    char args[MAX_NUMBER_OF_ARGS][MAX_LENGTH_OF_ARG]; //An array of char* arguments
    
    
    
    initializeFunctions(functions);
    
    
    while (1) {
        
        
        gets(s);
        index=getIndexForString(s);
        
        collectArguments(s,args);

        if (!callFunctionWithPointerAndArgs(functions[index],args)){
            puts("you typed: ");
            puts(s);
            newLine();

        }
        

    }
        
  for(;;);
}
/*
void greet(char  args[MAX_NUMBER_OF_ARGS][MAX_LENGTH_OF_ARG]){
    cmd_greet(args);
}

void senseOfLife(){
    cmd_senseOfLife();
}

void clear(){
    cmd_clrscr();
}

void whatIs(args){
    cmd_whatIs(args);
}
*/

void addCmdFunction(void (**functions)(),char* name,void (*function)()){
    int index=getIndexForString(name);
    functions[index]=function;
}

void initializeFunctions(void (**functions)()){
    
    addCmdFunction(functions,"privet",&cmd_privet);
    addCmdFunction(functions,"clrscr",&cmd_clrscr);
    addCmdFunction(functions,"senseOfLife",&cmd_senseOfLife);
    addCmdFunction(functions,"whatIs",&cmd_whatIs);


    
}


void resetArguments(char args[MAX_NUMBER_OF_ARGS][MAX_LENGTH_OF_ARG]){
    int i;
    
    for (i=0; i<MAX_NUMBER_OF_ARGS; i++) {
        strcpy(args[i]," ");
    }
}

int collectArguments(char* string, char args[MAX_NUMBER_OF_ARGS][MAX_LENGTH_OF_ARG]){

    int i=0,j=0,argNumber=0;
    
    resetArguments(args);
    
    while (string[i]!=' ') { //first word is the function name, skip that
        if (string[i]=='\0') {
            return 0; //no args
        }
        i++;
    };
    i++;
    

    
    //we found a space
    while (string[i]!='\0') {
        
        while (string[i]==' ') { //skip the spaces
            i++;
            if (string[i]=='\0') {
                return 0; //no args
            }
        }
        
        //we found an arg
        while (string[i]!=' ' && string[i]!='\0') {
            //putc(string[i]);
            args[argNumber][j]=string[i];
            j++;
            i++;
        }
        args[argNumber][j]='\0';
        //puts("arg: ");

       // puts(args[argNumber]);
        newLine();
        j=0;
        argNumber++;
    }
    
    return argNumber;
}




int getIndexForString(char *string){ //a character has a unique order in ASCII
    int i=0;
    int result=0;
    while (string[i]!='\0' && string[i]!=' ') {
        result=result+(string[i]-'a'+1)*(i+1);
        i++;
    }
    return (result>0) ? result:(-result); //return abs(result)
}





int callFunctionWithPointerAndArgs(void (*pointer)(),char args[MAX_NUMBER_OF_ARGS][MAX_LENGTH_OF_ARG]){
    if (pointer) {
        (*pointer)(args);
        newLine();
        return 1;
    }
    newLine();
    return 0;
}









