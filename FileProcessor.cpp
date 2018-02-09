//
//  FileProcessor.cpp
//  ece180-assignment1
//
//  Created by rick gessner on 1/10/18.
//

#include "FileProcessor.hpp"

#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>

FileProcessor::FileProcessor(const std::string aPath) : rootPath(aPath) {
  //complete the initialize process, if any...
}

/*
 * STUDENT: ProcessController calls this for each of your word-files
 */
FileProcessor& FileProcessor::run(const char* aFilename) {
  std::string theFullPath = rootPath + std::string("/content/") + std::string(aFilename);
  
  //--------------------------------------------------------
  // STUDENTS: Add code here to perform assignment tasks...
  //--------------------------------------------------------
  
  std::ifstream inputFile;
  inputFile.open(theFullPath);
  std::string word;
  bool isAlnum;
  std::string prevWord;
  std::string bigram;
  bool firstWord = true;
  while(inputFile >> word) {
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    std::string result;
    isAlnum = false;
    for(int i = 0; i < word.length(); i++){
      if(!ispunct(word[i])) {
        result += word[i];
      }
      if(isdigit(word[i])) {
        isAlnum = true;
        break;
      }
    }
    if (isAlnum or result == "") { //result empty when word just contained punctuations
      continue;
    }
    if (junkWords.count(result) == 0) {
      addWord(result);
    }
    if (not firstWord) {
      bigram = prevWord + "-" + result;
      addBigram(bigram);
    }
    
    prevWord = result;
    firstWord = false;
  }
  
  return *this;
}

void FileProcessor::addBigram(std::string bigram) {
  auto loc = bigramsCounts.find(bigram);
  if (loc != bigramsCounts.end()) { // If bigram exists in the map
    loc->second += 1;
  } else {
    bigramsCounts.insert(std::make_pair(bigram, 1));
  }
}

void FileProcessor::addWord(std::string word) {
  auto loc = wordCounts.find(word);
  if (loc != wordCounts.end()) { // If bigram exists in the map
    loc->second += 1;
  } else {
    wordCounts.insert(std::make_pair(word, 1));
  }
}

void FileProcessor::writeCSV(std::string filename) {
  std::ofstream outFile(filename);
  for (std::pair<std::string, int> element_a: wordCounts) {
    outFile << element_a.first << ", ";
  }
  outFile.close();
}

void FileProcessor::writeBigrams(std::string filename) {
  long numBigrams = 0;
  for (std::pair<std::string, int> element_a : bigramsCounts) {
    numBigrams += element_a.second;
  }
  std::ofstream outFile(filename);
  outFile << "[";
  for (std::pair<std::string, int> element_a : bigramsCounts) {
    double prob = (float)element_a.second / numBigrams;
    outFile << "{\"bigram\" : \"" << element_a.first << "\", \"probability\" : " << prob << "},";
  }
  outFile << "]";
}

void FileProcessor::setJunkWords(const std::set<std::string> &junkWords) {
  this->junkWords = junkWords;
}

const std::map <std::string, int>& FileProcessor::getWordCounts() const {
  return wordCounts;
}


