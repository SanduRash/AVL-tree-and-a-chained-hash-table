//Sandu Galbokka Hewa
//March 27, 2025
//Project 2 Data Structures and Algorithms: Hash Tables & AVL Trees

#include <iostream>
#include <fstream>
#include <string>
using namespace std;



/////////////////////////////////////////////////////// Creating HASH Table 

class linkNode{ // Create a class called linkNode
private:
  string _keyData; // Store name
  string _valueData;// Store contact number
  linkNode *_next;// Pointing to next 

  int _lenOfChain; // Length of each chain

  
public:
  linkNode(): _keyData(""), _valueData(""), _next(nullptr), _lenOfChain(1) {}
  linkNode(string _keydata, string _valuedata): _keyData(_keydata), _valueData(_valuedata), _next(nullptr), _lenOfChain(1) {}

  string keyData() const{return _keyData;}
  string& KeyData() {return _keyData;}

  string valueData() const{return _valueData;}
  string& valueData() {return _valueData;}

  linkNode* next() const{return _next;}
  linkNode* &next() {return _next;}

  int lenOfChain() const{return _lenOfChain;}
  int& lenOfChain() {return _lenOfChain;}

  bool isNextNull() {
    if(_next == nullptr)
      return true;
    else
      return false;
  }

   std::ostream& print(std::ostream &toStream) const
  {
    toStream << _keyData << "  "<< _valueData << endl;

    return toStream;
  }

};


int findSlot(string keyData, int size){  // This fuction will find which array slot the information should be store
  int tot = 0;
  int slotNum;
  
  for(unsigned int i =0;i<keyData.size();i++)
    tot += (int) keyData[i];

  slotNum = tot%size;
  return slotNum;
}


////////////////////////////////////////////////  Creating AVLTreeNode Class

class AVLTreeNode
{
private:
  string _keyData;
  string _valueData;
  AVLTreeNode *_left;
  AVLTreeNode *_right;
  AVLTreeNode *_parent;

  int _height;
  
public:
  AVLTreeNode(string _keydata, string _valuedata) : _keyData(_keydata), _valueData(_valuedata), _left(nullptr), _right(nullptr), _parent(nullptr), _height(1) {}

  string keyData() const {return _keyData;}
  string& keyData() {return _keyData;}

  string valueData() const {return _valueData;}
  string& valueData() {return _valueData;}

  AVLTreeNode* left() const{return _left;}
  AVLTreeNode* &left() {return _left;}

  AVLTreeNode* right() const {return _right;}
  AVLTreeNode* &right() {return _right;}

  AVLTreeNode* parent() const {return _parent;}
  AVLTreeNode* &parent() {return _parent;}

  int height() const {return _height;}
  int& height() {return _height;}

  bool isLeaf() const {return !_left && !_right;}
  bool isRoot() const {return !_parent;}

  int depth() const{
    int numAncestors = 0;
    AVLTreeNode *parentptr = _parent;

    while(parentptr != nullptr){
      numAncestors++;
      parentptr = parentptr->parent();
    }

    return numAncestors;
  }

  std::ostream& print(std::ostream &toStream) const
  {
    toStream << _keyData << "  "<< _valueData << endl;

    return toStream;
  }
  
};

AVLTreeNode* findHelper(AVLTreeNode *inSubTree, string keyToFind)
{
    if (!inSubTree)
        return nullptr;

    if (inSubTree->keyData() == keyToFind)
        return inSubTree;

    if (inSubTree->keyData() < keyToFind)
        return findHelper(inSubTree->right(), keyToFind);

    // must be in left subtree (or we would already have returned)
    return findHelper(inSubTree->left(), keyToFind);
}

int getHeight(const AVLTreeNode *subTree)
{
  if(!subTree)
    return 0;
  else
    return subTree->height();
}



// a single rotation , pulling up left child
//  k2 - the current root. 
//  returns the new root. 
AVLTreeNode* rotateRight(AVLTreeNode *k2)
{
  AVLTreeNode *subtreeParent = k2->parent();
  // NOTE: See course notes for picture of what k1 and k2 (and Y) mean here
  AVLTreeNode *k1 = k2->left();
  k2->left() = k1->right(); // Y
  k1->right() =  k2;

  // we just moved things around. Update associated subtree heights. 
  k2->height() = 1 + max (getHeight(k2->left()), getHeight(k2->right()) );
  k1->height() = 1 + max (getHeight(k1->left()), getHeight(k2) );

  // fix parent ptrs.
  k2->parent() = k1;
  if (k2->left()) k2->left()->parent()=k2; // patch Y's parent
  k1->parent() = subtreeParent;

  return k1;
}

