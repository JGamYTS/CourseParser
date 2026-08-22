#include "course.h"


std::string trim(const std::string& str)
{
  size_t first = str.find_first_not_of(' ');
  if (std::string::npos == first)
    {
      return str;
    }
  size_t last = str.find_last_not_of(' ');
  return str.substr(first, (last - first + 1));
}



// ---------------- MeetingTime ----------------

void MeetingTime::print(std::ostream& os) const {
  os << "    " << days << " | " << period
     << " (" << startTime << " - " << endTime << ")\n"
     << "    " << room;
  os << "\n";
}

// ---------------- FinalExam ----------------

void FinalExam::print(std::ostream& os) const {
  if (date.empty()) {
      os << "  (none scheduled)\n";
      return;
    }
  os << "  " << date << " @ " << startTime << " - " << endTime << "\n";
}

// ---------------- CourseSection ----------------

CourseSection::CourseSection(std::string classCode)
    : classCode_(std::move(classCode)){}

void CourseSection::addMeetingTime(const MeetingTime& mt) {
  meetingTimes_.push_back(mt);
}

void CourseSection::setInstructor(std::vector<std::string>& Instructors){
  instructor_ = std::move(Instructors);
}
void CourseSection::setCredits(int& credits){
  credits_ = std::move(credits);
}
void CourseSection::setDepartment(std::string& department){
  department_ = std::move(department);
}
void CourseSection::setMeetType(std::string& meetType){
  meetType_ = std::move(meetType);
}
void CourseSection::setWritingWords(int& writingWords){
  writingWords_ = std::move(writingWords);
}
void CourseSection::setFinalExam(FinalExam& finalExam){
  finalExam_ = std::move(finalExam);
}
void CourseSection::setClassStartDate(std::string& classStartDate){
  classStartDate_ = std::move(classStartDate);
}
void CourseSection::setClassEndDate(std::string& classEndDate){
  classEndDate_ = std::move(classEndDate);
}
void CourseSection::setMeetingTimes(std::vector<MeetingTime>& meetingTimes){
  meetingTimes_ = std::move(meetingTimes);
}

void CourseSection::setEEPEligible(){
  EEPEligible_ = true;
}

void CourseSection::print(std::ostream& os) const {

}

// ---------------- Course ----------------

Course::Course(std::string courseCode,
                std::string courseNumber,
                std::string title,
                std::string description,
                std::string prereq,
                std::vector<std::string> attributes)
    : courseCode_(std::move(courseCode)),
      courseNumber_(std::move(courseNumber)),
      title_(std::move(title)),
      description_(std::move(description)),
      prereq_(std::move(prereq)),
      attributes_(std::move(attributes)) {}

void Course::addSection(CourseSection& section) {
  sections_.push_back(section);
}

const CourseSection* Course::findSection(const std::string& classNumber) const {
  for (const auto& section : sections_) {
      if (section.getClassCode() == classNumber) {
          return &section;
        }
    }
  return nullptr;
}

void Course::addAttribute(const std::string& attribute){
  attributes_.push_back(attribute);
}

void Course::print(std::ostream& os) const {
  os << courseCode_ << courseNumber_ << " - " << title_ << "\n";
  os << description_ << "\n";
  if (!attributes_.empty()) {
      os << "Attributes: ";
      for (size_t i = 0; i < attributes_.size(); ++i) {
          os << attributes_[i] << (i + 1 < attributes_.size() ? ", " : "");
        }
      os << "\n";
    }
  if(!prereq_.empty()){
    os << prereq_ << "\n";
    }
  else{
    os << "Prereq: None" << "\n";
    }
  os << "----------------------------------------\n";
  for (const auto& section : sections_) {
      section.print(os);
      os << "----------------------------------------\n";
    }
}



// ---------------- loadCourseFromFile ----------------

std::vector<Course> loadCoursesFromFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
      throw std::runtime_error("Could not open course file: " + filename);
    }
  std::vector<Course> CourseOfferings;
         // Course-level fields

  std::vector<std::string> attributes;
  std::vector<CourseSection> sections;

         // Working state for the section currently being parsed
  std::string classCode, classNumber, instructor, department, meetType, classType;
  std::string classStartDate, classEndDate;
  int credits = 0;
  int writingWords = 0;
  bool eepEligible = false;
  FinalExam finalExam;

  int counter = 0;
  std::string rawLine;
  while (std::getline(file, rawLine) && rawLine.find("Have Questions? Contact Registrar") == std::string::npos) {
      if(rawLine.substr(0,6) == "      "){
          std::string courseCode, courseNumber, title, description, prereq;
          courseCode = rawLine.substr(6);
          std::getline(file, rawLine);
          courseNumber = rawLine;
          std::getline(file, rawLine);
          title = rawLine;
          std::stringstream ss;
          while (std::getline(file, rawLine)
                 && rawLine.find("Prereq:") == std::string::npos
                 && rawLine.find("Coreq: ") == std::string::npos
                 && rawLine.find("Class #") == std::string::npos) {
              ss << rawLine << " ";
          }
          description = ss.str();
          std::stringstream ss2;
          if (rawLine.find("Class #") == std::string::npos) {
              std::stringstream ss2;
              ss2 << rawLine << " ";
              while (std::getline(file, rawLine) && rawLine.find("Class #") == std::string::npos) {
                  ss2 << rawLine << " ";
                }
              prereq = ss2.str();
            } else {
              prereq.clear();  // no Prereq/Coreq field for this course
            }
          CourseOfferings.push_back(Course(courseCode, courseNumber, title, description, prereq));
          counter++;
        }
      /**
      else if(rawLine.find("Class #") != std::string::npos){
        classCode = rawLine.substr(7);
        CourseSection tempSection(classCode);
        std::getline(file, rawLine);
        std::vector<MeetingTime> meetings;
        while(rawLine.find("Additional Details") == std::string::npos){
          MeetingTime temp;
          temp.days = rawLine;
          std::getline(file, rawLine);
          temp.period = rawLine;
          std::getline(file, rawLine);
          temp.startTime = rawLine;
          std::getline(file, rawLine);
          temp.endTime = rawLine;
          std::getline(file, rawLine);
          temp.room = rawLine;
          std::getline(file, rawLine);
          meetings.push_back(temp);
        }
        tempSection.setMeetingTimes(meetings);
        while (std::getline(file, rawLine) && rawLine.find("Instructors") == std::string::npos){
            if(rawLine.find("EEP Eligible") != std::string::npos){
                tempSection.setEEPEligible();
              }
          }
      }
      **/
  }

  return CourseOfferings;
}

