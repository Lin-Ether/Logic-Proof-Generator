#include<bits/stdc++.h>
using namespace std;

string input_string[20000],n[20000],op,sub1,sub2;
long long b[27],p1,p2,p3,p4,counter=0,k,l,po;
int i=0,nums=0;
bool c[20000],d[27],s=false,t1,t2,boo=true,validity=false,boo2=true;
string o;
ostringstream output_string[20000],conclusion;

inline void refresh()
{
    system("cls");
}

//negation: serve as the "~" in logic
string negation(string ex1)
{
	int ct=0,ct2=0,flag=0;
	if (ex1.length()==2) ex1.erase(0,1);
	else if (ex1.length()==1) ex1.insert(0,"~");
	else if (ex1[0]=='~' and ex1[1]=='(' and ex1[ex1.length()-1]==')')
	{
		for (int j=0; j<=ex1.length()-1; j++)
		{
			
			if (ex1[j]=='(') 
			{
				ct++;
				flag=1;
			}
			if (ex1[j]==')') 
			{
				ct--;
				flag=1;
			}
			if (flag==1 and ct==0)
			{
				ct2++;
				flag=0;
			}
		}
		if (ct2!=2)
		{
			ex1.erase(0,2);
			ex1.erase(ex1.length()-1,1);
		}
		else 
		{
			ex1.insert(0,"~(");
			ex1.insert(ex1.length(),")");
		}
	}
	else
	{
		ex1.insert(0,"~(");
		ex1.insert(ex1.length(),")");
	}
	return ex1;
}

bool tf(string ex1)
{
	int ct=0,ct2=0,flag=0;
	bool t;
	if (ex1.length()==2) t=false;
	else if (ex1.length()==1) t=true;
	else if (ex1[0]=='~' and ex1[1]=='(' and ex1[ex1.length()-1]==')')
	{
		for (int j=0; j<=ex1.length()-1; j++)
		{
			
			if (ex1[j]=='(') 
			{
				ct++;
				flag=1;
			}
			if (ex1[j]==')') 
			{
				ct--;
				flag=1;
			}
			if (flag==1 and ct==0)
			{
				ct2++;
				flag=0;
			}
		}
		if (ct2!=2)
		{
			t=false;
		}
		else 
		{
			t=true;
		}
	}
	else
	{
		t=true;
	}
	return t;
}

//operation: to find the primer operator in the logic expression
string operation(string ex1)
{
	int pt1=0,pt2=0;
	int ct=0;
	int ct2=0,ct3=0;
	int flag=0;
	string op="0",op2,op3;
	pt1=ex1.find('(');
	if (pt1==-1)
	{
		pt2=ex1.find("|", 0);
		if (pt2==-1) pt2=ex1.find(">", 0);
		if (pt2==-1) pt2=ex1.find("&", 0);
		if (pt2!=-1) op=ex1[pt2];
	}
	else
	{
		for (int j=0; j<=ex1.length()-1; j++)
		{
			if (ex1[j]=='(') 
			{
				ct++;
				flag=1;
			}
			if (ex1[j]==')') 
			{
				ct--;
				flag=1;
			}
			if (flag==1 and ct==0)
			{
				ct2++;
				flag=0;
			}
		}
	}
	if (ct2==1)
	{
		if (ex1[0]=='~' and ex1[1]=='(' and ex1[ex1.length()-1]==')')
		{
			ct3=count(ex1.begin(),ex1.end(),'|')+count(ex1.begin(),ex1.end(),'>')+count(ex1.begin(),ex1.end(),'&');
			if (ct3==1) 
			{
				pt2=ex1.find("|", 0);
				if (pt2==-1) pt2=ex1.find(">", 0);
				if (pt2==-1) pt2=ex1.find("&", 0);
				op=ex1[pt2];
			}
			else if (ex1[2]=='~' and ex1[3]=='(' or ex1[2]=='(')
			{
				for (int j=2; j<=ex1.length()-2; j++)
				{
					if (ex1[j]=='(') 
					{
						ct++;          
						flag=1;
					}
					if (ex1[j]==')') 
					{
						ct--;
						flag=1;
					}
					if (flag==1 and ct==0)
					{
						op=ex1[j+1];
						break;
					}
				}
			}
			else 
			{
				pt2=ex1.find("|", 0);
				if (ex1.find(">", 0)<pt2) pt2=ex1.find(">", 0);
				if (ex1.find("&", 0)<pt2) pt2=ex1.find("&", 0);
				op=ex1[pt2];
			}
		}
		else if (ex1[0]=='~' and ex1[1]=='(' or ex1[0]=='(')
		{
			for (int j=0; j<=ex1.length()-1; j++)
			{
				if (ex1[j]=='(') 
				{
					ct++;
					flag=1;
				}
				if (ex1[j]==')') 
				{
					ct--;
					flag=1;
				}
				if (flag==1 and ct==0)
				{
					op=ex1[j+1];
					break;
				}
			}
		}
		else 
		{
			pt2=ex1.find("|", 0);
			if (ex1.find(">", 0)<pt2) pt2=ex1.find(">", 0);
			if (ex1.find("&", 0)<pt2) pt2=ex1.find("&", 0);
			op=ex1[pt2];
		}
	}
	else 
	{
		for (int j=0; j<=ex1.length()-1; j++)
		{
			if (ex1[j]=='(') 
			{
				ct++;
				flag=1;
			}
			if (ex1[j]==')') 
			{
				ct--;
				flag=1;
			}
			if (flag==1 and ct==0)
			{
				op=ex1[j+1];
				break;
			}
		}
	}
	return op;
}

