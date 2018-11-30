//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Marco A Ramirez
// Version     :
// Copyright   : Al que copia no se le acopla 
// Description : Get the pre, in and post order and minimum and maximum data
//============================================================================

#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

class Node
{
	private:
		int 	Data	;
		Node* 	Left	;
		Node* 	Right	;

	public:
		Node(int d = 0, Node* L =nullptr, Node* R = nullptr):Data(d), Left(L), Right(R){}

		//Setters
		void setData (int d)  { Data  = d; }
		void setLeft (Node* l){ Left  = l; }
		void setRight(Node* r){ Right = r; }

		//Getters
		int   getData (){ return Data ; }
		Node* getLeft (){ return Left ; }
		Node* getRight(){ return Right; }

		//Printers
		void printData (){ cout << Data ; }
		void printLeft (){ cout << Left ; }
		void printRight(){ cout << Right; }
		void printAll  (){
							cout << " Node(" << this << "):" << endl;
							if(this == nullptr){ cout << "\t[Null Node]" << endl; return; }
							cout << " \tData : " << Data    << endl;
							cout << " \tLeft : " << Left    << endl;
							cout << " \tRight: " << Right   << endl;
						 }

		//Doers
		bool hasLeftChild (){ return this->getLeft()  != nullptr ? true : false; }
		bool hasRightChild(){ return this->getRight() != nullptr ? true : false; }
		bool hasChildren  (){ return this->hasLeftChild() || this->hasRightChild() ? true : false; }
};

class BinarySearchTree
{
	private:
		string 			Name;
		int 			Size;
		int             Levels;
		int				Height;
		int				Width;
		Node* 			Root;
		Node*			EmptyNode;

	public:
		BinarySearchTree(string n = "Binary Search Tree 0"):Name(n)
		{
			Root = nullptr;
			Size = 0;

			EmptyNode = new Node(0);
		}

		//Setters
		void setName(string n){ Name = n; }

		//Getters
		string 	getName(){ return Name; }
		int		getSize(){ return Size; }
		Node*	getRoot(){ return Root; }

		//Print
		void printName(){ cout << Name; }
		void printSize(){ cout << Size; }
		void printRoot(){ cout << Root; }
		void printInfo(){ 	cout << "<<<- " << Name << " ->>>" << endl;
							cout << "\tNumber of Nodes: " << Size << endl;
							cout << "\tHeight: " << Height << " Levels: " << Levels << endl << endl;
							cout << "\tRoot      Node : " << Root << endl;
						}

		void printLevelOrder() //Print Tree values in Level Order (Breadth First)
		{
			if(this->isEmpty()){ cout << " Tree is empty! " << endl; return; }

			queue <Node*> Nq;
			int nodes = 0;
			int level = 0;
			int maxns = 1;

			Nq.push(Root);

			while(!Nq.empty())
			{
				Node* currentnode = Nq.front();
				cout << currentnode->getData() << " ";

				if(currentnode->hasLeftChild ()){ Nq.push(currentnode->getLeft ()); }
				if(currentnode->hasRightChild()){ Nq.push(currentnode->getRight()); }

				Nq.pop();
			}

			cout << endl;
		}

		void printTree() //Experimental
		{
			if(this->isEmpty()){ cout << " Tree is empty! " << endl; return; }

			vector<Node*> Nvec;
			vector<vector<Node*>> Lmat;
			queue <Node*> Nq;
			int nodes = 0;
			int level = 0;
			int maxns = 1;

			Nq.push(Root);

			while(!Nq.empty())
			{
				Node* currentnode = Nq.front();
				Nvec.push_back(currentnode);

				if(currentnode->hasChildren())
				{
					if(currentnode->hasLeftChild ()){ Nq.push(currentnode->getLeft ()); }else{ Nq.push(EmptyNode); }
					if(currentnode->hasRightChild()){ Nq.push(currentnode->getRight()); }else{ Nq.push(EmptyNode); }
				}
				else if(!currentnode->hasChildren() && currentnode != EmptyNode)
				{
					Nq.push(EmptyNode); Nq.push(EmptyNode);
				}
				if(currentnode == EmptyNode && level < Levels){ Nq.push(EmptyNode); Nq.push(EmptyNode); }

				Nq.pop();

				nodes++;
				if(nodes == maxns)
				{
					level++;
					if(level == Levels) { break; }
					maxns = pow(2, level);
					nodes = 0;
				}
			}

			cout << endl;

			level = 0;
			maxns = 1;
			vector<Node*> v;

			for(auto n : Nvec)
			{
				v.push_back(n);

				if(v.size() == maxns)
				{
					level++;
					maxns = pow(2, level);
					Lmat.push_back(v);
					v.clear();
				}
			}

			Width  = Lmat[Lmat.size() - 1].size();

			int W = Width * 25; //Tweak multiplier to modify tree print width (normal = 25)
			int H = Levels;
			level = 0;
			cout << endl << endl;
			for(auto lvl : Lmat)
			{
				//Data Print
				for(auto n : lvl)
				{
					int ww = (W/(pow(2,level + 1)) ) / 2;

					if(level == 0)
					{
						spacer(ww);
					}
					else
					{
						spacer(ww);
					}

					if(n != EmptyNode){ cout << n->getData(); }

					spacer(ww);
				}

				cout << endl;

				//Line Print
				for(auto n : lvl)
				{
					int ww = (W/(pow(2,level + 1)) ) / 2;
					int ww2 = ww / 2;

					if(level == 0)
					{
						spacer(ww - ww2 - 1);
						if(n->hasLeftChild()){ repeatChar(95, ww - ww2); }else { repeatChar(32, ww - ww2); }
					}
					else
					{
						spacer(ww - ww2);
						if(n->hasLeftChild()){ repeatChar(95, ww2); }else { repeatChar(32, ww - ww2); }
					}

					if(n->hasChildren() && level != H - 1){ cout << "|"; }

					if(n->hasRightChild()){ repeatChar(95, ww - ww2); }else { repeatChar(32, ww - ww2); }
					spacer(ww - ww2 + 1);
				}

				cout << endl;
				level++;
			}
		}

