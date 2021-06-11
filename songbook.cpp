/* @Author 
 * Student Name: Mustafa SAÐLAM
 * Student ID : 150140129 
 * Date: 21.11.2016*/ 
 
#include "songbook.h"
 
using namespace std;
 
typedef list datastruct;
datastruct book;
typedef song_node song_book;

void begin();  
void printmenu();
bool pick_op(char);
void listCreate();
void songAdd();
void player();
void songRemove();
void listDelete();
void listPrint();
void recordSave();
void appCease();

int main(){
	char operation;
	bool picker = true;  
	book.begin();
	while(picker){
		system("cls");
		printmenu();
		cin >> operation;
		picker = pick_op(operation);
	}
	return 0; 
}
  
void printmenu(){
	cout << "SONGBOOK APPLICATION (USING DOUBLY, CIRCULAR, MULTI LINKED LIST)" << endl;
	cout << "Choose an operation..." << endl;
	cout << "P :	Play" << endl;
	cout <<	"L :	Show all playlists" << endl;
	cout << "C :	Create a new playlist" << endl;
	cout << "A :	Add song to a playlist" << endl;
	cout << "R : 	Remove song from a playlist" << endl;
	cout << "D : 	Delete a playlist" << endl;
	cout << "W : 	Write to file (SAVE)" << endl;
	cout << "E : 	Exit program" << endl;
	cout << ">> " ;
}
 
bool pick_op(char operation){
	bool picker = true;         

	switch(operation){
		case 'P': case 'p':
			player();  
			break;
		case 'L': case 'l':
			listPrint(); 
			break;
		case 'C': case 'c':
			listCreate();
			break;
		case 'A': case 'a':
			songAdd();
			break;
		case 'R': case 'r':
			songRemove();
			break;
		case 'D': case 'd':
			listDelete();
			break;
		case 'W': case 'w': 
			recordSave();
			break;
		case 'E': case 'e': 
			appCease();  
			picker = false;
			break;
		default:
			picker = true;
			break;
	}
	return picker; 
}
 
