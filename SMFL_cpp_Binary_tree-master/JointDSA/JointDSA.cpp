// Zoltan Fuzesi C00197361 Date 05/02/2017 
//
#include <SFML/Graphics.hpp>
#include"BinaryTree.h"
#include <iostream>
#include"readFile.h"

//void printBinaryTree(Node* root, Node* nd, int level);


void gettext(readFile re, sf::Text text[6])
{
	for (int i = 1; i < 6; i++)
	{
		vector<int>v = re.readIn(i);
		string str = "Binary tree " + to_string(i) + " : ";
		for (int j = 0; j < v.size(); j++)
		{
			str += to_string(v[j]) + ", ";
		}
		text[i].setString(str);
		text[i].setCharacterSize(20);
	}
}

void buildTree(BinaryTree* binT, int textMenuPosition, vector<int>nodes, sf::Text treeMenu[7],Node* nd)
{
	binT->setRoot(NULL);
	binT->lastAddedNode = NULL;
	//nodes = re.readIn(textMenuPosition);
	treeMenu[5].setString("Remove fifth element : " + to_string(nodes[4]));
	string inputNums = "Input values : ";
	nd = NULL;
	//cout << "\nInsert Start\n" << endl;
	nd = binT->Insert(nd, binT->lastAddedNode, nodes[0], 500, 50);
	binT->setRoot(nd);
	
	inputNums += to_string(nodes[0]) + ", ";
	if (binT->lastAddedNode == NULL)
		binT->lastAddedNode = binT->getRoot();

	for (int i = 1; i < nodes.size(); i++)
	{
		Node* temp = NULL;
		inputNums += to_string(nodes[i]) + ", ";
		temp = binT->Insert(nd, binT->lastAddedNode, nodes[i], 500, 50);
	}
	
	treeMenu[6].setString(inputNums);
}

