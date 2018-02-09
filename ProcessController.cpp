//
//  ProcessController.cpp
//  ece180-assignment1
//
//  Created by rick gessner on 1/15/18.
//

#include "ProcessController.hpp"
#include <fstream>
#include <iostream>
#include <math.h>

ProcessController::ProcessController(const char *aRootPath) : rootPath(aRootPath) {
}

/*
 * STUDENT: This is where you add code to test your code/classes, as needed...
 */
ProcessController& ProcessController::runTests() {

  std::ofstream testout(rootPath+std::string("/testoutput.txt"));
  std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
  std::cout.rdbuf(testout.rdbuf()); //redirect

  std::cout << "running tests..."  << std::endl;

  // ----------------------------------
  // STUDENTS... Add your tests here...
  // ----------------------------------

  std::cout.rdbuf(coutbuf); //reset to standard output again
  coutbuf=nullptr;

  return *this;
}

/*
 * STUDENT: This is where you add code to manage the tasks in this assignment...
 */
ProcessController& ProcessController::runActual() {
  return processWordFiles();
}

ProcessController& ProcessController::processWordFiles() {
  FileProcessor f1(rootPath), f2(rootPath), f3(rootPath);

  // --------------------------------------------------------------------
  // STUDENTS... This control logic already works; see FileProcessor.cpp
  // --------------------------------------------------------------------

  std::set<std::string> stopWords = readStopWords("stopwords.txt");
  
  f1.setJunkWords(stopWords);
  f2.setJunkWords(stopWords);
  f3.setJunkWords(stopWords);
  
  f1.run("alice.txt");
  f2.run("verne.txt");
  f3.run("jfk.txt");
 
  f1.writeCSV("output_alice.txt");
  f2.writeCSV("output_verne.txt");
  f3.writeCSV("output_jfk.txt");
  
  f1.writeBigrams("bigrams_alice.json");
  f2.writeBigrams("bigrams_verne.json");
  f3.writeBigrams("bigrams_jsk.json");
  
  return saveSummary(f1, f2, f3);
}

ProcessController& ProcessController::saveSummary(const FileProcessor &f1, const FileProcessor &f2, const FileProcessor &f3) {

  //theResultFile is filename where you store your summary in assignment root folder...
  const char* theResultFile = "results.txt";
  
  // ----------------------------------------------------------
  // STUDENTS... Add code here to generate and save summary...
  // ----------------------------------------------------------
  float f1f2 = computeDistance(f1, f2);
  float f1f3 = computeDistance(f1, f3);
  
  std::ofstream summaryFile;
  summaryFile.open(theResultFile);
  summaryFile << "Distance AB: " << f1f2 << std::endl;
  summaryFile << "Distance AC: " << f1f3 << std::endl;
  summaryFile << "Document A is most similar to document ";
  if (f1f2 < f1f3) {
    summaryFile << "B";
  } else {
    summaryFile << "C";
  }
  summaryFile.close();
  return *this;
}

std::set<std::string>  ProcessController::readStopWords(std::string filename) {
  std::string path = rootPath + "/content/" + filename;
  std::ifstream inFile(path);
  std::string word;
  std::set<std::string> stopWords;
  while (inFile >> word) {
    std::size_t commaPos = word.find(",");
    word = word.substr(0, commaPos);
    stopWords.insert(word);
  }
  return stopWords;
}

float ProcessController::computeDistance(const FileProcessor &f1, const FileProcessor &f2) {
  long f1_dot = computeDotProduct(f1, f1);
  long f2_dot = computeDotProduct(f2, f2);
  long f1_f2_dot = computeDotProduct(f1, f2);
  float result = acos(f1_f2_dot / sqrt(f1_dot * f2_dot));
  return result;
}

long ProcessController::computeDotProduct(const FileProcessor &f1, const FileProcessor &f2) {
  long sum = 0;
  const std::map <std::string, int>& f1wordCounts = f1.getWordCounts();
  const std::map <std::string, int>& f2wordCounts = f2.getWordCounts();
  for (std::pair<std::string, int> element_a : f1wordCounts) {
    auto map_b_loc = f2wordCounts.find(element_a.first);
    if (map_b_loc != f2wordCounts.end()) {
      sum += element_a.second * map_b_loc->second;
    }
  }
  return sum;
}



