This project was compiled with Cmake and C++17. This project was made due to my issues with the UF Catalogue of courses and its antiquated systems. 

Course.h/.cpp contains class files for Courses/Classes(course sections)/Meeting Times. Also contains a function for reading in a list of courses from a formatted file.

Undergrad.txt is the unformatted download from the UF Schedule of Courses website because they refuse to give me a file containing them and I dont want to figure out the UF API. It is most likely incomplete as it ends around R and not Z. 

CourseFileFilter is a shell script to format Undergrad.txt into machineRead.txt and clearRead.txt, clearRead is mostly the same as machineRead with whitespace preserved to make it more legible.  

TODO:

Allow for searching by professors

Add recursive search to display a course and the full course listings of its pre-reqs

Change the storage of pre-reqs to a directed graph (delaying because of non-standard pre-req fields and non-class based pre-reqs)
