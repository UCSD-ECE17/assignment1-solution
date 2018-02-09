//
//  ProcessController.hpp
//  ece180-assignment1
//
//  Created by rick gessner on 1/15/18.
//

#ifndef ProcessController_hpp
#define ProcessController_hpp

#include <string>
#include "FileProcessor.hpp"
#include <set>

class ProcessController {
public:
  
  ProcessController(const char *aRootPath);
  
  ProcessController& runActual();
  ProcessController& runTests();

  std::set<std::string> readStopWords(std::string filename);

private:
  
  ProcessController& processWordFiles();
  ProcessController& saveSummary(const FileProcessor &f1, const FileProcessor &f2, const FileProcessor &f3);
    
  std::string rootPath;
  
  long computeDotProduct(const FileProcessor &f1, const FileProcessor &f2);
  float computeDistance(const FileProcessor &f1, const FileProcessor &f2);
};

#endif /* ProcessController_hpp */
