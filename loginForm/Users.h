#pragma once
#include <string>
#include<vector>
#include<stack>
#include"Messages.h"
using namespace std;
class Users
{
public:
	string Username;
	string password;
	string ID;
	vector<string> ListOfContacts;
	vector<Messages>Message;
	vector<Messages>sentMessages;
	stack<Messages>sentMessagesStack;
	void loadUserInfo();
	vector <Users> getUserInfo();
	void deleteThatMessage();
};

