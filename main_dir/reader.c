#include "header_dir/reader.h"
#include <stdio.h>
#include <string.h>

//file var for reader.c
static FILE * source;


boolean reader_openFile(char fileName[strlength]){
//opening source file for narration
	source = fopen(fileName,"r");
	if (source != NULL) 
		return true;
	else
		return false;
}

void reader_checkID(char* sentence,char* outp)
{
	char* s;
	int i = 0;
	for ( s=&sentence[0]; (*s != ' ') && (*s != '\0'); s++ )
    {
		outp[i] = *s;
		i++;
    }
	outp[i] = '\0';
}

void reader_searchID(char* id,char* outp){
//search the sentence of the following id 
//to be the parameter of build narration and pass it to output
	boolean found = false;
	char sentence[strlength];
	char idcheck[idlength];
	while ((!found) && (fgets(sentence,strlength,source) != NULL)){
		reader_checkID(sentence,idcheck);
		found = !strcmp(idcheck,id);
	}
	if (found) {
		boolean firstspace = false;
		char* s;
		int i = 0;
		for ( s=&sentence[0]; (*s != '\0'); s++ )
		{		
			if (firstspace) {
				outp[i] = *s;
				i++;
			} else
				firstspace = (*s == ' ');
		}
		outp[i] = '\0';
		rewind(source);
	} else {
		outp = NULL;
	}
}

void reader_build(char* id,char** battleStatus,char* outp){
//build the desired sentence
	char sentence[strlength];
	reader_searchID(id,sentence);
	if (sentence != NULL) {
		char* s;
		boolean checkingSpecial = false;
		char special[idlength];
		int i = 0;
		int o = 0;
		for ( s=&sentence[0];(*s != '\0'); s++ )
		{	
			if ((*s != '<') && (!checkingSpecial)) {
				outp[o] = *s;
				o++;
			} else {
				checkingSpecial = true;
				if (*s != '>') {
					if (*s != '<') {
						special[i] = *s;
						i++;
					}
				} else {
					checkingSpecial = false;
					special[i] = '\0';
					i = 0;
					reader_specialChar(special,battleStatus,outp,&o);
				}
			}
		}	
		outp[o] = '\0';
		if (outp[o-1] == '\n') {
			outp[o-1] = '\0';
		}
	} else {
		outp = NULL;
	}
}

void reader_specialChar(char* special,char** battleStatus,char* outp,int *newLength)
{	
	char *player_name = battleStatus[0];
	char *enemy_name = battleStatus[1];
	char *damage  = battleStatus[2];
	
	char* s;
	int i = *newLength;
	if (strcmp(special,"p") == 0) {
		for ( s=&player_name[0]; (*s != '\0'); s++ )
		{
			outp[i] = *s;
			i++;
		}
	} else {
		if (strcmp(special,"m") == 0) {
			for ( s=&enemy_name[0]; (*s != '\0'); s++ )
			{
				outp[i] = *s;
				i++;
			}
		} else {
			if (strcmp(special,"dmg") == 0) {
				for ( s=&damage[0]; (*s != '\0'); s++ )
				{
					outp[i] = *s;
					i++;
				}
			}
		}
	}
	*newLength = i;
}

void reader_close()
{
	fclose(source);
}