void player(){
	playlist* present = book.head;
	int i = 1, j;
	char op;
	system("cls");
	cout << "PLAY >" << endl;
	cout << "Choose an option" << endl;
	cout << "L: Play a playlist" << endl;
	cout << "S: Play a playlist starting from a specific song" << endl;
	cout << "P: Play a single song." << endl;
	cout << "E: Exit\n>> ";
	cin >> op;
	song_node* current;
	switch(op){
		case 'e': case 'E':
			system("cls");
			return;
			break;
		case 'l': case 'L':
			cout << "PLAYLISTS :" << endl;
			do{
				cout << i << ": " << present->name << endl;
				present = present->next;
				i++;
			}while(present != book.head);
			i=1;
			do{
				song_node* toadd = new song_node;
				cout << i << ": " << present->name << endl;
				cout << "PLAY(S) - ADD SONG(A) - REMOVE SONG(R) - DELETE(D)\nNEXT(N) - PREVIOUS(P) - EXIT(E)" << endl;
				cin >> op;
			
				switch(op){
					case 's': case 'S':
						system("cls");
						current = present->head;
						cout << "PLAY >" << endl;
						do{
							cout << "playing . . ." << endl;
							cout << current->data->name << " - " << current->data->singer << " - " << 
									current->data->year << " - " << current->data->style << endl;
							cout << "NEXT(N) - PREVIOUS(P) - EXIT(E)\n>> ";
							cin >> op;
							if((op=='n') || (op=='N')) current = current->next;
							else if((op=='p') || (op=='P')) current = current->prev;
						}while((op!='e') && (op!='E'));
						break;
					case 'd': case 'D':
						listDelete();
						break;
					case 'a': case 'A':
						current = present->head;
						cout << "Choose a song to add (0 to exit)" << endl;
						book.printList(book.head->next);
						cout << ">> ";
						cin >> j;
						if(j==0){system("cls"); break;}
						for(int k = 1; k<j; k++) current = current->next;
						toadd->data = current->data;
						book.addSong(present, toadd);
						cout << "Song succesfully added" << endl;
						break;
					case 'r': case 'R':
						current = present->head;
						cout << "Choose a song to remove(0 to exit)\n>> ";
						book.printList(present);
						cin >> j;
						if(j==0){system("cls"); break;}
						book.removeSong(present,j);
						cout << "Song succesfully removed" << endl;
						break;
					case 'n': case 'N':
						present = present->next;
						i = (i)%(book.playlist_count)+1;
						break;
					case 'p': case 'P':
						present = present->prev;
						i--;
						if(i<=0) i=+book.playlist_count;
						break;
					case 'e': case 'E':
						system("cls");
						return;
						break;
					default:
						return;
						break;	
				}
			}while(1);
			break;
		
		case 's': case 'S':
			cout << "PLAYLISTS :" << endl;
			do{
				cout << i << ": " << present->name << endl;
				present = present->next;
				i++;
			}while(present != book.head);
			i=1;
			do{
				song_node* toadd = new song_node;
				cout << i << ": " << present->name << endl;
				cout << "PLAY(S) - ADD SONG(A) - REMOVE SONG(R) - DELETE(D)\nNEXT(N) - PREVIOUS(P) - EXIT(E)" << endl;
				cin >> op;
			
				switch(op){
					case 's': case 'S':
						system("cls");
						current = present->head;
						cout << "PLAY >" << endl;
						cout << "Choose a song to play(0 to exit)" << endl;
						book.printList(present);
						cin >> j;
						if(j==0) break;
						for(int q = 1; q<j; q++) current = current->next;
						do{
							cout << "playing . . ." << endl;
							cout << current->data->name << " - " << current->data->singer << " - " << 
									current->data->year << " - " << current->data->style << endl;
							cout << "NEXT(N) - PREVIOUS(P) - EXIT(E)\n>> ";
							cin >> op;
							if((op=='n') || (op=='N')) current = current->next;
							else if((op=='p') || (op=='P')) current = current->prev;
						}while((op!='e') && (op!='E'));
						break;
					case 'd': case 'D':
						listDelete();
						break;
					case 'a': case 'A':
						current = present->head;
						cout << "Choose a song to add (0 to exit)" << endl;
						book.printList(book.head->next);
						cout << ">> ";
						cin >> j;
						if(j==0){system("cls"); break;}
						for(int k = 1; k<j; k++) current = current->next;
						toadd->data = current->data;
						book.addSong(present, toadd);
						cout << "Song succesfully added" << endl;
						break;
					case 'r': case 'R':
						current = present->head;
						cout << "Choose a song to remove(0 to exit)\n>> ";
						book.printList(present);
						cin >> j;
						if(j==0){system("cls"); break;}
						book.removeSong(present,j);
						cout << "Song succesfully removed" << endl;
						break;
					case 'n': case 'N':
						present = present->next;
						i = (i)%(book.playlist_count)+1;
						break;
					case 'p': case 'P':
						present = present->prev;
						i--;
						if(i<=0) i=+book.playlist_count;
						break;
					case 'e': case 'E':
						system("cls");
						return;
						break;
					default:
						return;
						break;	
				}
			}while(1);
			break;
		
		case 'p': case 'P':
			present = book.head->next;
			current = present->head;
			system("cls");
			
			cout << "PLAY >" << endl;
			cout << "Choose a song to play(0 to exit)" << endl;
			book.printList(present);
			cin >> j;
			if(j==0) break;
			system("cls");
			for(int q = 1; q<j; q++) current = current->next;
			do{
				cout << "playing . . ." << endl;
				cout << current->data->name << " - " << current->data->singer << " - " << 
						current->data->year << " - " << current->data->style << endl;
				cout << "NEXT(N) - PREVIOUS(P) - EXIT(E)\n>> ";
				cin >> op;
				if((op=='n') || (op=='N')) current = current->next;
				else if((op=='p') || (op=='P')) current = current->prev;
			}while((op!='e') && (op!='E'));
			break;
		default:
			return;
			break;
	}
}