		//Doers
		bool isEmpty(){	return Root == nullptr ? true : false; }

		void buildTree(vector<int> vec)
		{
			for(auto i : vec){ *this + new Node(i); }
		}

		void operator +(Node* n)
		{
			if(Size == 0)
			{
				Root = n;
			}
			else
			{
				addtoNode(n, Root);
			}

			Size++;
			Height = maxDepth(Root);
			Levels = Height + 1;
		}

		void operator +(vector<int> &vec)
		{
			for(auto i : vec){ 
                *this + new Node(i); }
		}

		Node* operator ==(int i)	//Search
		{
			if(Size == 0){	cout << " Tree is empty! " << endl; return nullptr; }

			return findData(i, Root);
		}

		void printNode(Node* p)
		{
			p->printAll();
		}

	//INSERT YOUR CODE HERE-----------------------------------------------------------------------------------

        int getmin(){
            queue <Node*> Q;

            Q.push(Root);
            Node* currentnode = Q.front();

            while(!Q.empty()){
                if(!currentnode->hasLeftChild()){ return currentnode->getData(); }
                currentnode = currentnode->getLeft();
            }

        }

        int getmax(){
            queue <Node*> Q;

            Q.push(Root);
            Node* currentnode = Q.front();

            while(!Q.empty()){
                if(!currentnode->hasLeftChild()){ return currentnode->getData(); }
                currentnode = currentnode->getRight();
            }

        }




        void printPreO(Node* currentnode){
           if ( currentnode == nullptr  ){ return;};
            cout << currentnode->getData() << " " ;
            printPreO(currentnode->getLeft());
            printPreO(currentnode->getRight());
        }

        void printInO(Node* currentnode){
             if ( currentnode == nullptr  ){ return;};
            printInO(currentnode->getLeft());
            cout << currentnode->getData() << " " ;
            printInO(currentnode->getRight());
        }

        void printPostO(Node* currentnode){
            if ( currentnode == nullptr  ){ return;};
            printPostO(currentnode->getLeft());
            printPostO(currentnode->getRight());
            cout << currentnode->getData() << " " ;
        }

	//INSERT YOUR CODE HERE-----------------------------------------------------------------------------------

	private:
		//Helpers
		void addtoNode(Node* node2add, Node* currentnode)
		{
			if(currentnode == nullptr){ return; }
			else if(node2add->getData() < currentnode->getData())
			{
				if(currentnode->getLeft() == nullptr)
				{
					currentnode->setLeft(node2add);
					return;
				}
				addtoNode(node2add, currentnode->getLeft());
			}
			else if(node2add->getData() > currentnode->getData())
			{
				if(currentnode->getRight() == nullptr)
				{
					currentnode->setRight(node2add);
					return;
				}
				addtoNode(node2add, currentnode->getRight());
			}

			return;
		}

		Node* findData(int data2find, Node* currentnode)
		{
			if(currentnode == nullptr){ return nullptr; }
			else if(data2find == currentnode->getData())
			{
				cout << "Found Data: " << data2find << " @ Node(" << currentnode << ")" << endl;
				return currentnode;
			}
			else if ( (currentnode->getLeft() == nullptr) && (currentnode->getRight() == nullptr) )
			{
				cout << "Data: " << data2find << " not found." << endl;
				return currentnode;
			}
			else if(data2find < currentnode->getData())
			{
				findData(data2find, currentnode->getLeft());
			}
			else if(data2find> currentnode->getData())
			{
				findData(data2find, currentnode->getRight());
			}

			return nullptr;
		}

		int maxDepth(Node* currentnode)
		{
			if(currentnode == nullptr){ return -1 ; }
			else
			{
				int lst_depth = maxDepth(currentnode->getLeft());
				int rst_depth = maxDepth(currentnode->getRight());

				return lst_depth > rst_depth ? ++lst_depth : ++rst_depth;
			}
		}

		void repeatChar(char c, unsigned int i){ while(i-- > 0){ cout << c; } }
		void spacer(int i){ while(i-- > 0){ cout << " " ; } }
};

int main() {
	BinarySearchTree BST;
	vector<int> v = {10, 6, 8, 7, 9, 3, 2, 4, 14, 12, 16, 18, 15, 11, 13};
	BST + v; 		 				//Create Tree from vector
	cout << (BST == 31) << endl;	//Search for 31 in tree
	BST.printInfo();		 		//Print Tree Info
	BST.printLevelOrder();			//Print Nodes in Level Order
	BST.printTree();				//Print Tree

	//INSERT YOUR CODE HERE-----------------------------------------------------------------------------------
    
    cout << "The minimum number is " << BST.getmin() << endl;

    cout << "the maximum value is " << BST.getmax() << endl;

    BST.printPreO(BST.getRoot());
    cout << endl;

    BST.printInO(BST.getRoot());
    cout << endl;

    BST.printPostO(BST.getRoot());
    cout << endl;
	//INSERT YOUR CODE HERE-----------------------------------------------------------------------------------

	return 0;
}