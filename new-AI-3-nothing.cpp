#include <iostream>
#include "rlutil.h"
#include <conio.h>
#include <algorithm>  //random_shuffle
#include <vector>       
#include <ctime>       
#include <cstdlib>      // rand,srand
#include <cmath>
#include <string>
#include <list>
#include <windows.h>
#include <unistd.h>
using namespace std;
int ex,ey;
int id;
struct node{
	int map[4][4],depth,x,y;
	double score;
	int child,parent;
	char born;
};
int pros(int a,int x,int y){
	if(a==16) return 0;
	int i,j;
	i=(a-1)/4;
	j=(a-1)%4;
	return abs(i-x) + abs(j-y);
}
int man(node n){
//	int s=0;
//	for(int i=0;i<4;++i){
//		for(int j=0;j<4;++j){
//			s += pros(n.map[i][j],i,j);
//		}
//	}
//	return s;
return 0;
}

void print(node a){
	cout<<"\n----------------------------------------\n";
	for(int i=0;i<4;++i){
	    for(int j=0;j<4;++j){
	     	if(a.map[i][j]!=16)
	        	cout<<a.map[i][j]<<"\t";
	        else{
	        	rlutil::setBackgroundColor(2);
	        	cout<<"   ";
				rlutil::setBackgroundColor(0);
				cout<<"\t";
	        	
	        }
	    }
	     cout<<endl<<endl;
	}
	cout<<"x:"<<a.x<<" y:"<<a.y<<" score:"<<a.score<<"\n";
	cout<<"\n----------------------------------------\n";
}
node start(){
	id+=1000;
	vector <int> v;
	for(int i=1;i<=16;++i)
	    v.push_back(i);
	srand(time(0));
	random_shuffle(v.begin(),v.end());
//	for(int i=0;i<v.size();++i)
//		cout<<v[i]<<" ";
//		exit(0);
	int c=0;
	node temp;
	for(int i=0;i<4;++i)
	    for(int j=0;j<4;++j){
	    	temp.map[i][j] = v[c];
	    	if(v[c]==16){
	    		temp.y=i;
	    		temp.x=j;
			}
	        ++c;
	    }
//	    print(temp);
//	    exit(0);
	temp.child = id;
	temp.parent = 0;
	temp.depth = 0;
	temp.born='s';
	temp.score = man(temp);
	return temp;
}
bool win(node n){
	for(int i=0;i<4;++i){
		for(int j=0;j<4;++j){
	     	if(n.map[i][j]!= (i*4+j)+1){
	     		return 0;
	     	}
		}
	}
	return 1;
}
bool chk(int i,int j){
	if(i<0 || i>3 || j<0 || j>3) return 0;
	return 1;
}
bool chk_brn(char s, char c){
//	if((s=='u' )&&(c=='d')) return 0;
//	if((s=='d' )&& (c=='u')) return 0;
//	if((s=='l' )&& (c=='r')) return 0;
//	if((s=='r' )&& (c=='l') )return 0;
	return 1;
}
bool sort_q(const node& a, const node& b) {
  return a.score < b.score;
}
node fake(){
	id+=100;
	node a;
	a.map[0][0]=5;
	a.map[0][1]=1;
	a.map[0][2]=2;
	a.map[0][3]=4;
	
	a.map[1][0]=9;
	a.map[1][1]=6;
	a.map[1][2]=3;
	a.map[1][3]=7;
	
	a.map[2][0]=16;
	a.map[2][1]=10;
	a.map[2][2]=15;
	a.map[2][3]=8;
	
	a.map[3][0]=13;
	a.map[3][1]=14;
	a.map[3][2]=12;
	a.map[3][3]=11;
	a.depth=0;
	a.x=0;
	a.y=2;
	a.child=id;
	a.parent=0;
	a.score=man(a);
	a.born='s';
	return a;
}
node search_baba(vector <node> &nodes,int id){
	for(int i=0;i<nodes.size();++i){
		if(nodes[i].child == id) return nodes[i];
	}
}
int main(){
	rlutil::setColor(2);
	int c=0;
	node temp = fake();
	print(temp);
	//cout<<temp.score<<"\n"<<temp.child<<"\n";
	vector <node> q;
	vector <node> path;
	vector <node> all_nodes;
	all_nodes.push_back(temp);
	q.push_back(temp);
	while(1){
		temp = q[0];
		if(!win(temp)){
			//-> after adding childs : sort(q.begin(),q.end(),sort_q);
			//after sourting queue
			node tmp;
			int father_id = temp.child;
			//right
			int a1 = temp.x+1 , a2 = temp.y;
			if(chk(a2,a1) && chk_brn(temp.born,'r')){
				tmp = temp;
				++ tmp.depth;
				tmp.parent = father_id;
				tmp.child = ++id;
				tmp.map[a2][a1-1] = tmp.map[a2][a1];
				tmp.map[a2][a1] = 16;
				++tmp.x;
				tmp.born='r';
				tmp.score = tmp.depth + man(tmp);
				q.push_back(tmp);
				all_nodes.push_back(tmp);
			}
			//left
			a1 = temp.x-1 , a2 = temp.y;
			if(chk(a1,a2) && chk_brn(temp.born,'l')){
				tmp = temp;
				++ tmp.depth;
				tmp.parent = father_id;
				tmp.child = ++id;
				tmp.map[a2][a1+1] = tmp.map[a2][a1];
				tmp.map[a2][a1] = 16;
				--tmp.x;
				tmp.born='l';
				tmp.score = tmp.depth + man(tmp);
				q.push_back(tmp);
				all_nodes.push_back(tmp);
			}
			//up
			a1 = temp.x , a2 = temp.y-1;
			if(chk(a1,a2) && chk_brn(temp.born,'u')){
				tmp = temp;
				++ tmp.depth;
				tmp.parent = father_id;
				tmp.child = ++id;
				tmp.map[a2+1][a1] = tmp.map[a2][a1];
				tmp.map[a2][a1] = 16;
				--tmp.y;
				tmp.born='u';
				tmp.score = tmp.depth + man(tmp);
				q.push_back(tmp);
				all_nodes.push_back(tmp);
			}
			//down
			a1 = temp.x , a2 = temp.y+1;
			if(chk(a1,a2) && chk_brn(temp.born,'d')){
				tmp = temp;
				++ tmp.depth;
				tmp.parent = father_id;
				tmp.child = ++id;
				tmp.map[a2-1][a1] = tmp.map[a2][a1];
				tmp.map[a2][a1] = 16;
				++tmp.y;
				tmp.born='d';
				tmp.score = tmp.depth + man(tmp);
				q.push_back(tmp);
				all_nodes.push_back(tmp);
			}
			q.erase(q.begin());
			sort(q.begin(),q.end(),sort_q);
			//
//            system("cls");
//            print(temp);
            cout<<"\nSTEP: "<<c;
            ++c;
//            cout<<"\n depth:"<<temp.depth<<" temp score:"<<temp.score<<" self id:"<<temp.child<<"\n---------------------------\n";
//			cout<<"\n++++++++++++++++++++++++++++++++\n";
////			sleep(1);
		}
		else{
//			system("cls");
//            print(temp);
//            cout<<"\nSTEP: "<<c;
//            ++c;
//            cout<<"\n depth:"<<temp.depth<<" temp score:"<<temp.score<<" self id:"<<temp.child<<"\n---------------------------\n";
//			cout<<"\n U WON!!! \n";
			//int self=temp.child,parent=-1;
			all_nodes.push_back(temp);
			path.push_back(temp);
			node baba;
			while(temp.parent){
				baba = search_baba(all_nodes,temp.parent);
				path.push_back(baba);
				temp = baba;
			}
			break;
		}
	}
	cout<<"\nSTEP: "<<c<<"\n";
	cout<<"\nCalculation Finished,\nPress any key to WATCH steps...!!\n";
	getch();
	for(int i=path.size()-1;i>=0;--i){
		system("cls");
		print(path[i]);
		cout<<"depth:"<<path[i].depth<<" , born:"<<path[i].born<<"\n";
		sleep(1);
	}
	cout<<"U WON !!!";
	cout<<"\nSTEP: "<<c<<"\n";
	system("pause>NULL");
	return 0;
}