void songAdd(){
	playlist* present = book.head;
	int i = 1, j;
	
	cout << "Please choose a list to add song(s) (0 to exit)" << endl;
	do{
		cout << setw(2) << i << ". " << present->name << endl;
		present = present->next;
		i++;
	}while(present != book.head);
	cout << ">> ";
	cin >> j;
	
	if(j==0) return;
	else if(j > book.playlist_count){
		cout << "Error, there is no such list!..." << endl;
		return;
	}
	else if(j<=3){
		cout << "Permission denied!!!..." << endl;
		return;
	}
	else{
		do{
			for(int i = 1; i<j; i++) present = present->next;//choosing a list to add
			song_node* current = book.head->next->head;//assigning head of sorted list
			cout << "Please choose a song from sorted list to add list named " << present->name << endl;
			book.printList(book.head->next);//printing the sorted list 
			cout << "(0 to exit) >> ";
			cin >> j;
			if(j == 0) return;
			else if( j > book.head->songnumber){
				cout << "Error, there is no such song!..." << endl;
				return;
			}
			else{
				for(int i = 1; i<j; i++) current = current->next;//choosing the song
				song_node* toadd = new song_node;
				toadd->data = current->data;
				toadd->parent = present;
				book.addSong(present, toadd);
			}
			cout << "Song succesfully added..." << endl;
			cout << "Press '0' to exit without any operation" << endl;
			cout << "Press '1' to add another song to this list (named " << present->name << ")" << endl;
			cout << "Press '2' to add a song to another list \n>> ";
			cin >> j;
		
			if(j==0) return; 
			else if(j==2) songAdd();
		}while(j == 1);
	}
}

void songRemove(){
	playlist* present = book.head;
	int i = 1, j;
	cout << "Please choose a list to remove song(s) (0 to exit)" << endl;
	do{
		cout << setw(2) << i << ". " << present->name << endl;
		present = present->next;
		i++;
	}while(present != book.head);
	cout << ">> ";
	cin >> j;
	
	if(j==0) return;
	else if(j > book.playlist_count){
		cout << "Error, there is no such list!..." << endl;
		return;
	}
	else if(j<=3){
		cout << "Permission denied!!!..." << endl;
		return;
	}
	else{
		do{
			for(int i = 1; i<j; i++) present = present->next;//choosing a list to remove song(s)
			song_node* current = present->head;//assigning head of 'present' list
			cout << "Please choose a song from list named " << present->name << " to remove" << endl;
			book.printList(present);//printing the list 
			cout << "(0 to exit) >> ";
			cin >> j;
			if(j == 0) return;
			else if( j > present->songnumber){
				cout << "Error, there is no such song!..." << endl;
				return;
			}
			else{
				book.removeSong(present, j);
			}
			cout << "Song succesfully deleted..." << endl;
			cout << "Press '0' to exit without any operation" << endl;
			cout << "Press '1' to remove another song from this list (named " << present->name << ")" << endl;
			cout << "Press '2' to remove a song from another list \n>> ";
			cin >> j;
		
			if(j==0) return; 
			else if(j==2) songRemove();
		}while(j == 1);
	}
}