void changeTree(BinaryTree* binT, int textMenuPosition, vector<int>nodes, sf::Text treeMenu[7], Node* nd,int treeMenuPosition)
{




	binT->setRoot(NULL);
	binT->lastAddedNode = NULL;
	if (nodes.size() >= 5)
		treeMenu[5].setString("Remove fifth element : " + to_string(nodes[4]));
	else
		treeMenu[5].setString("Tree has less than 5 Nodes");
	string inputNums = "Input values : ";
	nd = NULL;
	nd = binT->Insert(nd, binT->lastAddedNode, nodes[0], 500, 50);
	binT->setRoot(nd);
	inputNums += to_string(nodes[0]) + ", ";
	if (binT->lastAddedNode == NULL)
		binT->lastAddedNode = binT->getRoot();
	for (int i = 1; i < nodes.size(); i++)
	{
		Node* temp = NULL;
		inputNums += to_string(nodes[i]) + ", ";
		temp = binT->Insert(nd, binT->lastAddedNode, nodes[i], 500, 50);
	}
	treeMenu[6].setString(inputNums);
	binT->inorder(nd);
		
	treeMenu[7].setString("InOrder : " + binT->getInorderStr());
}
BinaryTree * binT;// = BinaryTree();
int main()
{
	//BinaryTree * binT;// = BinaryTree();
	binT = new BinaryTree();
	

	Node* nd = NULL;
	int a = 100;
	int b = 250;
	int timeCounter = 0;
	bool removeRoot = true;
	readFile re;
	bool menu = true;
	bool tree = false;
	bool up = true;
	bool upTree = true;
	bool down = true;
	bool downTree = true;
	bool enter = true;
	bool shuffleTree = true;
	int textMenuPosition = 3;
	int treeMenuPosition = 1;
	bool lock = true;
	bool lockRoot = true;
	vector<int>nodes;
	nodes.reserve(1000);
	string inputNums;
	//font
	sf::Font font;
	if (!font.loadFromFile("font/walk.ttf"))
	{
		std::cout << "Can't load font";
	}
	//quit
	sf::Text quit;
	quit.setFont(font);
	quit.setFillColor(sf::Color::Yellow);
	quit.setCharacterSize(15);
	quit.setStyle(sf::Text::Bold);
	quit.setString("Press Esc to Quit");
	quit.setPosition(sf::Vector2f(10, 10));

	//Tree menu
	sf::Text treeMenu[8];
	int startY = 30;
	for (int i = 0; i < 8; i++)
	{
		treeMenu[i].setFont(font);
		treeMenu[i].setFillColor(sf::Color::Red);
		treeMenu[i].setCharacterSize(18);
		treeMenu[i].setStyle(sf::Text::Bold);
		treeMenu[i].setString(to_string(i) + " Let see");
		treeMenu[i].setPosition(sf::Vector2f(10, startY));
		startY += 20;
	}
	treeMenu[0].setString("Operations : ");
	treeMenu[0].setFillColor(sf::Color::Cyan);
	treeMenu[1].setString("Main menu");
	treeMenu[2].setString("Remove root");
	treeMenu[3].setString("Random input");
	treeMenu[4].setString("Shuffle tree Enabled");
	treeMenu[5].setString("Remove fifth element : ");
	treeMenu[6].setString("Input values : ");
	treeMenu[6].setPosition(sf::Vector2f(550, 10));
	treeMenu[7].setString("InOrder : ");
	treeMenu[7].setPosition(sf::Vector2f(550, 30));
	
	//Menu
	sf::Text textMenu[6];
	int x = 200;
	int y = 100;
	//changed
	for (int i = 0; i < 6; i++)
	{
		textMenu[i].setFont(font);
		textMenu[i].setFillColor(sf::Color::Red);
		textMenu[i].setCharacterSize(44);
		textMenu[i].setStyle(sf::Text::Bold);
		textMenu[i].setString("");
		textMenu[i].setPosition(sf::Vector2f(x, y));
		y += 70;
	}
	textMenu[0].setFillColor(sf::Color::Blue);
	textMenu[0].setCharacterSize(64);
	textMenu[0].setString("Select a Binary tree : ");
	textMenu[0].setPosition(sf::Vector2f(80, 50));
	gettext(re, textMenu);
	
	textMenu[3].setFillColor(sf::Color::Green);


	//create Window
	sf::RenderWindow window(sf::VideoMode(1200, 750), "Binary tree by Zoltan Fuzesi");

	// set timepeFrame to 1 60th of a second. 60 frames per second

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// the clock object keeps the time.
	sf::Clock clock;


	clock.restart();

	while (window.isOpen())
	{
		// chek if the close window button is clicked on.
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greate than 1/60 update the world.

		if (timeSinceLastUpdate > timePerFrame)
		{

			window.clear();
			if (menu)
			{
				
				quit.setString("Press Esc to Quit");
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					up = true;
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					down = true;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&&up)
				{
					textMenuPosition--;
					if (textMenuPosition < 1)
						textMenuPosition = 5;
					//std::cout << textMenuPosition << std::endl;
					gettext(re, textMenu);
					for (int i = 1; i < 6; i++)
					{
						if (i == textMenuPosition)
						{
							textMenu[i].setFillColor(sf::Color::Green);
						}
						else
						{
							textMenu[i].setFillColor(sf::Color::Red);
						}
					}
					up = false;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&&down)
				{
					textMenuPosition++;
					if (textMenuPosition > 5 )
						textMenuPosition = 1;
					//std::cout << textMenuPosition << std::endl;
					gettext(re, textMenu);
					for (int i = 1; i < 6; i++)
					{
						if (i == textMenuPosition)
						{
							textMenu[i].setFillColor(sf::Color::Green);
						}
						else
						{
							textMenu[i].setFillColor(sf::Color::Red);
						}
					}
				
					down = false;
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					enter = true;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && enter)
				{
					binT->setRoot(NULL);
					binT->lastAddedNode = NULL;
					nodes.reserve(1000);
					nodes = re.readIn(textMenuPosition);
					cout << nodes.size() << "The size of the nodes vector" << endl;
					treeMenu[5].setString("Remove fifth element : " + to_string(nodes[4]));
					string inputNums = "Input values : ";
					nd = NULL;
					cout << "\nInsert Start\n" << endl;
					nd = binT->Insert(nd, binT->lastAddedNode, nodes[0], 500, 50);
					binT->setRoot(nd);
					inputNums += to_string(nodes[0]) + ", ";
					if (binT->lastAddedNode == NULL)
						binT->lastAddedNode = binT->getRoot();

					for (int i = 1; i < nodes.size(); i++)
					{
						Node* temp = NULL;
						inputNums += to_string(nodes[i]) + ", ";
						temp = binT->Insert(nd, binT->lastAddedNode, nodes[i], 500, 50);
					}
					treeMenu[6].setString(inputNums);
					//nodes = re.readIn(textMenuPosition);
					//buildTree(binT, textMenuPosition, nodes, treeMenu, nd);
					enter = false;
					menu = false;
					tree = true;
					binT->inorder(nd);
					treeMenu[7].setString("InOrder : " + binT->getInorderStr());
				}

				//Draw menu
				for (int i = 0; i < 6; i++)
				{
					window.draw(textMenu[i]);
				}
				

			}
			else if (tree)
			{
				if(nodes.size()>=5)
					treeMenu[5].setString("Remove fifth element : " + to_string(nodes[4]));
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					upTree = true;
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{ 
					downTree = true;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && upTree)
				{
					treeMenuPosition--;
					if (treeMenuPosition < 1)
						treeMenuPosition = 5;
					std::cout << treeMenuPosition << std::endl;
					for (int i = 1; i < 6; i++)
					{
						if (i == treeMenuPosition)
						{
							treeMenu[i].setFillColor(sf::Color::Green);
						}
						else
						{
							treeMenu[i].setFillColor(sf::Color::Red);
						}
					}
					upTree = false;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && downTree)
				{
					treeMenuPosition++;
					if (treeMenuPosition > 5)
						treeMenuPosition = 1;
					std::cout << treeMenuPosition << std::endl;
					for (int i = 1; i < 6; i++)
					{
						if (i == treeMenuPosition)
						{
							treeMenu[i].setFillColor(sf::Color::Green);
						}
						else
						{
							treeMenu[i].setFillColor(sf::Color::Red);
						}
					}

					downTree = false;
				}
			

				quit.setString("Press F1 back to menu");
				nd = binT->getRoot();
				if (nd != NULL)
				{
					if(lockRoot)
						binT->drawNodes(nd, window);
				}
					
		
				for (int i = 0; i < 8; i++)
				{
					window.draw(treeMenu[i]);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
				{
					menu = true;
					tree = false;
					binT->cleaeOrderStr();
					binT->destroyTree(nd);
					binT->treeHeight = 0;
					treeMenu[7].setString("");
					shuffleTree = true;
					treeMenu[4].setString("Shuffle tree Enabled");

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && enter)
				{
					enter = false;
					if (treeMenuPosition == 1)
					{
						cout << "Back to main" << endl;
						menu = true;
						tree = false;
						binT->cleaeOrderStr();
						binT->destroyTree(nd);
						binT->treeHeight = 0;
						treeMenu[7].setString("");
						shuffleTree = true;
						treeMenu[4].setString("Shuffle tree Enabled");
					}
					else if (treeMenuPosition == 2)
					{
						if (removeRoot)
						{
							
							binT->eraseTreeVector();
							cout << "PreOrder before delete root" << endl;
							if (nd != NULL)
							{						
								binT->deleteNode(binT->getRoot(), binT->getRoot()->data);
							}
							cout << "PreOrder after delete root" << endl;
							if (binT->getRoot() != NULL)
							{
								binT->eraseTreeVector();
								binT->resizeTreeVector();
								binT->PreOrder(binT->getRoot());
								nodes.erase(nodes.begin(), nodes.end());
								nodes.reserve(1000);
								nodes = binT->getTreeVector();
								delete binT;
								binT= new BinaryTree();
								changeTree(binT, textMenuPosition, nodes, treeMenu, nd, treeMenuPosition);
							}
							else
							{
								inputNums = "Input values : ";
								treeMenu[6].setString(inputNums);
								nodes.erase(nodes.begin(), nodes.end());
								nodes.reserve(1000); binT->eraseTreeVector();
								binT->resizeTreeVector();
							}
								enter = false;
								menu = false;
								tree = true;
								shuffleTree = true;
								treeMenu[4].setString("Shuffle tree enabled");
								if (nodes.size() < 20)
								{
									treeMenu[3].setString("Random input");
								}
								
								removeRoot = false;
						}
		
					}
					else if (treeMenuPosition == 3)
					{

						if (nodes.size() < 20)
						{
							treeMenu[3].setString("Random input");
							int  ran = (rand() % 100) + 1;
							binT->Insert(nd,binT->lastAddedNode, ran, 500, 50);//check
							nodes.push_back(ran);
							inputNums = "Input values : ";
							for (int i = 0;i < nodes.size(); i++)
							{
								inputNums += to_string(nodes[i]) + ", ";
							}
							treeMenu[6].setString(inputNums);
							shuffleTree = true;
							treeMenu[4].setString("Shuffle tree Enabled");
						}
						else
						{
							treeMenu[3].setString("Max size");
						}
					}
					else if (treeMenuPosition == 4)
					{
						if (removeRoot&&nodes.size()>0)
						{

							while (lock)
							{
								std::random_shuffle(nodes.begin(), nodes.end());
								lock = false;
							}
							lock = true;
							string str;
							binT->treeHeight = 0;
							binT->eraseTreeVector();
							delete binT;
							binT = new BinaryTree();
							changeTree(binT, textMenuPosition, nodes, treeMenu, nd, treeMenuPosition);
							enter = false;
							menu = false;
							tree = true;
							shuffleTree = false;
							treeMenu[4].setString("Disabled");
							removeRoot = false;
						}
					}
					else if (treeMenuPosition == 5)
					{

						if (nd != NULL && nodes.size() >= 5)
						{
							
							binT->deleteNode(binT->getRoot(), nodes[4]);
							cout << "Remove fifth node " << nodes[4] << endl;
							binT->eraseTreeVector();
							binT->PreOrder(binT->getRoot());
							nodes.erase(nodes.begin(), nodes.end());
							nodes.reserve(1000);
							nodes = binT->getTreeVector();
							changeTree(binT, textMenuPosition, nodes, treeMenu, nd, treeMenuPosition);
							enter = false;
							menu = false;
							tree = true;
						}
						else
							treeMenu[5].setString("Tree has less than 5 Nodes");
						shuffleTree = true;
						treeMenu[4].setString("Shuffle tree Enabled");
					}
					if (menu == false)
					{
						binT->cleaeOrderStr();
						nd = binT->getRoot();
						binT->inorder(nd);
						treeMenu[7].setString("InOrder : " + binT->getInorderStr());
					}
					
					
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					enter = true;
				}
			}
			
			window.draw(quit);
			
			
			window.display();
		
			if (removeRoot == false)
			{
				timeCounter++;
				treeMenu[2].setString("Disabled");
				treeMenu[4].setString("Disabled");
			}
				
			if (timeCounter % 20 == 0)
			{
				removeRoot = true;
				timeCounter = 0;
				if (nodes.size() > 0)
				{
					treeMenu[2].setString("Remove root");
					treeMenu[4].setString("Shuffle tree Enabled");
				}
				else
				{
					treeMenu[2].setString("Disabled");
					treeMenu[4].setString("Disabled");
				}
				
			}
			if (timeCounter > 20)
				timeCounter = 0;
			
			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}