// a single rotation , pulling up right child
//  k2 - the current root. 
//  returns the new root. 
AVLTreeNode* rotateLeft(AVLTreeNode *k2)
{
  AVLTreeNode *subtreeParent = k2->parent();

  // NOTE: See course notes for picture of what k1 and k2 (and Y) mean here
  AVLTreeNode *k1 = k2->right();
  k2->right() = k1->left(); // Y
  k1->left() =  k2;

  // we just moved things around. Update associated subtree heights. 
  k2->height() = 1 + max (getHeight(k2->left()), getHeight(k2->right()) );
  k1->height() = 1 + max (getHeight(k1->right()), getHeight(k2) );

  // fix parent ptrs.
  k2->parent() = k1;
  if (k2->right()) k2->right()->parent()=k2; // patch Y's parent
  k1->parent() = subtreeParent;

  return k1;
}

AVLTreeNode* doubleWithLeftChild(AVLTreeNode *k3)
{
  AVLTreeNode *k1 = k3->left();
  k3->left() = rotateLeft(k1);
  return rotateRight(k3);
}

AVLTreeNode* doubleWithRightChild(AVLTreeNode *k3)
{
  AVLTreeNode *k1 = k3->right();
  k3->right() = rotateRight(k1);
  return rotateLeft(k3);
}


AVLTreeNode* insertHelper(AVLTreeNode *intoSubTree, string keyToAdd, string valToAdd)
{
    if (intoSubTree == nullptr) // empty tree!
    {
      AVLTreeNode *newTree = new AVLTreeNode(keyToAdd, valToAdd);
        return newTree;
    }
    if (keyToAdd < intoSubTree->keyData() )
    {
        // want to insert in left subtree
      AVLTreeNode *newSubTree = insertHelper(intoSubTree->left(), keyToAdd, valToAdd);
        intoSubTree->left() = newSubTree;
        newSubTree->parent() = intoSubTree;

        // might need AVL rotations ... look at children's heights to decide
        int leftHeight = getHeight(intoSubTree->left());
        int rightHeight = getHeight(intoSubTree->right());

        // left imbalance
        if (leftHeight-rightHeight==2) 
	{
	  // is this a left-left imbalance?
	  if (keyToAdd < intoSubTree->left()->keyData() )
	  {
	      intoSubTree=rotateRight(intoSubTree);
	  }
	  // or is it a left-rght imabalance?
	  else
	  {
	      intoSubTree=doubleWithLeftChild(intoSubTree);
	  }
	}
    }
    else if (keyToAdd > intoSubTree->keyData() )
    {
        // want to insert into right subtree
        AVLTreeNode *newSubTree = insertHelper(intoSubTree->right(), keyToAdd, valToAdd);
        intoSubTree->right() = newSubTree;
        newSubTree->parent() = intoSubTree;

        // might need AVL rotations ... look at children's heights to decide
        int leftHeight = getHeight(intoSubTree->left());
        int rightHeight = getHeight(intoSubTree->right());

        // check for right imbalance
        if (rightHeight-leftHeight==2) 
	{
	  // is this a right-right imbalance?
	  if (keyToAdd >  intoSubTree->right()->keyData() )
	    {
	      intoSubTree=rotateLeft(intoSubTree);
	    }
	  // or is it a right-left imabalance?
	  else
	    {
	      intoSubTree=doubleWithRightChild(intoSubTree);
	    }
	}
    }
    else // == ... so already found in subtree!!
    {
      
    }

    // now that we've mved things areound, need to update this nodes height. 
    intoSubTree->height() = 1 + max(getHeight(intoSubTree->left()),
				    getHeight(intoSubTree->right()) ); 
    return intoSubTree;
}



class AVLTree{

private:
  AVLTreeNode *_root;
public:
  AVLTree() : _root(nullptr) {}

  AVLTreeNode* root() const {return _root;};

  AVLTreeNode* find(string keyToFind){
    return findHelper(_root, keyToFind);
  };

