
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>
#include <list>

using namespace std;


class viewSeats{
	private:
    struct node {
        char row_name;
        int seat_no;
        string availability;
        node *next, *prev;
    }*head = NULL, *tail = NULL;

    public:


	    void insert(char row_name, int seat_no, string availability) {
	        node *curr = new(node);
	        curr->row_name = row_name;
	        curr->seat_no = seat_no;
	        curr->availability = availability;

	        int ascii_of_row = (int)row_name;

	        if (head == NULL) {
	            head = tail = curr;
	            curr->next = curr->prev = curr;
	        }

           else {
                curr->next = head;
                head->prev = curr;
                head = curr;
                curr->prev = tail;

            }
        }


	    void view() {
	        int count = 0;
	        node *curr = head;
	        if(tail == NULL){
	            cout << "No seats booked yet." << endl;
	        }

	        else{
	            while (curr != tail) {
	                cout << "Seat Row " << curr->row_name << " Number " <<  curr->seat_no+1 << " -- Availability Status: " <<  curr->availability << endl;
	                curr = curr->next;
	                count++;
	            }
	            cout << "Seat Row " << curr->row_name << " Number " <<  curr->seat_no+1 << " -- Availability Status: " <<  curr->availability << endl;
	        }
	    }

	    void clear_list(){
	        if (head != NULL)
	        {
	            node* curr = head->next;
	            while (curr != NULL && curr != head)
	            {
	                cout << "Deleting " << "row: " << curr->row_name << "  " << "Seat no: " <<  curr->seat_no << endl;
	                node* temp = curr;
	                curr = curr->next;
	                delete temp;
	            };
	            cout << "Deleting " << "row: " << head->row_name << "  " << "Seat no: " <<  head->seat_no << endl;
	            delete head;
	            head = NULL;
	        }
	    }
		char alphabet[22] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V'};
		const char* board2[22][20];
//		const char separator = ' ';
		int count = 0;

		viewSeats(){
			for(int x = 0; x < 22; x++){
				for(int z = 0; z < 20; z++){
					board2[x][z] = "[ ]";
				}
			}
		}

		void seats(){
			cout << "    ";
			for(int c = 0; c < 20; c++){
				if(c < 10){
					cout << " " << c + 1 << " ";
				}
				else{
					cout << c + 1 << " ";
				}

				if(c != 0){
		    		if(c != 10){
		    			if(c == 13){
		    				cout << "       ";
						}
		    			if(c != 15 && c % 5 == 0){
			        		cout << "       ";
						}
					}
				}
			}
			cout << endl;

			for(int a = 0; a < 22; a++){
				cout << " " << alphabet[a] << "  ";
		        for(int b = 0; b < 20; b++){
		        	cout << board2[a][b];
		        	if(b != 0){
		        		if(b != 10){
		        			if(b == 13){
		        				cout << "       ";
							}
		        			if(b != 15 && b % 5 == 0){
				        		cout << "       ";
							}
						}
					}

		        }
		        cout << endl;
		    }
		    cout << "\n\n";
		    cout << right << setw(44) << setfill(' ') << "SCREEN" << endl;
		}
		void book(){
			char a;
			int b;
			cout << "\nWhich seat would you like to book?\nPlease enter seat row (e.g. A): ";
			cin >> a;
			cout << "Please enter seat number [1 - 20]: ";
			cin >> b;
			if(b < 1 || b > 20){
				cout << "Please enter a correct seat number." << endl;
			}
			for(int i = 0; i < 22; i++){
				if(alphabet[i] == a){
					b = b-1;
					if(board2[i][b] != "[x]"){
						count = 0;
						board2[i][b] = "[x]";
						insert(a, b, "Occupied");
						cout << "You have successfully booked Seat Row " << a << " Number " << b+1 << endl;
						break;

					}
					else if(board2[i][b] = "[x]"){
						cout << "Sorry, as shown on the screen the seat is already booked!\n";
						count = 1;
						break;
					}
				}
				else if(i == 21 && alphabet[i] != a){
					cout << "Seat row doesn't exist." << endl;
				}

			}
		}
};

