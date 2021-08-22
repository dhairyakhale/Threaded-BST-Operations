#include<bits/stdc++.h>

using namespace std;

class BST;

struct LLNode
{
	int data;
	LLNode* next;
};

struct LLNode2
{
	BST* data;
	LLNode2* next;
};

class BST
{
	private:
		
		int value;
		BST *left, *right;
		bool lthread, rthread;
		int rstval;				//No. of elements in a node's right subtree
								//Useful for kth largest element detection
	public:
		
		//Append into linked list of type LLNode
		//This is to store reverse inorder, & to store elements between k1 and k2
		void append(struct LLNode** head, int x)
		{
		    struct LLNode* temp = (struct LLNode*) malloc(sizeof(struct LLNode));	//Create node of type LLNode to be added
		 
		    struct LLNode *last = *head;	//Pointer which goes till last node
		  
			//inserting values into new node
		    temp->data = x;
		 	temp->next = NULL;
			
			//If list is empty
		    if (*head == NULL)
		    {
		       *head = temp;	//First element entered
		       return;
		    } 
		    
		    while (last->next != NULL)		//traverse to end of list
		        last = last->next;
		  
		    last->next = temp;				//Append new node to the current last element
		    return;   
		}
		
		//Append into linked list of type LLNode2
		//This is to store rstval of all the parents which have the given node in their right subtree
		//This is overloaded function of above, and has same operation
		void append(struct LLNode2** head, BST* x)
		{
		    struct LLNode2* temp = (struct LLNode2*) malloc(sizeof(struct LLNode2));
		 
		    struct LLNode2 *last = *head;
		  
		    temp->data  = x;
		    temp->next = NULL;
		 
		    if (*head == NULL)
		    {
		       *head = temp;
		       return;
		    } 
		    
		    while (last->next != NULL)
		        last = last->next;
		  
		    last->next = temp;
		    return;   
		}
	
		//Decrements each element of LLNode2 type linked list
		//If someone deletes a node, their parents who had that node in their right subtree should have rstval decremented by 1
		void rstvalAdjustment(struct LLNode2* head)
		{
			if(head==NULL)
				return;
			
			while(head != NULL)		//Traverses through the list of parents and decrements one by one
			{
				head->data->rstval--;
				head = head->next;
			}
		}
		
		//Prints out LLNode type linked list
		void printout(struct LLNode* ps)
		{
			while (ps != NULL)		//Traverses through the list and prints out their values one by one
			{
		     	cout<<ps->data<<" ";
		     	ps = ps->next;
			}	
		}
		
		//Inserts an element in the BST
		BST* insert(int x, BST* root, BST* parent)
		{
			if(root==NULL)					//When desired location is reached
			{
				BST* node = new BST;		//Create new BST node
				
				//Entering default values
				node->value = x;
				node->left = NULL;
				node->right = NULL;
				node->rstval=0;
				
				if(parent == NULL)			//If it is the first node
				{
					node->lthread = false;
					node->rthread = false;
				}
				
				else if(node->value < parent->value)	//Node is inserted as left-child of parent
				{
					//assigning parent's left thread to the new child (if exists)
					if(parent->lthread == false)
						node->lthread = false;
					else
					{
						node->left = parent->left;
						node->lthread = true;
					}
					
					//Assigning right thread pointing to parent
					node->right = parent;
					node->rthread = true;
				}
				else	//Node is inserted as right-child of parent
				{
					//assigning parent's right thread to the new child (if exists)
					if(parent->rthread == false)
						node->rthread = false;
					else
					{
						node->right = parent->right;
						node->rthread = true;
					}
					
					//Assigning left thread pointing to parent
					node->left = parent;
					node->lthread = true;
				}
				
				cout<<x<<": Inserted."<<endl;
				
				return node;	//Return the inserted node
			}
			else
			{
				parent = root;
				if(x == root->value)
				{
					cout<<x<<": Element already present."<<endl;
					return root;
				}
				else
				{
					//Recursively traversing in left subtree
					if(x < root->value)
					{
						if(root->lthread == true)	//If no left child
						{
							root->left = insert(x, NULL, parent);	//Make node's left point to null
							root->lthread = false;					//Make node's left thread false because node inserted in left
						}
						else
							root->left = insert(x, root->left, parent);
					}
					
					//Recursively traversing in right subtree
					else if(x > root->value)
					{
						root->rstval++;				//Increase count of no. of elements in right subtree
						
						if(root->rthread == true)	//If no right child
						{
							root->right = insert(x, NULL, parent);	//Make node's left point to null
							root->rthread = false;					//Make node's left thread false because node inserted in left
						}
						else
							root->right = insert(x, root->right, parent);	
					}
				}
			}
		}
		
