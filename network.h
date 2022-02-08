/******************************************************************************
 *
 * File Name: network.h
 *
 * Description: Header file for network analysis.
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/

#ifndef NETWORK_H_
#define NETWORK_H_
#include<iostream>
#include<vector>
#include "Tree.h"
using namespace std;


typedef struct post{

    string body;
    vector<string> topics;

    post(){
        body = "NONE";
        topics = vector<string>();
    }
};





typedef struct User{

    int id;

    string name;

    vector<post> posts;

    vector<int> followers;


    User(){
        id = -1 ;
        name = "None";
        posts = vector<post>();
        followers = vector<int>();
    }

};

/*
 * Description :
 * returns a vector of users in an XML Tree.
 */
vector<User> getUsers(Node* root);

#endif /* NETWORK_H_ */
