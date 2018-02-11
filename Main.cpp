# Redo_UndoOpertaion
Cut copy Operations Performed
#include<iostream>
using namespace std;
struct node{
	char command;
	char* data;
	int pos;
	struct node* next;
};
class STACK{
	public:
	struct node* top;
	STACK(){
		top=NULL;
	}
	void push(struct node* );
	struct node* pop();
	bool isEmpty();
};
void STACK::push(struct node* latest){
	if(top==NULL)
		top=latest;
	else{
		latest->next=top;
		top=latest;
	}
}
struct node* STACK::pop(){
	if(!isEmpty()){
		struct node* temp=top;
		top=top->next;
		return temp;
	}else
		cout<<"Stack is Empty"<<endl;
}
bool STACK::isEmpty(){
	return top==NULL;
}
int size(char* input){
	int count=0;
	for(int i=0;input[i]!='\0';i++)
		count++;
	return count;
}
char* enterWord(char* input,char* toEnter,int pos){
	char* temp=new char[size(input)+size(toEnter)+1];
	int tempIndex,inputIndex;
	for(tempIndex=0;tempIndex<pos;tempIndex++)
		temp[tempIndex]=input[tempIndex];
	inputIndex=tempIndex;
	
	for(int i=0;toEnter[i]!='\0';i++)
		temp[tempIndex++]=toEnter[i];
	temp[tempIndex++]=' ';
	for(;input[inputIndex]!='\0';inputIndex++)
		temp[tempIndex++]=input[inputIndex];
	temp[tempIndex]='\0';
	return temp;
}
char* insertWord(char* input,char* toEnter,int pos,int count=0,int travel=0){
	if(input[travel]=='\0')
		return input;
	if(pos==count){
		input=enterWord(input,toEnter,travel);
		return input;
	}
	if(travel==0&&isalpha(input[travel]))
		count=1;
	else if(input[travel]==' '&&isalpha(input[travel+1]))
		count++;
	return insertWord(input,toEnter,pos,count,travel+1);

}
struct node* makeNode(char cmd,char* dat,int position){
	struct node* latest=new node;
	latest->command=cmd;
	latest->data=dat;
	latest->pos=position;
	latest->next=NULL;
	return latest;
}
char* fetchWord(char* temp,char* input,int travel){
	for(int i=0;input[travel]!='\0'&&input[travel]!=' ';travel++,i++)
		temp[i]=input[travel];
	return temp;
		
}
char* fetchString(char* input,char* temp,int pos,int count=0,int travel=0){
	if(input[travel]=='\0')
		return input;
	if(count==pos){
		temp=fetchWord(temp,input,travel);
		return temp;
	}
	if(travel==0&&isalpha(input[travel]))
		count=1;
	else if(input[travel]==' '&&isalpha(input[travel+1]))
		count++;
	return fetchString(input,temp,pos,count,++travel);

}
char* getDeleted(char* input,char* word,int pos){
cout<<input<<endl;
	int sizeString=size(input);
	int sizeTemp=size(word)+1;
		int i;
	for( i=pos;i<sizeString;i++)
		input[i]=input[i+sizeTemp];
		input[i]='\0';
	//cout<<input<<endl;
	return input;
}
char* deleteWord(char* input,char* word,int pos,int count=0,int travel=0){
	//cout<<input<<endl;
	if(input[travel]=='\0')
		return input;
	if(pos==count){
		//cout<<input<<endl;
		input=getDeleted(input,word,travel);
		return input;
	}
	if(travel==0&&isalpha(input[travel]))
		count=1;
	else if(input[travel]==' '&&isalpha(input[travel+1]))
		count++;
	return deleteWord(input,word,pos,count,++travel);
}
int main(){
	cout<<"Enter the String"<<endl;
	char* input=new char[100];
	cin.getline(input,100);
	STACK undo;
	STACK redo;
	//cout<<insertWord(input,"not",3)<<endl;
	while(1){
		cout<<"enter i for insert  d for delete u for undo r for redo q to exit"<<endl;
		char choice;
		cin>>choice;
		if(choice=='i'){
			cout<<"Enter the String to Enter"<<endl;
				char* toEnter=new char[50];
				cin>>toEnter;
				cout<<"Enter the pos"<<endl;
				int pos;
				cin>>pos;
				struct node* latest=makeNode('i',toEnter,pos);
				undo.push(latest);
				while(!redo.isEmpty())
					redo.pop();
				input=insertWord(input,toEnter,pos);
		}
		if(choice=='d'){
			cout<<"Enter the pos to delete"<<endl;
			int pos;
			cin>>pos;
			char* word=new char[50];
			word=fetchString(input,word,pos);
			struct node* latest=makeNode('d',word,pos);
			undo.push(latest);
			input=deleteWord(input,word,pos);
		}
		if(choice=='u'){
			if(!undo.isEmpty()){
			struct node* latest=new node;
			latest=undo.pop();
			redo.push(latest);
			if(latest->command=='i')
				input=deleteWord(input,latest->data,latest->pos);
			else
				input=insertWord(input,latest->data,latest->pos);
			}
		}
		if(choice=='r'){
			if(!redo.isEmpty()){
			struct node* latest=new node;
			latest=redo.pop();
			undo.push(latest);
			if(latest->command=='i')
				input=insertWord(input,latest->data,latest->pos);
			else
				input=deleteWord(input,latest->data,latest->pos);
			}
		}	
		if(choice=='q')
			break;
		cout<<input<<endl;
	}
}
