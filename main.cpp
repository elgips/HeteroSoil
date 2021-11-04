/*
 * main.cpp
 *
 *  Created on: Dec 31, 2020
 *      Author: gips
 */
#include <cstdio>
#include <iostream>
#include <iomanip>
#include "heterospace.hpp"


int main(){
space s(0.0,1.0,0.0,1.0,0.0,1.0);
point3D p(0.501,0.498,0.2);
point3D p2(1.2,1.2,1.2);
space* sa=&s;
heterospace HS(sa);
nodeSP* N1;
nodeSP* N2;
N1=HS.getLeafSpacePointerFromPoint(p);
HS.divideSpace();
N2=HS.getLeafSpacePointerFromPoint(p);
cout <<s<<endl;
bool x=s.PointInSpace(p);
cout << x<<endl;
char a='a';
int b=1;
char c=a*b;
cout<<c;
}
