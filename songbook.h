/* @Author
 * Student Name: Mustafa SAÐLAM
 * Student ID : 150140129
 * Date: 21.11.2016*/

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;

struct song {
  char* name  ;
  char* singer ;
  char* style ;
  int year;
};

struct playlist;

struct song_node {
  song* data;
  song_node* next;
  song_node* prev;
  playlist* parent;
};

struct playlist {
  int songnumber;
  char* name ;
  song_node* head;
  playlist* next;
  playlist* prev;
};

struct list {
  int playlist_count;
  char* datasource;
  FILE* fileP;
  playlist* head;
  song* data_;
  char* listname;
  void begin();
  void readFrom();
  void addSong(playlist* present, song_node* toadd);
  playlist* createList(char* listname);//creates a new list named listname
  void createSortedList();
  void createRandomList();
  void printList(playlist* toprint);//prints list which is send to print
  void removeSong(playlist* present, int ordernum);
  void deleteList(playlist* todelete, int a);
  void write2file();
  void terminate();
};

void list::begin(){
	playlist_count = 0;
	head = NULL;

	datasource = new char[20];
	strcpy(datasource, "songbook.txt");
	if(!(fileP = fopen(datasource,"r+"))){
		if(!(fileP = fopen(datasource,"w+"))){
			cerr << "File could not open!!!" << endl;
			return;
		}
	}
	readFrom();
}

void list::readFrom(){
	char stringy[99];
	char *token;

	char* listname = new char[20];
	strcpy(listname, "Chronological");
	createList(listname);

	while(!(feof(fileP))){
		song_node *newnode = new song_node;
		data_ = new song;

		newnode->parent = head;
		fgets(stringy,99,fileP);
		if(strcmp(stringy,"*****\n") == 0) break;

		token = strtok(stringy, "\t\n");
		data_->name = new char[strlen(token)];
		strcpy(data_->name,token);

		token = strtok(NULL, "\t\n");
		data_->singer = new char[strlen(token)];
		strcpy(data_->singer, token);

		token = strtok(NULL, "\t\n");
		data_->year = atoi(token);

		token = strtok(NULL, "\t\n");
		data_->style = new char[strlen(token)];
		strcpy(data_->style,token);

		newnode->data = data_;
		newnode->parent = head;

		addSong(head, newnode);
	}
	createSortedList();
	createRandomList();

	// reading user created lists
	if(feof(fileP)){
		fclose(fileP);
		return;
	}
	while(!feof(fileP)){
		listname = new char[20];
		fgets(listname,20,fileP);
		listname[strcspn(listname, "\n")] = '\0';//getting rid of the last <\n> (EOL) character
		playlist* newlist = createList(listname);

		while(!(feof(fileP))){
			song_node *newnode = new song_node;
			data_ = new song;

			newnode->parent = newlist;
			fgets(stringy,99,fileP);
			if(strcmp(stringy,"*****\n") == 0) break;

			token = strtok(stringy, "\t\n");
			data_->name = new char[strlen(token)];
			strcpy(data_->name,token);

			token = strtok(NULL, "\t\n");
			data_->singer = new char[strlen(token)];
			strcpy(data_->singer, token);

			token = strtok(NULL, "\t\n");
			data_->year = atoi(token);

			token = strtok(NULL, "\t\n");
			data_->style = new char[strlen(token)];
			strcpy(data_->style,token);

			newnode->data = data_;
			newnode->parent = newlist;

			addSong(newlist, newnode);
		}
	}
	fclose(fileP);
}

void list::createSortedList(){
	listname = new char[20];
	strcpy(listname, "Sorted");
	playlist* sorted = createList(listname);
	song_node* current = head->head;

	do{
		song_node* traverse = sorted->head;
		song_node* toadd = new song_node;
		toadd->parent = sorted;
		toadd->data = current->data;

		if(sorted->songnumber == 0){//adding first node
			sorted->head = toadd;
			sorted->head->next = sorted->head;
			sorted->head->prev = sorted->head;
			sorted->songnumber++;
			current = current->next;
		}
		else{
			if(strcmp(current->data->singer, sorted->head->data->singer) < 0){//add as the head node
				sorted->head->prev->next = toadd;
				toadd->prev = sorted->head->prev;
				toadd->next = sorted->head;
				sorted->head->prev = toadd;
				sorted->head = toadd;
				sorted->songnumber++;
				current = current->next;
			}
			else{
				while((traverse != sorted->head->prev) && (strcmp(toadd->data->singer,traverse->data->singer) >= 0)){
					traverse = traverse->next;
				}

				if (strcmp(toadd->data->singer,traverse->data->singer) > 0){//add middle or the end
					toadd->next = traverse;
					toadd->prev = traverse->prev;
					traverse->prev->next = toadd;
					traverse->prev = toadd;
					sorted->songnumber++;
					current = current->next;
				}
				else {
					while((strcmp(toadd->data->singer,traverse->data->singer) == 0) && (strcmp(toadd->data->name,traverse->prev->data->name) > 0)){
						traverse = traverse->next;
					}
					toadd->next = traverse;
					toadd->prev = traverse->prev;
					traverse->prev->next = toadd;
					traverse->prev = toadd;
					sorted->songnumber++;
					current = current->next;
				}
			}
		}
	}while(current != head->head);
}

