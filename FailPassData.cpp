#include<bits/stdc++.h>
#define NSub 5
#define Qualify 50.0
using namespace std;
class Student
{
	private:
		string name,regId,status,raw_line,grade;
		float marks[NSub];
		float perMarks;
	public:
		string getRegId()
		{
			return regId;
		}
		string getStatus()
		{
			return status;
		}
		string getRawLine()
		{
			return raw_line;
		}
		void getData(string N,string R,float *m,string rLine)
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
				else if(perMarks >= 50.0)
					grade="D";
				else
					grade="F";						
			}
			else
				status="Fail";		
		}
		void printDetail()
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
};
void printPassStu(vector<Student> &stu)
{
	cout<<"\t* Qualified Student's Data *"<<endl;
	for(int i=0;i<stu.size();i++)
	{
		if(stu[i].getStatus()=="Qualified")
			stu[i].printDetail();
	}
}
void printFailStu(vector<Student> &stu)
{
	cout<<"\t* Failed Student's Data *"<<endl;
	for(int i=0;i<stu.size();i++)
	{
		if(stu[i].getStatus()=="Fail")
			stu[i].printDetail();
	}
}
