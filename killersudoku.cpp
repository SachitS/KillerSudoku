#include<iostream>
using namespace std;
int A[9][9]={0}; //Final matrix
int n; // number of cages
void print();
struct index{ //struct of element
	int x; //x co-ordinate
	int y; //y co-ordinate
	index(){ //constructor
		x=0;
		y=0;
	}
	index& operator=(index& i){ //overload = operator, refer line 35
		this->x=i.x;
		this->y=i.y;
		return *this;
	}
};
struct cage{
	int num; //number of elements in the cage
	int sum; //sum of cage
	index cells[81];
	cage(){ //constructor
		num=0;
		sum=0;
		for(int j=0;j<9;j++){
			cells[j].x=0;
			cells[j].y=0;
		}
	}
	cage& operator=(cage & c){ //overload = operator, refer line 138
		this->num=c.num;
		this->sum=c.sum;
		for(int i=0;i<c.num;i++){
			this->cells[i]=c.cells[i];
		}
		return *this;
	}
};
bool rowCheck(index t, int num){ //Check if incoming 'num' is different than all elements in row
	for(int i=0; i<9; i++){
		if(A[t.x][i]==num){
			return 0;
		}
	}
	return 1;
}
bool colCheck(index t, int num){ //Check if incoming 'num' is different than all elements in column
	for(int i=0; i<9; i++){
		if(A[i][t.y]==num){
			return 0;
		}
	}
	return 1;
}
bool boxCheck(index t, int num){ //Check if incoming 'num' is different than all elements in nonet/box
	int xf=(t.x/3)*3, yf=(t.y/3)*3;
	for(int i=xf;i<xf+3;i++){
		for(int j=yf;j<yf+3;j++){
			if(A[i][j]==num && t.x != i && t.y != j){
				return 0;
			}
		}
	}
	return 1;
}
bool cageCheck(index t,int num,cage c){ //Check if incoming 'num' is different than all elements in cage
	for(int i=0;i<c.num;i++){
		if(A[c.cells[i].x][c.cells[i].y]==num){
			return 0;
		}
	}
	return 1;
}
bool valid(index t,int num, cage c){ //check for validity of num at index t
	bool check;
	check=rowCheck(t,num);
	if(check==0){
		return 0;
	}
	check=colCheck(t,num);
	if(check==0){
		return 0;
	}
	check=boxCheck(t,num);
	if(check==0){
		return 0;
	}
	check=cageCheck(t,num,c);
	if(check==0){
		return 0;
	}
	check=(num<=c.sum);
	if(check==0){
		return 0;
	}
	A[t.x][t.y]=num; //temp assignment to the element
	int isZero=0; 
	for(int i=0;i<c.num;i++){ //to check if there is a zero element in cage
		if(A[c.cells[i].x][c.cells[i].y]==0){
			isZero=1;
		}
	}
	int sumtemp=0;
	if(isZero==0){ // if there is no zero element then check that sum is equal to cage.sum
		for(int i=0;i<c.num;i++){
			sumtemp +=	A[c.cells[i].x][c.cells[i].y];
		}
		if(sumtemp==c.sum){
			return check;
		}
		else{
			A[t.x][t.y]=0;
			return 0;
		}
	}
	A[t.x][t.y]=0;
	return check;
}
bool emptyelem(int &row, int &col){ //finding first empty element
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (A[row][col] == 0)
                return true;
    return false;
	}
bool solve(cage p[]){ //actual solving function.
	cage cager; //cage of (row,column)
	index t; //index of (row,column)
	int row,col;
	if (!emptyelem(row, col)) //row,col passed by reference so that we get first empty element
       return true;
	t.x=row; //assigning t to (row,column)
	t.y=col;
	for(int i=0;i<n;i++){ //loop to assign cager
		for(int j=0;j<p[i].num;j++){
			if(p[i].cells[j].x == t.x && p[i].cells[j].y == t.y){
				cager=p[i]; //assign cager to the cage in which t is there.
			}
		}
	}
	for (int num = 0; num <= 10; num++) //backtracking
    {
    	if(num==10){ //if num tries to take value 10, then return false
    		A[row][col]=0;
    		return false;
    	}
        if (valid(t, num, cager)) // check for validity of num at index t
        {
            A[row][col] = num;
            if (solve(p))
                return true;
            A[row][col] = 0;
        }
    }
    return false; //triggers backtracking
}
void print(){ 
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			cout<<A[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}
int main(){
	cin>>n;
	cage store[n];
	for(int i=0;i<n;i++){
		cin>>store[i].num;
		cin>>store[i].sum;
		for(int j=0;j<store[i].num;j++){
			cin>>store[i].cells[j].x>>store[i].cells[j].y;
		}
	}
	solve(store);

	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			cout<<A[i][j]<<" ";
		}
		cout<<endl;
	}
}