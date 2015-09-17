#include <iostream>
#include <fstream>
#include<sstream>
#include<string>
#include<list>

using namespace std;

class Input{
	int num;
	int rate;
public:
	Input(int inputNum):num(inputNum),rate(0){}
	int GetInputNumber()const { return num; }
	int GetRate() {return rate; }
	void IncRate() {rate++;}
	void IncRate(int r) {rate+=r;}


};

list<Input> inputs;

bool compareInput(const Input& first,const Input& second) {
	return (first.GetInputNumber() < second.GetInputNumber()) ;
}

void GetInputs(ifstream& file,int percent){
	string value;
	double score,def,i,average;
	int inputNum;
	int counter=1;
	list<Input>::iterator iter;

	getline ( file, value, ' ' );
	average=stod(value);
	getline ( file, value, ' ' );
	getline ( file, value, '\n' );
	inputNum=stoi(value)+1;
	
	while ( file.good() ){
		
		getline ( file, value, ' ' );
		if(value=="This")
			break;
		score=stod(value);
		getline ( file, value, ' ' );
		getline ( file, value, '\n' );
		inputNum=stoi(value)+1;
		
		def=abs(score-average)/average;
		
		if(def < (1/percent)){
			average=(average*counter+score)/(++counter);
		}else {
			counter++;
			for (iter=inputs.begin(); iter != inputs.end(); ++iter){
				if(iter->GetInputNumber()==inputNum)
					break;
			}
			cout<<def<<endl;
			for(i=1;i<percent;i+=1)
				if(def > i/percent){
					
					iter->IncRate(i);
				}
				
		}
		
	}

}

void GetRates(ifstream& file,int weight){
	string value;
	int rate;
	int inputNum;
	list<Input>::iterator iter;

	while ( file.good() ){
		
		getline ( file, value, ' ' );
		if(value=="This")
			break;
		rate=stoi(value);
		getline ( file, value, ' ' );
		getline ( file, value, '\n' );
		inputNum=stoi(value)+1;
		for (iter=inputs.begin(); iter != inputs.end(); ++iter){
			if(iter->GetInputNumber()==inputNum){
				iter->IncRate(weight*rate);
				break;
			}
		}
		
		
	}

}

int main(){
	ifstream file1 ( "inscountSorted.txt" );
	ifstream file2 ( "timeSorted.txt" );
	ifstream file3 ( "FileTraceSorted.txt" );
	ifstream file4 ( "memoryTraceSorted.txt" );
	ifstream file5 ( "socketSorted.txt" );
	ifstream file6 ( "stackdepthSorted.txt" );
	ifstream file7 ( "FunctionsCountSorted.txt" );
	ifstream file8 ( "DoubleFreeSorted.txt" );
	ofstream oss;
	list<Input>::iterator iter;
	for(int i=1;i<=26;i++)
		inputs.push_back(Input(i));
	//InsCount
	GetInputs(file1,3000);

	//Time
	GetInputs(file2,2);

	//File Trace
	GetRates(file3,2);

	//Memory Trace
	GetInputs(file4,100);

	//Socket
	GetInputs(file5,50);

	//Stack Depth
	GetInputs(file6,2000);

	// Functions Counter
	GetRates(file7,2);

	//Double Free
	GetRates(file8,5);

    inputs.sort(compareInput) ;
	oss.open("Rate.txt");
	for (iter=inputs.begin(); iter != inputs.end(); ++iter)
		oss << "Input " << iter->GetInputNumber() << ": " << iter->GetRate() << endl;
	
	system("pause");
}