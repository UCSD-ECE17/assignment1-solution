//
//  FileProcessor.hpp
//  ece180-assignment1
//
//  Created by rick gessner on 1/10/18.
//

#ifndef FileProcessor_hpp
#define FileProcessor_hpp

#include <string>
#include <map>
#include <set>

class FileProcessor {
public:

  FileProcessor(const std::string aPath);
  
  FileProcessor& run(const char* anInputFilename);
  
  void setJunkWords(const std::set <std::string>& junkWords);
  
  void writeCSV(std::string filename);
  
  void writeBigrams(std::string filename);
  
  const std::map <std::string, int>& getWordCounts() const;
  
protected:
  std::string rootPath;
  std::map <std::string, int> wordCounts;
  std::set <std::string> junkWords;
  std::map <std::string, int> bigramsCounts;
  void addBigram(std::string bigram);
  void addWord(std::string word);
};

#endif /* FileProcessor_hpp */
