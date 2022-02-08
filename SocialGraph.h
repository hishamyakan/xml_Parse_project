/******************************************************************************
 *
 * File Name: SocialGraph.h
 *
 * Description: Header file for SocialGraph Class.
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/

#ifndef SOCIALGRAPH_H_
#define SOCIALGRAPH_H_

#include<vector>
#include "network.h"
using namespace std;

class SocialGraph{

private:
	vector<User> users;
	vector<vector<int>> followers;
	//vector<vector<int>> followings;

	/*
	 * Description :
	 * returns the name of the user with the most number of elements in its adjacency list.
	 */
	vector<string> Most(vector<vector<int>> v);

	/*
	 * Description :
	 * returns an adjacency list of followings instead of followers.
	 */
	vector<vector<int>> getFollowings();

public:
	/*
	 * Description :
	 * Graph Constructor
	 */
	SocialGraph(vector<User> users);

	/*
	 * Description :
	 * Printing method that prints the followers and followings of each user.
	 */
	void print();


	/*
	 * Description :
	 * returns the name of the user with the most followers.
	 */
	vector<string> mostInfluentialUser();

	/*
	 * Description :
	 * returns the name of the user with the most followings.
	 */
	vector<string> mostActiveUser();

	/*
	 * Description :
	 * returns the names of the mutual users between 2 users.
	 */

	vector<string> mutualFollowers(string user1 , string user2);

	/*
	 * Description :
	 * returns the names of user's followers of followers.
	 */
	vector<string> Suggestions(string user);

	vector<string> UserNames();

	vector<vector<string>> StringList();
};


#endif /* SOCIALGRAPH_H_ */
