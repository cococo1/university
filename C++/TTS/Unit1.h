//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <MPlayer.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------
class TText_Reader_Ro : public TForm
{
__published:	// IDE-managed Components
        TMediaPlayer *player2;
        TMediaPlayer *player;
        TEdit *Edit1;
        TButton *Start;
        TTimer *timer;
        TOpenDialog *OpenDialog1;
        TButton *select_file;
        TButton *stop;
        TButton *pause;
        void __fastcall StartClick(TObject *Sender);
        void __fastcall timerTimer(TObject *Sender);
        void __fastcall select_fileClick(TObject *Sender);
        void __fastcall stopClick(TObject *Sender);
        void __fastcall pauseClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
        __fastcall TText_Reader_Ro(TComponent* Owner);
};
//---------------------------------------------------------------------------
typedef struct list_of_files
{
        char *file;
        int copy; //Takes value 1 if this file is a copy, 0 otherwise.
                //When we remove a file from list, we should know if there was made
                // a copy of original file and this copy should be removed.
        struct list_of_files* next;
}list_of_files;
//---------------------------------------------------------------------------
extern PACKAGE TText_Reader_Ro *Text_Reader_Ro;
//---------------------------------------------------------------------------
char* copy_file(list_of_files* element);
//Creates a copy of .wav file, which name is contained in element->file
//also creates a new element and inserts it into list after this element
//and returns the name of new created file.
//*element -the pointer to some element which needs to  be duplicated.
int exist(char *name);
//Verifyes if exist a .wav file by given name (1-found, 0-not found;)
void delete_files(char* file1,char* file2,list_of_files** head);
//Verifys if first files from list are still opened (file1, file2),
//if not deletes the elements from list, modifing the adress of the head
//and deletes copies from HD if this element from list is a created copy .
// *file1 - pointer to name of the file which is opened in player;
// *file2 - pointer to name of the file which is opened in player2;
//**head - pointer to pointer of the first element of the link list;
list_of_files* add_before(char* word,list_of_files* adress,list_of_files** head);
//Adds an element into link list before indicated adress; If head is NULL, creates head
//Also copies string *word into element->file (new created element);
//*adress - the pointer of adress before which we should insert new element;
list_of_files* add_after(char* word, list_of_files* adress,list_of_files** head);
//Adds an element into link list after indicated adress; If head is NULL, creates head
//Also copies string *word into element->file (new created element);
//*adress - the pointer of adress after which we should insert new element;
char* separate(char* word,int i,int n);
//Returns a sub-string of word, which starts with index i, and will have the length n
//If null-byte is reached it stops. Function is used in divide() function
void divide(char* word,int n,list_of_files** head,int control,list_of_files* old_adress);
//Main version of recursive function, which forms a list of list_of_files, searching
// biggest existing .wav files
//  word - string to investigate;
// n - number of characters that should contain a string in order to be found (starts
//with 10 and decrements at the end)
//** head - adress of the head of the list;
// control - verifyes if we should insert the new element before or after existing old_adress;
//old_adress - last stored element in list;
void edit_string(char* string);
//Substitutes with '-' everywhere where are other simbols than digits or letters
// (for pause, space) .
void find_words_in_sentence(char*sentence);
//Uses global variable char** words where it stores words from sentence
//---------------------------------------------------------------------------
#endif