class Info{
    string key;
    string value;
    public:
        Info(string name, string password){
            this->key = name;
            this->value = password;
        }

    string getKey(){
        return key;
    }

    string getValue(){
        return value;
    }
};

class Hash{
	int no_of_buckets;
	list<Info> *table;

	public:
		Hash(){
            table = new list<Info>[26];
        }

        int validateUserName(int index, string name){
            for(auto x: table[index]){
               if(x.getKey() == ""){
                    return 0;
                }

            }

            for(auto x: table[index]){
               if(x.getKey() == name){
                    return 1;
                }
            }
            return 2;
		}

		int validatePass(int index, string name, string pass){
            for(auto x: table[index]){
               if(x.getKey() == ""){
                    return 0;
                }

            }

            for(auto x: table[index]){
               if(x.getKey() == name){
               		if(x.getValue() == pass){
                    	return 1;
                    }
                }
            }
            return 2;
		}

		void insertInfo(Info info, int index){
            table[index].push_back(info);
        }

		void deleteInfo(string account){
		    int position;
            int counter = 0;
		    char first_Letter = account[0];
		    int ascii_firstLetter = (int)first_Letter;
		    int index = hashFunction(ascii_firstLetter);

		    list <Info> :: iterator i;
            for (i = table[index].begin();
            i != table[index].end(); i++) {
            if (i->getKey() == account)
                break;
            }

  // if key is found in hash table, remove it
            if (i != table[index].end())
                table[index].erase(i);
		}

		void displayInfos(){
		    for(int i = 0; i<26; i++){
                cout << "Index " << i << " contains:" << endl;
                for(auto x: table[i]){
                    cout << "Name: " << x.getKey() << endl << "Password: " << x.getValue() << endl;
                }
                cout << endl;
            }
		}

		int hashFunction(int ascii_of_first_letter){
            return ascii_of_first_letter-65;
		}
};

