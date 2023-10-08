/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <string>
#include <stdexcept>
#include "Tag.h"

using std::string;
using std::vector;

Tag::Tag(string tagName) /* TODO(student): initialize */ {
  // TODO(student): implement constructor checks
  if(tagName.length() < 2 || tagName.at(0) != '#' || !(isalpha(tagName.at(1))) || tagName.at(tagName.length()-1) == '!' || tagName.at(tagName.length()-1) == ',' || tagName.at(tagName.length()-1) == '?' || tagName.at(tagName.length()-1) == '.') {
    throw std::invalid_argument("");
  }
  for(unsigned int i = 1; i < tagName.length(); i++) {
    if(isupper(tagName[i])) {
      throw std::invalid_argument("");
    }
  }
  this->tagName = tagName;

}

string Tag::getTagName() {
  // TODO(student): implement getter
  return tagName;
}

vector<Post*>& Tag::getTagPosts() {
  // TODO(student): implement getter
  return tagPosts;
}

void Tag::addTagPost(Post* post) {
  // TODO(student): add post to tag posts
  if (post == nullptr) {
  	throw std::invalid_argument("");
  } else {
  	tagPosts.push_back(post);
  } 
}
