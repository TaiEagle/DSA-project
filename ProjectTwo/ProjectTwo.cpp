
/**
 * Author: Dakota Osborne
 * Date: 02/17/2026
 * This program takes a file as input, loads the courses from the file and puts them
 * into a binary tree data structure, prints a sorted list of the courses, and allows the user
 * to search and print a specific course.
 *
 * */
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;


struct Course{
	string code;
	string name;
	vector<string> pre;

	//Default constructor
	Course(){


	}

	Course(string aCode, string aName, vector<string> aPre){
		code = aCode;
		name = aName;
		pre = aPre;

	}

};

struct  Node{
	Course course;
	Node* leftNode;
	Node* rightNode;

	//Default constructor
	Node(){
		leftNode = nullptr;
		rightNode = nullptr;
	}
	Node(Course acourse): Node(){
		course = acourse;

	}

};



class BSTCourse{

	private:
	Node* root;
	void addNode(Node* node, Course course);
	void inOrder(Node* node);
	void printCourse(Course course);
	public:
	BSTCourse();

	virtual ~BSTCourse();
	void DelAll(Node* currNode);
	void Menu(BSTCourse tree);
	void LoadCourses(string file);
	void Insert(Course course);

	void PrintAll();
	void Search(Node*& node, Node*& nodeParent, string code);
	bool CodesSearch(vector<string> codes, vector<string> pre);
	void PrintCourse(string code);
};

	//constructor
	BSTCourse::BSTCourse(){
		root = nullptr;
	}

	/*
	 * This method is used for the destructor
	 * Parameter Node pointer
	 * returns nothing
	 * **/
	void BSTCourse::DelAll(Node* currNode){

		if(currNode == nullptr){
				return;
			}
			if(currNode->leftNode != nullptr){
				DelAll(currNode->leftNode);
			}
			if(currNode->rightNode != nullptr){
				DelAll(currNode->rightNode);
			}
			delete currNode;

	}
	/*
	 * destructor
	 * **/
	BSTCourse::~BSTCourse(){
		// recurse from root deleting every node
			DelAll(this->root);
	}

	/*
	 * This method inserts a node in the binary tree if the root is not null
	 * Parameter: Node pointer, Course object
	 * returns nothing
	 *
	 * **/
	void BSTCourse::addNode(Node* node, Course course){
		// if node is larger then add to left
			if(node->course.code > course.code){
				// if no left node
				if(node->leftNode == nullptr){
					// this node becomes left
					node->leftNode = new Node(course);
					return;
				}
				// else recurse down the left node
				addNode(node->leftNode, course);

			}


		    // else
			else{
		        // if no right node
				if(node->rightNode == nullptr){
					// this node becomes right
					node->rightNode = new Node(course);
					return;
				}

		        //else
				else{
		            // recurse down the left node
					addNode(node->rightNode, course);
				}
			}
	}



	/*
	 * this method inserts a course object into the binary tree
	 * Parameter: Course object
	 * returns nothing
	 *
	 * **/
	void BSTCourse::Insert(Course course){

		    // FIXME (6a) Implement inserting a bid into the tree
		    // if root equarl to null ptr
			if(this->root == nullptr){
				// root is equal to new node bid
				this->root = new Node(course);
			}

		    // else
			else{
		      // add Node root and bid
				this->addNode(this->root, course);
			}
		}



	/*
	 * this method is used for the pre requisit validation search
	 * Parameter: vector with strings and vector with strings
	 * returns a boolean value
	 * **/
	bool BSTCourse::CodesSearch(vector<string> codes, vector<string> pre){
		int codeCount = 0;
		int i;
		int r;
		int preSize = pre.size();
		int codeSize = codes.size();
		for(i = 0; i < preSize; ++i){//for every element in pre vector
			for(r = 0;  r < codeSize; ++r){//for every element in codes vector
				if(pre.at(i).compare(codes.at(r))  == 0){//comapre the codes
					++codeCount;//if they are the same increase count and move on to the next code in pre
					break;
				}
			}
		}

		if(codeCount == preSize){
			return true;
		}
		else{
			return false;
		}

	}
	/**
	 * This method loads the bids from the provided file and puts it into the Tree data structure
	 *Parameter 1: string
	 * returns nothing
	 * */
	void BSTCourse::LoadCourses(string file){

		string line;
		string line2;
		char del = ',';

		string temp;
		string name;
		string code;
		int i;
		int numCourses = 0;
		vector<string> codes;


		try{
			ifstream File; //file object
			File.open(file);// open file
			//if file is not open throw exception
			if(File.is_open() == 0){

				throw invalid_argument("File did not open");
			}


			//get list of codes
			while(getline(File, line)){

				code = line.substr(0, line.find(","));//Get code sub string

				codes.push_back(code);//add substring to the vector
				++numCourses;
			}
			File.close();//reset file buffer

			//reopen file
			File.open(file);
			//if file is not open throw exception
			if(File.is_open() == 0){
				throw invalid_argument("File did not open");
						}




			//get course objects
			while(getline(File, line)){//for each line in the file while there is a line left

				vector<string> lineVec;
				stringstream line2(line);
				//string split by ","
				while(getline(line2, temp, del)){//for each sub string in line partitioned by ","
					lineVec.push_back(temp);
				}
				//create course object
				Course course = Course();
				//set course code
				course.code = lineVec.at(0);
				//set course name
				course.name = lineVec.at(1);
				//set course pre vector
				int size = lineVec.size();
				if(lineVec.size() > 1){//if pre requisits exist
				for(i = 2; i < size; ++i){
					if(lineVec.at(i) != "")//for edge case ",,"
						course.pre.push_back(lineVec.at(i));
				}
				}
				//pre requisit validation
				if(this->CodesSearch(codes, course.pre) == true){
					//insert into tree
					Insert(course);

				}
				else{
					//do not insert
				}
			}




			//free resources
			File.close();
			//throw invalid_argument;
		} catch(invalid_argument badFile){
			cout << "File did not open properly." << endl;
		}

		cout << "Courses read: " << numCourses << endl;

	}

	/*
	 * this method prints the courses in order
	 *Parameters: Node pointer
	 *Parameters: returns nothing
	 * **/
	void BSTCourse::inOrder(Node* node){

		int i;
		if(node == nullptr){
			return;
		}
		inOrder(node->leftNode);
		cout << "CODE: " << node->course.code << " NAME: "<< node->course.name << " PRE-REQUISITS: ";
		if(node->course.pre.size() > 0){//if the vector is not empty
			for(i = 0; i < node->course.pre.size(); ++i){
					if(i == node->course.pre.size() -1){ //last one in list
						cout << node->course.pre.at(i) << endl;
					}
					else{
						cout << node->course.pre.at(i) << ", ";
					}

			}
		}
		else{
			cout << "None" << endl;

		}
		inOrder(node->rightNode);
	}


	/**
	 * This method prints every course in a sorted structure
	 *Parameters:
	 * returns nothing
	 * */
	void BSTCourse::PrintAll(){
		this->inOrder(this->root);

	}


	/**
	 * This method searches the Binary Search tree
	 *Parameter: Node pointer reference, Node pointer reference, string
	 * returns a course object
	 * */

	void BSTCourse::Search(Node*& node, Node*& nodeParent, string code){
		if(node == nullptr){
			cout << "Course not found" << endl;
				return;
			}
			//If node is a match
			if(node->course.code == code){
				printCourse(node->course);
				 return;
			}
			// else
			nodeParent = node;
			//Traverse left
			if(code < node->course.code){
				node = node->leftNode;
				Search(node, nodeParent, code);
			}
			//Traverse right
			else{
				node = node->rightNode;
				Search(node, nodeParent, code);
			}
	}
	/**
	 * this method prints a course
	 * Parameter: Course object
	 * returns nothing
	 * */
	void BSTCourse::printCourse(Course course){
		int i;
		int size = course.pre.size();
		cout << "CODE: " << course.code << " NAME: "<< course.name << " PRE_REQUISITS: ";
		if(size > 0){//if the vector is not empty
			for(i = 0; i < size; ++i){
				if(i == size -1){ //last one in list
					cout << course.pre.at(i) << endl;
				}
				else{
					cout << course.pre.at(i) << ", ";
					}
					}
		}
		else{
			cout << "None" << endl;
		}
	}



	/*
	 *This method searches the BST to find the given course and prints the courses information
	 *Parameter: string
	 *returns nothing
	 * **/

	void BSTCourse::PrintCourse(string code){
		Node* currNode = this->root;//set search parameters
		Node* nodeParent = nullptr;//set search parameters

		this->Search(currNode, nodeParent, code); // search for matching course
	}

	/*
	 *This method is the user interface
	 *Parameter: BSTCourse object
	 *returns nothing
	 * **/
	void BSTCourse::Menu(BSTCourse tree){
		int userChoice;
		//string file = "CS 300 ABCU_Advising_Program_Input.csv";
		string file;
		string code;
		string testCode = "CSCI301";
		string cinBuffEmpty;

		while(userChoice != 9){

			//User options
			cout<< "1 Load data from the file" << endl;
			cout<< "2. Print ordered list of all courses" << endl;
			cout<< "3. Print course details for a specified course" << endl;
			cout<< "9. Exit" <<endl;
			cin >> userChoice;
			//incase of cin buffer issue
			if(cin.fail()){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			switch(userChoice){
				case 1:


					cout << "Enter full path of the file name: " ;
					try{
					getline(cin, cinBuffEmpty); //empty cin buffer
					getline(cin, file); //get file name

					}catch(exception e){
						cout<< "cin fail " << endl;
					}


					tree.LoadCourses(file);
					//cin.clear();
					break;
				case 2:
					tree.PrintAll();
					break;
				case 3:
					cout << "Enter a course to print: ";
					try{
					getline(cin, cinBuffEmpty);//empty cin buffer
					getline(cin, code);//get code to search for
					}catch(exception e){
						cout<< "cin fail " << endl;
					}
					tree.PrintCourse(code);
					break;
				case 9:
					break;
				default:
					cout<<"Enter a valid option." << endl;
					break;


			}
		}

	}



	int main(){
		//create class object
		BSTCourse courses = BSTCourse();

		//run user interface
		courses.Menu(courses);


		return 0;
	}







