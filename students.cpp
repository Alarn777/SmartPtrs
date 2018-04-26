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

Student::~Student() {

}


//
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
void course::add_student_to_cource(Student *Stud_) {

    if (student_count < 100)
    {
        students_in_course[student_count] = Stud_;
        student_count++;
    } else
    {
        cerr << "Course is full, unable to add student." << endl;
    }
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
    for(int j = 0; students_in_course[j] && !found_;j++) {
        Student *temp_stud = students_in_course[j];
        if(temp_stud->get_student_id() == _id) {
            found_ = true;
            return students_in_course[j];
        }
    }
    return nullptr;
}

void course::remove_student(string &_id) {
    bool found_ = false;
    int found_num = -1;
    for(int j = 0; students_in_course[j] && !found_;j++) {
        Student *temp_stud = students_in_course[j];
        if(temp_stud->get_student_id() == _id) {
            found_ = true;
            found_num = j;
        }
    }
    if(found_)
    {
//        Student *temp_stud = students_in_course[found_num];
        students_in_course[found_num] = students_in_course[student_count];
        students_in_course[student_count] = nullptr;
        student_count--;
    }
}


department::department() {
    department_name = "";

}
//
department::department(string &dep_name) {
    department_name = dep_name;
    cources_count = 0;
    student_count = 0;
}

void department::add_course_to_dep(course& new_course) {
    if(cources_count < 100)
    {
        SmartPtr<course>new_course_smart = &new_course;
        courses_in_department[cources_count] = new_course_smart;
        cources_count++;
    }
    else
    {
        cerr << "Departmet is full, unable to add course." << endl;
    }



}

void department::add_stud_to_dep(Student* new_stud_in_dep) {
    if(student_count < 400)
    {
        SmartPtr<Student>new_stud_in_dep_smart = new_stud_in_dep;
        students_in_department[student_count] = new_stud_in_dep_smart;
        student_count++;
    }
    else
    {
        cerr << "Departmet is full, unable to add course." << endl;
    }
}

Student *department::find_student_in_dep(string &student_id) {
    bool found_ = false;
    for(int j = 0; students_in_department[j] && !found_;j++) {
        Student *temp_stud = students_in_department[j];
        if(temp_stud->get_student_id() == student_id) {
            found_ = true;
            return students_in_department[j];
        }
    }
    return nullptr;
}

void department::remove_student(string &_id) {
    bool found_ = false;
    int found_num = -1;
    for(int j = 0; students_in_department[j] && !found_;j++) {
        Student *temp_stud = students_in_department[j];
        if(temp_stud->get_student_id() == _id) {
            found_ = true;
            found_num = j;
        }
    }
    if(found_)
    {
//        Student *temp_stud = students_in_course[found_num];
        students_in_department[found_num] = students_in_department[student_count];
        students_in_department[student_count] = nullptr;
        student_count--;
    }
}

department::~department() = default;

college::college() {
    college_name = "";
    department_count = 0;
    course_count = 0;
    student_count = 0;
}



college::college(string &new_college_name){
    college_name = new_college_name;
    department_count = 0;
    course_count = 0;
    student_count = 0;
}

college &college::startcollege(fstream& initiation_file) {
    college *new_college = new college();
    char buffer[512];
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
//                    department new_(temp_tag);
                    auto *new_ = new department(temp_tag);
                    new_college->add_dep_to_colledge(*new_);
                    i++;
                    }while(buffer_[i]);
//                    for (i = 0 ;i < 3; i++) {
//                        department *temp = new_college.departments_in_college[i];
//                        cout << temp->get_department_name() << endl;
//                    }
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
                    auto *new_course = new course();
                    new_course->set_course_id(stoi(temp_tag));
                    i++;
                    new_college->add_course_to_college(*new_course);

                }while(buffer_[i]);
//                for (i = 0 ;i < 3; i++) {
//                    course *temp = new_college->courses_in_college[i];
//                    cout << temp->get_course_id() << endl;
//                }
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
//                    cout << course_num;
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

void college::add_dep_to_colledge(department &new_department_name) {
    if (department_count < 30)
    {
        SmartPtr<department> smart_dep = &new_department_name;
        departments_in_college[department_count] = smart_dep;
        department_count++;
    } else
    {
        cerr << "College is full, unable to add departments." << endl;
    }
}

void college::add_course_to_college(course& new_course_in_call) {
    if (course_count < 1000)
    {
        SmartPtr<course>smart_course = &new_course_in_call;
        courses_in_college[course_count] = smart_course;
        course_count++;
    } else
    {
        cerr << "College is full, unable to add departments." << endl;
    }
}

department *college::find_dep_in_college(string &dep_name) {
    bool found_dep = false;
    for(int j = 0; departments_in_college[j] && !found_dep;j++) {
        department *temp_dep = departments_in_college[j];
        if(temp_dep->get_department_name() == dep_name) {
            found_dep = true;
            return departments_in_college[j];
        }
    }
    return nullptr;
}

void college::add_stud_to_college(Student *new_stud) {
    if(student_count < 400)
    {
        SmartPtr<Student>new_stud_in_dep_smart = new_stud;
        students_in_college[student_count] = new_stud_in_dep_smart;
        student_count++;
    }
    else
    {
        cerr << "College is full, unable to add student." << endl;
    }
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

Student *college::find_student_in_college(string &student_id) {
    bool found_ = false;
    for(int j = 0; students_in_college[j] && !found_;j++) {
        Student *temp_course = students_in_college[j];
        if(temp_course->get_student_id() == student_id) {
            found_ = true;
            return students_in_college[j];
        }
    }
    return nullptr;
}

void college::exclude_student(string &_id,string& _year) {
    Student* temp_stud = find_student_in_college(_id);
    Student* temp_for_record = new Student(temp_stud->get_first_name(),temp_stud->get_student_id(),temp_stud->get_last_name(),temp_stud->get_address(),temp_stud->get_starting_year());
    bool found_ = false;
    for(int j = 0; students_in_college[j] && !found_;j++) {
        Student *temp_course = students_in_college[j];
        if(temp_course->get_student_id() == _id) {
            found_ = true;
            students_in_college[j] = nullptr;
            students_in_college[j] = temp_for_record;
        }
    }
    int i = 0;
    temp_stud = nullptr;
    temp_for_record->set_points(i);
    bool act = false;
    temp_for_record->set_activity(act);
    int year = stoi(_year);
    temp_for_record->set_excluded_year(year);

}


//
//
//
//}
