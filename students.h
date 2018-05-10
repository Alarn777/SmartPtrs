//
// Created by Michael Rokitko on 20/04/2018.


#include <iostream>
#include <fstream>
#include "vector"
#include <string>
#include "smartPtr.h"
#ifndef INC_1_STUDENTS_H
#define INC_1_STUDENTS_H
using namespace std;
//
class Student{
public:
    Student();
    Student(string& fist_name, string& id, string& last_name, string& address,int& start_year);
    string& get_first_name() { return _fist_name;}
    string& get_last_name() { return _last_name;}
    string& get_student_id() { return _student_id;}
    string& get_address() { return _address;}
    int& get_starting_year() { return starting_year;}
    int& get_points() { return points;}
    int& get_excluded_year() { return excluded_year;}
    bool ifActiveNow() { return isActive;}
    void set_first_name(string& new_first_name) {_fist_name = new_first_name;}
    void set_last_name(string& new_last_name) {_last_name = new_last_name;}
    void set_id(string& new_id) {_student_id = new_id;}
    void set_address(string& new_address) {_address = new_address;}
    void set_starting_year(int& new_starting_year) {starting_year = new_starting_year;}
    void set_points(int& new_points) {points = new_points;}
    void add_points(int& new_points) {points += new_points;}
    void set_activity(bool& new_) { isActive = new_;}
    void set_excluded_year(int& new_excluded_year) {excluded_year = new_excluded_year;}
    void print();
    ~Student();
private:
    bool isActive;
    string _fist_name;
    string _last_name;
    string _student_id;
    string _address;
    int starting_year;
    int points;
    int excluded_year;
};


class course {
public:
    course();
    course(int& id);
    course(string& name_cource, int new_course_id, int new_course_value);
    string& get_course_name() { return course_name;}
    int& get_course_id() { return course_id;}
    int& get_course_value() { return course_value;}

    void set_course_name(string& new_course_name) {course_name = new_course_name;}
    void set_course_id(int id) { course_id = id;}
    void set_course_value(int& id) {course_value = id;}
    void add_student_to_cource(SmartPtr<Student>& Stud_);
    void give_student_points(string& _id);
    Student* find_stud_in_course(string& _id);
    void remove_student(string& _id);

    ~course();
private:

    string course_name;
    int course_id;
    int course_value;
    int student_count;
    vector<SmartPtr<Student>> students_in_course;
};

class department {
public:
    department();
    explicit department(string& dep_name);
    string& get_department_name() { return department_name;}
    void add_course_to_dep(course& new_course);

    void set_department_name(string& new_department_name) {department_name = new_department_name;}
    void add_stud_to_dep(SmartPtr<Student>& new_stud_in_dep);
    Student* find_student_in_dep(string& student_id);
    void remove_student(string& _id);
    void student_list();


    ~department();
private:
    string department_name;
    vector<SmartPtr<course>> courses_in_department;
    vector<SmartPtr<Student>> students_in_department;
};

class college {
public:
    college();
    explicit college(string& new_college_name);
    string& get_college_name() { return college_name;}
    course& get_courses_in_college() { return reinterpret_cast<course &>(courses_in_college);}
    void set_college_name(string& new_college_name) {college_name = new_college_name;}
    college& startcollege(fstream& initiation_file);
    void add_dep_to_colledge(SmartPtr<department>& new_department_name);
    void add_course_to_college(SmartPtr<course>& new_cource_name);
    void add_stud_to_college(SmartPtr<Student>& new_stud_in_coll);
    department* find_dep_in_college(string& dep_name);
    course* find_course_in_college(string& course_id);
    SmartPtr<Student>& find_student_in_college(string& student_id);
    void exclude_student(string& _id,string& _year);
    ~college();
private:
    string college_name;
    int department_count;
    int course_count;
    vector<SmartPtr<department>> departments_in_college;
    vector<SmartPtr<course>> courses_in_college;
    vector<SmartPtr<Student>> students_in_college;

};


#endif //INC_1_STUDENTS_H