int main()
{
	const char separator = ' ';

	vector<viewSeats> seatsAvengers; // vector that contains seats for a movie at a certain time. 1 movie = 1 vector
	vector<viewSeats> seatsAladdin;
	vector<viewSeats> seatsJW3;
	vector<viewSeats> seatsG2;

	vector<string> currentMovies;
	vector<string> comingSoon;

	for(int i = 0; i < 3; i++){
		seatsAvengers.push_back(viewSeats()); // creates multiple objects based on how many time slots are available
		seatsAladdin.push_back(viewSeats());
		seatsJW3.push_back(viewSeats());
		seatsG2.push_back(viewSeats());
	}

	map<string, vector<viewSeats> > moviesInfo;
	// initializing movies available
	moviesInfo.insert({"AVENGERS: END GAME", seatsAvengers});
	moviesInfo.insert({"ALADDIN", seatsAladdin});
	moviesInfo.insert({"JOHN WICK: CHAPTER 3 - PARABELLUM", seatsAladdin});
	moviesInfo.insert({"GODZILLA II: KING OF THE MONSTERS", seatsG2});
	comingSoon.push_back("ANNA");
	comingSoon.push_back("CHILDS PLAY");
	comingSoon.push_back("MEN IN BLACK: INTERNATIONAL");
	comingSoon.push_back("TOY STORY 4");
	Hash hash1;
    string input_name, input_password;
    int input_choice, index, check, ascii_firstLetter, checkPass, index1, ascii_firstLetter1;

    while(true){
    	cout << right << setw(30) << setfill(separator) << "TIXXX ONLINE BOOKING" << endl;
        cout << "1. Login" << endl << "2. Register" << endl << "3. View" << endl << "4. Exit" << endl << endl;
        cout << "Please input choice: " << endl;
        cin >> input_choice;

        if(input_choice == 1){
        	string a;
        	string n;
            cout << "Enter username: ";
            cin >> a;
            a[0] = toupper(a[0]);

            char first_Letter = a[0];
            ascii_firstLetter = (int)first_Letter;
            index = hash1.hashFunction(ascii_firstLetter);


            check = hash1.validateUserName(index, a);
            if(check == 1){
        		cout << "Enter password: ";
        		cin >> n;
        		checkPass = hash1.validatePass(index, a, n);
        		if(checkPass == 1){
        			cout << "Welcome " << a << endl;
        			break;
				}
				else if(checkPass == 0 || checkPass == 2){
					cout << "Incorrect user name or password.\n" << endl;
				}
			}
			else if (check == 0 || check == 2) {
                cout << "Incorrect user name or password.\n" << endl;
		    }
        }

        else if(input_choice == 2){
            cout << "Please input user name (No space in user name): " << endl;
            cin >> input_name;

            input_name[0] = toupper(input_name[0]);

            char first_Letter = input_name[0];
            ascii_firstLetter = (int)first_Letter;
            index = hash1.hashFunction(ascii_firstLetter);

            check = hash1.validateUserName(index, input_name);

            if(check == 1) {
                cout << "This user name is already taken. Please choose another user name.\n" << endl;
		    }

		    else if (check == 0 || check == 2) {
                cout << "Please input password [3..20]: " << endl;
				cin.ignore();
				getline(cin, input_password);
				if(input_password.length() < 3 || input_password.length() > 20){
					cout << "Password must be between 3 until 30 characters. \n" << endl;
				}
				else{
					Info info(input_name, input_password);
	                hash1.insertInfo(info, index);
	                cout << "Account registered!\n" << endl;
				}
		    }
        }

        else if(input_choice == 3){
            hash1.displayInfos();
        }

        else if(input_choice == 4){
            break;
        }
    }

	while(true){
		cout << right << setw(30) << setfill(separator) << "TIXXX ONLINE BOOKING" << endl;
		int x;
		cout << "\n1. View Movies Available\n2. Upcoming Movies (Coming Soon)\n3. Exit" << endl;
		cin >> x;
		if(x == 3){
			break;
		}
		switch(x){
			case 1:
				{
				int y;
				int count = 1;
				cout << right << setw(30) << setfill(separator) << "MOVIES AVAILABLE" << endl;
				for(map<string, vector<viewSeats> >::const_iterator itr = moviesInfo.begin(); itr != moviesInfo.end(); ++itr){
			        cout << count << ". " << itr->first << endl;
			        currentMovies.push_back(itr->first);
			        count++;
			    }
			    cout << "\n\n5. GO BACK" << endl;
				cin >> y;
				if(y == 1){
					cout << "Time Available: \n1. 11:00\n2. 13:40\n3. 19:05\n\n4. GO BACK" << endl;

					int a;
					cin >> a;
					if(a == 1){
						int b;
						cout << "How many seats would you like to book: " << endl;
						cin >> b;
						cout << "\nMOVIE: " << currentMovies[0] << endl;
						seatsAladdin[0].seats();
						seatsAladdin[0].view();
						for(int i = 0; i < b; i++){
							seatsAladdin[0].book();
							if(seatsAladdin[0].count == 1){
								b++;
							}
							
						}
						break;
					}
					else if(a == 2){
						int b;
						cout << "How many seats would you like to book: " << endl;
						cin >> b;
						cout << "\nMOVIE: " << currentMovies[0] << endl;
						seatsAladdin[1].seats();
						seatsAladdin[1].view();
						for(int i = 0; i < b; i++){
							seatsAladdin[1].book(); 
							if(seatsAladdin[1].count == 1){
								b++;
							}
						}
						break;
					}
					else if(a == 3){
						int b;
						cout << "How many seats would you like to book: " << endl;
						cin >> b;
						cout << "\nMOVIE: " << currentMovies[0] << endl;
						seatsAladdin[2].seats();
						seatsAladdin[2].view();
						for(int i = 0; i < b; i++){
							seatsAladdin[2].book(); 
							if(seatsAladdin[2].count == 1){
								b++;
							}
						}
						break;
					}
					else{
						break;
					}
				}
				else if(y == 2){
					cout << "Time Available: \n1. 16:20\n2. 21:45\n\n3. GO BACK" << endl;

					int a;
					cin >> a;
					if(a == 1){
						int b;
						cout << "How many seats would you like to book: " << endl;
						cin >> b;
						cout << "\nMOVIE: " << currentMovies[1] << endl;
						seatsAvengers[0].seats();
						seatsAvengers[0].view();
						for(int i = 0; i < b; i++){
							seatsAvengers[0].book(); 
							if(seatsAvengers[0].count == 1){
								b++;
							}
						}
						break;
					}
					else if(a == 2){
						int b;
						cout << "How many seats would you like to book: " << endl;
						cin >> b;
						cout << "\nMOVIE: " << currentMovies[1] << endl;
						seatsAvengers[1].seats();
						seatsAvengers[1].view();
						for(int i = 0; i < b; i++){
							seatsAvengers[1].book(); 
							if(seatsAvengers[1].count == 1){
								b++;
							}
						}
						break;
					}
					else{
						break;
					}
				}
				else if(y == 3){
					cout << "Time Available: \n1. 11:00\n2. 16:20\n3. 21:40\n\n4. GO BACK" << endl;

					int a;
					cin >> a;
					if(a == 1){
						int b;
						cout << "How many seats would you like to book: " << endl;
						cin >> b;
						cout << "\nMOVIE: " << currentMovies[2] << endl;
						seatsG2[0].seats();
						seatsG2[0].view();
						for(int i = 0; i < b; i++){
							seatsG2[0].book(); 
							if(seatsG2[0].count == 1){
								b++;
							}
						}
						break;
					}
					else if(a == 2){
						int b;
						cout << "How many seats would you like to book: " << endl;
						cin >> b;
						cout << "\nMOVIE: " << currentMovies[2] << endl;
						seatsG2[1].seats();
						seatsG2[1].view();
						for(int i = 0; i < b; i++){
							seatsG2[1].book(); 
							if(seatsG2[1].count == 1){
								b++;
							}
						}
						break;
					}
					else if(a == 3){
						int b;
						cout << "How many seats would you like to book: " << endl;
						cin >> b;
						cout << "\nMOVIE: " << currentMovies[2] << endl;
						seatsG2[2].seats();
						seatsG2[2].view();
						for(int i = 0; i < b; i++){
							seatsG2[2].book(); 
							if(seatsG2[2].count == 1){
								b++;
							}
						}
						break;
					}
					else{
						break;
					}

				}
				else if(y == 4){
					cout << "Time Available: \n1. 13:40\n2. 19:00\n\n3. GO BACK" << endl;

					int a;
					cin >> a;
					if(a == 1){
						int b;
						cout << "How many seats would you like to book: " << endl;
						cin >> b;
						cout << "\nMOVIE: "<< currentMovies[3] << endl;
						seatsJW3[0].seats();
						seatsJW3[0].view();
						for(int i = 0; i < b; i++){
							seatsJW3[0].book(); 
							if(seatsJW3[0].count == 1){
								b++;
							}
						}
						break;
					}
					else if(a == 2){
						int b;
						cout << "How many seats would you like to book: " << endl;
						cin >> b;
						cout << "\nMOVIE: " << currentMovies[3] << endl;
						seatsJW3[1].seats();
						seatsJW3[1].view();
						for(int i = 0; i < b; i++){
							seatsJW3[1].book(); 
							if(seatsJW3[1].count == 1){
								b++;
							}
						}
						break;
					}
					else{
						break;
					}
				}
				else{
					break;
				}
				}

			case 2:
				int count = 1;
				cout << right << setw(30) << setfill(separator) << "UPCOMING MOVIES" << endl;
				for(int i = 0; i < 4; i++){
					cout << count << ". " << comingSoon[i] << endl;
					count++;
				}
				break;
		}
	}

	seatsAladdin[0].clear_list();
	seatsAladdin[1].clear_list();
	seatsAladdin[2].clear_list();

	seatsAvengers[0].clear_list();
	seatsAvengers[1].clear_list();

	seatsG2[0].clear_list();
	seatsG2[1].clear_list();
	seatsG2[2].clear_list();

	seatsJW3[0].clear_list();
	seatsJW3[1].clear_list();

	return 0;
}
