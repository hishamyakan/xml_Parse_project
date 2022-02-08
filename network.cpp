/******************************************************************************
 *
 * File Name: network.cpp
 *
 * Description: Source file for network analysis.
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/

#include<iostream>
#include<vector>
#include<string>
#include "tree.h"
#include "network.h"
using namespace std;

/*
 * Description :
 * returns a vector of topics from a topics Node.
 * Time Complexity : O(n)
 * Space Complexity : O(n)
 */
static vector<string> getTopics(Node* topicsNode){

	vector<string> res = vector<string>() ;

	for(int i = 0 ; i < topicsNode->ChildrenNo() ; i++){

		res.push_back(topicsNode->getChild(i)->getData());

	}
	return res;
}

/*
 * Description :
 * returns a post of a post node.
 * Time Complexity : O(n)
 * Space Complexity : O(n)
 */
static post getPost(Node* PostNode){

	string body;
	vector<string> topics;

	for(int i = 0 ; i < PostNode->ChildrenNo() ; i++){

		if(PostNode->getChild(i)->getOpTag() == "<body>")

			body = PostNode->getChild(i)->getData();

		else
			topics = getTopics(PostNode->getChild(i));
	}

	post result;

	result.body = body;
	result.topics = topics;
	return result;
}

/*
 * Description :
 * returns a vector of posts of a posts node.
 * Time Complexity : O(n)
 * Space Complexity : O(n)
 */
static vector<post> getPosts(Node* Posts){

	vector<post> res;

	for(int i = 0 ; i < Posts->ChildrenNo() ; i++){
		res.push_back( getPost(Posts->getChild(i)) );
	}
	return res;
}

/*
 * Description :
 * returns a follower id from a follower node.
 * Time Complexity : O(n)
 * Space Complexity : O(n)
 */
static int getFollower(Node* f){


	for(int i = 0 ; i < f->ChildrenNo() ; i++){

		if(f->getChild(i)->getOpTag() == "<id>")

			return stoi(f->getChild(i)->getData());

	}

	return -1;
}


/*
 * Description :
 * returns a vector of followers ids from a followers node.
 * Time Complexity : O(n)
 * Space Complexity : O(n)
 */
static vector<int> getFollowers(Node* followers){

	vector<int> res;

	for(int i = 0 ; i < followers->ChildrenNo() ; i++){

		res.push_back( getFollower(followers->getChild(i)) );

	}
	return res;
}


/*
 * Description :
 * returns a User from a User node.
 * Time Complexity : O(n)
 * Space Complexity : O(n)
 */
static User getUser(Node * user){

	User res;

	for(int i = 0 ; i < user->ChildrenNo() ; i++){

		if(user->getChild(i)->getOpTag() == "<id>")

			res.id = stoi(user->getChild(i)->getData());

		else if(user->getChild(i)->getOpTag() == "<name>")
			res.name = user->getChild(i)->getData();

		else if(user->getChild(i)->getOpTag() == "<posts>")
			res.posts = getPosts(user->getChild(i));

		else if(user->getChild(i)->getOpTag() == "<followers>")
			res.followers = getFollowers(user->getChild(i));

	}
	return res;

}


/*
 * Description :
 * returns a vector of users in an XML Tree.
 * Time Complexity : O(n)
 * Space Complexity : O(n)
 */
vector<User> getUsers(Node* root){

	vector<User> users ;

	for(int i = 0 ; i < root->ChildrenNo() ; i++){

		users.push_back(getUser(root->getChild(i)));
	}

	return users;
}