		//Searches for an element in the BST
		BST* search(int x, BST* root)
		{
			if(root == NULL)
			{
				cout<<"Not found."<<endl;
				return root;					//Return NULL
			}
			
			if(x == root->value)				//Current node's value = input x
				cout<<x<<" found!"<<endl;
				
			//Recursively traversing left subtree to search
			else if (x < root->value)
			{
				if(root->lthread == true)		//If no left child
					root = search(x, NULL);		//not found
				else
					root = search(x, root->left);
			}
			
			//Recursively traversing right subtree to search
			else if(x > root->value)
			{
				if(root->rthread == true)		//If no right child
					root = search(x, NULL);		//not found
				else
					root = search(x, root->right);
			}
			
			return root;	//Return the found node
		}
		
		//Return the leftmost node of tree with root as given node
		BST* leftmost(BST* node)
		{	
			while(node!= NULL && node->lthread == false && node->left != NULL)	//Loop till node's left child is NULL, or till node itself is NULL(when tree empty)
				node = node->left;		//Keep traversing leftwards
			
			return node;	//Return leftmost node, or NULL if empty tree
		}
		
		//Return the leftmost node of tree with root as given node		
		BST* rightmost(BST* node)
		{
			while(node!=NULL && node->rthread == false && node->right != NULL)	//Loop till node's right child is NULL, or till node itself is NULL(when tree empty)
				node = node->right;		//Keep traversing rightwards
			
			return node;	//Return rightmost node, or NULL if empty tree
		}
		
		//Returns the node which is inorder successor of the input node
		BST* successorNode(BST* node)
		{
			if(node == NULL)
			{
				cout<<"Invalid Input."<<endl;
				return node;
			}
			
			if(node->rthread)			//If right thread exists, return what it points (the whole point of threading)
				return node->right;
			
			return leftmost(node->right);	//Else, return leftmost node of right subtree of the input node
		}
		
		//Returns the VALUE OF node which is inorder successor of the input node
		//Same logic as above
		int successor(BST* node)
		{
			if(node == NULL)
			{
				cout<<"Invalid Input. Returning -1."<<endl;
				return -1;
			}
			
			if(node->rthread)
				return node->right->value;
			
			return leftmost(node->right)->value;
		}
		
		// Returns the node which is inorder predecessor of the input node
		BST* predecessor(BST* node)
		{
			if(node == NULL)	
			{
				cout<<"Invalid Input."<<endl;
				return node;
			}
			
			if(node->lthread)			//If left thread exists, return what it points (the whole point of threading)
				return node->left;
			
			return rightmost(node->left);	//Else, return rightmost node of left subtree of the input node
		}
		
		//Deleting leaf node
		//Component function of del()
		BST* del_0Child(BST* node, BST* root, BST* parent, LLNode2 *ps)
		{
			if(parent == NULL)		//Delete only node of tree
				root = NULL;
			
			//If left leaf deleted, assign left thread of node to parent
			else if(node == parent->left)
			{
				parent->lthread = node->lthread;
				parent->left = node->left;	
			}
			//If right leaf deleted, assign right thread of node to parent
			else
			{
				parent->rthread = node->rthread;
				parent->right = node->right;
			}
			
			rstvalAdjustment(ps);	//Adjust rstval of parents, as all of them will lose one element from right subtree
			
			node = NULL;
			delete node;
			return root;			//Return root of the tree
		}
		
