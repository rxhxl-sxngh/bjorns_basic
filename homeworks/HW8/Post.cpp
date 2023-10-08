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
#include <string>
#include <stdexcept>
#include "Post.h"
#include <sstream>

using std::string;
using std::vector;
using std::stringstream;

Post::Post(unsigned int postId, string userName, string postText)
  : postId(postId), userName(userName), postText(postText) {
  if (postId == 0 || userName == "" || postText == "") {
    throw std::invalid_argument("post constructor: invalid parameter values");
  }
}

unsigned int Post::getPostId() {
  return postId;
}

string Post::getPostUser() {
  return userName;
}

string Post::getPostText() {
  return postText;
}

vector<string> Post::findTags() {
  // TODO(student): extracts candidate tags based on occurrences of # in the post
  vector<string> tags = {};
  stringstream ss;
  ss << getPostText();
  string word;
  int endOfWord = 0;
  string tag = "";

  while(ss >> word) {
    endOfWord = word.length()-1;
    tag = "";
    if(word.at(0) == '#') {
      for(int i = word.length()-1; i >= 0; i--) {
        if((word.at(i) != '!') && (word.at(i) != '.') && (word.at(i) != ',') && (word.at(i) != '?')) {
          endOfWord = i;
          break;
        }
      }
      for(int i = 0; i <= endOfWord; i++) {
        tag += tolower(word.at(i)); 
      }
      tags.push_back(tag);
    } 
  }
  return tags;

}