//prestr: to find the former unit of a combined logic expression
string prestr(string ex1)
{
	int pt1=0,pt2=0;
	int ct=0;
	int ct2=0,ct3=0;
	int flag=0;
	string sub1="0";
	pt1=ex1.find('(');
	if (pt1==-1)
	{
		pt2=ex1.find("|", 0);
		if (pt2==-1) pt2=ex1.find(">", 0);
		if (pt2==-1) pt2=ex1.find("&", 0);
		if (pt2!=-1) sub1=ex1.substr(0,pt2);
	}
	else
	{
		for (int j=0; j<=ex1.length()-1; j++)
		{
			
			if (ex1[j]=='(') 
			{
				ct++;
				flag=1;
			}
			if (ex1[j]==')') 
			{
				ct--;
				flag=1;
			}
			if (flag==1 and ct==0)
			{
				ct2++;
				flag=0;
			}
		}
	}
	if (ct2==1)
	{
		if (ex1[0]=='~' and ex1[1]=='(' and ex1[ex1.length()-1]==')')
		{	
			ct3=count(ex1.begin(),ex1.end(),'|')+count(ex1.begin(),ex1.end(),'>')+count(ex1.begin(),ex1.end(),'&');
			if (ct3==1) 
			{
				pt2=ex1.find("|", 0);
				if (pt2==-1) pt2=ex1.find(">", 0);
				if (pt2==-1) pt2=ex1.find("&", 0);
				sub1=ex1.substr(2,pt2-2);
			}
			else if (ex1[2]=='~' and ex1[3]=='(' or ex1[2]=='(')
			{
				for (int j=2; j<=ex1.length()-2; j++)
				{
					if (ex1[j]=='(') 
					{
						ct++;
						flag=1;
					}
					if (ex1[j]==')') 
					{
						ct--;
						flag=1;
					}
					if (flag==1 and ct==0)
					{
						sub1=ex1.substr(2,j-1);
						break;
					}
				}
			}
			else 
			{
				pt2=ex1.find("|", 0);
				if (ex1.find(">", 0)<pt2) pt2=ex1.find(">", 0);
				if (ex1.find("&", 0)<pt2) pt2=ex1.find("&", 0);
				sub1=ex1.substr(2,pt2-2);
			}
		}
		else if (ex1[0]=='~' and ex1[1]=='(' or ex1[0]=='(')
		{
			for (int j=0; j<=ex1.length()-1; j++)
			{
				if (ex1[j]=='(') 
				{
					ct++;
					flag=1;
				}
				if (ex1[j]==')') 
				{
					ct--;
					flag=1;
				}
				if (flag==1 and ct==0)
				{
					sub1=ex1.substr(0,j+1);
					break;
				}
			}
		}
		else 
		{
			pt2=ex1.find("|", 0);
			if (ex1.find(">", 0)<pt2) pt2=ex1.find(">", 0);
			if (ex1.find("&", 0)<pt2) pt2=ex1.find("&", 0);
			sub1=ex1.substr(0,pt2);
		}
	}
	else 
	{
		for (int j=0; j<=ex1.length()-1; j++)
		{
			if (ex1[j]=='(') 
			{
				ct++;
				flag=1;
			}
			if (ex1[j]==')') 
			{
				ct--;
				flag=1;
			}
			if (flag==1 and ct==0)
			{
				sub1=ex1.substr(0,j+1);
				break;
			}
		}
	}
	ct=0;
	ct2=0;
	flag=0;
	if (sub1[0]=='(' and sub1[sub1.length()-1]==')')
	{
		for (int j=0; j<=sub1.length()-1; j++)
		{
			
			if (sub1[j]=='(') 
			{
				ct++;
				flag=1;
			}
			if (sub1[j]==')') 
			{
				ct--;
				flag=1;
			}
			if (flag==1 and ct==0)
			{
				ct2++;
				flag=0;
			}
		}
		if (ct2==1)
		{
			sub1.erase(0,1);
			sub1.erase(sub1.length()-1,1);
		}
	}
	return sub1;
} 