  void insert(string newKey, string newVal)
    {
      _root=insertHelper(_root, newKey, newVal);
    };

};





////////////////////////////////////////////////////// MAIN

int main(int argc, char *argv[])
{
  ifstream ifile(argv[1]);
  string name;
  string contactNum;

  string sortMethod = argv[2];

  ///////////////////////////////////// if user needs to do avl method then create a AVLTree.
  if (sortMethod == "avl")
    {

      AVLTree myTree;
      ifile >>name;
      ifile >>contactNum;
      
      while(ifile)
	{
	  myTree.insert(name, contactNum);// Read data inside of the file and insert those data into AVL tree.
	  
	  ifile >>name;
	  ifile >>contactNum;
	  
	}
      
      cout<<"Tree Height: "<<myTree.root()->height()<<endl;
      
      string ch;
      string nametofind;
      
      while(ch != "q")
	{
	  cin >> ch;
	  
	  if(ch == "g")// if ch is g, show the relevent contact number
	    {
	      cin >> nametofind;
	      cout<<myTree.find(nametofind)->valueData()<<endl;
	    }
	  
	  if(ch == "u")
	    {
	      cin >> nametofind;
	      string newContactNum;
	      cin >> newContactNum;
	      
	      myTree.find(nametofind)->valueData() = newContactNum; // update the previous contact number into new one
	    }
	}
      
    }


  //////////////////////////////////////////// if the user needs to do a hash method, create a array and then combine it with link list
  else if (sortMethod == "hash")
    {
      
      int size = atoi(argv[3]);  
      linkNode* arr = new linkNode[size];
      linkNode* newNode;
      linkNode* temp;
      int maxChainLen = 0;
      
      ifile >>name;
      ifile >>contactNum;


      
      while(ifile)
	{      
	  int indx = findSlot(name, size);
	  
	  if(arr[indx].keyData() == "")
	    {
	      arr[indx] = linkNode(name, contactNum);
	      
	      if (maxChainLen <= arr[indx].lenOfChain())
		maxChainLen = arr[indx].lenOfChain();
	    }
	  else
	    {
	      newNode = new linkNode(name, contactNum);
	      if(arr[indx].lenOfChain() == 1)
		{
		  arr[indx].next() = newNode;
		  arr[indx].lenOfChain()++;
		  if (maxChainLen <= arr[indx].lenOfChain())
		    maxChainLen = arr[indx].lenOfChain();
		}
	      else
		{
		  temp = arr[indx].next();
		  
		  while(!(temp->isNextNull()))
		    {
		      temp = temp->next();
		    }
		  
		  temp->next() = newNode;
		  arr[indx].lenOfChain()++;
		  
		  if (maxChainLen <= arr[indx].lenOfChain())
		    maxChainLen = arr[indx].lenOfChain();
		}
	    }
	  
	  ifile >>name;
	  ifile >>contactNum;
	}


      
      
      cout<<"Max Chain Length: "<<maxChainLen<<endl;



      
      string ch;
      string nametofind;
      
      while (ch != "q")
	{
	  cin >> ch;
	  
	  
	  if(ch == "g")
	    {
	      cin >> nametofind;
	      int index = findSlot(nametofind, size);
	      
	      
	      if(arr[index].keyData()== nametofind)
		cout<<arr[index].valueData()<<endl;
	      else
		{
		  temp = arr[index].next();
		  for(int i = 0; i < arr[index].lenOfChain()-1; i++)
		    {
		      if(nametofind == temp->keyData())
			{
			  cout<<temp->valueData()<<endl;
			  break;
			}
		      temp = temp->next();
		    }
		}
	      
	    }
	  
	  
	  if(ch == "u")
	    {
	      cin >> nametofind;
	      string newContactNum;
	      cin >> newContactNum;
	      
	      int index = findSlot(nametofind, size);
	      
	      
	      if(arr[index].keyData()== nametofind)
		{
		  arr[index].valueData() = newContactNum;
		  //cout<<arr[index].valueData()<<endl;
		}
	      else
		{
		  temp = arr[index].next();
		  for(int i = 0; i < arr[index].lenOfChain()-1; i++)
		    {
		      if(nametofind == temp->keyData())
			{
			  temp->valueData() = newContactNum;
			  break;
			}
		      temp = temp->next();
		    }
		}
	      
	    }
	  
	}
      
    }
  
  
   
  return 0;
}
