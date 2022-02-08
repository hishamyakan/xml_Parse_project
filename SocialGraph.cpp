/******************************************************************************
 *
 * File Name: SocialGraph.cpp
 *
 * Description: Source file for SocialGraph Class.
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/

#include "SocialGraph.h"
#include <iostream>
#include<vector>
#include "network.h"
using namespace std;

/*
 * Description :
 * Searches for a the index of the user with a given id.
 */
static int search(vector<User> users, int id){

	for(int i = 0 ; i < (int)users.size() ; i++){
		if(users[i].id == id)
			return i;
	}
	return -1;
}
/*
 * Description :
 * Searches for a the index of the user with a given name.
 */
static int search(vector<User> users, string name){

	for(int i = 0 ; i < (int)users.size() ; i++){
		if(users[i].name == name)
			return i;
	}
	return -1;
}


/*
 * Description :
 * returns the name of the user with the most number of elements in its adjacency list.
 * Time Complexity : O(|V|)
 * Space Complexity : O(|V|)
 */
vector<string> SocialGraph::Most(vector<vector<int>> v){

	vector<string> res;
	if(users.size() == 0)
		return {"The Graph is Empty"};

	int max_ind = 0 , max_followers =0;

	for(int i = 0 ; i < v.size() ; i++){
		if(max_followers < v[i].size()){
			//max_ind = i ;
			max_followers = v[i].size();
		}
	}

	for(int i = 0 ; i < (int)users.size() ; i++){
		if(v[i].size() == max_followers)
			res.push_back(users[i].name);
	}
	return res;

}

/*
 * Description :
 * returns an adjacency list of followings instead of followers.
 * Time Complexity : O(|V|^2)
 * Space Complexity : O(|V|+|E|)
 */
vector<vector<int>> SocialGraph::getFollowings(){

	vector<vector<int>>followings = vector<vector<int>>(users.size());

	int i = 0 ;

	for(auto follower_list : followers){

		for(auto id : follower_list){

			int loc = search(this->users,id);

			followings[loc].push_back(users[i].id);
		}
		i++;
	}
	return followings;
}
/*
 * Description :
 * Graph Constructor
 * Time Complexity : O(|V|+|E|)
 * Space Complexity : O(|V|+|E|)
 */
SocialGraph::SocialGraph(vector<User> users){

	this->users = users;

	for(auto user : users)
		followers.push_back(user.followers);

}

/*
 * Description :
 * Printing method that prints the followers and followings of each user.
 */
void SocialGraph::print(){

	for(int i = 0 ; i < (int)users.size() ; i++){
		cout<<"User Name: "<<users[i].name<<endl;


		cout<<"Followers:"<<endl;

		for(int j = 0 ; j < (int)followers[i].size() ; j++){
			int id = followers[i][j];
			for(auto user : users)
				if(user.id == id)
					cout<<user.name<<" " ;
			cout<<followers[i][j]<<" ";
		}
#ifdef followings
		cout<<endl;
		cout<<"He Follows: "<<endl;
		for(auto id : followings[i]){
			for(auto user: users)
				if(user.id == id)
					cout<<user.name<<" ";
		}
		cout<<endl;

#endif
	}
}
/*
 * Description :
 * returns the name of the user with the most followers.
 * Time Complexity : O(|V|)
 * Space Complexity : O(|V|)
 */
vector<string> SocialGraph::mostInfluentialUser(){

	return Most(followers);

}

/*
 * Description :
 * returns the name of the user with the most followings.
 * Time Complexity : O(|V|)
 * Space Complexity : O(|V|)
 */
vector<string> SocialGraph::mostActiveUser(){
	return Most(getFollowings());

}
/*
 * Description :
 * returns the names of the mutual users between 2 users.
 * Time Complexity : O(|V|*|E|^2)
 * Space Complexity : O(|V|)
 */

vector<string> SocialGraph::mutualFollowers(string user1 , string user2){
	int loc1 = search(users,user1);
	int loc2 = search(users,user2);

	if(loc1 == -1 || loc2 == -1)
		return vector<string>();

	vector<string> mutual;

	for(int i = 0 ; i < followers[loc1].size() ; i++){
		for(int j = 0 ; j < followers[loc2].size() ; j++){

			if(followers[loc1][i] == followers[loc2][j]){
				int loc = search(users, followers[loc1][i]);

				mutual.push_back(users[loc].name);
			}

		}
	}
	return mutual;
}

/* Time Complexity : O(|V|*|E|^2)
 * Space Complexity : O(|V|)
 */
vector<string> SocialGraph::Suggestions(string user){

	int user_loc = search(users,user);//O(V)
	vector<string> res;
	for(auto id : followers[user_loc]){//O(E)

		int follower_loc =search(users,id);//O(V)

		for(auto F_of_F_id : followers[follower_loc]){//O(E)
			string name = users[search(users,F_of_F_id)].name;//O(V)

			if(user != name)
				res.push_back(name);
		}

	}

	/*Stage 1 : remove already followers*/
	vector<string> temp;
	for(auto name:res){

		bool isFollower = false;

		for(auto id :followers[user_loc]){

			int follower_loc = search(users,id);

			if(name == users[follower_loc].name){
				isFollower = true;
				break;
			}


		}
		if(!isFollower)
			temp.push_back(name);
	}

	/*Stage 2 : remove duplicates*/
	res = vector<string>();

	for(auto name : temp){

		bool isAdded = false;
		for(auto added_name : res){
			if (name == added_name){
				isAdded = true;
				break;
			}
		}

		if(!isAdded)
			res.push_back(name);
	}
	return res;

}



/*
 *
 * Description :
 * returns a list of user names.
 * Time Complexity : O(|V|)
 * Space Complexity : O(|V|)
 */

vector<string> SocialGraph::UserNames(){

	vector<string> res;

	for(auto user : users){

		res.push_back(user.name);

	}
	return res;
}

/*
 * Description :
 * returns a string adjacency list.
 * Time Complexity : O(|V|^2)
 * Space Complexity : O(|V|+|E|)
 */

vector<vector<string>> SocialGraph::StringList(){

	vector<vector<string>> res;

	vector<string> temp;

	for(auto followers_list : getFollowings()){

		temp = vector<string>();

		for(auto id : followers_list){

			int loc = search(users,id);
			temp.push_back(users[loc].name);


		}
		res.push_back(temp);

	}
	return res;
}
