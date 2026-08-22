#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>


  struct MeetingTime {
    std::string days;       // e.g. "M,W"
    std::string period;     // e.g. "Period 4"
    std::string startTime;  // e.g. "10:40 AM"
    std::string endTime;    // e.g. "11:30 AM"
    std::string room;       // e.g. "0129"
    void print(std::ostream& os = std::cout) const;
  };

  struct FinalExam {
    std::string date;       // e.g. "12/8/2026"
    std::string startTime;  // e.g. "3:00 PM"
    std::string endTime;    // e.g. "5:00 PM"

    void print(std::ostream& os = std::cout) const;
  };

  class CourseSection {
  public:
    CourseSection() = default;

    CourseSection(std::string classCode);

           // --- Modifiers ---
    void addMeetingTime(const MeetingTime& mt);

           // --- Accessors ---
    const std::string& getClassCode() const { return classCode_; }
    std::vector<std::string>& getInstructor() {return instructor_;}
    int getCredits() { return credits_; }
    std::string& getDepartment()  { return department_; }
    const std::string& getMeetType()  { return meetType_; }
    int getWritingWords()  { return writingWords_; }
    FinalExam& getFinalExam()  { return finalExam_; }
    std::string& getClassStartDate()  { return classStartDate_; }
    std::string& getClassEndDate()  { return classEndDate_; }
    std::vector<MeetingTime>& getMeetingTimes()  { return meetingTimes_; }

           // --- Setters ---
    void setInstructor(std::vector<std::string>& Instructors);
    void setCredits(int& credits);
    void setDepartment(std::string& department);
    void setMeetType(std::string& meetType);
    void setWritingWords(int& writingWords);
    void setFinalExam(FinalExam& finalExam);
    void setClassStartDate(std::string& classStartDate);
    void setClassEndDate(std::string& classEndDate);
    void setMeetingTimes(std::vector<MeetingTime>& meetingTimes);
    void setEEPEligible();

    void print(std::ostream& os = std::cout) const;

  private:
    std::string classCode_;
    std::vector<MeetingTime> meetingTimes_;
    bool EEPEligible_ = false;
    double courseFees_ = 0;
    std::string genEd_;
    std::vector<std::string> instructor_;
    int credits_ = 0;
    std::string department_;
    std::string meetType_;
    int writingWords_ = 0;
    FinalExam finalExam_;
    std::string classStartDate_;
    std::string classEndDate_;

  };

  class Course {
  public:
    Course() = default;

    Course(std::string courseCode,
            std::string courseNumber,
            std::string title,
            std::string description,
            std::string prereq,
            std::vector<std::string> attributes = {});

           // --- Modifiers ---
    void addSection(const CourseSection& section);
    void addAttribute(const std::string& attribute);

           // --- Accessors ---
    const std::string& getCourseCode() const { return courseCode_; }
    const std::string& getCourseNumber() const { return courseNumber_; }
    const std::string& getTitle() const { return title_; }
    const std::string& getDescription() const { return description_; }
    const std::string& getPrereq() const { return prereq_; }
    const std::vector<std::string>& getAttributes() const { return attributes_; }
    const std::vector<CourseSection>& getSections() const { return sections_; }

           // Look up a section by its class number (e.g. "10053"); returns nullptr if not found
    const CourseSection* findSection(const std::string& classNumber) const;
    void addSection(CourseSection& section);


    void print(std::ostream& os = std::cout) const;

  private:
    std::string courseCode_;
    std::string courseNumber_;
    std::string title_;
    std::string description_;
    std::string prereq_;
    std::vector<std::string> attributes_;   // e.g. {"WR"}
    std::vector<CourseSection> sections_;
  };

  std::vector<Course>loadCoursesFromFile(const std::string& filename);

#endif // COURSE_H
