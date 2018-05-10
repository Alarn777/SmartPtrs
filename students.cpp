////
//// Created by Michael Rokitko on 20/04/2018.
////
#include "students.h"
Student::Student(){
    _fist_name = "";
    _last_name = "";
    _address = "";
    _student_id = "";
    starting_year = 0;
    excluded_year = 0;
    points = 0;
    isActive = true;
}
Student::Student(string& fist_name, string& id, string& last_name, string& address,int& start_year) {
     _fist_name = fist_name;
     _last_name = last_name;
     _address = address;
    _student_id = id;
    starting_year = start_year;
    excluded_year = 0;
    points = 0;
    isActive = true;
}

void Student::print() {
    cout << "----------------------------" << endl;
    cout << "ID:" << _student_id << endl;
    cout << "First Name:" << _fist_name << endl;
    cout << "Last Name:" << _last_name << endl;
    cout << "Address:" << _address << endl;
    cout << "Year Started:" << starting_year << endl;
    cout << "Current Points:" << points << endl;
    if(!isActive)
        cout << "Excluded Year:" << excluded_year << endl;
    cout << "----------------------------" << endl;
}

Student::~Student() {

}

course::course(int &id) {
    course_id = id;
    course_value = 0;
    course_name = "";
}


course::course(string& name_cource, int new_course_id, int new_course_value)
{
    course_name = name_cource;
    course_id = new_course_id;
    course_value = new_course_value;
    student_count = 0;
}

course::course()
{
    course_name = "";
    course_id = 0;
    course_value = 0;
    student_count = 0;
}
void course::add_student_to_cource(SmartPtr<Student>& Stud_) {
        students_in_course.push_back(Stud_);
}

void course::give_student_points(string &_id) {
        Student* temp_stud = find_stud_in_course(_id);
        if(temp_stud)
            temp_stud->add_points(course_value);
        else
            cout << "No student to add to" << endl;
}






course::~course() {}

Student *course::find_stud_in_course(string &_id) {
    bool found_ = false;
    for (auto i = students_in_course.begin(); i != students_in_course.end() && !found_; i++) {
        Student *temp_ = *i;
        if (temp_->get_student_id() == _id) {
            found_ = true;
            return *i;
        }
    }
    return nullptr;
}

void course::remove_student(string &_id) {
    bool found_ = false;
    auto i = students_in_course.begin();
    for (; i != students_in_course.end() && !found_; i++) {
        Student *temp_ = *i;
        if (temp_->get_student_id() == _id) {
            found_ = true;
        }
    }
    if(found_)
    {
        --i;
        students_in_course.erase(i);
    }
}




department::department() {
    department_name = "";

}
//
department::department(string &dep_name) {
    department_name = dep_name;

}

void department::add_course_to_dep(course& new_course) {

    SmartPtr<course> *new_course_smart;
    new_course_smart = new SmartPtr<course>(&new_course);
    courses_in_department.push_back(*new_course_smart);
}

void department::add_stud_to_dep(SmartPtr<Student>& new_stud_in_dep) {
//    SmartPtr<Student> *new_stud_in_dep_smart;
//    new_stud_in_dep_smart = new  SmartPtr<Student>(new_stud_in_dep);
    students_in_department.push_back(new_stud_in_dep);

}

Student *department::find_student_in_dep(string &student_id) {
    bool found_ = false;
    for (auto i = students_in_department.begin(); i != students_in_department.end() && !found_; i++) {
        Student *temp_ = *i;
        if (temp_->get_student_id() == student_id) {
            found_ = true;
            return *i;
        }
    }
    return nullptr;
}

void department::remove_student(string &_id) {
    bool found_ = false;
    auto i = students_in_department.begin();
    for (; i != students_in_department.end() && !found_; i++) {
        Student *temp_ = *i;
        if (temp_->get_student_id() == _id) {
            found_ = true;
        }
    }
    if(found_)
    {
        --i;
        students_in_department.erase(i);

    }
}

void department::student_list() {
    auto i = students_in_department.begin();
    for (; i != students_in_department.end(); i++) {
        Student *temp_ = *i;
        temp_->print();
    }
}

department::~department() = default;

college::college() {
    college_name = "";
    department_count = 0;
    course_count = 0;
}



college::college(string &new_college_name){
    college_name = new_college_name;
    department_count = 0;
    course_count = 0;
}

