/*
 * space.hpp
 *
 *  Created on: 3 Nov 2021
 *      Author: zvias
 */

#ifndef SRC_SPACE_HPP_
#define SRC_SPACE_HPP_
#include <iostream>
#include "point3D.h"
class space{
public:
	double xd,xu,yd,yu,zd,zu;
	friend std::ostream& operator<< (std::ostream& out, const space& s);
	space(){
		xd=-1;
		xu=-1;
		yd=-1;
		yu=-1;
		zd=-1;
		zu=-1;
	}
	space(double _xd,double _xu,double _yd,double _yu,double _zd,double _zu){
		this->xd=_xd;
		this->xu=_xu;
		this->yd=_yd;
		this->yu=_yu;
		this->zd=_zd;
		this->zu=_zu;
	}
	static space* newSpace(){
		space* temp=new space;
		return temp;
	}
	void operator =(const space &_s){
		this->xd=_s.xd;
		this->xu=_s.xu;
		this->yd=_s.yd;
		this->yu=_s.yu;
		this->zd=_s.zd;
		this->zu=_s.zu;
	}
	void set(double _xd,double _xu,double _yd,double _yu,double _zd,double _zu){
		this->xd=_xd;
		this->xu=_xu;
		this->yd=_yd;
		this->yu=_yu;
		this->zd=_zd;
		this->zu=_zu;
	}
	bool PointInSpace(const point3D& _p){
		bool x=(_p.x>this->xd)&&(_p.x<this->xu)&&(_p.y>this->yd)&&(_p.y<this->yu)&&(_p.z>this->zd)&&(_p.z<this->zu);
		return x;
	}
//	}
//	bool operator<(const point3D& P){
//		bool x=P.x<this.xd&&P.y<this.yd&&P.z<this.zd;
//		return x;
//	}

};
ostream& operator<<(ostream& os, const space& s)
{
    os << "(xd,xu)=("<<s.xd<< ","<<s.xu<< ");(yd,yu)=("<<s.yd<< ","<<s.yu<< ");(zd,zu)=("<<s.zd<< ","<<s.zu<<");" ;
    return os;
}



#endif /* SRC_SPACE_HPP_ */
