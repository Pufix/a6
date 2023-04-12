#pragma once
#include "service.h"
#include<iostream>
int mod(int a) {
	if (a < 0)
		return a * -1;
	return a;
}
void removeSpaces(string& str) {
	int n = str.length()-1;
	while (str[n] == ' ')
		str.erase(n--, 1);

}
class userInterface {
public:
	service serv;
	void login() {
		bool loggedIn = false;
		string username;
		cout << "username: ";
		getline(cin, username);
		removeSpaces(username);
		cout << "password: ";
		string password;
		getline(cin, password);
		removeSpaces(username);
		loggedIn = this->serv.Login(username, password);
		if (!loggedIn)
			cout << "Wrong username or password!" << endl;
		else
			cout << "Succesfully logged in as " << this->serv.GetUsername() << endl;
	}
	void regist() {
		string username;
		cout << "Please enter username: ";
		getline(cin, username);
		removeSpaces(username);
		string password;
		cout << "Please enter password: ";
		getline(cin, password);
		removeSpaces(password);
		string password2;
		cout << "Please re-enter password: ";
		getline(cin, password2);
		if (password == password2) {
			int result = this->serv.addUser(username, password);
			if (result != -1)
				cout << "Succesfully registered!" << endl;
			else
				cout << "Username already taken!" << endl;
		}
		else
			cout << "Passwords don't match!" << endl;
	}
	void startUp() {
		do {
			cout << "If you already have an account type 'login' otherwise type 'register'." << endl;
			string command;
			getline(cin, command);
			removeSpaces(command);
			if (command == "login")
				this->login();
			else if (command == "register")
				this->regist();
			else
				cout << "Invalid command!" << endl;
			cout << endl << endl;
		} while (this->serv.currentUser.privilegeLevel == -1);
	}
	int commandRecognition(string command) {
		if (command == "exit"||command == "quit")
			return 0;
		if(strstr(command.c_str(), "add") == command.c_str())
			return 1;
		if(strstr(command.c_str(), "delete") == command.c_str())
			return 2;
		if(strstr(command.c_str(), "update") == command.c_str())
			return 3;
		if(strstr(command.c_str(), "list") == command.c_str())
			return 4;
		if(strstr(command.c_str(), "filter") == command.c_str())
			return 5;
		if (command == "help")
			return 6;
		if (strstr(command.c_str(), "next") == command.c_str())
			return 8;
		if (strstr(command.c_str(), "save") == command.c_str())
			return 9;
		if (strstr(command.c_str(),"movie list")==command.c_str())
			return 10;
		if (strstr(command.c_str(), "watchlist remove ") == command.c_str())
			return 12;
		if (strstr(command.c_str(), "watchlist") == command.c_str())
			return 11;
		return -1;
	}
	void addCommand(string command){
		//cout << "add <user> <username> <password>" << endl;
		command.erase(command.begin(), command.begin() + 3);
		if (command == "") {
			cout << "add <user> <username> <password>" << endl;
			cout << "add <movie> <title> <year> <genre> <likes> <trailerLink>" << endl;	
			return;
		}
		command.erase(command.begin(), command.begin()+1);
		if (strstr(command.c_str(), "user") == command.c_str()) {
			command.erase(command.begin(), command.begin() + 5);
			string username;
			username = command;
			for (int i = 0; i <= username.size(); i++)
				if (i == username.size()) {
					cout << "Error: Invalid command!" << endl;
					return;
				}
				else if (username[i] == ' ') {
					username.erase(username.begin() + i, username.end());
					command.erase(command.begin(), command.begin() + i);
					break;
				}
			string password;
			password = command;
			while (!password.empty() && password[0] == ' ')
				password.erase(password.begin());
			if (username == "" || password == "") {
				cout << "Error: Invalid command!" << endl;
				return;
			}
			int result = this->serv.addUser(username, password);
			if (result == -1)
				cout << "Error: Username already exists!" << endl;
			else
				cout << "Succesfully added user " << username << endl;
		}
		else if (strstr(command.c_str(), "movie") == command.c_str()) {
			command.erase(command.begin(), command.begin() + 6);
			//add <movie> <title> <year> <genre> <likes> <trailerLink>
            string title;
			title = command;
			for (int i = 0;i <= title.size();i++)
				if (i == title.size()) {
					cout << "Error: Invalid command!" << endl;
					return;
				}
				else if (title[i] == ' ') {
					title.erase(title.begin() + i, title.end());
					command.erase(command.begin(), command.begin() + i+1);
					break;
				}
			if (title == "") {
				cout << "Error: Invalid command!" << endl;
				return;
			}
			string year;
			year = command;
			for (int i = 0;i <= year.size();i++)
				if (i == year.size()) {
					cout << "Error: Invalid command!" << endl;
					return;
				}
				else if (year[i] == ' ') {
					year.erase(year.begin() + i, year.end());
					command.erase(command.begin(), command.begin() + i+1);
					break;
				}
				else if (year[i] < '0' || year[i] > '9') {
					cout << "Error: Invalid command!" << endl;
					return;
				}
			if (year == "") {
				cout << "Error: Invalid command!" << endl;
				return;
			}
			
			string genre;
			genre = command;
			for (int i = 0;i <= genre.size();i++)
				if (i == genre.size()) {
					cout << "Error: Invalid command!" << endl;
					return;
				}
				else if (genre[i] == ' ') {
					genre.erase(genre.begin() + i, genre.end());
					command.erase(command.begin(), command.begin() + i+1);
					break;
				}
			if (genre == "") {
				cout << "Error: Invalid command!" << endl;
				return;
			}
			string likes;
			likes = command;
			for (int i = 0;i <= likes.size();i++)
				if (i == likes.size()) {
					cout << "Error: Invalid command!" << endl;
					return;
				}
				else if (likes[i] == ' ') {
					likes.erase(likes.begin() + i, likes.end());
					command.erase(command.begin(), command.begin() + i+1);
					break;
				}
				else if (likes[i] < '0' || likes[i]>'9') {
					cout << "Error: Invalid command!" << endl;
					return;
				}
			if (likes == "") {
				cout << "Error: Invalid command!" << endl;
				return;
			}
			string trailer;
			trailer = command;
			for (int i=0;i<trailer.size();i++)
				if (command[i] == ' ') {
					cout << "Error: Invalid command" << endl;
					return;
				}
			int result = this->serv.addMovie(title, stoi(year), genre, stoi(likes), trailer);
			if (result == -1)
				cout << "Error: Movie already exists!" << endl;
			else
				cout << "Succesfully added movie " << title << endl;
		}
		else
			cout << "Error: Invalid command!" << endl;		
	}
	void deleteCommand(string command){
		command.erase(command.begin(), command.begin() + 6);
		if (command[0] != ' ') {
			cout << "delete <user> <username>" << endl;
			cout << "delete <movie> <title>" << endl;
			return;
		}
		command.erase(command.begin(), command.begin() + 1);
		if (strstr(command.c_str(), "movie") == command.c_str()) {
			command.erase(command.begin(), command.begin() + 5);
			if (command[0] != ' ') {
				cout << "Error: Invalid command!" << endl;
				return;
			}
			command.erase(command.begin(), command.begin() + 1);
			int result = serv.removeMovie(command);
			if (result == 0)
				cout << "Movie deleted!" << endl;
			else if (result == -2)
				cout << "You do not administrator privileges" << endl;
			else
				cout << "The given movie is not in the database"<<endl;
			return;
		}
		else if (strstr(command.c_str(), "user") == command.c_str()) {
			command.erase(command.begin(), command.begin() + 4);
			if (command[0] != ' ') {
				cout << "Error: Invalid command!" << endl;
				return;
			}
			command.erase(command.begin(), command.begin() + 6);
			int result = serv.removeUser(command);
			if (result == 0)
				cout << "User deleted!" << endl;
			else if (result == -2)
				cout << "You do not administrator privileges" << endl;
			else
				cout << "The given user is not in the database"<<endl;
			return;
			return;
		}
		cout << "Error: Invalid command!" << endl;
	}
	void listCommand(string command){
		command.erase(command.begin(), command.begin() + 4);
		if (command[0] != ' ') {
			cout << "list <users/movies>" << endl;
			return;
		}
		command.erase(command.begin(), command.begin() + 1);
		if (command == "movies" || command == "movie") {
			vector<movie>&result = serv.listMovies();
			/*for (int i = 0; i < result.size(); i++)
				cout << result[i] << endl;*/
			for (auto i : result)
				cout << i << endl;
		}
		else if (command == "users" || command == "user") {
			vector<user> &result = serv.listUsers();
			if (result.size() == 1 && result[0] == user()) {
				cout << "You do not have administrator privleges!" << endl;
				return;
			}
			/*for (int i = 0; i < result.size(); i++)
				cout << result[i] << endl;*/
			for (auto i : result)
				cout << i << endl;
		}
	}
	void updateCommand(string command) {
		if (command == "update"){
			cout << "update <movie> <movieTitle> <field> <newData>" << endl; 
			return;
		}
		command.erase(command.begin(), command.begin() + 7);
		if (strstr(command.c_str(), "movie ") != command.c_str()) {
			cout << "Error: Invalid command!" << endl;
			return;
		}
		command.erase(command.begin(), command.begin() + 6);
		string title = command;
		bool ok = false;
		for (int i = 0; i < title.size(); i++) {
			if (title[i] == ' '){
				ok = true;
				title.erase(title.begin() + i, title.end());
				command.erase(command.begin(), command.begin() + i+1);
				break;
			}
		}
		if (!ok) {
			cout << "Error: Invalid command!" << endl;
			return;
		}
		if (strstr(command.c_str(), "genre ") == command.c_str()) {
			command.erase(command.begin(), command.begin() + 6);
			int result =serv.updateMovieGenre(title, command);
			if (result == 0)
				cout << "Succesfully updated movie " << title << endl;
			else if (result == -1)
				cout << "Movie not found!" << endl;
			else if (result == -2)
				cout << "You do not have administrator privileges!" << endl;
			return;
		}
		if (strstr(command.c_str(), "year ") == command.c_str()) {
			command.erase(command.begin(), command.begin() + 5);
			for (int i = 0; i < command.size(); i++) {
				if (command[i] < '0' || command[i] > '9') {
					cout << "Error: Invalid command!" << endl;
					return;
				}
			}
			int result = serv.updateMovieYear(title, stoi(command));
			if (result == 0)
				cout << "Succesfully updated movie " << title << endl;
			else if (result == -1)
				cout << "Movie not found!" << endl;
			else if (result == -2)
				cout << "You do not have administrator privileges!" << endl;
			return;
		}
		if (strstr(command.c_str(), "likes ") == command.c_str()) {
			command.erase(command.begin(), command.begin() + 6);
			for (int i = 0; i < command.size(); i++) {
				if (command[i] < '0' || command[i] > '9') {
					cout << "Error: Invalid command!" << endl;
					return;
				}
			}
			int result = serv.updateMovieLikes(title, stoi(command));
			if (result == 0)
				cout << "Succesfully updated movie " << title << endl;
			else if (result == -1)
				cout << "Movie not found!" << endl;
			else if (result == -2)
				cout << "You do not have administrator privileges!" << endl;
			return;
		}
		if (strstr(command.c_str(), "trailer ") == command.c_str()) {
			command.erase(command.begin(), command.begin() + 8);
			int result = serv.updateMovieTrailer(title, command);
			if (result == 0)
				cout << "Succesfully updated movie " << title << endl;
			else if (result == -1)
				cout << "Movie not found!" << endl;
			else if (result == -2)
				cout << "You do not have administrator privileges!" << endl;
			return;
		}
		if (strstr(command.c_str(), "title ") == command.c_str()) {
			command.erase(command.begin(), command.begin() + 6);
			int result = serv.updateMovieTitle(title, command);
			if (result == 0)
				cout << "Succesfully updated movie " << title << endl;
			else if (result == -1)
				cout << "Movie not found!" << endl;
			else if (result == -2)
				cout << "You do not have administrator privileges!" << endl;
			return;
		}
		cout << "Error: Invalid command!" << endl;
		return;
	}
	void movieList(string command) {
		if (serv.currentUser.privilegeLevel == 0) {
			cout << "You are an admin!" << endl;
			return;
		}
		if (command == "movie") {
			cout << "movie list <genre>" << endl;
			return;
		}
		command.erase(command.begin(), command.begin() + 10);
		if (command == "") {
			vector<movie> &result = serv.listMovies();
			int index = 0;
			bool running = true;
			if (result.size() == 0) {
				cout << "No movies found!" << endl;
				return;
			}
			do {
				cout << result[mod(index)%result.size()] << endl;
				system(string("start ").append(result[mod(index) % result.size()].trailer).c_str());
				string command;
				cout << "next/previous/exit/add" << endl;
				getline(cin,command);
				if (command == "next")
					index++;
				else if (command == "previous")
					index--;
				else if (command == "exit")
					running = false;
				else if (command == "add") {
					if (serv.checkMovieWatchlist(result[mod(index) % result.size()]))
						cout << "Movie already in watchlist!" << endl;
					else{
						serv.addMovieToWatchlist(result[mod(index) % result.size()]);
						serv.updateCurrentUser();
						cout << "Succesfully added movie to watchlist!" << endl;
					}
				}
				else
					cout << "Invalid command!" << endl;
			} while (running);
			return;
		}
		command.erase(command.begin(), command.begin() + 1);
		vector<movie> &results = serv.listMovies(), result;
		/*for (int i=0;i<results.size();i++)
			if (results[i].genre == command) {
				result.push_back(results[i]);
			}*/
		for (auto &i : results)
			if (i.genre == command)
				result.push_back(i);
		int index = 0;
		if (result.size() == 0) {
			cout << "No movies found!" << endl;
			return;
		}
		bool running = true;
		do {
			cout << result[mod(index) % result.size()] << endl;
			system(string("start ").append(result[mod(index) % result.size()].trailer).c_str());
			string command;
			cout << "next/previous/exit/add" << endl;
			getline(cin, command);
			if (command == "next")
				index++;
			else if (command == "previous")
				index--;
			else if (command == "exit")
				running = false;
			else if (command == "add") {
				if (serv.checkMovieWatchlist(result[mod(index) % result.size()]))
					cout << "Movie already in watchlist!" << endl;
				else {
					serv.addMovieToWatchlist(result[mod(index) % result.size()]);
					serv.updateCurrentUser();
					cout << "Succesfully added movie to watchlist!" << endl;
				}
			}
			else
				cout << "Invalid command!" << endl;
		} while (running);
		return;
	}
	void seeWatchList() {
		if (serv.currentUser.privilegeLevel == 0) {
			cout << "You are an admin!" << endl;
			return;
		}
		vector<string> results = serv.getWatchlist();
		vector<movie> result;
		/*for (int i = 0; i < results.size(); i++) {
			movie m = serv.searchMovieByUUID(results[i]);
			if (m.title != "")
				result.push_back(m);
		}*/
		for (auto& i : results) {
			movie m = serv.searchMovieByUUID(i);
			if (m.title != "")
				result.push_back(m);
		}
		/*for (int i = 0; i < result.size(); i++)
			cout << result[i] << endl;*/
		for (auto&i : result)
			cout << i << endl;
		/*for (int i = 0; i < result.size(); i++)
			result[i] = movie();*/
		for (auto&i : result)
			i = movie();
		return;
	}
	void helpScreenAdmin() {
		cout << "add <user> <username> <password>" << endl;
		cout << "add <movie> <title> <year> <genre> <likes> <trailerLink>" << endl;
		cout << "delete <user> <username>"<<endl;
		cout << "delete <movie> <title>"<<endl;
		cout << "list <users/movies>" << endl;
		cout << "update <movie> <movieTitle> <field> <newData>" << endl;
	}
	void helpScreenUser(){
		cout << "movie list <genre>" << endl;
		cout << "watchlist" << endl;
		cout << "watchlist remove <title>" << endl;
	}
	void removeWatchList(string command) {
		//watchlist remove 
		command.erase(command.begin(), command.begin() + 17);
		int i=0;
		vector<string> results = serv.getWatchlist();
		vector<movie> watchlist;
		/*for (i = 0; i < results.size(); i++)
			watchlist[i] = serv.searchMovieByUUID(results[i]);*/
		for (auto&i : results)
			watchlist.push_back(serv.searchMovieByUUID(i));
		for (i = 0; i < watchlist.size(); i++)
			if (watchlist[i].title == command)
				break;
		if (i == watchlist.size()) {
			cout << "Movie not found!" << endl;
			return;
		}
		cout << "Did you like the movie? <y/n>" << endl;
		string ye;
		getline(cin, ye);
		if (ye == "y")
			serv.likeMovie(i);
		serv.removeMovieWatchlist(i);
		serv.updateCurrentUser();
	}
	bool run() {
		string command;
		getline(cin, command);
		removeSpaces(command);
		int action = commandRecognition(command);
		switch (action) {
		case 0:
			return false;
		case 1:
			this->addCommand(command);
			break;
		case 2:	
			this->deleteCommand(command);
			break;
		case 3:
			this->updateCommand(command);
			break;
		case 4:
			this->listCommand(command);
			break;
		case 5:
			this->updateCommand(command);
			break;
		case 6:
			if (serv.currentUser.privilegeLevel==0)
				this->helpScreenAdmin();
			else
				this->helpScreenUser();
			break;
		case 10:
			this->movieList(command);
			break;
		case 11:
			this->seeWatchList();
			break;
		case 12:
			this->removeWatchList(command);
			break;
		default:
			cout << "Error: Invalid command!\n";
			break;
		}
		return true;
	}
};