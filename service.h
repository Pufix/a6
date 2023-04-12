#pragma once
#include "repository.h"
using namespace std;
class service {
private:
public:
	repository repo;
	user &currentUser=user();
	bool Login(string userName, string password) {
		user &a = this->searchUser(userName);
		if (a == user())
			return false;
		if (a.checkPassword(password)) {
			currentUser = a;
			return true;
		}
		return false;
	}
	service() {
		this->currentUser.privilegeLevel = -1;
	}
	string GetUsername() {
		if (this->currentUser.privilegeLevel == -1)
			return "Not logged in!";
		return this->currentUser.username;
	}
	user &searchUser(string username) {
		for (auto &i : this->repo.getAllUsers())
			if (i.username == username)
				return i;
		return user();
	}
	int addUser(string username, string password) {
		if (this->searchUser(username) == user()) {
			user newuser;
			newuser.username = username;
			newuser.setPassword(password);
			newuser.uuid = generateUUID();
			newuser.privilegeLevel = 1;
			this->repo.addUser(newuser);
			return 0;
		}
		return -1;
	}
	movie &searchMovie(string title) {
		for (auto &i : this->repo.getAllMovies())
			if (i.title == title)
				return i;
		return movie();
	}
	movie& searchMovieByUUID(string uuid) {
		for (auto &i : this->repo.getAllMovies())
			if (i.uuid == uuid)
				return i;
		return movie();
	}
	int addMovie(string title, int year, string genre, int likes, string trailer) {
		if (this->currentUser.privilegeLevel != 0)return -1;
		if (this->searchMovie(title) == movie()){
			this->repo.addMovie(movie(title, genre, year, likes, trailer, generateUUID()));
			return 0;
		}
		return -1;
	}
	int removeMovie(string title) {
		if (this->currentUser.privilegeLevel != 0)return -2;
		if (this->searchMovie(title) != movie()) {
			this->repo.deleteMovie(this->searchMovie(title));
			return 0;
		}
		return -1;
	}
	int removeUser(string username) {
		if (this->currentUser.privilegeLevel != 0)return -2;
		if (this->searchUser(username) != user()) {
			this->repo.deleteUser(this->searchUser(username));
			return 0;
		}
		return -1;
	}
	vector<user> &listUsers() {
		vector<user>&result=vector<user>();
		if (this->currentUser.privilegeLevel != 0)return result;
		return repo.getAllUsers();
	}
	vector<movie> &listMovies() {
		return repo.getAllMovies();
	}
	int updateMovieTitle(string title,string newTitle) {
		if (this->currentUser.privilegeLevel != 0)return -2;
		if (this->searchMovie(title) != movie()) {
			this->searchMovie(title).title=newTitle;
			return 0;
		}
		return -1;
	}
	int updateMovieGenre(string title, string newGenre) {
		if (this->currentUser.privilegeLevel != 0)return -2;
		if (this->searchMovie(title) != movie()) {
			movie film = this->searchMovie(title);
			film.genre = newGenre;
			repo.updateMovie(film);
			return 0;
		}
		return -1;
	}
	int updateMovieYear(string title, int newYear) {
		if (this->currentUser.privilegeLevel != 0)return -2;
		if (this->searchMovie(title) != movie()) {
			movie film = this->searchMovie(title);
			film.year = newYear;
			repo.updateMovie(film);
			return 0;
		}
		return -1;
	}
	int updateMovieLikes(string title, int newLikes) {
		if (this->currentUser.privilegeLevel != 0)return -2;
		if (this->searchMovie(title) != movie()) {
			movie film = this->searchMovie(title);
			film.likes = newLikes;
			repo.updateMovie(film);
			return 0;
		}
		return -1;
	}
	int updateMovieTrailer(string title, string newTrailer) {
		if (this->currentUser.privilegeLevel != 0)return -2;
		if (this->searchMovie(title) != movie()) {
			movie film = this->searchMovie(title);
			film.trailer = newTrailer;
			repo.updateMovie(film);
			return 0;
		}
		return -1;
	}
	void addMovieToWatchlist(movie &mov) {
		if (this->currentUser.privilegeLevel == -1)return;
		this->currentUser.watchlist.push_back(mov.uuid);
	}
	void updateCurrentUser() {
		this->repo.updateCrtUser(this->currentUser);
	}
	vector<string> &getWatchlist() {
		return this->currentUser.watchlist;
	}
	void likeMovie(int index) {
		repo.likeMovie(index);
	}
	void removeMovieWatchlist(int index) {
		this->currentUser.watchlist.erase(currentUser.watchlist.begin() + index);
	}
	bool checkMovieWatchlist(movie &movie) {
		for (auto &i : this->currentUser.watchlist)
			if (i == movie.uuid)
				return true;
		return false;
	}
};