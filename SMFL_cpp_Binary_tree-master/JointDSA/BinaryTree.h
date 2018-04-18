// Zoltan Fuzesi C00197361 Date 05/02/2017 
//

#pragma once
#include <SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include<vector>
using namespace std;

struct Text {
	sf::Text number;
	sf::Font font;
	
	
	Text()
	{
		getFont();
		number.setPosition(sf::Vector2f(0, 0));
		number.setString("");
		number.setFont(font);
		number.setFillColor(sf::Color::Green);
		number.setCharacterSize(25);
		number.setStyle(sf::Text::Bold);

	}

	~Text()
	{

	}

	sf::Font getFont()
	{
		if (!font.loadFromFile("walk.ttf"))
		{
			cout << "failed to load walk" << endl;
		}
	
		return font;
	}


	sf::Text getText()
	{
		return number;
	}
	void updateText(float x, float y, int data)
	{
		number.setPosition(sf::Vector2f((x + 20) - 17, (y + 20) - 17));
		number.setString(to_string(data));
	}
	void updateTXT(int data)
	{
		number.setString(to_string(data));
	}

};

class CircleShape {

	sf::CircleShape cr;


public:
	float xt1;
	float yt1;
	float xt2;
	float yt2;
	float xb1;
	float yb1;
	float xb2;
	float yb2;
	float lastEndPointLeftX;
	float lastEndPointLeftY;
	float lastEndPointRightX;
	float lastEndPointRightY;

	CircleShape() {
		
		cr.setPosition(0, 0);
		cr.setFillColor(sf::Color::White);
		cr.setRadius(20);
		cr.setOutlineColor(sf::Color::Red);
		cr.setOutlineThickness(1);
	}
	~CircleShape()
	{
		
	}

	sf::CircleShape getCircleObject()
	{
		return cr;
	}
	
	void updateCircleXY(float x, float y)
	{
		cr.setPosition(x, y);
	}
	void UpdateCircleShape(float x, float y, float x1, float y1, float x2, float y2, float xb1, float yb1, float xb2, float yb2) {
		cr.setPosition(x, y);
		cr.setFillColor(sf::Color::White);
		cr.setRadius(20);
		cr.setOutlineColor(sf::Color::Red);
		cr.setOutlineThickness(1);
		this->xt1 = x1;
		this->yt1 = y1;
		this->xt2 = x2;
		this->yt2 = y2;
		this->xb1 = xb1;
		this->yb1 = yb1;
		this->xb2 = xb2;
		this->yb2 = yb2;
		this->lastEndPointLeftX = x1;
		this->lastEndPointLeftY = y1;
		this->lastEndPointRightX = xb1;
		this->lastEndPointRightY = yb1;

	}
	void setXt1(int x){ xt1 = x; }
	void setYt1(int y){	yt1 = y; }
	void setXt2(int x){	xt2 = x; }
	void setYt2(int y){	yt2 = y; }
	void setXb1(int x){	xb1 = x; }
	void setYb1(int y){	yb1 = y; }
	void setXb2(int x){	xb2 = x; }
	void setYb2(int y){ yb2 = y; }
	void setLastEndPointLeftX(int x)  { lastEndPointLeftX = x; }
	void setLastEndPoinLeftY(int y)   { lastEndPointLeftY = y; }
	void setLastEndPointRightX(int x) { lastEndPointRightX = x; }
	void setLastEndPoinRightY(int y)  { lastEndPointRightY = y; }

	float getXt1(){ return xt1;	}
	float getYt1(){	return yt1;	}
	float getXt2(){	return xt2;	}
	float getYt2(){	return yt2; }
	float getXb1(){	return xb1;	}
	float getYb1(){	return yb1; }
	float getXb2(){	return xb2;	}
	float getYb2(){	return yb2;	}
	float setLastEndPointLeftX()  { return lastEndPointLeftX; }
	float setLastEndPoinLeftY()   { return lastEndPointLeftY; }
	float setLastEndPointRightX() { return lastEndPointRightX; }
	float setLastEndPoinRightY()  { return lastEndPointRightY; }


	void reBuildCircle(float x, float y)
	{
		cr.setPosition(x, y);
	}
};
	

struct Node {
	CircleShape cr;
	Text txt;
	int data;
	Node* left;
	Node* right;
	Node* parent;

	float X;
	float Y;
	~Node()
	{


	}

	void updateCircle(float x, float y, float x1, float y1, float x2, float y2, float xb1, float yb1, float xb2, float yb2)
	{
		cr.UpdateCircleShape(x, y, x1, y1, x2, y2, xb1, yb1, xb2, yb2);
	}

	void updateText(float x, float y, int data)
	{
		txt.updateText(x,y,data);
	}

};

class BinaryTree
{
	
public:
	BinaryTree();
	~BinaryTree();
	vector<int>tree;
	Node* root;
	Node* lastAddedNode;
	string orderstr;
	int treeHeight;
	Node* Insert(Node* root, Node* parent, int data,float x, float y);
	Node* newNode(Node* parent, int data, float x, float y);
	Node* deleteNode(Node* root, int data);
	Node* FindMin(Node* root);
	Node* getRoot();
	int findHeight(Node* node);
	void resizeTreeVector();
	void eraseTreeVector();
	void eraseFirst();
	void PreOrder(Node* root);
	void setRoot(Node* root);
	void inorder(Node* root);
	void setOrderStr(string str);
	void destroyTree(Node* root);
	void cleaeOrderStr();
	void drawNodes(Node* root, sf::RenderWindow& wind);
	vector<int> getTreeVector();
	string getInorderStr();
	bool search(Node* root, int data);
};