		//Deleting node with one child
		//Component function of del()
		BST* del_1Child(BST* node, BST* root, BST* parent, LLNode2 *ps)
		{
			BST* temp;
			
			//Check if node has left child or right
			
			if(node->lthread == false && node->left!=NULL)		//If only left child exists
				temp = node->left;								//assign left child to temp
				
			else							//Else if only right child exists
				temp = node->right;			//Assign right child to temp
				
			if(parent == NULL)				//If only node in tree
				root = temp;
				
			else if(node == parent->left)	//If node is left child of parent
				parent->left = temp;		//parent's left child becomes node's child
				
			else							//If node is right child of parent
				parent->right = temp;		//parent's right child becomes node's child
				
			BST* s = successorNode(node);	//Inorder successor of node
			BST* p = predecessor(node);		//Inorder predecessor of node
			
			if(node->lthread == false && node->left!=NULL)		//If node has left child
				p->right = s;									//Assign node's right thread to its child
				
			else if(node->rthread == false && node->right!=NULL)	//If node has right child
				s->left = p;										//Assign node's left thread to its child
			
			rstvalAdjustment(ps);	//Adjust rstval of parents, as all of them will lose one element from right subtree
			
			delete node;
			return root;			//Return root of the tree
		}
		
		//Deleting node with two children
		//Component function of del()
		BST* del_2Child(BST* node, BST* root, BST* parent, LLNode2 *ps)
		{
			BST* parent_s = node;	//Parent of inorder successor
			BST* s = node->right;	//Done so that traversal into left subtree gives the node's inorder successor
			
			//Traverse into left subtree
			while(s->lthread == false)
			{
				parent_s = s;
				s = s->left;
			}
			
			node->value = s->value;		//Value of inorder successor is copied into node
			
			//Now we will delete the inorder successor itself, as its value is now copied
			if ((s->lthread == false && s->left != NULL) || (s->rthread == false && s->right != NULL))	//When inorder successor has one child
	        	root = del_1Child(s, root, parent_s, ps);
	        	
	    	else											//When inorder successor is a leaf node
	        	root = del_0Child(s, root, parent_s, ps);
	        	
	        rstvalAdjustment(ps);	//Adjust rstval of parents, as all of them will lose one element from right subtree
	 
	    	return root;			//Return root of the tree
		}
		
		//Main delete function
		BST* del(int x, BST* root)
		{	
			BST* node = root;
			BST* parent = NULL;
			
			struct LLNode2* ps = NULL;		//To create linked list of all parents of the node to be deleted, if node is in their RST
											//To be used for adjusting rstval of parents
											
			int flag = 0;					//If node found, flag = 1
 
 			//Finding the node to be deleted
		    while (node != NULL)
			{
		        if (x == node->value)		//Node found
				{
		            flag = 1;
		            break;
		        }
		        parent = node;				//Parent assigned before node is traversed
		        
		        if (x < node->value) 		//Traversal in left subtree, similar to search
				{
		            if (node->lthread == false)
		                node = node->left;
		            else
		                break;
		        }
		        else
				{
		            if (node->rthread == false)
		            {
		            	append(&ps, parent);	//Add parent to linked list, as we enter right subtree
		            	node = node->right;
					}
		            else
		                break;
		        }
		    }
		 
		    if (flag == 0)
		        cout<<"Node not present in tree."<<endl;
			
			//If node has 2 children
			else if((node->lthread == false && node->left != NULL) && (node->rthread == false && node->right != NULL))
			{
				root = del_2Child(node, root, parent, ps);
			}
			//If node has 1 child
			else if((node->lthread == false && node->left != NULL) || (node->rthread == false && node->right != NULL))
			{
				root = del_1Child(node, root, parent, ps);
			}
			//If leaf node
			else
			{
				root = del_0Child(node, root, parent, ps);
			}
			
			return root;	//Return the Root of the tree
		}
		
