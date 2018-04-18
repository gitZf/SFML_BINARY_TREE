// Zoltan Fuzesi C00197361 Date 05/02/2017 


#include"BinaryTree.h"
#include <SFML/Graphics.hpp>

BinaryTree::BinaryTree()
{
	root = NULL;
}

BinaryTree::~BinaryTree()
{
	destroyTree(root);
}
bool BinaryTree::search(Node* root, int data) {
	if (root == NULL)
		return false;

	else if (root->data == data) 
		return true;
	else if (data <= root->data) 
		return search(root->left, data);
	else 
		return search(root->right, data);
}

int BinaryTree::findHeight(Node* node)
{
	if (node == NULL) return 0;
	return 1 + std::max(findHeight(node->left), findHeight(node->right));
}

Node* BinaryTree::Insert(Node* root,Node* parent, int data,float x,float y) {
	if (root == NULL) {
		root = newNode(parent, data,x,y);
		lastAddedNode = root;
	}
	else
	{
		
		if (data <= root->data) {
			if (root->parent==root)
			{
				x = x / 2 + 80;
			}
			root->left = Insert(root->left,parent, data, x - 80 , y + 80);
		}
		else {
			if (root->parent == root)
			{
				x += x / 2 - 80;
			}
			root->right = Insert(root->right,parent, data, x + 80, y + 80);
		}
	}
	return root;
}



Node* BinaryTree::newNode(Node* parent, int data,float x,float y) {
	treeHeight++;
	lastAddedNode = parent;
	Node* newNode = new Node();
	newNode->parent = parent;
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	newNode->X = x;
	newNode->Y = y;
	//x AND y -> circle position x+10 AND y+10 ->top node center  0 AND 0 -> left node  center x+10 AND y+10 ->top node center 0 AND 0 -> right node center
	newNode->updateCircle(x, y, x+17, y+17, x+17, y+17, x+17, y+17, x+17, y+17);
	newNode->updateText(x,y,data);
	if (getRoot() == NULL)
	{
		setRoot(newNode);
		newNode->parent = newNode;
	}
		

	cout << " new node -> "<< data << " inserted " << x << " and " << y << endl;
	return newNode;
}

//drawing the tree
void BinaryTree::drawNodes(Node* root,sf::RenderWindow& wind)
{
	if (root != NULL)
	{
		if (root->left != NULL) drawNodes(root->left, wind);
		if (root->right != NULL) drawNodes(root->right, wind);
		wind.draw(root->cr.getCircleObject());
		if (root->left != NULL)
		{
			root->cr.setXt2(root->left->X + 17);
			root->cr.setYt2(root->left->Y + 17);
		}
		else
		{
				root->cr.setXb1(root->X + 17);
				root->cr.setYb2(root->Y + 17);		
		}
		if (root->right != NULL)
		{
			root->cr.setXb2(root->right->X + 17);
			root->cr.setYb2(root->right->Y + 17);
		}
		else
		{
				root->cr.setXb2(root->X + 17);
				root->cr.setYb2(root->Y + 17);
		}
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(root->cr.getXt1(), root->cr.getYt1())),sf::Vertex(sf::Vector2f(root->cr.getXt2(), root->cr.getYt2())),

			sf::Vertex(sf::Vector2f(root->cr.getXt1(), root->cr.getYt1())),sf::Vertex(sf::Vector2f(root->cr.getXb2(), root->cr.getYb2()))
		};
		wind.draw(line, 4, sf::Lines);
		wind.draw(root->txt.getText());
	}
}
string BinaryTree::getInorderStr()
{
	return orderstr;
}
void BinaryTree::setOrderStr(string str)
{
	orderstr += str;
}

void BinaryTree::cleaeOrderStr()
{
	orderstr = "";
}

void BinaryTree::destroyTree(Node* root)
{
	if (root != NULL)  // it's not
	{
		destroyTree(root->left);
		destroyTree(root->right);
		delete root;
	}
}

void BinaryTree::inorder(Node *root)
{
	if (root != NULL)
	{
		if (root->left) inorder(root->left);
		orderstr += to_string(root->data) + ", ";
		if (root->right) inorder(root->right);
	}

}

void BinaryTree::resizeTreeVector()
{
	tree.reserve(1000);
}
void BinaryTree::PreOrder(Node *root)
{
	if (root != NULL)
	{
		tree.push_back(root->data);
		if (root->left) PreOrder(root->left);
		if (root->right) PreOrder(root->right);
	}

}

vector<int> BinaryTree::getTreeVector()
{
	return tree;
}

void BinaryTree::eraseFirst()
{
	tree.erase(tree.begin());
}
void BinaryTree::eraseTreeVector()
{
	tree.erase(tree.begin(), tree.end());
}
void BinaryTree::setRoot(Node* root)
{
	this->root = root;
	
}
Node* BinaryTree::getRoot()
{
	return this->root;
}


Node* BinaryTree::deleteNode(struct Node *root, int data) {
	if (root == NULL)
		return root;
	else if (data < root->data)
		root->left = deleteNode(root->left, data);
	else if (data > root->data)
		root->right = deleteNode(root->right, data);
	else {
		// Case 1: No Child
		if (root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
		}
		// Case 2 : one child
		else if (root->left == NULL) {
			root = root->right;
			setRoot(root);
			return root;
		}
		else
		{
			if (root->right == NULL) {
				root = root->left;
				root->txt.updateText(root->X, root->Y, root->data);
				setRoot(root);
				return root;
			}
			else {
				struct Node *temp = FindMin(root->right);
				root->data = temp->data;
				root->txt.updateText(root->X, root->Y, temp->data);
				root->right = deleteNode(root->right, temp->data);
			}
		}
		
	}

	setRoot(root);
	return root;
}

Node* BinaryTree::FindMin(Node* root)
{
	if (root == NULL)
		return NULL;
	else if (root->left == NULL)
		return root;
	else
		return FindMin(root->left);
}

