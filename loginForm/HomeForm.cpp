#include "HomeForm.h"
#include"Users.h"
#include<fstream>
#include <cstdio>
#include<vector>
#include "Messages.h"
using namespace std;

static Users liveuser;
ifstream messageReader;
vector<Messages>specificUserRecivedMessages;

void HomeForm::setLiveUser(Users user)
{
	liveuser = user;
}

void HomeForm::uploadContanctsList()
{
	liveuser.ListOfContacts.clear();
	messageReader.open("Data/listOfContacts/" + liveuser.Username + ".txt");
	if (!messageReader) {
		ofstream createTheFile("Data/listOfContacts/" + liveuser.Username + ".txt", ios::app);
		cout << "not in Message Reader";
	}

	while (messageReader) {
		string s;
		messageReader >> s;
		liveuser.ListOfContacts.push_back(s);
	}
	messageReader.close();
}

void HomeForm::addContact(string s)
{
	
	for (int i = 0; i < liveuser.getUserInfo().size(); i++) {
		if (liveuser.getUserInfo()[i].Username == s) {
			liveuser.ListOfContacts.push_back(s);
			ofstream UpdateLocalContacts("Data/listOfContacts/" + liveuser.Username + ".txt", ios::app);
			UpdateLocalContacts << s;
			UpdateLocalContacts << "\n";
			MessageBox::Show("Added Succesfully", "Done", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
			break;
		}
	 }
}

void HomeForm::sendMessage(Messages message)
{
	ofstream usersFileUpdate("Data/Messages/" + message.receiver + ".txt", ios::app);
	
	usersFileUpdate << message.content;
	usersFileUpdate << "\n***\n";
	usersFileUpdate << message.receiver;
	usersFileUpdate << " ";
	usersFileUpdate << message.sender;
	usersFileUpdate << " false\n";
	MessageBox::Show("Message sent successfully", "Done", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
	messageReader.open("Data/sentMessages/" + message.sender + ".txt", ios::app);
	if (!messageReader) {
		ofstream createTheFile("Data/Messages/" + liveuser.Username + ".txt", ios::app);
	}
	ofstream usersSentMessagesFileUpdate("Data/sentMessages/" + message.sender + ".txt", ios::app);
	usersSentMessagesFileUpdate << message.content;
	usersSentMessagesFileUpdate << "\n***\n";
	usersSentMessagesFileUpdate << message.receiver;
	usersSentMessagesFileUpdate << " ";
	usersSentMessagesFileUpdate << message.sender;
	usersSentMessagesFileUpdate << " false\n";
	messageReader.close();
	usersSentMessagesFileUpdate.close();
}
void HomeForm::uploadUserMessages() {
	liveuser.Message.clear();
	messageReader.open("Data/Messages/" + liveuser.Username + ".txt");
	if (!messageReader) {
		ofstream createTheFile("Data/Messages/" + liveuser.Username + ".txt", ios::app);
	}
	else {

		bool isContentRead = false;
		string s, s0;

		Messages tempMessage;
		while (messageReader) {
			if (!isContentRead) {
				messageReader >> s;
				if (s == "***") { 
					isContentRead = true; 
				}
				else if (s == "-1")
					break;
				else
					tempMessage.content += s;
				tempMessage.content += " ";
			}
			else {
				messageReader >> tempMessage.receiver;
				messageReader >> tempMessage.sender;
				messageReader >> s0;

				if (s0 == "true")tempMessage.isFavourite = true;
				else tempMessage.isFavourite = false;

				liveuser.Message.push_back(tempMessage);
				isContentRead = false;
				tempMessage.content.clear();
			}
		}
	}
	messageReader.close();
}
void HomeForm::uploadUserSentMessages()
{
	liveuser.sentMessages.clear();
	messageReader.open("Data/sentMessages/" + liveuser.Username + ".txt");
	if (!messageReader) {
		ofstream createTheFile("Data/sentMessages/" + liveuser.Username + ".txt", ios::app);
	}
	else {

		bool isContentRead = false;
		string s, s0;

		Messages tempMessage;
		while (messageReader) {
			if (!isContentRead) {
				messageReader >> s;
				if (s == "***") { isContentRead = true; }
				else if (s == "-1")
					break;
				else
					tempMessage.content += s;
				tempMessage.content += " ";
			}
			else {
				messageReader >> tempMessage.receiver;
				messageReader >> tempMessage.sender;
				messageReader >> s0;

				if (s0 == "true")tempMessage.isFavourite = true;
				else tempMessage.isFavourite = false;

				liveuser.sentMessages.push_back(tempMessage);
				isContentRead = false;
				tempMessage.content.clear();
			}
		}
	}
	messageReader.close();
}

void HomeForm::reloadUserSentMessages()
{
	
	ofstream usersSentMessagesFileUpdate("Data/sentMessages/" + liveuser.Username + ".txt", ios::app);
	cout<< liveuser.sentMessages.size() <<endl;
	for (int i = 0; i < liveuser.Message.size();i++) {
		usersSentMessagesFileUpdate << liveuser.sentMessages[i].content;
		usersSentMessagesFileUpdate << "\n***\n";
		usersSentMessagesFileUpdate << liveuser.sentMessages[i].receiver;
		usersSentMessagesFileUpdate << " ";
		usersSentMessagesFileUpdate << liveuser.sentMessages[i].sender;
		usersSentMessagesFileUpdate << " false\n";
	}
	usersSentMessagesFileUpdate.close();
}

string HomeForm::getContact(int i)
{
	return liveuser.ListOfContacts[i];
}

Users HomeForm::getLiveUser()
{
	return liveuser;
}

void HomeForm::deleteLastSentMessage() {
	liveuser.deleteThatMessage();
}

Messages HomeForm::getMessage(int i)
{
	return liveuser.Message[i];
}

Messages HomeForm::getSentMessage(int i)
{
	return liveuser.sentMessages[i];
}


