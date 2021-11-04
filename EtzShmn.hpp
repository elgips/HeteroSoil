/*
 * EtzShmn.h
 * A class for general octree structures
 *  Created on: 03/11/21
 *      Author: El'ad Gips
 */

#ifndef ETZSHMN_H_
#define ETZSHMN_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <cstdio>
#include <random>
#include<fstream>
#include<sstream>
#define Nchild 8;// 8 child nodes for each mid node
using namespace std;

template <typename T>
class node{
public:
	T 				value;// value variable(s) of the node
	bool 			state;// type of node - leaf 0 or mid 1 node
	node* 			children[8];// pointers array of the nodes children - 8 children for each mid-node
	node* 			parent;// a pointer to the node's parent node
/*Node constructor
 * INPUT - T _value		-node value-variables values
 * 		   node* _parent-[ parent node pointer
 *OUTPUT - a pointer to a defined new node*/
	static node* newNode(T _value,node* _parent){
		node* temp=new node;
		temp->state=false;//wet node as child node
		temp->value=_value;//set node's value-variables values'
		temp->parent=_parent;//set node's parent pointer
		if(_parent!=0x0)
			_parent->setStateP();// set the parent node state to 'parent'
		return temp;
	}
	/*setStateP()
	 * Set the node state to parent*/
	void setStateP(){
		this->state=true;
	}
	 /*setStateC()
	  *Set the node state to child and disconnect it from its children*/
	void setStateC(){
		this->state=false;
		this->children={0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
	}
	/*appendChild
	 * append a Child to a parent (Seems unnes it this case)
	 * INPUT: node* _parent - parent node pointer,node* _child - child node pointer ,unsigned int _childNum - child index from parent children,
	 * OUTPUT - NON*/
	static void appendChild(node* _parent,node* _child,unsigned int _childNum){
		if(notMyPapa(_parent, _child)){
			_child->parent=_parent;
			_parent->setStateP();
			_parent->children[_childNum]=_child;
		}
		else{
			invalid_argument("there is a loop in the tree");
			terminate();
		}
	}
	/*Check there is no inner loop
	 *
	 * INPUT: node* _parent - parent node pointer,node* _child - child node pointer
	 * 	 * OUTPUT - boolean val - 1 : no loop, 0 there is a loop*/
	static bool notMyPapa(node* _parent,node* _child){
		node* ancestor=_parent;
		bool fatherLikeSon=false;
		while(ancestor!=0x0){
			fatherLikeSon=(fatherLikeSon||(_child==ancestor));
			if(fatherLikeSon)return !fatherLikeSon;
			ancestor=ancestor->parent;
		}
		return !fatherLikeSon;
	}
//	/*Check if child is a branch of ancestor
//		 *
//		 * INPUT: node* _parent - parent node pointer,node* _child - child node pointer
//		 * 	 * OUTPUT - boolean val - 1 :it is a branch, 0 there it is not*/
//	static bool isMember(node* _parent,node* _child){
//		bool x=(_parent==_child);
//		typename vector<node<T>*>::iterator it;
//		if(!x){
//			if(_parent->state){
//				for(it=_parent->children.begin();(it!=_parent->children.end())&&(!x);it++){
//					x=+isMember(*it,_child);
//				}
//			}
//		}
//		return x;
//	}
	/*A print overload must be preperd for non standard templates */
	void TreePrintAux(node* _child,ofstream* out){
		*out<<endl;
		*out<<*(_child->value);
		if(_child->state){
			typename vector<node<T>*>::iterator it;
			for(unsigned int i=0;i<=7;i++){
				TreePrintAux(_child->children[i],out);
			}
		}
	}
	void topToBottom2Text(string _fileName){
		ofstream out( _fileName.c_str(), ios::out );
		out<<*(this->value);
		if(this->state){
			typename vector<node<T>*>::iterator it;
			for(unsigned int i=0;i<=7;i++){
				TreePrintAux(this->children[i],&out);
			}
		}
		out.close();
	}
	static void copySubTreeAux(node* _root,node* _parent,unsigned int _childNum){
		node* n=newNode(_root->value, _parent);
		_parent->appendChild(_parent, n,_childNum);
		typename vector<node<T>*>::iterator it;
		for(unsigned int i=0;i<=7;i++){
			copySubTreeAux(_root->children[i],n);
		}
	}
	node* copySubTree(node* _root){
		node *n=newNode(_root->value,NULL);
		typename vector<node<T>*>::iterator it;
		for(unsigned int i=0;i<=7;i++){
			copySubTreeAux(_root->children[i],n);
		}
		return n;
	}

//	static void cutBranch(node* _branch){
//		node* parent=_branch->parent;
//		bool f=false;
//		_branch->parent=NULL;
//		typename vector<node<T>*>::iterator it;
//		for(it=parent->children.begin();(it!=parent->children.end())&&(!f);it++){
//			if(&(*it)==_branch){
//				parent->children.erase(it);
//				f=true;
//			}
//		}
//	}
};



#endif /* ETZSHMN_H_ */