void list::createRandomList(){
	srand( time( NULL ) );
	int temp, maxR = head->songnumber, i = 0;
	int randNumS[maxR];

	do{//generating numbers between 0 to record number (23) in random order for further usage
		turningpoint:
		temp = rand() % maxR;
		int j = 0;
		for(; j<i; j++){
			if(temp == randNumS[j]) goto turningpoint;
		}
		randNumS[i] = temp;
		i++;
	}while(i<maxR);

	song_node* current;

	if(playlist_count < 3){//creating at the beginning as the 3rd playlist
		listname = new char[20];
		strcpy(listname, "Random");
		playlist* random = createList(listname);

		for(int i = 0; i<maxR; i++){
			current = head->head;
			for(int j = 0; j<randNumS[i]; j++){
				current = current->next;
			}

			song_node* toadd = new song_node;
			toadd->parent = random;
			toadd->data = current->data;

			addSong(random, toadd);
		}
	}
	else{
		playlist* random = head->next->next;
		song_node* tochange = random->head;

		for(int i = 0; i<maxR; i++){//change rcord order when function is called again and again
			current = head->head;
			for(int j = 0; j<randNumS[i]; j++){
				current = current->next;
			}
			tochange->data = current->data;
			tochange = tochange->next;
		}
	}
}

void list::printList(playlist* toprint){
	if(toprint == head->next->next) createRandomList();
	song_node *temp = toprint->head;
	cout << " " << toprint->name << endl;
	int i = 1;
	do{
		cout << setw(2) << right << i << ". " << setw(40) << left << temp->data->name << "\t" << setw(20) << temp->data->singer << "\t";
		cout << temp->data->year << "\t"<< temp->data->style<< "\t" << endl;
		temp = temp->next;
		i++;
	}while(temp!=toprint->head);

	getchar();
}

playlist* list::createList(char* listname){
	playlist* tocreate = new playlist;

	tocreate->head = NULL;
	tocreate->next = NULL;
	tocreate->prev = NULL;
	tocreate->songnumber = 0;
	tocreate->name = listname;


	if(head==NULL){
		head = tocreate;
		head->next = head;
		head->prev = head;
	}
	else{
		tocreate->next = head;
		head->prev->next = tocreate;
		tocreate->prev = head->prev;
		head->prev = tocreate;
	}
	playlist_count++;
	return tocreate;
}

void list::addSong(playlist* present, song_node* toadd){
	toadd->parent = present;

	if(present->songnumber == 0){//first node
		present->head = toadd;
		present->head->prev = present->head;
		present->head->next = present->head;
		present->songnumber++;
	}
	else{//other nodes
		present->head->prev->next = toadd;
		toadd->prev = present->head->prev;
		toadd->next = present->head;
		present->head->prev = toadd;
		present->songnumber++;
	}
}

void list::removeSong(playlist* present, int ordernum){
	song_node* toremove = present->head;
	for(int i = 1; i < ordernum; i++){
		toremove = toremove->next;
	}
	if(toremove == present->head){
		toremove->next = present->head;
	}
	toremove->prev->next = toremove->next;
	toremove->next->prev = toremove->prev;

	delete toremove;
	present->songnumber--;
}

void list::deleteList(playlist* todelete, int a){
	if((head == todelete) && (a == 0)){
		cerr << "Sorry, you can not delete this playlist!..." << endl;
		return;
	}

	if(todelete->head != NULL){
		do{
			removeSong(todelete,todelete->songnumber);
		}while(todelete->songnumber>0);
	}

	todelete->prev->next = todelete->next;
	todelete->next->prev = todelete->prev;
	delete todelete;
	playlist_count--;
}

void list::terminate(){
	write2file();

	delete[] listname;
	delete[] datasource;

	while(playlist_count > 1){
		deleteList(head->next,1);
	}

	delete data_;
	deleteList(head,1);

	if (fileP != NULL) fclose(fileP);
}

void list::write2file(){
	if(!(fileP = fopen(datasource,"w+"))){
		cerr << "File could not open!!!" << endl;
		return;
	}
	playlist* present = head;
	song_node* current = present->head;

	do{
		fprintf(fileP,"%s\t%s\t%d\t%s\n",current->data->name,current->data->singer,current->data->year,current->data->style);
		current = current->next;
	}while(current != present->head->prev);//this is because of the last EOL's existance
		fprintf(fileP,"%s\t%s\t%d\t%s",current->data->name,current->data->singer,current->data->year,current->data->style);

	if(playlist_count > 3){
		present = present->next->next->next;//begin with the 4th one
		while(present != head){
			current = present->head;
			fprintf(fileP,"\n*****\n%s\n",present->name);
			do{
				fprintf(fileP,"%s\t%s\t%d\t%s\n",current->data->name,current->data->singer,current->data->year,current->data->style);
				current = current->next;
			}while(current != present->head->prev);//this is also because of the last EOL
				fprintf(fileP,"%s\t%s\t%d\t%s",current->data->name,current->data->singer,current->data->year,current->data->style);
			present = present->next;
		}
	}
	fclose(fileP);
	cout << "Records have succesfully been saved in the file named " << datasource << endl;
}