void listCreate(){
	int choose = 0;
	cout << "Create a playlist (0 to exit without any operation)" << endl;
	cout << "1. With a specific style" << endl;
	cout << "2. With a common singer" << endl;
	cout << "3. Combination of existing playlists" << endl;
	cout << "4. Combination of existing songs" << endl;
	cout << ">> ";
	cin >> choose;
	
	if(choose == 1){
		char *styles[book.head->songnumber];
		song_node *current = book.head->head;
		playlist *newlist; 
		int i = 0;
		do{// taking name of styles
			int j=0;
			for(; j<i; j++){
				if(strcmp(styles[j], current->data->style) == 0){
					break;
				}
			}
			if(j==i){
				styles[i] = new char[strlen(current->data->style)];
				strcpy(styles[i], current->data->style);
				i++;
			}
			current = current->next;	
		}while(current != book.head->head);
		
		cout << "Please choose one of the styles to create a new playlist (0 to exit without any operation)" << endl;
		for(int j = 0; j<i; j++)
			cout << j+1 << ". " << styles[j] << endl;
		cout << ">> ";
		cin >> choose;
		if(choose==0) return;
		cout << "Please enter the name of the new playlist\n>> ";
		book.listname = new char[20];
		cin >> book.listname;
		newlist = book.createList(book.listname);
		
		do{
			if(strcmp(styles[choose-1], current->data->style) == 0){
				song_node *toadd = new song_node;
				toadd->data = current->data;
				toadd->parent = newlist;
				book.addSong(newlist, toadd);
			}
			current = current->next;
		}while(current != book.head->head);
	}
	
	else if(choose == 2){	
		char *singers[book.head->songnumber];
		playlist* newlist;
		song_node *current = book.head->next->head;
		int i = 0; 
		do{//taking name of singers
			int j=0;
			for(; j<i; j++){
				if(strcmp(singers[j], current->data->singer) == 0){
					break;
				}
			}
			if(j==i){
				singers[i] = new char[strlen(current->data->singer)];
				strcpy(singers[i], current->data->singer);
				i++;
			}
			current = current->next;	
		}while(current != book.head->next->head);
		
		cout << "Please choose one of the singers to create a new playlist(0 to exit without any operation)" << endl;
		for(int j = 0; j<i; j++)
			cout << setw(2) << j+1 << ". " << singers[j] << endl;
		cout << ">> ";
		cin >> choose;
		if(choose==0) return;
		cout << "Please enter the name of the new playlist\n>> ";
		book.listname = new char[20];
		cin >> book.listname;
		newlist = book.createList(book.listname);;
		
		do{
			if(strcmp(singers[choose-1], current->data->singer) == 0){
				song_node *toadd = new song_node;
				toadd->data = current->data;
				toadd->parent = newlist;
				book.addSong(newlist, toadd);
			}
			current = current->next;
		}while(current != book.head->next->head);
	}
	
	else if(choose == 3){
		playlist* present = book.head;
		int i = 1, j;
		do{
			cout << setw(2) << i << ". " << present->name << endl;
			present = present->next;
			i++;
		}while(present != book.head);
		
		cout << "\nPlease choose a list first... (0 to exit without any operation)\n>> ";
		cin >> i;
		if(i==0) return;
		
		cout << "Please choose another list to concatenante with the first one";
		cout << "(0 to exit without any operation)\n>> ";
		cin >> j;
		if(j==0) return;
		
		cout << "Please enter the name of the new list\n>> ";
		book.listname = new char[20];
		cin >> book.listname;
		
		playlist* newlist = book.createList(book.listname);
		
		present = book.head;
		for(;i>0;i--)	present = present->next;
		song_node* current = present->head;
		do{
			song_node* toadd = new song_node;
			toadd->data = current->data;
			toadd->parent = newlist;
			book.addSong(newlist, toadd);	
			current = current->next;	
		}while(current!=present->head);
		
		present = book.head;
		for(;j>0;j--)	present = present->next;
		current = present->head;
		do{
			song_node* toadd = new song_node;
			toadd->data = current->data;
			toadd->parent = newlist;
			book.addSong(newlist, toadd);	
			current = current->next;	
		}while(current!=present->head);
	}
 	
	else if(choose == 4){
		song_node* current = book.head->next->head;
		book.listname = new char[20];
		strcpy(book.listname,"Newlist");
		
		int i, j;
		char yesno;
	
		book.printList(book.head->next);
	
		cout << "\nPlease enter order of the song you want to add the new playlist" << endl;
		cout << "(0 to exit without any operation) >> ";
		cin >> j;
		if(j==0) return;
	
		playlist* newlist = book.createList(book.listname);
		song_node* todiffer = newlist->head;
	
		do{
			i=1;
			jumpingpoint:
			current = book.head->next->head;
			for(;i<j;i++){ 
				current = current->next;
			}
			
			todiffer = newlist->head;
			do{
				if(newlist->head != NULL){
					if(strcmp(todiffer->data->name, current->data->name) == 0){
						cout << "This song is already in the list.\nDo you really want to add it again? (Y/N)>> ";
						cin >> yesno;
						if((yesno == 'y') || (yesno == 'Y')) break;
						if((yesno == 'n') || (yesno == 'N')) {
							cout << "Adding canceled..." << endl;
							cout << "Enter the next one (0 to end adding) >> ";
							cin >> j;
							if(j==0) break;
							goto jumpingpoint;
						}
					}
					todiffer = todiffer->next;
				}
			}while(todiffer != newlist->head);
			
			if(j!=0){
				song_node* toadd = new song_node;
				toadd->data = current->data;
				toadd->parent = newlist;
				book.addSong(newlist,toadd);
			}
			
			if(j==0) break;
			cout << "Enter the next song (0 to exit) >> ";
			cin >> j;
		
			if(j==0) break;
			if(j > book.head->songnumber) continue;
		}while(1);
		
		cout << "Name of the new playlist will be 'Newlist'. Do you want to change it? (Y/N)\n>> ";
		cin >> yesno;
		switch(yesno){
			case 'y': case 'Y':
				cout << "Please enter a new name for the new playlist\n>> ";
				book.listname = new char[20];
				cin >> book.listname;
				strcpy(newlist->name, book.listname);
				cout << "Successfully done..." << endl;
				break;
			case 'n': case 'N':
				cout << "It will remain as it is..." << endl;
				return;
				break;
			default:
				return;
				break;
		}
	}
	getchar();
}

