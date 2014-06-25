/*
Text-to-speech program for romanian language .
Modified : 16/05/2011
Author : Chetrusca Maxim
Time : 50 hours...
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <conio.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TText_Reader_Ro *Text_Reader_Ro;
int j=0;  
//Global variable used as index at array of words
//( is needed in two functions, that is why it is global.)
list_of_files *head=NULL, *adress=NULL;
char **words=NULL;
//An array of strings, that represent a sentence 
//---------------------------------------------------------------------------
__fastcall TText_Reader_Ro::TText_Reader_Ro(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
char* copy_file(list_of_files* element)
{
	if (!element) { ShowMessage("Error! copy_file()"); return "sounds//-.wav"; }
	FILE *f1=NULL,*f2=NULL;
    list_of_files* new_element=NULL;
	int i=0,n=0;
	char *str=(char*)malloc(23*sizeof(char));
	char *str1=(char*)malloc(20*sizeof(char));
	char c;
    new_element=(list_of_files*)malloc(sizeof(list_of_files));
    //Allocating memory for new element
    if (!new_element || !str || !str1) { ShowMessage("Error! copy_file()"); return "sounds//-.wav"; }
    new_element->file=(char*)malloc(sizeof(char)*(1+strlen(element->file)));
    //Allocating memory for name of the file;
    if (!new_element->file) { ShowMessage("Error! copy_file()"); return "sounds//-.wav";  }
	//"-.wav" - name of file with pause;
    new_element->next=element->next;
    new_element->copy=1;
    //IMPORTANT : this is a copy, so in the end, when function delete_files will
    //be called, the file created now will be deleted from HD ;
    //so we assign to new_element->copy 1 , to know that this is a copy.
    element->next=new_element;
	while (element->file[i]!='.') { new_element->file[i]=element->file[i]; i++; }
    new_element->file[i]='\0';
	//Copies the name of the .wav without extension
	f1=fopen(element->file,"rb");
	//Binary reading.
	if (!f1) { ShowMessage("Error! copy_file()"); return "sounds//-.wav"; }
	f2=f1;
	//We need f2!=NULL at while .
	strcpy(str1,new_element->file);
    // ShowMessage(str1);
	// We need always the initial name, for example "a" (from "a.wav"),
    //so we store it into str1
	// then we will use :a0,a1..(copy name),
	while (f2)
	{
		strcpy(new_element->file,str1);
        //ShowMessage(new_element->file);
		//New name starts also with "a"
		str=itoa(n,str,10);
		//converts n into string . 10 - decimal form .initial n=0.
        new_element->file=strcat(new_element->file,str);
        // ShowMessage(new_element->file);
		//Adds some number to the end of the original name;
        new_element->file=strcat(new_element->file,".wav");
        //ShowMessage(new_element->file);
		f2=fopen(new_element->file,"r");
		fclose(f2);
		// Even if we close a file, f2!=NULL
        // if it exists, then a new name should be chosen
		//HERE : if a new name, for example "a0" already exists,
		// then another name is created, for example "a1"
		++n;
	}  //END OF WHILE(f2)
	//ShowMessage("name found.");

	f2=fopen(new_element->file,"wb");
	//binary writting
	if (!f2){ ShowMessage("Error! copy_file()"); return "sounds//-.wav"; }
	while (!feof(f1))  //feof(file) - function that detects the end of file.
	{
		fread(&c,sizeof(char),1,f1);
		//reads one character from f1, stores it in c;
		fwrite(&c,sizeof(char),1,f2);
		//writes one character into f2.
	}  //END OF WHILE(feof()) ShowMessage("Done.");
	free(str);
	free(str1);
	fclose(f1);
	fclose(f2);
	return new_element->file;
}
//---------------------------------------------------------------------------
int exist(char* name)
{
	//This function is called in divide function
    if (!name) return 0;
    if (strlen(name)>10) return 0;
	FILE *f=NULL;
	char *s1=(char*)(malloc(sizeof(char)*23));
	if (!s1) { ShowMessage("Error! exist()."); return 0; }
    // s1=strcpy(s1,ExtractFilePath(Application->ExeName).c_str());
    strcpy(s1,"sounds\\");
	strcat(s1,name);
	strcat(s1,".wav");
    // ShowMessage(s1);
	f=fopen(s1,"r");
	free(s1);
	s1=NULL;
	if (!f) {  fclose(f);   return 0; }
    fclose(f);
	return 1;
}
//---------------------------------------------------------------------------
void delete_files(char* file1,char* file2,list_of_files** head)
{
	if (!file1 || !file2 || !*head) {ShowMessage("Error! delete_files()"); return;}
	int i,a=1,b=1; //i used in for-loop, a,b - result of strcmp()
    list_of_files *c=*head;
    while ((a!=0) && (b!=0) && *head)
	{
		a=strcmp(file1,(*head)->file);
        b=strcmp(file2,(*head)->file);
        if ((a!=0) && (b!=0))        //These files are not opened.
		{
			c=(*head);
            // ShowMessage(c->file);
            //ShowMessage(c->copy);
            if (c->copy)  remove(c->file); //ShowMessage("deleted."); }
            (*head)=(*head)->next;
            free(c->file);
            free(c);
            c=NULL;
		}
	}
}
//---------------------------------------------------------------------------
list_of_files* add_before(char* word,list_of_files *adress,list_of_files** head)
{
	if (!word) {ShowMessage("Error! add_before()."); return NULL;}
	list_of_files *c=NULL, *p=NULL;
	if (!*head) 
	{
		*head=(list_of_files*)malloc(sizeof(list_of_files));
		if (!*head) { ShowMessage("Error! add_before()."); return NULL; }
        (*head)->file=(char*)malloc(sizeof(char)*(14+strlen(word)));
        //14 =sounds//+'\0'+".wav"
        if (!(*head)->file) { ShowMessage("Error! add_before()."); return NULL; }
        strcpy((*head)->file,"sounds//");
		strcat((*head)->file,word);
        strcat((*head)->file,".wav");
		(*head)->next=NULL;
        (*head)->copy=0;
		return *head;
	}
	c=*head;
	if (adress==*head)
	{
		p=(list_of_files*)malloc(sizeof(list_of_files));
		if (!p) { ShowMessage("Error! add_before()."); return NULL;}
        p->file=(char*)malloc(sizeof(char)*(14+strlen(word)));
        //14 =sounds//+'\0'+".wav"
        if (!p->file) { ShowMessage("Error! add_before()."); return NULL; }
        strcpy(p->file,"sounds//");
		strcat(p->file,word);
        strcat(p->file,".wav");
		p->next=c;
        p->copy=0;
		*head=p;
		return p;
	}
	while(c->next!=adress && c->next) c=c->next;
	if (!c) { ShowMessage("Error! add_before()."); return NULL; }
	p=(list_of_files*)malloc(sizeof(list_of_files));
	if (!p) { ShowMessage("Error! add_before()."); return NULL; }
    p->file=(char*)malloc(sizeof(char)*(14+strlen(word)));
    //14 =sounds//+'\0'+".wav"
    if (!p->file) { ShowMessage("Error! add_before()."); return NULL;  }
    strcpy(p->file,"sounds//");
	strcat(p->file,word);
    strcat(p->file,".wav");
	p->next=c->next;
    p->copy=0;
	c->next=p;
	return p;
}
//----------------------------------------------------------
list_of_files* add_after(char* word, list_of_files* adress, list_of_files** head)
{
	if (!word) {ShowMessage("Error! add_after()."); return NULL;}
	list_of_files *p=NULL;
    if (!*head)
	{
		*head=(list_of_files*)malloc(sizeof(list_of_files));
		if (!*head) { ShowMessage("Error! add_after()"); return NULL; }
        (*head)->file=(char*)malloc(sizeof(char)*(14+strlen(word)));
        //14 =sounds//+'\0'+".wav"
        if (!(*head)->file) {ShowMessage("Error! add_after()"); return NULL;}
        strcpy((*head)->file,"sounds//");
		strcat((*head)->file,word);
        strcat((*head)->file,".wav");
		(*head)->next=NULL;
        (*head)->copy=0;
		return *head;
	}
	if (!adress) {ShowMessage("Error! add_after."); return NULL;}
	p=(list_of_files*)malloc(sizeof(list_of_files));
	if (!p) {ShowMessage("Error! add_after()"); return NULL; }
    p->file=(char*)malloc(sizeof(char)*(14+strlen(word)));
    //14 =sounds//+'\0'+".wav"
    if (!p->file) { ShowMessage("Error! add_after()"); return NULL; }
    strcpy(p->file,"sounds//");
	strcat(p->file,word);
    strcat(p->file,".wav");
	p->next=adress->next;
    p->copy=0;
	adress->next=p;
	return p;
}
//----------------------------------------------------------

char* separate(char* word,int i,int n)
{
	if (!word) {ShowMessage("Error! separate()."); return NULL;}
	int j=0;
	char *c=(char*)malloc(sizeof(char));
	if (!c) {ShowMessage("Error! separate()."); return NULL;}

	while(j<n)
	{
		if (word[i]=='\0') break;
		c[j]=word[i];
		j++; i++;
		c=(char*)realloc(c,sizeof(char)*(j+1));
		if (!c) {ShowMessage("Error! separate()."); return NULL;}
	}
	c[j]='\0';
	return c;
}
//--------------------------------------------------------
void divide(char* word,int n,list_of_files** head,int control,list_of_files* old_adress)
{
	int i=0;
	char* test=NULL;
	list_of_files* new_adress=NULL;
	if (!word[i])  return;
    // ShowMessage(word);
	if (strlen(word)<n) { divide(word,n-1,head,control,old_adress); return; }
	while (word[i])
	{
		//if (strlen(word)-i<n)n--;
		test=separate(word,i,n);
		if (strlen(test)<(unsigned)n) { break;}
        // ShowMessage(test);
		if (exist(test)) 
		{   
			//ShowMessage("Found word!");
			if (!control) new_adress=add_before(test,old_adress,head);
			else  new_adress=add_after(test,old_adress,head);
			word[i]='\0'; divide(word,n,head,0,new_adress); 
			divide(&word[i+strlen(test)],n,head,1,new_adress);//sterge; divide(a); divide(b); 
            //  ShowMessage("bingo!");
			return;
		}
		i++;
	}    //End of while(word[i])
	if (n==0) return;
	divide(word,n-1,head,control,old_adress);
}

//---------------------------------------------------------------------------
void edit_string(char* string)
{
	if (!string) {ShowMessage("Error! edit_string()"); return;}
	int i=0;

	while (string[i])
	{
		if (!isdigit(string[i]) && !isalpha(string[i]))
		{
			if (string[i]=='.' || string[i]=='!' || string[i]=='?')
				string[i]='(';
			else string[i]='-';
		}

		i++;
	}
}
//---------------------------------------------------------------------------
void __fastcall TText_Reader_Ro::StartClick(TObject *Sender)
{
   char *string=NULL;
   int length=0;
   Start->Enabled=false;
   select_file->Enabled=false;
   //ShowMessage(Edit1->Text.Length());
   length=Edit1->Text.Length();
   string=(char*)malloc(sizeof(char)*(1+length));
   //words=(char**)malloc(sizeof(char*));
   if (!string){ ShowMessage("Error! Start()"); return ; }
   strcpy(string,Edit1->Text.c_str());
   string[length]='\0';
   //ShowMessage(string);
   if (!strcmp(string,""))
   {
	   ShowMessage("No written words.");
	   Start->Enabled=true;
	   select_file->Enabled=true;
	   free(string);
	   return;
   }
   strlwr(string);

   find_words_in_sentence(string);//Separates string into words,and store them into
   //global variable char** words
   free(string);
   string=NULL;
   timer->Enabled=true;
   stop->Enabled=true;
   pause->Enabled=true;  //If the word is not played, timer is called once in 50 mlsec.
    // This is the pause
 /////////////////////////////////////////////////////////////////////////////

}
//---------------------------------------------------------------------------
void __fastcall TText_Reader_Ro::timerTimer(TObject *Sender)
{
	int i=0;    //Used to control which player to open now;
	int length1=0,length2=0;
	list_of_files* p=NULL;  //pointer used to traverse the list of files;
 /////////////////////////////////////////////////////////////////////////////
	
	head=NULL;
    timer->Enabled=false;  //That time in which words are played timer should not be called.

    //ShowMessage(words[j]);
	if (!words[j])
	{
		ShowMessage("This is not a word.");
        while (words[j])
		{
			free(words[j]);
			words[j]=NULL;
			j++;
		}
		free(words);
		words=NULL;
		Start->Enabled=true;
		select_file->Enabled=true;
		stop->Enabled=false;
		pause->Enabled=false;
        return;
	}
	divide(words[j],10,&head,0,NULL);

	if (!head)
	{
		ShowMessage("Still not head after divide.");
        while (words[j])
        {
			free(words[j]);
            words[j]=NULL;
            j++;
		}
		free(words);
		words=NULL;
		Start->Enabled=true;
		select_file->Enabled=true;
		stop->Enabled=false;
		pause->Enabled=false;
		return;
	}
    adress=NULL; //global variable

    p=head;

//11111111111111
	while (p)
	{
		//ShowMessage(p->file);
		if (p==head)   //That means this is the first iteration;
		{
			player->FileName=p->file; //"sounds//a.wav";
			//ShowMessage(player->FileName);
			if (!strcmp(p->file,"sounds//a.wav")) player2->FileName="sounds//-.wav";
            else  player2->FileName="sounds//a.wav";
            // ShowMessage(player2->FileName);
            //It is necessary to initialize  player2->FileName;
			player2->Open();
			player->Open();
			player->Play();
			++i;        //If i is odd, then player2 should open next file,
                        //otherwise player;
			p=p->next;
		}
		length1=player->Length;
		if ((player->Position>=(length1-length1/2.5)) && (i%2!=0))
        //When previous track is "ending" the next one beggins
		{
			delete_files(player->FileName.c_str(),player2->FileName.c_str(),&head);
            //Deletes the files from list that were already played;
			player2->FileName=p->file;
			if (player2->FileName==player->FileName)
            //Two players cannot open the same file
            //If so, we must make a copy of it
			{
				player2->FileName=copy_file(p);
				//This function call added also a new element in list, after p
                //and created a copy of file p->file
                p=p->next;
			}
		    //	ShowMessage(player2->FileName);
			player2->Open();
			player2->Play();
			++i;
            p=p->next;
		}
        length2=player2->Length;
		if ((player2->Position>=(length2-length2/2.5))&& (i%2==0))
		{
			delete_files(player->FileName.c_str(),player2->FileName.c_str(),&head);
			player->FileName=p->file;
			if (player2->FileName==player->FileName)
			{
				player->FileName=copy_file(p);
                p=p->next;
			}
		    //	ShowMessage(player->FileName);
			player->Open();
			player->Play();
			++i;
            p=p->next;
		}
	}
    // ShowMessage("Reached end of while");
	// END OF WHILE(p)

	while (1)     //This while simply "waits" when the playing will end.
	{
		//ShowMessage(player->Position);
        //ShowMessage(player2->Position);
        if ((player->Position==player->Length) &&
         ((player2->Position==player2->Length)|| player2->Position==0)) break;
         if ((player2->Position==player2->Length) &&
         ((player->Position==0)|| player->Position==player->Length)) break;
	} //Then , we can delete all remaining files from list :
	player->Close();
    player2->Close();
    player->FileName="";
    player2->FileName="";
    if (head) delete_files(player->FileName.c_str(),player2->FileName.c_str(),&head);
    p=head;
//PAUSE
//////////////////////
	free(words[j]); //words[j] just was played . so , we can erease it.
    free(head);     // head is prepared for a new play.
    head=NULL;
    words[j]=NULL;
    j++;               //going to the next word.
	//  }  END OF WHILE(WORDS[J])
	if (!words[j])    //That means : no more words.
	{
		timer->Enabled=false;
		free(words);
        words=NULL;
        Start->Enabled=true;
        select_file->Enabled=true;
        stop->Enabled=false;
        pause->Enabled=false;
	}
	else if (stop->Enabled) timer->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TText_Reader_Ro::select_fileClick(TObject *Sender)
{
	FILE *file=NULL;
	int length=0,i=0;
	char c,*string=NULL;
	select_file->Enabled=false;
	Start->Enabled=false;
	OpenDialog1->InitialDir=GetCurrentDir();
	//ShowMessage(GetCurrentDir());
	if (!OpenDialog1->Execute()) goto label1;
	length=OpenDialog1->FileName.Length();
	if (  length>4  &&
    OpenDialog1->FileName[length]=='t' &&
     OpenDialog1->FileName[length-1]=='x' &&
     OpenDialog1->FileName[length-2]=='t' )
	{
		file=fopen(OpenDialog1->FileName.c_str(),"r");
        if (!file) { ShowMessage("Error! select_Click()"); goto label1; }
/////////////////////////////////////////////////////////////////////
		c=getc(file);
		while (!feof(file) && i<1000)
		{
			string=(char*)realloc(string,sizeof(char)*(i+1));
            if (!string) {ShowMessage("Error! select_fileClick()"); goto label1;}
            string[i]=c;
            c=getc(file);
            i++;
		}
		string=(char*)realloc(string,sizeof(char)*(i+1));
		if (!string) {ShowMessage("Error! select_fileclick()"); goto label1;}
        string[i]='\0';
        ShowMessage(string);
        strlwr(string);
        find_words_in_sentence(string);
        free(string);
        string=NULL;

        SetCurrentDir(ExtractFilePath(Application->ExeName));

             /*while (words[j])
                 {
                  ShowMessage(words[j]);
                        j++;
                 } */
        j=0;
        timer->Enabled=true;
        stop->Enabled=true;
        pause->Enabled=true;

	}
	else ShowMessage("This is not a text file (.txt).");


