/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

std::string kYourName = "Gorway Dong"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
  std::set<std::string> resultSet;
  std::ifstream infile("students.txt");
  if(!infile.is_open()){
    std::cerr << "Failed to open file!" << std::endl;
    return resultSet;
  }
  std::string lineString;
  while (getline(infile,lineString))
  {
    resultSet.insert(lineString);
  }
  return resultSet;
}

std::string get_initials(std::string name){
  std::string initials;
  initials.push_back(name.at(0));
  int spaceLocation = name.find(' ');
  initials.push_back(name.at(spaceLocation+1));
  return initials;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  std::queue<const std::string*> namesQueue;
  std::string initials = get_initials(name);
  for(auto it = students.begin();it!=students.end();++it){
    if(get_initials(*it) == initials){
      namesQueue.push(&(*it));
    }
  }
  return namesQueue;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  if(matches.empty()){
    std::cout<<"NO MATCHES FOUND."<<std::endl;
    return nullptr;
  }
  srand(time(nullptr));
  int random_num = rand() % matches.size();
  for(int i =0;i < random_num;i++){
    matches.pop();
  }
  return *(matches.front());
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