		//Printing inorder traversal of tree given by the node
		void inorder(BST* root)
		{	
			cout<<"Inorder: ";
			root=leftmost(root);	//Go to leftmost node of tree
			
			while(root != NULL)
			{
				cout<<root->value<<" ";		//Print value
				
				if(root->rthread)			//If right thread exists, go to the node pointed by it
					root = root->right;
				else
					root = leftmost(root->right);	//else go to inorder successor of node
			}
			cout<<endl;
		}
		
		//Storing reverse inorder of the tree in a linked list
		struct LLNode* reverseInorder(BST* root)
		{			
			struct LLNode *ps = NULL;	//Initializing linked list
			
			root=rightmost(root);		//Go to rightmost node
			
			while(root != NULL)
			{
				append(&ps, root->value);	//Append the value of the node into linked list
				
				if(root->lthread)			//If left thread exists, go to the node pointed by it
					root = root->left;
				else
					root = rightmost(root->left);	//Else go to inorder predecessor
			}
			
			cout<<"Reverse Inorder: ";
			printout(ps);					//Print the linked list
			cout<<endl;
			
			return ps;						//Return the linked list
		}
		
		//Finds all elements with value >=k1 and <=k2
		struct LLNode* allElementsBetween(int k1, int k2, BST* root)
		{
			BST* node1 = search(k1, root);	//Store node with value k1
			BST* node2 = search(k2, root);	//Store node with value k2
			
			if(node1 == NULL || node2 == NULL || k1>k2)		//If either of nodes don't exist, or k1<k2
			{
				cout<<"Invalid Input."<<endl;
				return NULL;
			}
			
			struct LLNode *ps = NULL;		//Initialize the linked list
			
			//Doing essentially inorder traversal from node1 to node2
			while(node1 != node2)
			{
				append(&ps, node1->value);	//Append node's value into linked list
				
				if(node1->rthread)
					node1 = node1->right;
				else
					node1 = leftmost(node1->right);
			}
			append(&ps, node1->value);	//Append node2, as it would be left due to while condition
			
			cout<<"Nodes between "<<k1<<" and "<<k2<<": ";
			
			printout(ps);				//Print the linked list
			cout<<endl;					//Return the linked list
			
			return ps;
		}
		
		//Finds kth largest element from the tree
		BST* kthElement(int k, BST* root)
		{
			int temp = k;
			if(root==NULL)
			{
				cout<<"invalid input."<<endl;
				return root;
			}
			
			BST* node = root;	
			
			while(node)
			{
				if(node->rstval+1 == temp)		//If number of right subtree nodes of the node + itself is equal to k
				{
					cout<<k<<"th largest element: "<<node->value<<endl;		//node is the kth largest element
					return node;
				}
				else if(temp > node->rstval+1)	//If number of RST nodes of the node + itself is greater than k
				{
					temp -= node->rstval+1;		//Reduce k by the number of nodes in RST of the node + itself (cuz we skipped them)
					node = node->left;			//Traverse to left subtree
				}
				else
					node = node->right;			//Keep traversing right
			}
			
			cout<<"not enough nodes"<<endl;		//If node is not found in the loop, that means nodes < k
			return node;
		}
		
		//Used to print null nodes on diagram
		//Called when node is NULL
		//Component function of printTree()
		void printTree_null(int val, int nullc, fstream &myfile)
		{
		    myfile<<"    null"<<nullc<<" [shape=point];\n";
		    myfile<<"    "<<val<<" -> null"<<nullc<<";\n";
		}
		