label: label1:
	if (file) { fclose(file); }
	if (!timer->Enabled) { select_file->Enabled=true; Start->Enabled=true; }
}
//---------------------------------------------------------------------------
void find_words_in_sentence(char* sentence)
{
	if (!sentence) { ShowMessage("Error! find_words_in_sentence()"); return; }
	int i=0,start_position=0,n=0;
	edit_string(sentence);  //Mark the spaces, ',' ,'.', \ ,etc
	//ShowMessage(sentence);
	while (sentence[i])   //Finds the words in sentence and introduce them into array of strings
	{
		while (sentence[i]=='-' && sentence[i]) {i++;}
        if (!sentence[i]) break;
        start_position=i;
        j=0;   //global variable  but it is used for other sake in this function
        if (sentence[i]!='-' && sentence[i])
        {
			n++;
            words=(char**)realloc(words,sizeof(char*)*n);
            if (!words) {ShowMessage("Error! find_words_in_sentence()"); return;}
            words[n-1]=NULL;
        }

        while (sentence[i]!='-' && sentence[i])
        {   //ShowMessage(n);
			i++;
            words[n-1]=(char*)realloc(words[n-1],sizeof(char)*(i+1-start_position));
            if (!words[n-1]) {ShowMessage("Error! find_words_in_sentence()"); return;}
            words[n-1][j]=sentence[i-1];
            j++;
        }
		if (words[n-1])
		{
			words[n-1][j]='\0';
			//ShowMessage(words[n-1]);
		}
		// free(words[n-1]);
        //words[n-1]=NULL;
	}
	//ShowMessage(string);
    n++;
    words=(char**)realloc(words,sizeof(char*)*n);
    if (!words) { ShowMessage("Error! find_words_in_sentence()"); return;}
    words[n-1]=NULL;
    j=0;
    /*  while (words[j])
    {
    ShowMessage(words[j]);
    j++;
    }*/
	j=0;
}
//---------------------------------------------------------------------------

void __fastcall TText_Reader_Ro::stopClick(TObject *Sender)
{
	stop->Enabled=false;
	pause->Enabled=false; 
	timer->Enabled=false;
	while (words[j])
	{
		free(words[j]);
        words[j]=NULL;
        j++;
	}	
	free(words);
	words=NULL;
	j=0;
	if (head)
	{
		delete_files(player->FileName.c_str(),player2->FileName.c_str(),&head);
        head=NULL;
	}
	adress=NULL;
	Start->Enabled=true;
	select_file->Enabled=true;

}
//---------------------------------------------------------------------------

void __fastcall TText_Reader_Ro::pauseClick(TObject *Sender)
{
	if (stop->Enabled)
	{
		stop->Enabled=false;
        timer->Enabled=false;
        pause->Caption="Resume reading";
	}
	else
	{
         stop->Enabled=true;
         timer->Enabled=true;
         pause->Caption="Pause reading";
	}


}
//---------------------------------------------------------------------------

//END OF FILE. 
/////////////////////////////////////////////////////////////////////////////

