#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "course.h"
#include <regex>

using namespace std;

void printHelp(std::string progName){
  cout <<
    "catalogue-search 1.0" << "\n"
    "Search the UF catalogue from the command line.\n\n"
    "USAGE:\n"
    "  " << progName << " [OPTIONS] <query>\n"
    "OPTIONS:\n"
    "  --course                      Search for a course using course code\n"
    "  --dep                         List all courses with the same prefix\n"
    "  --name                        Search for a course using course name\n"
    "  --recursive N                 Use alongside previous flags to recursively print N layers of pre-requisites"
    "  --prereq                      Search for courses that require the given course code as a pre-requisite)\n"
    "EXAMPLES:\n"
    "  " << progName << " --course EEL3111C\n"
    "  " << progName << " --recursive 4 --course EEL4745C\n"
    "  " << progName << " --name \"Heat and Mass Transfer\"\n"
    "  " << progName << " --prereq PHY2048\n";
}

void notEnoughArguments(){
  cout << "Please insert enough arguments\n";
}

int main (int argc, char *argv[]) {
  vector<Course> courseList = loadCoursesFromFile("machineRead.txt");
  std::regex coursePattern(R"([A-Z]{3}[0-9]{4}[A-Za-z]?)");
  std::regex depPattern(R"([A-Z]{3})");

  if (argc == 1){
      printHelp(argv[0]);
      return 1;
    }
  else if(argc < 3){
      notEnoughArguments();
      return 1;
  }

  string choice(argv[1]);

  if(!choice.compare("--course")){
      string searchQuery(argv[2]);
      if(!regex_search(searchQuery, coursePattern)){
        cout << "Invalid course code.\n";
        return 1;
      }
      for(Course c : courseList){
          if(!c.getCourseCode().compare(searchQuery.substr(0,3)))
            if(c.getCourseNumber().find(searchQuery.substr(3)) != string::npos)
              c.print();
        }
    }
  else if(!choice.compare("--name")){
      string searchQuery(argv[2]);

      for(Course c : courseList){
          if(c.getTitle().find(searchQuery) != string::npos)
            c.print();
        }
    }
  else if(!choice.compare("--prereq")){
      string searchQuery(argv[2]);

      for(Course c : courseList){
          if(c.getPrereq().find(searchQuery) != string::npos)
            c.print();
        }
    }
  else if(!choice.compare("--dep")){
      string searchQuery(argv[2]);
      if(!regex_search(searchQuery, depPattern)){
          cout << "Invalid course prefix.\n";
          return 1;
        }
      for(Course c : courseList){
          if(!c.getCourseCode().compare(searchQuery))
            c.print();
        }
    }
  else{
      cout << "Unknown command.\n";
    }
  return 0;
}
