#include "smartPtr.h"
#include "students.h"
using namespace std;

void simulation_(fstream& sim_,college& new_college);
int main(int argc, char* argv[]) {
    college Shenkar;
    fstream initiator;
    fstream simulation;
    fstream outFile;
    initiator.open(argv[1]);
    if (!initiator.is_open())
        cout << "Error opening file" << endl;
    else
        Shenkar = Shenkar.startcollege(initiator);
    simulation.open(argv[2]);
    outFile.open(argv[3]);
    if (!simulation.is_open() || !outFile.is_open() )
        cout << "Error opening file" << endl;
    else
        simulation_(simulation,Shenkar,outFile);






    string buffer_;
    string name = "Dan";
    string lastname = "Cohen";
    string id = "111111111";
    string address = "Tel-Aviv Dereh-ha-shalom 120";



    return 0;

}



void simulation_(fstream& sim_,college& new_college,fstream& out_file){
    int decision = -1;
    char buffer[512];
    string buffer_;
    string temp_tag = "";
    int const menuEnd = 99;
    while(!sim_.eof()) {
        getline(sim_, buffer_);
        if (buffer_[0] == '#' || buffer_.empty())
            continue;
        temp_tag = "";
        for (int i = 0; i < buffer_.length(); i++) {
            while (buffer_[i] != ',' && buffer_[i] != '\n' && buffer_[i] != '\r' && buffer_[i] != '\0') {

                if (buffer_[i] != '\r' && buffer_[i] != '\n')
                    temp_tag += buffer_[i];
                i++;
            }
            i++;
            decision = stoi(temp_tag);
            switch (decision) {
                case 1: {
                    //1, name = Dan, Last name = cohen, id = 065899652, adress = Tel-Aviv Dereh-ha-shalom 120
                    for (temp_tag = "";buffer_[i] != ',' && buffer_[i] != '\n' && buffer_[i] != '\r' && buffer_[i] != '\0';i++ )
                    {
                        if (buffer_[i] != '\r' && buffer_[i] != '\n')
                            temp_tag += buffer_[i];
                    }
                    i++;
                    string name = temp_tag;

                    temp_tag = "";
                    for (temp_tag = "";buffer_[i] != ',' && buffer_[i] != '\n' && buffer_[i] != '\r' && buffer_[i] != '\0';i++ )
                    {
                        if (buffer_[i] != '\r' && buffer_[i] != '\n')
                            temp_tag += buffer_[i];
                    }
                    i++;
                    string last_name = temp_tag;
                    for (temp_tag = "";buffer_[i] != ',' && buffer_[i] != '\n' && buffer_[i] != '\r' && buffer_[i] != '\0';i++ )
                    {
                        if (buffer_[i] != '\r' && buffer_[i] != '\n')
                            temp_tag += buffer_[i];
                    }
                    i++;
                    string id_temp = temp_tag;
                    for (temp_tag = "";buffer_[i] != ',' && buffer_[i] != '\n' && buffer_[i] != '\r' && buffer_[i] != '\0';i++ )
                    {
                        if (buffer_[i] != '\r' && buffer_[i] != '\n')
                            temp_tag += buffer_[i];
                    }
                    i++;
                    string temp_address = temp_tag;
                    for (temp_tag = "";buffer_[i] != ',' && buffer_[i] != '\n' && buffer_[i] != '\r' && buffer_[i] != '\0';i++ )
                    {
                        if (buffer_[i] != '\r' && buffer_[i] != '\n')
                            temp_tag += buffer_[i];
                    }
                    i++;
                    int year_ = stoi(temp_tag);
                    for (temp_tag = "";buffer_[i] != ',' && buffer_[i] != '\n' && buffer_[i] != '\r' && buffer_[i] != '\0';i++ )
                    {
                        if (buffer_[i] != '\r' && buffer_[i] != '\n')
                            temp_tag += buffer_[i];
                    }
                    i++;
                    department *dep_ = new_college.find_dep_in_college(temp_tag);
                    auto *new_student = new Student(name, id_temp, last_name, temp_address, year_);
                    dep_->add_stud_to_dep(new_student);
                    new_college.add_stud_to_college(new_student);
                    cout << "Student was added" << endl;
                    break;

                }
                case 2: {
                    for (temp_tag = "";buffer_[i] != ',' && buffer_[i] != '\n' && buffer_[i] != '\r' && buffer_[i] != '\0';i++ )
                    {
                        if (buffer_[i] != '\r' && buffer_[i] != '\n')
                            temp_tag += buffer_[i];
                    }
                    i++;
                    string id = temp_tag;
                    temp_tag = "";
                    for (temp_tag = "";buffer_[i] != ',' && buffer_[i] != '\n' && buffer_[i] != '\r' && buffer_[i] != '\0';i++ )
                    {
                        if (buffer_[i] != '\r' && buffer_[i] != '\n')
                            temp_tag += buffer_[i];
                    }
                    i++;
                    string course_code = temp_tag;
                    course* temp_course = new_college.find_course_in_college(course_code);
                    Student* temp_student = new_college.find_student_in_college(id);
                    temp_course->add_student_to_cource(temp_student);
                    cout << "Student " << id <<  " was added to course " << course_code << endl;
                    break;
                }

                case 3: {
                    for (temp_tag = "";buffer_[i] != ',' && buffer_[i] != '\n' && buffer_[i] != '\r' && buffer_[i] != '\0';i++ )
                    {
                        if (buffer_[i] != '\r' && buffer_[i] != '\n')
                            temp_tag += buffer_[i];
                    }
                    i++;
                    string id = temp_tag;
                    temp_tag = "";
                    for (temp_tag = "";buffer_[i] != ',' && buffer_[i] != '\n' && buffer_[i] != '\r' && buffer_[i] != '\0';i++ )
                    {
                        if (buffer_[i] != '\r' && buffer_[i] != '\n')
                            temp_tag += buffer_[i];
                    }
                    i++;
                    string course_code = temp_tag;
                    course* temp_course = new_college.find_course_in_college(course_code);
                    temp_course->give_student_points(id);
                    break;
                }
                case 4: {
                    for (temp_tag = "";buffer_[i] != ',' && buffer_[i] != '\n' && buffer_[i] != '\r' && buffer_[i] != '\0';i++ )
                    {
                        if (buffer_[i] != '\r' && buffer_[i] != '\n')
                            temp_tag += buffer_[i];
                    }
                    i++;
                    string id = temp_tag;
                    temp_tag = "";
                    for (temp_tag = "";buffer_[i] != ',' && buffer_[i] != '\n' && buffer_[i] != '\r' && buffer_[i] != '\0';i++ )
                    {
                        if (buffer_[i] != '\r' && buffer_[i] != '\n')
                            temp_tag += buffer_[i];
                    }
                    i++;
                    string year_excluded = temp_tag;
                    new_college.exclude_student(id,year_excluded);
                    cout << "Student " << id <<  " was excluded in year " << year_excluded << endl;

//                    Student* a = new_college.find_student_in_college(id);
//                    cout << a->get_excluded_year() << " " << a->get_points();
                    break;
                }
                case 5: {


                    break;
                }

                case 99: {

                    cout << "Good bye!" << endl;
                    break;
                }
                default:
                    cout << "Good bye!" << endl;
                    break;

            }


        }
    }
}