		//Used to print the nodes and their edges
		//Component function of printTree()
		void printTree_main(BST* node, fstream &myfile)
		{
		    static int nullc = 0;	//Used to name null nodes uniquely (null1, null2)
		
			//Printing all the left edges & threads
		    if (node->left!=NULL)	
		    {
		    	if(node->lthread==false)	//Printing proper edge
		    	{
		    		myfile<<"    "<<node->value<<" -> "<<node->left->value<<";\n";
		        	printTree_main(node->left, myfile);		//Recursively traverse to left subtree
				}
		        else	//Printing left threads
		        	myfile<<"    "<<node->value<<" -> "<<node->left->value<<" [color=\"blue\"];\n";
		    }
		    else	//Printing edge to NULL node
		        printTree_null(node->value, nullc++, myfile);
		
			//Printing all the right edges & threads
		    if (node->right)
		    {
		    	if(node->rthread==false)	//Printing proper edge
		    	{
		    		myfile<<"    "<<node->value<<" -> "<<node->right->value<<";\n";
		        	printTree_main(node->right, myfile);		//Recursively traverse to right subtree
				}
		        else	//Printing right threads
		        	myfile<<"    "<<node->value<<" -> "<<node->right->value<<" [color=\"red\"];\n";
		    }
		    else	//Printing edge to NULL node
		        printTree_null(node->value, nullc++, myfile);
		}
		
		//Driver function for printTree_main()
		void printTree(BST* root)
		{
			fstream myfile;
			myfile.open("graph1.gv",ios::out|ios::trunc);	//Creating file for graph in write mode, which clears after it is opened again
			
			BST* node = root;
			BST* parent = node;
			
			//Initial printing in .gv file
			myfile<<"digraph BST {\n";
			myfile<<"    label = \"RED: rthread, BLUE: lthread\";\n";
			myfile<<"    node [fontname=\"Arial\"];\n";
			
			if (root==NULL)		//If tree is empty, graph file is empty
	        	myfile<<endl;
		    else if (root->right == NULL && root->left == NULL)		//If tree has only one node, print that
		        myfile<<"    "<<root->value<<";\n";
		    else
	        	printTree_main(root, myfile);		//Else call printTree_main
			
			myfile<<"}\n";		//Final printing in .gv file
			
			myfile.close();		//Closing the file
			
			system("dot -Tsvg graph1.gv > output.svg & output.svg");	//Opens cmd, converts ,gv into .svg, opens it
		}
		
};

//---------------------------------------------DRIVER CODE---------------------------------------------

int main()
{
	BST tree, *root=NULL;
	struct LLNode* ps;
	
	int choice=0, x=0;
	cout<<"1. insert\n2. search\n3. delete\n4. reverseInorder\n5. successor\n6. split\n7. allElementsBetween\n8. kthElement\n9. printTree\n0. exit\n";
	while(true)
	{
		cout<<"Enter the operation which you want to attempt: ";
		cin>>choice;
		
		switch(choice)
		{
			case 0:
				{
					cout<<"Goodbye!"<<endl;
					return 0;
				}
			case 1:
				{
					cout<<"Insert element: ";
					cin>>x;
					if(root==NULL)
						root = tree.insert(x,root, root);
					else
						tree.insert(x, root, root);
					break;
				}
			case 2:
				{
					cout<<"Search for: ";
					cin>>x;
					tree.search(x, root);
					break;
				}
			case 3:
				{
					cout<<"Delete element: ";
					cin>>x;
					root = tree.del(x, root);
					break;
				}
			case 4:
				{
					if(root == NULL)
						cout<<"Empty tree."<<endl;
					else
						ps = tree.reverseInorder(root);
					break;
				}
			case 5:
				{
					cout<<"Find successor of: ";
					cin>>x;
					cout<<"It is: "<<tree.successor(tree.search(x,root))<<endl;
					break;
				}
			case 6:
				{
					cout<<"Didn't implement due to lack of time."<<endl;
					break;
				}
			case 7:
				{
					int k1,k2;
					cout<<"Insert k1 and k2 separated by space: ";
					cin>>k1>>k2;
					ps = tree.allElementsBetween(k1,k2,root);
					break;
				}
			case 8:
				{
					cout<<"Insert k: ";
					cin>>x;
					tree.kthElement(x,root);
					break;
				}
			case 9:
				{
					cout<<"Close the image to come back."<<endl;
					tree.printTree(root);
					break;
				}
			default:
				{
					cout<<"Invalid input, try again."<<endl;
					break;
				}
		}
		
	}
	
	return 0;            
}
