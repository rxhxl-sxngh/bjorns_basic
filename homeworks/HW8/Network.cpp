/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Network.h"

using std::string;
using std::vector;
using namespace std;

Network::Network() {
  // empty containers of vectors already created
  // no implementation is needed here
}

void Network::loadFromFile(string fileName) {
  // TODO(student): load user and post information from file
  ifstream inFS(fileName);
  if (!inFS.is_open()) {
    throw invalid_argument("");
  }

  string line = "";
  try {
    while(getline(inFS,line)) {
      string type;
      string text;
      string userID;
      unsigned int postID;
      stringstream ss;
      ss << line;
      ss >> type;

      if(type == "User") {
        ss >> userID;
        addUser(userID);
      } else if (type == "Post") {
        ss >> postID;
        ss >> userID;
        getline(ss,text);
        if(ss.fail()) {
          throw runtime_error("");
        }
        while(isspace(text[0])) {
          text.erase(0);
        }
        text = " " + text;
        addPost(postID, userID, text);
        ss.clear();
        ss.str("");
      } else {
        throw runtime_error("");
      }
    }
  } catch(...) {
    throw runtime_error("");
  }

  inFS.close();

  
}

void Network::addUser(string userName) {
  // TODO(student): create user and add it to network
  string correct = userName;
  for (unsigned int i = 0; i < correct.length(); i++)  {
    correct[i] = tolower(correct[i]);
  }
  for (unsigned int i = 0; i < users.size(); i++)  {
    if(correct == users[i]->getUserName()) {
      throw invalid_argument("");
    }
  }
  User* newUser = new User(correct);
  users.push_back(newUser);
  cout << "Added User " << correct << endl;
}

void Network::addPost(unsigned int postId, string userName, string postText) {
  // TODO(student): create post and add it to network
  for (unsigned int i = 0; i < posts.size(); i++)  {
    if(postId == posts[i]->getPostId()) {
      throw invalid_argument("");
    }
  }

  bool noUser = true;
  for(unsigned int i = 0; i < users.size(); i++) {
    if(userName == users[i]->getUserName()) {
      Post* newPost = new Post(postId,userName,postText);
      posts.push_back(newPost);
      users[i]->addUserPost(newPost);
      noUser = false;
    }
  }
  if (noUser) {
    throw invalid_argument("");
  }

  vector<string> newTags = posts.at(posts.size()-1)->findTags();
  for(unsigned int i = 0; i < newTags.size(); i++) {
    bool isNewTag = true;
    for(unsigned int j = 0; i < tags.size(); i++) {
      if(newTags[i] == tags[j]->getTagName()) {
        isNewTag = false;
        tags[j]->addTagPost(posts.at(posts.size()-1));
      }
    }

    try {
      if(isNewTag) {
        Tag* newTag = new Tag(newTags[i]);
        tags.push_back(newTag);
        tags.at(tags.size()-1)->addTagPost(posts.at(posts.size()-1));
      }
    } catch (exception& e) {
    }
  }
  cout << "Added Post " << postId << " by " << userName << endl;
  
}

vector<Post*> Network::getPostsByUser(string userName) {
  // TODO(student): return posts created by the given user
  if (userName.empty()) {
    throw invalid_argument("");
  }
  for(unsigned int i = 0; i < users.size(); i++) {
    if(userName == users[i]->getUserName()) {
      return users[i]->getUserPosts();
    }
  }
  throw invalid_argument("");
}

vector<Post*> Network::getPostsWithTag(string tagName) {
  // TODO(student): return posts containing the given tag
  if (tagName.empty()) {
    throw runtime_error("");
  }
  for(unsigned int i = 0; i < tags.size(); i++) {
    if(tagName == tags.at(i)->getTagName()) {
      return tags[i]->getTagPosts();
    }
  }
  throw invalid_argument("");
  

 /*
 if (tagName.empty()) {
    throw invalid_argument("");
 }
 vector<Post*> everyPost = {};
 vector<Post*> postsWithTag = {};
 for(unsigned int i = 0; i < users.size(); i++) {
  vector<Post*> currentUserPosts = users[i]->getUserPosts();
  for(unsigned int j = 0; j < users[i]->getUserPosts().size(); j++) {
    everyPost.push_back(currentUserPosts[j]);
  }
 }
 for(unsigned int i = 0; i < everyPost.size(); i++) {
  vector<string> currentPostTags = everyPost[i]->findTags();
  for(unsigned int j = 0; j < currentPostTags.size(); j++) {
    if(tagName == currentPostTags[j]) {
      postsWithTag.push_back(everyPost[i]); 
    }
  }
 }
 if(postsWithTag.size() == 0) {
  throw invalid_argument("");
 }
 return postsWithTag;
 */
 

}

vector<string> Network::getMostPopularHashtag() {
  // TODO(student): return the tag occurring in most posts
  unsigned int tagMaxOccurrences = 0;
  vector<string> popularHashtags;
  for (unsigned int i = 0; i < tags.size(); i++) {
    if (tagMaxOccurrences < (tags.at(i)->getTagPosts()).size()) {
      popularHashtags.clear();
      popularHashtags.push_back(tags.at(i)->getTagName());
      tagMaxOccurrences = (tags.at(i)->getTagPosts()).size();
    } else if (tagMaxOccurrences == (tags.at(i)->getTagPosts()).size()) {
      popularHashtags.push_back(tags.at(i)->getTagName());
    }
  }
  return popularHashtags;

}

/**
  * Destructor
  * Do not change; already implemented.
  */
Network::~Network() {
  for (unsigned int i = 0; i < users.size(); ++i) {
    delete users.at(i);
  }
  for (unsigned int i = 0; i < tags.size(); ++i) {
    delete tags.at(i);
  }
  for (unsigned int i = 0; i < posts.size(); ++i) {
    delete posts.at(i);
  }
}