college &college::startcollege(fstream& initiation_file) {
    college *new_college = new college();
    string buffer_;
    while(!initiation_file.eof())
    {
        getline(initiation_file, buffer_);
        if(buffer_[0] == '#' || buffer_.empty())
            continue;

        for(int i = 0; i< buffer_.length();i++)
        {
            string temp_tag;
            while(buffer_[i] != ':' && buffer_[i] != '\0' && buffer_[i] != '\r') {
                temp_tag += buffer_[i];
                i++;
            }
            if(temp_tag == "College") {
                temp_tag = "";
                i++;
                do {
                    if(buffer_[i] != '\r' && buffer_[i] != '\n')
                        temp_tag += buffer_[i];
                    i++;
                } while (buffer_[i]);
                new_college->set_college_name(temp_tag);
            }
            if(temp_tag == "Departments")
            {
                temp_tag = "";
                i++;
                do {
                    temp_tag = "";
                    while(buffer_[i] != ',' && buffer_[i] != '\n' && buffer_[i] != '\r' && buffer_[i] != '\0')
                    {

                        if (buffer_[i] != '\r' && buffer_[i] != '\n')
                            temp_tag += buffer_[i];
                        i++;
                    }

                    SmartPtr<department> dep_temp = new department(temp_tag);
                    new_college->add_dep_to_colledge(dep_temp);
                    i++;
                    }while(buffer_[i]);

            }
            if(temp_tag == "UniversityCoursesList")
            {

                temp_tag = "";
                i++;
                do {
                    temp_tag = "";
                    while(buffer_[i] != ',' && buffer_[i] != '\n' && buffer_[i] != '\r' && buffer_[i] != '\0')
                    {

                        if (buffer_[i] != '\r' && buffer_[i] != '\n')
                            temp_tag += buffer_[i];
                        i++;
                    }
                   int id_ =  stoi(temp_tag);
                    SmartPtr<course> new_course = new course(id_);
                    i++;
                    new_college->add_course_to_college(new_course);

                }while(buffer_[i]);

            }
            if(temp_tag == "CourseDetails")
            {
                i++;
                temp_tag = "";
                while(buffer_[i] != ',' && buffer_[i] != '\n' && buffer_[i] != '\r' && buffer_[i] != '\0')
                {

                    if (buffer_[i] != '\r' && buffer_[i] != '\n')
                        temp_tag += buffer_[i];
                    i++;
                }
                string depToAddTo = temp_tag;
                bool found_dep = false;
                int depIndex = -1;
                for(int j = 0; new_college->departments_in_college[j] && !found_dep;j++) {
                    department *temp_dep = new_college->departments_in_college[j];
                    if(temp_dep->get_department_name() == depToAddTo) {
                        depIndex = j;
                        found_dep = true;
                    }
                }
                if(found_dep)
                {
                    i++;
                    temp_tag = "";
                    while(buffer_[i] != ',' && buffer_[i] != '\n' && buffer_[i] != '\r' && buffer_[i] != '\0')
                    {

                        if (buffer_[i] != '\r' && buffer_[i] != '\n')
                            temp_tag += buffer_[i];
                        i++;
                    }
                    string course_num = temp_tag;
                    i++;
                    temp_tag = "";
                    while(buffer_[i] != ',' && buffer_[i] != '\n' && buffer_[i] != '\r' && buffer_[i] != '\0')
                    {

                        if (buffer_[i] != '\r' && buffer_[i] != '\n')
                            temp_tag += buffer_[i];
                        i++;
                    }
                    int course_value = stoi(temp_tag);

                    i++;
                    temp_tag = "";
                    while(buffer_[i] != ',' && buffer_[i] != '\n' && buffer_[i] != '\r' && buffer_[i] != '\0')
                    {

                        if (buffer_[i] != '\r' && buffer_[i] != '\n')
                            temp_tag += buffer_[i];
                        i++;
                    }
                    string course_name = temp_tag;
                    for(int j = 0; new_college->courses_in_college[j];j++) {
                        course *temp_course = new_college->courses_in_college[j];
                        if (temp_course->get_course_id() == stoi(course_num)) {
                            temp_course->set_course_name(course_name);
                            temp_course->set_course_value(course_value);
                        }
                    }
                }
            }
        }
    }
    cout << "College was added successfully" << endl;
    return *new_college;
}



college::~college() {

}

void college::add_dep_to_colledge(SmartPtr<department> &new_department_name) {
        departments_in_college.push_back(new_department_name);
}

void college::add_course_to_college(SmartPtr<course>& new_cource_name){

        courses_in_college.push_back(new_cource_name);
}

department *college::find_dep_in_college(string &dep_name) {
    bool found_ = false;
    for (auto i = departments_in_college.begin(); i != departments_in_college.end() && !found_; i++) {
        department *temp_dep = *i;
        if (temp_dep->get_department_name() == dep_name) {
            found_ = true;
            return *i;
        }
    }
    return nullptr;
}

void college::add_stud_to_college(SmartPtr<Student>& new_stud_in_coll) {

    students_in_college.push_back(new_stud_in_coll);
}

course *college::find_course_in_college(string &course_id) {
    bool found_ = false;
    for(int j = 0; courses_in_college[j] && !found_;j++) {
        course *temp_course = courses_in_college[j];
        if(temp_course->get_course_id() == stoi(course_id)) {
            found_ = true;
            return courses_in_college[j];
        }
    }
    return nullptr;
}

SmartPtr<Student>& college::find_student_in_college(string &student_id) {
    bool found_ = false;
    for (auto i = students_in_college.begin(); i != students_in_college.end() && !found_; i++) {
        Student *temp_ = *i;
        if (temp_->get_student_id() == student_id) {
            found_ = true;
            return *i;
        }
    }
    SmartPtr<Student> temp = nullptr;
    return temp;
}


void college::exclude_student(string &_id,string& _year) {
    Student* temp_stud = find_student_in_college(_id);
    int foundIndex = -1;
    bool found_ = false;
    for (auto &i : departments_in_college) {
        department *temp_ = i;
        temp_->remove_student(_id);
    }
    for(auto &i : courses_in_college) {
        course* temp_course = i;
        temp_course->remove_student(_id);
    }
    int year = stoi(_year);
    temp_stud->set_excluded_year(year);
    bool activity = false;
    temp_stud->set_activity(activity);
}


