/*
 * hetrospace.hpp
 *
 *  Created on: 3 Nov 2021
 *      Author: zvias
 */

#ifndef SRC_HETEROSPACE_HPP_
#define SRC_HETEROSPACE_HPP_
#include "EtzShmn.hpp"
#include "space.hpp"
typedef node<space> nodeSP;

class heterospace{
public:
	nodeSP* SpaceTree;
	heterospace(space* S){
		SpaceTree=nodeSP::newNode(*S, NULL);
	}
	heterospace(){
		SpaceTree=nodeSP::newNode(*(space::newSpace()),NULL);;
	}
	void divideSpace(){
		double mx,my,mz;//mid points
		mx=(this->SpaceTree->value.xd+this->SpaceTree->value.xu)/2;
		my=(this->SpaceTree->value.yd+this->SpaceTree->value.yu)/2;
		mz=(this->SpaceTree->value.zd+this->SpaceTree->value.zu)/2;
		space Ts;
		Ts.set(this->SpaceTree->value.xd, mx, this->SpaceTree->value.yd, my, this->SpaceTree->value.zd, mz);
		nodeSP::appendChild(SpaceTree, nodeSP::newNode(Ts, NULL),0);
		Ts.set( mx,this->SpaceTree->value.xu, this->SpaceTree->value.yd, my, this->SpaceTree->value.zd, mz);
		nodeSP::appendChild(SpaceTree, nodeSP::newNode(Ts, NULL),1);
		Ts.set( mx,this->SpaceTree->value.xu, my,this->SpaceTree->value.yu, this->SpaceTree->value.zd, mz);
		nodeSP::appendChild(SpaceTree, nodeSP::newNode(Ts, NULL),2);
		Ts.set(this->SpaceTree->value.xd,mx, my,this->SpaceTree->value.yu, this->SpaceTree->value.zd, mz);
		nodeSP::appendChild(SpaceTree, nodeSP::newNode(Ts, NULL),3);
		Ts.set(this->SpaceTree->value.xd, mx, this->SpaceTree->value.yd, my,mz, this->SpaceTree->value.zu);
		nodeSP::appendChild(SpaceTree, nodeSP::newNode(Ts, NULL),4);
		Ts.set( mx,this->SpaceTree->value.xu, this->SpaceTree->value.yd, my, mz, this->SpaceTree->value.zu);
		nodeSP::appendChild(SpaceTree, nodeSP::newNode(Ts, NULL),5);
		Ts.set( mx,this->SpaceTree->value.xu, my,this->SpaceTree->value.yu, mz, this->SpaceTree->value.zu);
		nodeSP::appendChild(SpaceTree, nodeSP::newNode(Ts, NULL),6);
		Ts.set(this->SpaceTree->value.xd,mx, my,this->SpaceTree->value.yu,mz, this->SpaceTree->value.zu);
		nodeSP::appendChild(SpaceTree, nodeSP::newNode(Ts, NULL),7);
	}
	nodeSP* getLeafSpacePointerFromPoint(const point3D& _p){
		nodeSP* tmp=nodeSP::newNode(*(space::newSpace()),NULL);
		int index;
		tmp=this->SpaceTree;
		if(!tmp->value.PointInSpace(_p)){
			out_of_range("The point is not in the space region");
			return 0x0;
			terminate();
		}
		else
			while(tmp->state){
				index=1*int(tmp->children[0]->value.PointInSpace(_p))
				+2*int(tmp->children[1]->value.PointInSpace(_p))
				+4*int(tmp->children[2]->value.PointInSpace(_p))
				+8*int(tmp->children[3]->value.PointInSpace(_p))
				+16*int(tmp->children[4]->value.PointInSpace(_p))
				+32*int(tmp->children[5]->value.PointInSpace(_p))
				+64*int(tmp->children[6]->value.PointInSpace(_p))
				+128*int(tmp->children[7]->value.PointInSpace(_p));
				switch(index){
				case 1:
					tmp=tmp->children[0];
					break;
				case 2:
					tmp=tmp->children[1];
					break;
				case 4:
					tmp=tmp->children[3];
					break;
				case 8:
					tmp=tmp->children[4];
					break;
				case 16:
					tmp=tmp->children[5];
					break;
				case 32:
					tmp=tmp->children[6];
					break;
				case 64:
					tmp=tmp->children[7];
					break;
				default:
					out_of_range("The point is on boundery, use real values and not natural");
					return 0x0;
				}
			}
				return tmp;

			}
	};



#endif /* SRC_HETEROSPACE_HPP_ */
