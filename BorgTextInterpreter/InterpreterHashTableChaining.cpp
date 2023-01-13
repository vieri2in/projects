//Course: Data Structure
//location: IVC
//Time: fall 2022

//Task Description:
//Build a hash table using chaining as the collision resolution technique.
//Insertions into the hash table will correspond to declarations of variablesand values in a program, 
//searches will be requests for the value of a variable.
//Some variables will be local and have a narrow scope while some variables will be global.

//Acknowledgement:
//Prof. Cuevas taught me how to control the scope of local and global variables
//by introducing the scope attribute to each node and manipulating it when entering or leaving an inner scope. 
//That is, increment the scope value when entering an inner scope, while poping out all variables with this scope value and
//decrementing the the scope value when leaving the inner scope.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;
//set the size of 2 purposely to creat collision and make the task more challenging
const int SIZE = 2;
const int EMPTY = -999;

class Node{
public: 
	string variableName;
    int value;
	int scope;//introduce this attribute to control variable scopes
    Node* next;
    Node(string name, int scopeInput, int valueInput = EMPTY, Node* ptr = 0){
		variableName = name;
		scope = scopeInput;
		value = valueInput;
        next = ptr;
    }
};

class List{
private:
    Node* head, *tail;
public:  
    List(){
        head = 0;
        tail = 0;
    }
	void decalreVarToHead(string varName, int scope){
		Node* temp = new Node(varName, scope);
		if (isEmpty()) {
			head = tail = temp;
		}
		else{
			temp->next = head;
          	head = temp;
		}	   
	}
	//assign an value to the variable
	void assignValue(string varName, int value){
		for (Node* current = head;
		     current != 0;
		     current = current->next){
				if (current->variableName == varName){
					current->value = value;
					return;
				}
		}
	}
	int lookup(string varName){
		int returnData = EMPTY;
		for (Node* current = head;
		     current != 0;
		     current = current->next){
				if (current->variableName == varName){
					returnData = current->value;
				}
		}
		return returnData;
	}	
	void  deleteFromHead(int scopeInput) {
		if (isEmpty()||head->scope != scopeInput){
			return;
		}
		while(head->scope == scopeInput && !isEmpty() ){
			Node *tmp = head;	
			if (head == tail)		
				head = tail = 0;	
			else 
				head = head->next;
			delete tmp;		
		}					
	}		
    bool isEmpty() {
        return head == 0;
    }
    void printList(){
        for (Node* current = head; current != 0; current = current->next){
			if (current != 0){
				cout << current->variableName;
				cout << "(scope = " << current->scope << ") ";
            	cout << "(value = " << current->value << ") ";  
        	}
		}
        cout << endl;
    }
};

class HashTableChaining{
private:
    List* lists;
public:  
    HashTableChaining(){
		lists = new List[SIZE]; 
    }
	int hash(string input) {
		int lengh = input.length();
		int total = 0;
		for (int i = 0; i < lengh; i++){
			char ch = input[i];
			total += (int)ch * (i + 1);
		}
		return total % SIZE;
	}
    void insertVar(string label, int scope){
		int index = hash(label);
		lists[index].decalreVarToHead(label, scope);
    }
	void assignVar(string label, int value){
		int index = hash(label);
		lists[index].assignValue(label, value);			
	}
	void pop(int scope){
		for (int i = 0; i < SIZE; i++){
			lists[i].deleteFromHead(scope);
		}
	}
	int search(string label){
		int index = hash(label);
		return lists[index].lookup(label);
	}
    void printHashTable(){
        for (int i = 0; i < SIZE; i++){
			if (!lists[i].isEmpty()){
				cout << "Index:" << i << " ";
				lists[i].printList();
			}
        }
    }
};
int arithOperate(int a, int b, char opr){
	int result;
	switch (opr){
				case '+':
				result =  a + b;
				break;
				case '-':
				result =  a - b;
				break;
				case '*':
				result = a * b;
				break;
				case '/':
				result =  a / b;
				break;
				case '%':
				result =  a % b;
				break;					
				case '^':
				result =  pow(a, b);
				break;
			}
	return result;		
};
int main() {
	//open file
	ifstream myfile("borg.txt");
	string line;
	//check file open
	if(!myfile.is_open()){
		cout << "File fails to open." << endl;
		return 0;
	}
	int scopeLevel = 0;
	HashTableChaining* interpreter = new HashTableChaining();
	while(getline(myfile, line)){
		stringstream parts(line);
		string part1;
		parts >> part1;
		//COM
		if(part1 == "COM"){
			continue;
		}
		//START
		if(part1 == "START"){
			scopeLevel++;//increment the scope value when entering an inner scope
		}
		//VAR declaration & assignment
		if (part1 == "VAR"){
			string part2;
			parts >> part2;
			interpreter->insertVar(part2, scopeLevel);
			//assignment
			string part3, part4;
			parts >> part3 >> part4;
			if (part3 == "="){
				int data = atof(part4.c_str());
				interpreter->assignVar(part2, data);
			}
		}
		//PRINT
		if(part1 == "PRINT"){
			string part2;
			parts >> part2;
			string part3, part4;
			parts >> part3 >> part4;
			//invalid print operation
			if(interpreter->search(part2) == EMPTY){
				cout << part2 << " IS UNDEFINED" << endl;
			}
			//print an arithmetic expression
			//supported operators : +-/ *%^(plus, minus, divide, multiple, modulo, exponent)
			else if(part3 != "" && part4 != ""){
				int result;
				int operand1 = interpreter->search(part2);
				int operand2 = atof(part4.c_str());
				result = arithOperate(operand1, operand2, part3[0]);
				cout << part2 << " " << part3 << " " << part4 << " IS "<< result << endl;
			}
			//print a variable
			else{
				cout << part2 <<" IS " << interpreter->search(part2) << endl;
			}
		}			
		//FINISH
		if(part1 == "FINISH"){
			//poping out all variables with this scope value
			interpreter->pop(scopeLevel);
			//decrementing the the scope value when leaving the inner scope
			scopeLevel--;			     
		}
		//VARIABLE ++ -- = (i.e., increment, decrement, or reassignment operations)
		if( (part1 != "COM" || part1 != "START" || part1 != "VAR" || part1 != "PRINT" || part1 != "FINISH")
			&& interpreter->search(part1) != EMPTY ){
				string part2;
				parts >> part2;
				int newValue;
				if(part2 == "++"){
					newValue = interpreter->search(part1) + 1;
				}
				if (part2 == "--"){
					newValue = interpreter->search(part1) - 1;
				}
				if (part2 == "="){
					string part3;
					parts >> part3;
					newValue = atof(part3.c_str());					
				}
				interpreter->assignVar(part1, newValue);//update the variable
		}
	}
	myfile.close();
	return 0;
}

// BORAMIR IS 25
// LEGOLAS IS 101
// GANDALF IS UNDEFINED
// BORAMIR * 2 IS 52
// GANDALF IS 49
// BORAMIR IS 26
// GANDALF IS UNDEFINED
// LEGOLAS IS 1000
// LEGOLAS IS 1000
// LEGOLAS IS 999
