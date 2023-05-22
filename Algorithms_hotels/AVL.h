#pragma once

#include <iostream>
#include <string>

class Hotel {
public:
	std::string name;
	std::string acr;
	int numb_of_rooms;
	int numb_of_single_rooms;
	int numb_of_double_rooms;
	int numb_of_triple_rooms;
	int price;
	Hotel();
	Hotel(std::string n,std::string a, int r, int s, int d, int t, int p);
	Hotel( const Hotel& h);
	friend std::ostream& operator<< (std::ostream& out, Hotel& ht);
};

//структура для красивого вывода 
struct Trunk {
	Trunk* prev;
	std::string str;
	Trunk(Trunk* prev, std::string str) {
		this->prev = prev;
		this->str = str;
	}
};

class Node {
private:
	Node* left;
	Node* right;
	Hotel hotel;
	int height;
public:
	Node(Hotel& h); 

	Hotel get_hotel(Node* p);

	int get_height(Node* p);

	int get_balfactor(Node* p);

	void fixheight(Node*& p);

	Node* singleRotateRight(Node* p);

	Node* singleRotateLeft(Node* p);

	void balance(Node*& p);

	void insert(Hotel& ht, Node*& p);

	void  traversal(Node* p);

	Node* search(int &key, Node* p);

	void print(Node* root, Trunk* prev, bool isRight);

};

class AVL {
private:
	Node* root;
public:
	AVL();

	void insert_node(Hotel ht);

	void display();

	void find(int& price);
};