void listDelete(){
	cout << "Please choose a list to delete (0 to exit) " << endl;
	
	playlist* present = book.head;
	int i = 1, j;
	do{
		cout << setw(2) << i << ". " << present->name << endl;
		present = present->next;
		i++;
	}while(present != book.head);
	
	present = book.head;
	cin >> j;
	if (j<=3){
		cout << "Permission denied !!!..." << endl;
	}
	else if (j == 0 ){
		return;
	}
	else if (j > book.playlist_count){
		cout << "There is no such list..." << endl;
	}
	else{
		for(i=1; i<j; i++) present = present->next;
		book.deleteList(present, 1);
		cout << "Succesfully deleted" << endl;
	}
	system("pause");
}

void listPrint(){
	playlist* present = book.head;
	playlist* toprint = book.head;
	song_node* current = present->head;
	int i = 1, j;
	char op;
	
	do{
		system("cls");
		song_node* toadd = new song_node;
		cout << "PLAYLISTS >" << endl;
		do{
			cout << i << ". " << toprint->name << endl;
			toprint = toprint->next;
			i++;
		}while(i<=book.playlist_count);
		toprint = book.head;
		cout << endl;
		i=1;
		book.printList(present);
		cout << endl << "SELECT(S) - NEXT(N) - PREV(P) - EXIT(E)" << endl;
		cout <<">> ";	
		cin >> op;
		
		switch(op){
			case 'e': case 'E':
				system("cls");
				return;
				break;
			case 'n': case 'N':
				present = present->next;
				break;
			case 'p': case 'P':
				present = present->prev;
				break;
			case 's': case 'S':
				cout << "PLAY(P) - ADD SONG(A) - REMOVE SONG(R) - DELETE(D) - EXIT(E)" << endl;
				cin >> op;
				switch(op){
					case 'e': case 'E':
						system("cls");
						break;
					case 'p': case 'P':
						system("cls");
						current = present->head;
						cout << "PLAY >" << endl;
						cout << "Choose a song to play(0 to exit)" << endl;
						book.printList(present);
						cin >> j;
						if(j==0) break;
						for(int q = 1; q<j; q++) current = current->next;
						do{
							cout << "playing . . ." << endl;
							cout << current->data->name << " - " << current->data->singer << " - " << 
									current->data->year << " - " << current->data->style << endl;
							cout << "NEXT(N) - PREVIOUS(P) - EXIT(E)\n>> ";
							cin >> op;
							if((op=='n') || (op=='N')) current = current->next;
							else if((op=='p') || (op=='P')) current = current->prev;
							
						}while((op!='e') && (op!='E'));
						
						break;
						
					case 'd': case 'D':
						listDelete();
						break;
					case 'a': case 'A':
						current = present->head;
						cout << "Choose a song to add (0 to exit)" << endl;
						book.printList(book.head->next);
						cout << ">> ";
						cin >> j;
						if(j==0){system("cls"); break;}
						for(int k = 1; k<j; k++) current = current->next;
						toadd->data = current->data;
						book.addSong(present, toadd);
						cout << "Song succesfully added" << endl;
						break;
					case 'r': case 'R':
						current = present->head;
						cout << "Choose a song to remove (0 to exit)\n>> ";
						book.printList(present);
						cin >> j;
						if(j==0)break;
						book.removeSong(present,j);
						cout << "Song succesfully removed" << endl;
						break;
					default:
						return;
						break;	
				}
			default:
				return;
				break;
		}
	}while(1);
	system("cls");
}
     
void recordSave(){
	char yesno;
	int q;
	cout << "Records are going to save in a file named " << book.datasource << endl;
	cout << "Do you want to take another look into records? (Y/N)\n>> ";
	cin >> yesno;
	
	switch(yesno){
		case 'n': case'N':
			book.write2file();
			break;
		case 'y': case 'Y':
			listPrint();
			cout << "Press 0 to exit without saving >> ";
			cin >> q;
			if (q==0) return;
			break;
		default:
			cout << "Saving is denied..." << endl;
			return;
	}
	getchar();
}
			
void appCease(){
	char operation; 
	cout << "The records will be saved and the app will be terminated.\nAre you sure? (Y/N) \n>> " ;
	cin >> operation;
	if (operation == 'Y' || operation == 'y'){
		book.terminate();
	}
}
 