//poststr: to find the latter unit of a combined logic expression
string poststr(string ex1)
{
	int pt1=0,pt2=0;
	int ct=0;
	int ct2=0,ct3=0;
	int flag=0;
	string sub1="0";
	pt1=ex1.find('(');
	if (pt1==-1)
	{
		pt2=ex1.find("|", 0);
		if (pt2==-1) pt2=ex1.find(">", 0);
		if (pt2==-1) pt2=ex1.find("&", 0);
		if (pt2!=-1) sub1=ex1.substr(pt2+1,ex1.length()-pt2-1);
	}
	else
	{
		for (int j=0; j<=ex1.length()-1; j++)
		{
			
			if (ex1[j]=='(') 
			{
				ct++;
				flag=1;
			}
			if (ex1[j]==')') 
			{
				ct--;
				flag=1;
			}
			if (flag==1 and ct==0)
			{
				ct2++;
				flag=0;
			}
		}
	}
	if (ct2==1)
	{
		if (ex1[0]=='~' and ex1[1]=='(' and ex1[ex1.length()-1]==')')
		{	
			ct3=count(ex1.begin(),ex1.end(),'|')+count(ex1.begin(),ex1.end(),'>')+count(ex1.begin(),ex1.end(),'&');
			if (ct3==1) 
			{
				pt2=ex1.find("|", 0);
				if (pt2==-1) pt2=ex1.find(">", 0);
				if (pt2==-1) pt2=ex1.find("&", 0);
				sub1=ex1.substr(pt2+1,ex1.length()-pt2-2);
			}
			else if (ex1[2]=='~' and ex1[3]=='(' or ex1[2]=='(')
			{
				for (int j=2; j<=ex1.length()-2; j++)
				{
					if (ex1[j]=='(') 
					{
						ct++;
						flag=1;
					}
					if (ex1[j]==')') 
					{
						ct--;
						flag=1;
					}
					if (flag==1 and ct==0)
					{
						sub1=ex1.substr(j+2,ex1.length()-j-3);
						break;
					}
				}
			}
			else 
			{
				pt2=ex1.find("|", 0);
				if (ex1.find(">", 0)<pt2) pt2=ex1.find(">", 0);
				if (ex1.find("&", 0)<pt2) pt2=ex1.find("&", 0);
				sub1=ex1.substr(pt2+1,ex1.length()-pt2-2);
			}
		}
		else if (ex1[0]=='~' and ex1[1]=='(' or ex1[0]=='(')
		{
			for (int j=0; j<=ex1.length()-1; j++)
			{
				if (ex1[j]=='(') 
				{
					ct++;
					flag=1;
				}
				if (ex1[j]==')') 
				{
					ct--;
					flag=1;
				}
				if (flag==1 and ct==0)
				{
					sub1=ex1.substr(j+2,ex1.length()-j-2);
					break;
				}
			}
		}
		else 
		{
			pt2=ex1.find("|", 0);
			if (ex1.find(">", 0)<pt2) pt2=ex1.find(">", 0);
			if (ex1.find("&", 0)<pt2) pt2=ex1.find("&", 0);
			sub1=ex1.substr(pt2+1,ex1.length()-pt2-1);
		}
	}
	else 
	{
		for (int j=0; j<=ex1.length()-1; j++)
		{
			if (ex1[j]=='(') 
			{
				ct++;
				flag=1;
			}
			if (ex1[j]==')') 
			{
				ct--;
				flag=1;
			}
			if (flag==1 and ct==0)
			{
				sub1=ex1.substr(j+2,ex1.length()-2);
				break;
			}
		}
	}
	ct=0;
	ct2=0;
	flag=0;
	if (sub1[0]=='(' and sub1[sub1.length()-1]==')')
	{
		for (int j=0; j<=sub1.length()-1; j++)
		{
			
			if (sub1[j]=='(') 
			{
				ct++;
				flag=1;
			}
			if (sub1[j]==')') 
			{
				ct--;
				flag=1;
			}
			if (flag==1 and ct==0)
			{
				ct2++;
				flag=0;
			}
		}
		if (ct2==1)
		{
			sub1.erase(0,1);
			sub1.erase(sub1.length()-1,1);
		}
	}
	return sub1;
} 

