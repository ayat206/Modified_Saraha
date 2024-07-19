#pragma once
#include"Users.h"
#include<vector>

ref class HomeForm
{
public:
	void setLiveUser(Users user);
	void uploadUserMessages();
	void uploadUserSentMessages();
	void reloadUserSentMessages();
	void uploadContanctsList();
	void addContact(string s);
	void sendMessage(Messages message);
	string getContact(int i);
	Users getLiveUser();
	void deleteLastSentMessage();
	Messages getMessage(int i);
	Messages getSentMessage(int i);
	
};

