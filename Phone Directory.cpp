#include<iostream>
#include<string>
#include<fstream>
#include<bits/stdc++.h>
#include<typeinfo>
#include<iomanip>
#include<cstdlib>
#include<unistd.h>
using namespace std;
struct node
{
        long int *data;
        node **child;
};

class trie
{
        struct node *root;
        public:
                trie(){
                        root=newNode();
                }
                node* newNode();
                void insertion(string,long int);
                void searchFull(string);
                void searchPrefix(string);
                void searchPrefix(char);
                void searching(node*,string);
};

node* trie::newNode()
{
        struct node *n=new node;
        n->data=new long int[27];
        for(int i=0;i<27;i++)
                n->data[i]=0;
        n->child=new node*[27];
        return n;
}

void trie::insertion(string ele,long int num1)
{
        struct node *ptr=root,*temp;
        for(int i=0;i<ele.length();i++){
                if(ptr->data[ele[i]-65]==0){
                        ptr->data[ele[i]-65]=1;
                        temp=newNode();
                        ptr->child[ele[i]-65]=temp;
                        ptr=temp;
                }
                else{
                        ptr=ptr->child[ele[i]-65];
                }
        }
        ptr->data[26]=num1;
}

void trie::searchFull(string ele)
{
        string s="";
        struct node *ptr=root;
        for(int i=0;i<ele.length();i++){
                if(ptr->data[ele[i]-65]==1){
                        s+=ele[i];
                        ptr=ptr->child[ele[i]-65];
                }
                else{
                        cout<<"\t\t\t\t\t\t\t The contact doesn't exist..."<<endl;
                        return;
                }
        }
        if(s.length()==ele.length() && ptr->data[26]!=0){
                cout<<"\t\t\t\t\t\t\t\t Name   : "<<s<<endl;
                cout<<"\t\t\t\t\t\t\t\t Number : "<<ptr->data[26]<<endl;
        }
        else if(s.length()!=ele.length() || ptr->data[26]==0){
                cout<<"\t\t\t\t\t\t\t The contact doesn't exist..."<<endl;
                return;
        }
}

void trie::searchPrefix(char ele)
{
        string s="";
        struct node *ptr=root;
        if(ptr->data[ele-65]==1){
                s+=ele;
                ptr=ptr->child[ele-65];
        }
        else{
                return;
        }
        searching(ptr,s);
}

void trie::searchPrefix(string ele)
{
        string s="";
        struct node *ptr=root;
        for(int i=0;i<ele.length();i++){
                if(ptr->data[ele[i]-65]==1){
                        s+=ele[i];
                        ptr=ptr->child[ele[i]-65];
                }
                else{
                        cout<<"\t\t\t\t\t\t\t The contact doesn't exist..."<<endl;
                        return;
                }
        }
        searching(ptr,s);
}

void trie::searching(node* ptr,string s)
{
        struct node *temp=ptr;
        for(int i=0;i<26;i++){
                if(ptr->data[i]==1){
                        temp=ptr;
                        s+=char(i+65);
                        ptr=ptr->child[i];
                        searching(ptr,s);
                        ptr=temp;
                        string str="";
                        for(int i=0;i<s.length()-1;i++){
                                str+=s[i];
                        }
                        s=str;
                }
        }
        if(ptr->data[26]!=0){
                cout<<"\t\t\t\t\t\t\t\t Name   : "<<s<<endl;
                cout<<"\t\t\t\t\t\t\t\t Number : "<<ptr->data[26]<<endl<<endl;
                return;
        }
}