int main()  
{  
	
	
	cout<<"This program is for propositional logic."<<"\n\n";
	cout<<"Capitalise the letters. You should put your conclusion in the last line."<<"\n\n";
	cout<<"Use \"~\" for the negation sign; \">\" for the implies sign; \"&\" for the and sign; \"|\" for the or sign."<<"\n\n";
	cout<<"End the input with \"0\"."<<"\n\n";

	for (int j=1; j<=27; j++)
		b[j]=0;
		
	for (int j=1; j<=27; j++)
		d[j]=false;
		
	for (int j=1; j<=27; j++)
		c[j]=true;
	
    while (input_string[i]!="0")
	{
		i++;
		getline(cin,input_string[i]);
	}
	
	cout<<"\n";
	i=i-1;
	refresh();
	cout<<"This program is for propositional logic."<<"\n\n";
	cout<<"Capitalise the letters. You should put your conclusion in the last line."<<"\n\n";
	cout<<"Use \"~\" for the negation sign; \">\" for the implies sign; \"&\" for the and sign; \"|\" for the or sign."<<"\n\n";
	cout<<"End the input with \"0\"."<<"\n\n";
	for (int j=1; j<=i-1; j++)
		output_string[j]<<j<<")     "<<input_string[j];
	po=i-1;
	conclusion<<" [CON: "<<input_string[i];
	input_string[i]=negation(input_string[i]);
	output_string[i]<<i<<")ASM: "<<input_string[i]; 
	int j=1;
	
	while (1)
	{
		if (j==1 and counter!=0 and s==true) counter=0;
		else if (j==1 and counter==0 and s==true) break;
		else if (j==1 and counter==0 and s!=true) s=true;
		while (c[j]==false)
		{
			j++;
			j=(j-1)%i+1;
			if (j==1 and counter!=0) counter=0;
			else if (j==1 and s!=true) s=true;
			else if (j==1 and s==true) 
			{
				boo=false;
				break;
			}
		}
		if (boo==false or boo2==false) break;
		for (int k=1; k<=i; k++)
		{
			for (int m=k+1; m<=i; m++)
			if (c[k]!=false and operation(input_string[k])=="0" and operation(input_string[m])=="0" and input_string[k]==negation(input_string[m]))
			{
				i=max(m,k);
				output_string[i+1].str("");
				output_string[i+1]<<i+1<<")     "<<negation(input_string[po+1])<<"	(from "<<po+1<<"; "<<min(m,k)<<" contradicts "<<max(m,k)<<")";
				validity=true;
				i++;
				boo2=false;
				break;
			}
			if (boo2==false) break;
		}
		if (boo==false or boo2==false) break;
		op=operation(input_string[j]);
		if (op=="&") t1=true;
		else t1=false;
		if (operation(input_string[j])=="0")
		{
			for (int k=1; k<=i; k++)
			{
				if (operation(input_string[k])=="&") t1=true;
				else t1=false;
				if (c[k]!=false and t1!=tf(input_string[k]) and (prestr(input_string[k])==input_string[j] or prestr(input_string[k])==negation(input_string[j]) or poststr(input_string[k])==input_string[j] or poststr(input_string[k])==negation(input_string[j])))
				{	
					if (operation(input_string[k])=="&")
					{
						if (prestr(input_string[k])==input_string[j]) 
						{
							c[k]=false;
							input_string[i+1]=negation(poststr(input_string[k]));
							output_string[i+1]<<i+1<<")     "<<input_string[i+1]<<"	(from "<<min(k,j)<<" and "<<max(k,j)<<")";
							i++;
							counter++;
						}
						if (poststr(input_string[k])==input_string[j]) 
						{
							c[k]=false;
							input_string[i+1]=negation(prestr(input_string[k]));
							output_string[i+1]<<i+1<<")     "<<input_string[i+1]<<"	(from "<<min(k,j)<<" and "<<max(k,j)<<")";
							i++;
							counter++;

						}
					}
					if (operation(input_string[k])=="|")
					{
						if (prestr(input_string[k])==negation(input_string[j]))
						{
							c[k]=false;
							input_string[i+1]=poststr(input_string[k]);
							output_string[i+1]<<i+1<<")     "<<input_string[i+1]<<"	(from "<<min(k,j)<<" and "<<max(k,j)<<")";
							i++;
							counter++;
						}
						if (poststr(input_string[k])==negation(input_string[j]))
						{
							c[k]=false;
							input_string[i+1]=prestr(input_string[k]);
							output_string[i+1]<<i+1<<")     "<<input_string[i+1]<<"	(from "<<min(k,j)<<" and "<<max(k,j)<<")";
							i++;
							counter++;
						}
					}
					if (operation(input_string[k])==">")
					{
						if (prestr(input_string[k])==input_string[j])
						{
							c[k]=false;
							input_string[i+1]=poststr(input_string[k]);
							output_string[i+1]<<i+1<<")     "<<input_string[i+1]<<"	(from "<<min(k,j)<<" and "<<max(k,j)<<")";
							i++;
							counter++;
						}
						if (poststr(input_string[k])==negation(input_string[j]))
						{
							c[k]=false;
							input_string[i+1]=negation(prestr(input_string[k]));
							output_string[i+1]<<i+1<<")     "<<input_string[i+1]<<"	(from "<<min(k,j)<<" and "<<max(k,j)<<")";
							i++;
							counter++;
						}
					}
				}
			}
		}
		if (tf(input_string[j])==t1)
		{
			if (op=="&") 
			{
				c[j]=false;
				input_string[i+1]=prestr(input_string[j]);
				input_string[i+2]=poststr(input_string[j]);
				output_string[i+1]<<i+1<<")     "<<input_string[i+1]<<"	(from "<<j<<")";
				output_string[i+2]<<i+2<<")     "<<input_string[i+2]<<"	(from "<<j<<")"; 
				i=i+2;
				counter++;
			}
			if (op=="|")
			{
				c[j]=false;
				input_string[i+1]=negation(prestr(input_string[j]));
				input_string[i+2]=negation(poststr(input_string[j]));
				output_string[i+1]<<i+1<<")     "<<input_string[i+1]<<"	(from "<<j<<")";
				output_string[i+2]<<i+2<<")     "<<input_string[i+2]<<"	(from "<<j<<")"; 
				i=i+2;
				counter++;
			}
			if (op==">")
			{
				c[j]=false;
				input_string[i+1]=prestr(input_string[j]);
				input_string[i+2]=negation(poststr(input_string[j]));
				output_string[i+1]<<i+1<<")     "<<input_string[i+1]<<"	(from "<<j<<")";
				output_string[i+2]<<i+2<<")     "<<input_string[i+2]<<"	(from "<<j<<")"; 
				i=i+2;
				counter++;
			}
		}
		
		j++;
		j=(j-1)%i+1;
	}
	
//	if (validity==false)
//	{ 
//		for (int k=1; k<=i; k++)
//		{
//			
//		}
//		for (int k=1;k<=i; k++)
//		{
//			if (operation(input_string[k])!="0") 
//			{
//				i++;
//				input_string[i]=prestr(input_string[k]);
//				output_string[i]<<i<<")ASM: "<<input_string[i];
//				break;
//			}
//		}
//		
//	}
	
	
	nums=log10(i);
	for (int k=1; k<=po; k++)
	{	
		
		for (int m=1; m<=ceil(nums-log10(k)); m++) cout<<" ";
		cout<<output_string[k].str()<<endl;
	}
	for (int m=1; m<=ceil(nums-log10(po)); m++) cout<<" ";
	cout<<conclusion.str()<<endl;
	for (int k=po+1; k<=i; k++)
	{
		for (int m=1; m<=ceil(nums-log10(k)); m++) cout<<" ";
		cout<<output_string[k].str()<<endl;
	}
	if (validity==true) cout<<"VALID";
	cin.get(); 
}
