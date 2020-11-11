/*
 * FEUPConsulting.cpp
 *
 *  Created on: 10/12/2017
 *      Author: CS
 */

#include "FEUPConsulting.h"

FEUPConsulting::FEUPConsulting(): expertizes(Expertize("", 0)) {
}

FEUPConsulting::FEUPConsulting(vector<Project*> projects): expertizes(Expertize("", 0)) {
	this->projects = projects;
}

void FEUPConsulting::addProjects(vector<Project*> projects) {
	this->projects = projects;
}

vector<Project*> FEUPConsulting::getProjects() const{
	return this->projects;
}


// get the expertize objet with the given name, including all students with the corresponding skills
Expertize FEUPConsulting::getExpertize(string name, unsigned cost) {
	Expertize itemNotFound("", 0);
	Expertize expertize(name, cost);
	Expertize search = expertizes.find(expertize);

	return search;
}


void FEUPConsulting::addProject(Project* project) {
	//TODO
	Expertize itemNotFound("", 0);
	Expertize expertize(project->getExpertize(), project->getCost());
	Expertize search = expertizes.find(expertize);

	if(search == itemNotFound) {
		this->expertizes.insert(expertize);
	}

	projects.push_back(project);
}

BST<Expertize> FEUPConsulting::getExpertizes() const {
	return this->expertizes;
}

void FEUPConsulting::addNewExpertize(const Expertize & expertize1) {
	this->expertizes.insert(expertize1);
}

vector<StudentPtr> FEUPConsulting::getStudents() const {
	vector<StudentPtr> ptrs;
	HashTabStudentPtr::const_iterator it1 = this->students.begin();
	HashTabStudentPtr::const_iterator it2 = this->students.end();
	for(; it1 != it2; it1++) {
			ptrs.push_back(*it1); //We can make it a bit more complex by considering only records with a condition!
	}
	return ptrs;
}

void FEUPConsulting::setStudents(vector<StudentPtr>& newStudents) {
	for(int i = 0; i < newStudents.size(); i++) students.insert(newStudents[i]);
}

priority_queue<Student> FEUPConsulting::getActiveStudents() const {
	return activeStudents;
}
void FEUPConsulting::setActiveStudents(priority_queue<Student>& students) {
	activeStudents = students;
}


//
// TODO: Part I   - BST
//

void FEUPConsulting::addAvailability(Student* student, string expertizeAvailable, unsigned cost) {
    BSTItrIn<Expertize> tree(expertizes);

    while(!tree.isAtEnd()){
        //Found expertize
        if (tree.retrieve().getName() == expertizeAvailable && tree.retrieve().getCost() == cost){
            Expertize e = tree.retrieve();
            expertizes.remove(e);
            vector<Student*> found = e.getConsultants();
            found.push_back(student);
            e.setConsultants(found);
            expertizes.insert(e);
            return;
        }
        tree.advance();
    }
    //No expertize found
    Expertize e(expertizeAvailable, cost);
    vector<Student*> vec = {student};
    e.setConsultants(vec);
    expertizes.insert(e);
}

vector<Student*> FEUPConsulting::getCandidateStudents(Project* project) const {
	vector<Student*> temp;
	BSTItrIn<Expertize> tree(expertizes);

	while (!tree.isAtEnd()){
        //Found right expertize
	    if (tree.retrieve().getName() == project->getExpertize() && tree.retrieve().getCost() == project->getCost()){
	        //Check expertize availability
	        for (auto stu:tree.retrieve().getConsultants()){
	            if (stu->getCurrentProject() == "") temp.push_back(stu);
	        }

	    }
	    tree.advance();
	}
	return temp;
}


bool FEUPConsulting::assignProjectToStudent(Project* project, Student* student) {
    BSTItrIn<Expertize> tree(expertizes);

    if (project->getConsultant() != NULL) return false;

    while (!tree.isAtEnd()){
        //Wanted expertize and cost
        if (tree.retrieve().getName() == project->getExpertize() && tree.retrieve().getCost() == project->getCost()){
            //Check available students
            for (auto stu:tree.retrieve().getConsultants()){
                if (stu->getEMail() == student->getEMail()){
                    if (stu->getCurrentProject() == ""){
                        stu->addProject(project->getTitle());
                        project->setConsultant(stu);
                        return true;
                    }
                }
            }
        }
        tree.advance();
    }
	return false;
}

//
// TODO: Part II  - Hash Table
//

void FEUPConsulting::addStudent(Student* student) {
    students.insert(student);
}

void FEUPConsulting::changeStudentEMail(Student* student, string newEMail) {
	students.erase(student);
	student->setEMail(newEMail);
	students.insert(student);
}


//
// TODO: Part III - Priority Queue
//

void FEUPConsulting::addActiveStudents(const vector<Student>& candidates, int min) {
    for (auto stu:candidates) if (stu.getPastProjects().size() >= min) activeStudents.push(stu);
}


int FEUPConsulting::mostActiveStudent(Student& studentMaximus) {
    priority_queue<Student> copy = activeStudents;
    if (copy.empty()) return 0;

    Student first = copy.top();
    copy.pop();
    Student second = copy.top();

    if (first.getPastProjects().size() == second.getPastProjects().size()) return 0;

    studentMaximus = first;

    return copy.size() + 1;

}





