int main()
{
        system("clear");
        trie t;
        long int n;
        char num[10];
        char ch;
        string line,s,s1,word,ele,temp;
        string s2;
        fstream f;
        f.open("sample.txt",ios::out|ios::in);
        int i=0,choice;
        while(getline(f,line)){
                stringstream iss(line);
                while(iss>>word){
                        if(i%2==0){
                                for(int j=0;j<word.length();j++){
                                        if(word[j]>=97 && word[j]<=122)
                                                s+=(word[j]-32);
                                        else
                                                s+=word[j];
                                }
                        }
                        else if(i%2==1){
                                s1=word;
                                for(int j=0;j<s1.length();j++){
                                        num[j]=s1[j];
                                }
                                n=atol(num);
                                t.insertion(s,n);
                                s="";
                                s1="";
                        }
                        i++;
                }
        }
        f.close();
        do{
                for(int h=0;h<2;h++)
                        cout<<"---------------------------------------------------------------------------------";
                cout<<"-"<<endl<<endl;
                cout<<"\t\t\t\t\t\t\t\t PHONE DIRECTORY"<<endl<<endl;
                cout<<"\t\t\t\t\t\t\t 1.Add a file of directory"<<endl<<endl;
                cout<<"\t\t\t\t\t\t\t 2.Display the full phone directory"<<endl<<endl;
                cout<<"\t\t\t\t\t\t\t 3.Search the contact by full name"<<endl<<endl;
                cout<<"\t\t\t\t\t\t\t 4.Search the contact by prefix"<<endl<<endl;
                cout<<"\t\t\t\t\t\t\t 5.Exit"<<endl<<endl;
                for(int h=0;h<2;h++)
                        cout<<"---------------------------------------------------------------------------------";
                cout<<"-"<<endl<<endl;
                cout<<"\t\t\t\t\t\t Enter your choice : ";
                cin>>choice;
                cout<<endl;
                switch(choice){
                        case 1:
                        {
                                cout<<"\t\t\t\t\t Enter the file that need to be added=";
                                cin>>ele;
                                ifstream f(ele.c_str());
                                i=0;
                                while(getline(f,line)){
                                        stringstream iss(line);
                                        while(iss>>word){
                                                if(i%2==0){
                                                        for(int j=0;j<word.length();j++){
                                                                if(word[j]>=97 && word[j]<=122)
                                                                        s+=(word[j]-32);
                                                                else
                                                                        s+=word[j];
                                                        }
                                                }
                                                else if(i%2==1){
                                                        s1=word;
                                                        for(int j=0;j<s1.length();j++){
                                                                num[j]=s1[j];
                                                        }
                                                        n=atol(num);
                                                        t.insertion(s,n);
                                                        s="";
                                                        s1="";
                                                }
                                                i++;
                                        }
                                }
                                f.close();
                                cout<<endl<<"\t\t\t\t\t\t File added successfully..."<<endl;
                                cout<<endl;
                                break;
                        }
                        case 2:
                        {
                                cout<<endl<<"\t\t\t\t\t\t\t\t Contact details"<<endl<<endl;
                                for(int i=0;i<26;i++){
                                        t.searchPrefix(char(i+65));
                                }
                                break;
                        }
                        case 3:
                        {
                                cout<<"\t\t\t\t\t  Enter the name of the contact : ";
                                cin>>ele;
                                for(int i=0;i<ele.length();i++){
                                        if(ele[i]>=97 && ele[i]<=122)
                                                s+=(ele[i]-32);
                                        else
                                                s+=ele[i];
                                }
                                cout<<endl<<"\t\t\t\t\t\t\t\t Contact details"<<endl<<endl;
                                t.searchFull(s);
                                s="";
                                break;
                        }
                        case 4:
                        {
                                cout<<"\t\t\t\t\t Enter the name of the contact : ";
                                cin>>ele;
                                for(int i=0;i<ele.length();i++){
                                        if(ele[i]>=97 && ele[i]<=122)
                                                s+=(ele[i]-32);
                                        else
                                                s+=ele[i];
                                }
                                cout<<endl<<"\t\t\t\t\t\t\t\t Contact details"<<endl<<endl;
                                t.searchPrefix(s);
                                s="";
                                break;
                        }
                        case 5:
                        {
                                system("clear");
                                cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<"\t\t\t\t\t\t\t\t\t Exiting..."<<endl<<endl;
                                sleep(5);
                                system("clear");
                                break;
                        }
                        default:
                        {
                                cout<<"\t\t\t\t\t Invalid choice..."<<endl<<endl;
                                break;
                        }
                }
        }while(choice!=5);
}
