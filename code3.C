#include <iostream>
#include <fstream>
#include <math.h>
#include <random>
#include <stdlib.h>
using namespace std;

float Force_x(float x1,float x2, float x3, float y1,float y2, float y3, float m1,float m2)
{
float G = 4*3.1415*3.1415;
float f;
f = -G*m1*(x1-x2)/(pow(pow((x1 - x2),2) + pow((y1 - y2),2) ,1.5)) - G*m2*(x1-x3)/(pow(pow((x1 - x3),2) + pow((y1 - y3),2) ,1.5));
return f;
}

float Force_y(float x1,float x2,float x3, float y1,float y2, float y3, float m1,float m2)
{
float G = 4*3.1415*3.1415;
float f;
f = -G*m1*(y1-y2)/(pow(pow((x1 - x2),2) + pow((y1 - y2),2) ,1.5)) - G*m2*(y1-y3)/(pow(pow((x1 - x3),2) + pow((y1 - y3),2) ,1.5));

return f;
}

float Force_x1(float x1,float x2,  float y1,float y2, float m1)
{
float G = 4*3.1415*3.1415;
float f;
f = -G*m1*(x1-x2)/(pow(pow((x1 - x2),2) + pow((y1 - y2),2) ,1.5) );
return f;
}

float Force_y1(float x1,float x2, float y1,float y2, float m1)
{
float G = 4*3.1415*3.1415;
float f;
f = -G*m1*(y1-y2)/(pow(pow((x1 - x2),2) + pow((y1 - y2),2) ,1.5));

return f;
}

int main(){

ofstream fout2;
//fout.open("data2.txt");
int n_p = 10000;
int n = 10000;
float h = 0.01;
float m1,m2;
float e1,a1;

std::random_device rd;
std::mt19937 eng(rd());
std::uniform_real_distribution<>distr(2,3);
float **x3,**y3,**v_x3,**v_y3;

float* t = new float[n];
float* x1 = new float[n];
float* x2 = new float[n];
 x3 = new float*[n_p];
float* y1 = new float[n];
float* y2 = new float[n];
y3 = new float*[n_p];
float* v_x1 = new float[n];
float* v_x2 = new float[n];
 v_x3 = new float*[n_p];
float* v_y1 = new float[n];
float* v_y2 = new float[n];
 v_y3 = new float*[n_p];

for( int k = 0; k < n_p; k++ ){
	x3[k] = new float[n];
	y3[k] = new float[n];
	v_x3[k] = new float[n];
	v_y3[k] = new float[n];
}

float pi = 3.1415;

m1 = 0.001;
m2 = 1.0;
e1 = 0.0;
a1= 5.2;
float m3 = 0.0;

x1[0] = 0.0;
x2[0] = 0.0;
y1[0] = 5.2;
y2[0] = 0.0;
v_x1[0] = -sqrt(4*pow(3.1415,2)/a1);
v_x2[0] = 0.0;
v_y1[0] = 0.0;
v_y2[0] = 0.0;
cout << v_x1[0] << endl;
cout << v_y1[0]*v_y1[0] + v_x1[0]*v_x1[0] << endl;

t[0] = 0.0;

float a ;
//Initial Conditions 
for(int i = 0; i < n_p; i++){

	a = distr(eng);
	x3[i][0] = 0.0;
	y3[i][0] = a;
	v_y3[i][0] = 0.0;
	v_x3[i][0] = -sqrt(4*pow(3.1415,2)/a);
}

for ( int i = 0 ; i < n_p ; i++){
	for (int j=0; j<n ; j++)
	{
	if(i == 0){
	t[j+1] = t[j] + h;
	x1[j+1] = x1[j] + h*v_x1[j];
	//x2[j+1] = x2[j] + h*v_x2[j];
	x2[j+1] = 0;
	y1[j+1] = y1[j] + h*v_y1[j];
	y2[j+1] = y2[j] + h*v_y2[j];

	v_x1[j+1] = v_x1[j] + h*Force_x1(x1[j+1],x2[j+1],y1[j+1],y2[j+1],m2);
	//v_x2[j+1] = v_x2[j] + h*Force_x1(x2[j+1],x1[j+1],y2[j+1],y1[j+1],m1);
	v_x2[j+1] = 0;
	v_y1[j+1] = v_y1[j] + h*Force_y1(x1[j+1],x2[j+1],y1[j+1],y2[j+1],m2);
	//v_y2[j+1] = v_y2[j] + h*Force_y1(x2[j+1],x1[j+1],y2[j+1],y1[j+1],m1);
	v_y2[j+1] = 0;
	}	
	x3[i][j+1] = x3[i][j] + h*v_x3[i][j];
	y3[i][j+1] = y3[i][j] + h*v_y3[i][j];
	v_x3[i][j+1] = v_x3[i][j] + h*Force_x(x3[i][j+1],x1[j+1],x2[j+1],y3[i][j+1],y1[j+1],y2[j+1],m1,m2);
	v_y3[i][j+1] = v_y3[i][j] + h*Force_y(x3[i][j+1],x1[j+1],x2[j+1],y3[i][j+1],y1[j+1],y2[j+1],m1,m2);
	}
	}

cout << v_y1[0]*v_y1[0] + v_x1[0]*v_x1[0] + 4*pi*pi*m1/(x1[0]*x1[0]+y1[0]*y1[0])<< endl;

//#pragma omp for



	fout2.open("distances2.txt");
	for ( int i = 0 ; i < n_p ; i++){
		//fout2<<sqrt(x3[i][n]*x3[i][n]+y3[i][n]*y3[i][n])<<endl;
		fout2 << x3[i][n] << y3[i][n] << endl;
	}





}



