#include <StudentObject.h>

StudentObject::StudentObject(wxString name, wxString id, wxString roll_no, wxString className)
{
    this->name = name;
    this->id = id;
    this->roll_no = roll_no;
    this->className = className;
}
wxString StudentObject::getName(){
    return this->name;
}
wxString StudentObject::getId(){
    return this->id;
}
wxString StudentObject::getRollNo(){
    return this->roll_no;
}
wxString StudentObject::getClassName(){
    return this->className;
}
//setters
void StudentObject::setName(wxString &name){
    this->name = name;
}
void StudentObject::setId(wxString &id){
    this->id = id;
}
void StudentObject::setRollNo(wxString &roll_no){
    this->roll_no = roll_no;
}
void StudentObject::setClassName(wxString &className){
    this->className = className;
}