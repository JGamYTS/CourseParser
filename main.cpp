#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "course.h"

using namespace std;

int
main ()
{
  vector<Course> Temp = loadCoursesFromFile("Undergrad.txt");
  while(true){
    string search = "";
    cin >> search;
    search.insert(3, " ");
    cout << "Courses which require " << search << ":\n\n";
    for(auto course : Temp){
        if(course.getPrereq().find(search) != string::npos)
          course.print();

      }
    search = "";
    }
  return 0;
}
