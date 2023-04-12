#pragma once
#include "domain.h"
using namespace std;
#include <fstream>
class repository {
private:
	vector<movie> movies;
	vector<user> users;
public:
	repository() {
		this->userLoad();
		this->movieLoad();
	}
	void addUser(user &newUser) {
		this->users.push_back(newUser);
	}
	void addMovie(movie &newMovie) {
		this->movies.push_back(newMovie);
	}
	user &getUser(int index) {
		return this->users[index];
	}
	movie &getMovie(int index) {
		return this->movies[index];
	}
	int counterUsers() {
		return this->users.size();
	}
	int counterMovies() {
		return this->movies.size();
	}
	void deleteUser(int index) {
		this->users.erase(users.begin()+index);
	}
	void deleteMovie(int index) {
		this->movies.erase(movies.begin() + index);
	}
	vector<user>&getAllUsers() {
		return this->users;
	}
	vector<movie>&getAllMovies() {
		return this->movies;
	}
	void userDump() {
		ofstream fout("users.txt");
		for (auto i: users) 
			fout << i << endl;
	}
	void movieDump() {
		ofstream fout("movies.txt");
		for (auto i : movies) 
			fout << i << endl;
	}
	void userLoad() {
		ifstream fin("users.txt");
		while (!fin.eof()) {
			user newUser;
			fin >> newUser;
			if (newUser.username == "")
				break;
			users.push_back(newUser);
		}
	}
	void movieLoad() {
		ifstream fin("movies.txt");
		while (!fin.eof()) {
			movie newMovie;
			fin >> newMovie;
			if (newMovie.title == "")
				break;
			this->movies.push_back(newMovie);
		}
	}
	void deleteMovie(movie &movieToDelete) {
		int index = 0;
		for (auto &i: movies)
			if (i == movieToDelete) {
				this->movies.erase(movies.begin() + index);
				index++;
				return;}
			else
				index++;
	}
	void deleteUser(user &userToDelete) {
		int index = 0;
		for (auto &i : users)
			if (i == userToDelete) {
				this->users.erase(users.begin() + index);
				return;}
			else
				index++;
	}
	void updateMovie(movie &movieToUpdate) {
		for (auto &i : movies)
			if (i == movieToUpdate) {
				i = movieToUpdate;
				return;
			}
	}
	void updateCrtUser(user &userToUpdate) {
		for (auto &i : users)
			if (i == userToUpdate) {
				i = userToUpdate;
				return;
			}
	}
	movie& getMovieByUUID(string UUID) {
		for (auto &i : movies)
			if (i.uuid == UUID)
				return i;
	}
	void likeMovie(int index) {
		this->movies[index].likeSelf();
	}
};