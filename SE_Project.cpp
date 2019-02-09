#include<bits/stdc++.h>
#define NSub 5      				// Number of Subjects
#define Qualify 50.0 				// Percentage of Marks for Qualify
# define PRECISION 5
using namespace std;
const std::string WHITESPACE=" \n\r\t\f\v";
std::string ltrim(const std::string& s)
{
	size_t start=s.find_first_not_of(WHITESPACE);
	return (start== std::string::npos) ? "" : s.substr(start);
}
std::string rtrim(const std::string& s)
{
	size_t end=s.find_last_not_of(WHITESPACE);
	return (end== std::string::npos) ? "" : s.substr(0,end+1);
}
std::string trim(const std::string& s)
{
	return rtrim(ltrim(s));
}
string  floatToString(float num)
{
   int whole_part = num;
   int digit = 0, reminder =0;
   int log_value = log10(num), index = log_value;
   long wt =0;

   // String containg result
   string str;

   //Extract the whole part from float num
   for(int  i = 1 ; i < log_value + 2 ; i++)
   {
       wt  =  pow(10.0,i);
       reminder = whole_part  %  wt;
       digit = (reminder - digit) / (wt/10);

       //Store digit in string
       str[index--] = digit + 48;              // ASCII value of digit  = digit + 48
       if (index == -1)
          break;    
   }

    index = log_value + 1;
    str[index] = '.';

   float fraction_part  = num - whole_part;
   float tmp1 = fraction_part,  tmp =0;

   //Extract the fraction part from  num
   for( int i= 1; i < PRECISION; i++)
   {
      wt =10; 
      tmp  = tmp1 * wt;
      digit = tmp;

      //Store digit in string
      str[++index] = digit +48;           // ASCII value of digit  = digit + 48
      tmp1 = tmp - digit;
   }    

   return str;
}
class Student					// This is the user define data type
{
	private:
		string name,regId,status,raw_line,grade;				//All private member of the Student class
		float marks[NSub];
		float perMarks;
	public:
		string getMathMarks()
		{
			return (floatToString(marks[0]));
		}
		string getPhyMarks()
		{
			return (floatToString(marks[1]));
		}
		string getCheMarks()
		{
			return (floatToString(marks[2]));
		}
		string getEngMarks()
		{
			return (floatToString(marks[3]));
		}
		string getHNDMarks()
		{
			return (floatToString(marks[4]));
		}
		string getRegId()  							//To get regId private member
		{
			return regId;
		}
		string getStatus() 							//To get status private member
		{
			return status;
		}
		string getRawLine() 							//To get rawLine private member
		{
			return raw_line;
		}
		string getName()
		{
			return name;
		}
		string getGrade()
		{
			return grade;
		}
		void getData(string N,string R,float *m,string rLine) 			//To get all input in stu class object
		{
			name=N;
			regId=R;
			raw_line=rLine;
			for(int i=0; i<NSub; i++)
			{
				marks[i]=m[i];
				perMarks+=marks[i];
			}
			perMarks/=NSub;
			if(perMarks>=Qualify)
			{
				status="Qualified";
				if(perMarks > 85.0)
					grade="A+";
				else if(perMarks >= 75.0)
					grade="A";
				else if(perMarks >= 65.0)
					grade="B+";
				else if(perMarks >= 60.0)
					grade="B";
				else if(perMarks >= 55.0)
					grade="C";
				else
					grade="D";						
			}
			else
			{
				grade="";
				status="Fail";
			}		
		}
		void printDetail() 								//To display the stu class object for specific student
		{
			cout<<"Name: "<<name<<"\nReg.Id: "<<regId<<endl;
			cout<<"Marks:";
			for(int i=0; i<NSub; i++)
				cout<<marks[i]<<" ";
			cout<<endl<<"Percentage: "<<perMarks<<endl;
			cout<<"Grade: "<<grade<<endl;
			cout<<"Status: "<<status<<endl;	
			cout<<"-------------------------------"<<endl;
		}
		void printDetailAll() 								//To display the stu class object for all student 
		{
			cout<<name<<"\t"<<regId<<"\t\t"<<marks[0]<<"\t\t    "<<marks[1]<<"\t\t  "<<marks[2]<<"\t\t        "<<marks[3]<<"\t\t  "<<marks[4]<<"\t\t  "<<perMarks<<"\t\t\t"<<grade
			<<"\t\t"<<status<<endl;
		}
};
void printPassStu(vector<Student> &stu);  							//Print All Qualified Student Data
void printFailStu(vector<Student> &stu);  							//Print All Non-Qualified Student Data
unsigned CountStudents(string dbName)      							//Counting the No. of Student in Database
{
	ifstream inFileDB;
	inFileDB.open(dbName.c_str());
	if (!inFileDB.is_open()) 
	{
		cout<<"Error! While opening the input.txt file"<<endl;
		exit(1);
	}
     	unsigned NStu=0;
	char newLine=';';
	string text;
     	while(getline(inFileDB, text.erase(text.find_last_not_of(" \n\r\t")+1), '\n'))
    	{
        	for(unsigned int i=0; i< text.length(); i++)
        	{
            		if(text.at(i) == newLine)
            		{
                		NStu++;
            		}
        	}
    	}
	inFileDB.close();
	return NStu;
}
void getDataFromFile(vector<Student> &stu,string dbName)          					//Getting the student data from file
{	
	unsigned NStu=CountStudents(dbName);
	ifstream inFile;
	inFile.open(dbName.c_str());
	if (!inFile.is_open()) 
	{
		cout<<"Error! While opening the input.txt file"<<endl;
		exit(1);
	}
	vector<Student> stu1(NStu);
	string line;
	string name,regId;
	float marks[NSub];
	unsigned i=0;
	while( getline(inFile, line) && i < NStu ) 
	{
		stringstream linestream( line );
    	string value;
		for(int p=0;getline(linestream, value,',');p++)
		{
			if(p==0)
				name=value;
			else if(p==1)
				regId=value;
			else if(p>=2)
				marks[p-2]=atof(value.c_str());
		}
		stu1[i].getData(name,regId,marks,line);
		stu.push_back(stu1[i]);
		i++;	
	}
	stu1.clear();
	stu1.shrink_to_fit(); 
	inFile.close();
}
int searchReg(vector<Student> &stu,string reg) 									//Searching a particular student by regId
{
	
	int flag=0;
	for(int i=0;i<stu.size();i++)
	{
		if(stu[i].getRegId()==reg)
		{
			flag=1;
			return i;
		}
	}
	if(flag==0)
	{
		//cout<<"Not Found.."<<endl;
		return -1;
	}
}
void searchName(vector<Student> &stu,string name) 									//Searching a particular student by regId
{
	
	int flag=0;
	for(int i=0;i<stu.size();i++)
	{
		if(stu[i].getName()==name)
		{
			flag=1;
			stu[i].printDetail();
		}
	}
	if(flag==0)
	{
		cout<<"Not Found.."<<endl;
	}
}
void searchGrade(vector<Student> &stu,string grade) 									//Searching a particular student by regId
{
	
	int flag=0;
	for(int i=0;i<stu.size();i++)
	{
		if(stu[i].getGrade()==grade)
		{
			flag=1;
			stu[i].printDetail();
		}
	}
	if(flag==0)
	{
		cout<<"Not Found.."<<endl;
	}
}
typedef std::list<std::string> StrList;
void tokenize(const std::string& in, const std::string& delims, StrList& tokens)
{
    tokens.clear();

    std::string::size_type pos_begin  , pos_end  = 0;
    std::string input = in;

    input.erase(std::remove_if(input.begin(), 
                              input.end(),
                              [](auto x){return std::isspace(x);}),input.end());

    while ((pos_begin = input.find_first_not_of(delims,pos_end)) != std::string::npos)
    {
        pos_end = input.find_first_of(delims,pos_begin);
        if (pos_end == std::string::npos) pos_end = input.length();

        tokens.push_back( input.substr(pos_begin,pos_end-pos_begin) );
    }
}
string getDetails(vector<Student> &stu,int serialNo)
{
	unsigned ch=0;
	string name="",mathMarks="",phyMarks="",cheMarks="";
	string engMarks"",hindiMarks="",newLine="",rLine=stu[serialNo].getRawLine();
	cout<<"Press 1.Update Name"<<"\nPress 2.Update Mathematics Marks"<<endl;
	cout<<"Press 3.Update Physics Marks"<<"\nPress 4.Update Chemistry Marks"<<endl;
	cout<<"Press 5.Update English Marks"<<"\nPress 6.Update Hindi Marks"<<endl;
	cout<<"Press 7.No Update require"<<endl;
	stringstream ss(rLine);
	unsigned deli=0,dirty=1;
	cout<<"Enter Choice: ";
	cin>>ch;
	switch(ch)
	{
		case 1:
			cout<<"Name: ";
			cin.ignore();
			getline(cin, name);
			deli=0;
			while( ss.good() ) 
			{
       			string substr;
       			getline( ss, substr, ',' );
       			if(substr==stu[serialNo].getName())
       				substr=trim(name);
       			newLine+=substr;	
       			if(deli<4)	
       				newLine+=",";
       			else
				   newLine+=";";	
       			deli++
    		}
			break;
		case 2:
			cout<<"Mathematics: ";
			cin>>mathMarks;
			deli=0;
			while( ss.good() ) 
			{
       			string substr;
       			getline( ss, substr, ',' );
       			if(substr==stu[serialNo].getMathMarks())
       				substr=trim(mathMarks);
       			newLine+=substr;	
       			if(deli<4)	
       				newLine+=",";
       			else
				   newLine+=";";	
       			deli++
    		}
			break;
		case 3:
			cout<<"Physics: ";
			cin>>phyMarks;
			deli=0;
			while( ss.good() ) 
			{
       			string substr;
       			getline( ss, substr, ',' );
       			if(substr==stu[serialNo].getPhyMarks())
       				substr=trim(phyMarks);
       			newLine+=substr;	
       			if(deli<4)	
       				newLine+=",";
       			else
				   newLine+=";";	
       			deli++
    		}
			break;
		case 4:
			cout<<"Chemistry: ";
			cin>>cheMarks;
			deli=0;
			while( ss.good() ) 
			{
       			string substr;
       			getline( ss, substr, ',' );
       			if(substr==stu[serialNo].getCheMarks())
       				substr=trim(cheMarks);
       			newLine+=substr;	
       			if(deli<4)	
       				newLine+=",";
       			else
				   newLine+=";";	
       			deli++
    		}
			break;
		case 5:
			cout<<"English: ";
			cin>>engMarks;
			deli=0;
			while( ss.good() ) 
			{
       			string substr;
       			getline( ss, substr, ',' );
       			if(substr==stu[serialNo].getEngMarks())
       				substr=trim(engMarks);
       			newLine+=substr;	
       			if(deli<4)	
       				newLine+=",";
       			else
				   newLine+=";";	
       			deli++
    		}
			break;
		case 6:
			cout<<"Hindi: ";
			cin>>hindiMarks;
			deli=0;
			while( ss.good() ) 
			{
       			string substr;
       			getline( ss, substr, ',' );
       			if(substr==stu[serialNo].getHNDMarks())
       				substr=trim(hindiMarks);
       			newLine+=substr;	
       			if(deli<4)	
       				newLine+=",";
       			else
				   newLine+=";";	
       			deli++
    		}
			break;
		case 7:
			cout<<"Student Data not modified"<<endl;
			dirty=0;
			break;
		default:
			dirty=0;
			cout<<"Invalid Choice"<<endl;							
	}
	if(dirty==1)
		return newLine;
	else
		return rLine;	
}
void modify(vector<Student> &stu,string dbName)  								//Modifing a particular student data by regID
{
	string reg,rLine;
	int stu_serialNo=0;
	printf("Enter the Student RegId: ");
	cin>>reg;
	printf("\t*Available Details*\n");
	stu_serialNo=searchReg(stu,reg);
	if(stu_serialNo<0)
	{
		cout<<"Data Not Found!"<<endl;
	}
	else
	{
		ofstream outFile("tempout.txt"); //Modified File temporary
		ifstream inputFile(dbName.c_str());
		if(!outFile || !inputFile)
    		{
        		cout << "Error! While opening file" << endl;
        		exit(1);
    		}
		stu[stu_serialNo].printDetail();
		rLine=stu[stu_serialNo].getRawLine();
		string newLine=getDetails(stu,stu_serialNo),x;
		while (!inputFile.eof())
		{
    			getline(inputFile,x);
    			if (x == rLine)
    			{
        			outFile << newLine << endl;
    			}
    			else
        			outFile << x << endl;
		}
		outFile.close();
		inputFile.close();
	}
	cout<<"Student Data successfully modified"<<endl;
	remove(dbName.c_str());
	rename("tempout.txt",dbName.c_str());
	stu.clear();
	stu.shrink_to_fit();                                            
	getDataFromFile(stu,dbName);
}
void deleteStudent(vector<Student> &stu,string dbName)    							//Deleting the student data from database file 
{
	string reg,rLine;
	int stu_serialNo=0;
	printf("Enter the Student RegId: ");
	cin>>reg;
	stu_serialNo=searchReg(stu,reg);
	cout<<"\t*Available Details*"<<endl;
	if(stu_serialNo<0)
	{
		cout<<"Data Not Found!"<<endl;
	}
	stu[stu_serialNo].printDetail();
	char select;
	choice: cout<<"\nSure you want to delete it(y/n)?: ";
	cin>>select;
	if(select=='Y' || select=='y')
	{
		ofstream outFile("tempout.txt");     //Modified File temporary
		ifstream inputFile(dbName.c_str());
		if(!outFile || !inputFile)
    		{
        		cout << "Error! While opening file" << endl;
        		exit(1);
    		}
		rLine=stu[stu_serialNo].getRawLine();
		string newLine="",x;
		while (!inputFile.eof())
		{
    			getline(inputFile,x);
    			if (x == rLine)
    			{
        			outFile << newLine;
    			}
    			else
        			outFile << x << endl;
		}
		cout<<"The Student "<<reg<<" data deleted"<<endl;
		outFile.close();
		inputFile.close();
		remove(dbName.c_str());
		rename("tempout.txt",dbName.c_str());
		stu.clear();
		stu.shrink_to_fit();
		getDataFromFile(stu,dbName);		
	}
	else if(select=='N' || select=='n')
	{
		cout<<"The Student "<<reg<<" data not deleted"<<endl;
	}
	else
		goto choice;
}
void addStudent(vector<Student> &stu,string dbName)  								//Adding new student data into database file
{
	unsigned newStudents=0;
	string newStudentData;
	cout<<"Enter No. of New Student: ";
	cin>>newStudents;
	ofstream ofile(dbName.c_str(), ios::out | ios::app); 
	for(int r=0;r<newStudents;r++)
	{
		cin.ignore();
		getline(cin,newStudentData);
		newStudentData+="\n";
		ofile << newStudentData;
	}
	ofile.close();
	cout<<"The Student data added successfully"<<endl;
	stu.clear();
	stu.shrink_to_fit();
	getDataFromFile(stu,dbName);
}
int main()     													//Main Driver method
{
    	unsigned choice=0,stu_serialNo=0;
    	string reg,dbName,name,grade;
    	cout<<"\nEnter your data file name: ";
	cin>>dbName;
	vector<Student> stu;
	getDataFromFile(stu,dbName);
	while(1)
	{
		cout<<"\t** Welcome at Student System **"<<endl;
		cout<<"Choose Any Following Operation by Pressing Operation No."<<endl;
		cout<<"1.Print the Whole Student Data"<<endl;
		cout<<"2.Searching Student by RegId"<<endl;
		cout<<"3.Searching Student by Name"<<endl;
		cout<<"4.Searching Student by Grade"<<endl;
		cout<<"5.Print the Quilified Student Data"<<endl;
		cout<<"6.Print the Failed Student Data"<<endl;
		cout<<"7.Adding New Student Data"<<endl;
		cout<<"8.Modify the Student Data"<<endl;
		cout<<"9.Removing the Student Data"<<endl;
		cout<<"10.Exit"<<endl;
		cout<<"=>Enter your choice: ";
		cin>>choice;
		cout<<endl;
		switch(choice)
		{
			case 1:
				cout<<"\t\t\t\t\t\t\t   *** ALL STUDENT DETAILS ***"<<endl;
				for(int i=0;i<175;i++)
					cout<<"=";
				cout<<endl<<"Name\t\t Reg.Id\t\t    Mathematics\t\tPhysics\t\tChemistry\t\tEnglish\t\tHindi\t\tPercentage\t\tGrade\t\tStatus"<<endl;
				for(int i=0;i<175;i++)
					cout<<"-";
				cout<<endl;
				for(int i=0;i<stu.size();i++)
					stu[i].printDetailAll();
				break;
			case 2:
				cout<<"Enter the Student RegId: ";
				cin>>reg;
				stu_serialNo=searchReg(stu,reg);
				if(stu_serialNo>=0)
					stu[stu_serialNo].printDetail();
				else
					cout<<"Data Not Found!"<<endl;
				break;
			case 3:
				cout<<"Enter Student Name: ";
				cin.ignore();
				getline(cin,name);
				printf("\t*Available Details*\n");
				searchName(stu,name);
				break;
			case 4:
				cout<<"Enter Student Grade: ";
				cin>>grade;
				printf("\t*Available Details*\n");
				searchGrade(stu,grade);
				break;			
			case 5:
				printf("\t*Available Details*\n");
				printPassStu(stu);
				break;
			case 6:
				printf("\t*Available Details*\n");
				printFailStu(stu);
				break;
			case 7:
				addStudent(stu,dbName);
				break;	
			case 8:
				modify(stu,dbName);
				break;
			case 9:
				deleteStudent(stu,dbName);
				break;	
			case 10:
				cout<<"Thanks.."<<endl;
				stu.clear();
				stu.shrink_to_fit();
				exit(1);
			default:
				cout<<"Invalid Choice"<<endl;								
		}
	}
	return 0;
}
