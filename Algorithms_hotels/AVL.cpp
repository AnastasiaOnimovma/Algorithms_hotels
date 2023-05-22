#include "AVL.h"
#include <fstream>

Hotel::Hotel() :
	name(""), acr(""), numb_of_rooms(0), numb_of_single_rooms(0), numb_of_double_rooms(0), numb_of_triple_rooms(0), price(0) {}
Hotel::Hotel(std::string n, std::string a, int r, int s, int d, int t, int p) :
	name(n), acr(a),numb_of_rooms(r), numb_of_single_rooms(s), numb_of_double_rooms(d), numb_of_triple_rooms(t), price(p) {}
Hotel::Hotel(const Hotel &h){
	name = h.name;
	acr = h.acr;
	numb_of_rooms = h.numb_of_rooms;
	numb_of_single_rooms = h.numb_of_single_rooms;
	numb_of_double_rooms = h.numb_of_double_rooms;
	numb_of_triple_rooms = h.numb_of_triple_rooms;
	price = h.price;
}

std::ostream& operator<< (std::ostream& out, Hotel& ht) {
	std::cout.width(10);
	out << ht.name<<" (" << ht.acr << ")";
	out.width(6);
	out << ht.numb_of_rooms;
	out.width(12);
	out << ht.numb_of_single_rooms;
	out.width(12);
	out << ht.numb_of_double_rooms;
	out.width(12);
	out << ht.numb_of_triple_rooms;
	std::cout.width(7);
	out<< ht.price << "\n";
	return out;
}



Node::Node(Hotel& h) {
	left = right = 0; 
	height = 1;
	hotel = h;
}

Hotel Node::get_hotel(Node* p) {
	return p->hotel;
}

int Node::get_height(Node* p) {
	return p ? p->height : 0;
}
	
int Node::get_balfactor(Node* p) {
	return get_height(p->right) - get_height(p->left);
}
	
void Node::fixheight(Node*& p) {
	p->height = std::max(get_height(p->left), get_height(p->right)) + 1;
}
	
Node* Node::singleRotateRight(Node* p) {
	Node* q = p->left;
	p->left = q->right;	
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

Node* Node::singleRotateLeft(Node* p) {
	Node* q = p->right;
	p->right = q->left;
	q->left = p;
	fixheight(p);
	fixheight(q);
	return q;
}


void Node::balance(Node*& p) {
	fixheight(p);
	if (get_balfactor(p) == 2){
		if (get_balfactor(p->right) < 0)
			p->right = singleRotateRight(p->right);
		p = singleRotateLeft(p);
	}
	if (get_balfactor(p) == -2){
		if (get_balfactor(p->left) > 0)
			p->left = singleRotateLeft(p->left);
		p = singleRotateRight(p);
	}
}


void Node::insert(Hotel& ht, Node*& p) {
	if (p == NULL) {
		p = new Node(ht);
	}
	else if (ht.price < p->hotel.price) {
		insert(ht, p->left);
	}
	else if (ht.price > p->hotel.price) {
		insert(ht, p->right);
	}
	balance(p);
	//return p;
}

void  Node::traversal(Node* p){
	if (p == NULL)
		return;
	traversal(p->left);
	std::cout << p->hotel.price << " ";
	traversal(p->right);
}

Node* Node::search(int &pr, Node* p) {
	if (p != NULL) {
		if (pr == p->hotel.price)
			return p;
		if (pr < p->hotel.price)
			return search(pr, p->left);
		else
			return search(pr, p->right);
	}
	else return NULL;
}


void showTrunks(Trunk* p, int& count) {
	if (p == nullptr) {
		return;
	}
	showTrunks(p->prev, count);
	count++;
	std::cout << p->str;
}

void Node::print(Node* root, Trunk* prev, bool isRight) {
	if (root == nullptr) {
		return;
	}
	std::string prev_str = "    ";
	Trunk* trunk = new Trunk(prev, prev_str);
	print(root->right, trunk, true);
	if (!prev) {
		trunk->str = " -->";
	}
	else if (isRight) {
		trunk->str = ".-->";
		prev_str = "   |";
	}
	else {
		trunk->str = "'-->";
		prev->str = prev_str;
	}
	int count = 0;
	showTrunks(trunk, count);
	std::cout << " " << root->hotel.price << "(" << root->hotel.acr << ")\n";
	if (prev) {
		prev->str = prev_str;
	}
	trunk->str = "   |";
	print(root->left, trunk, false);
}

AVL::AVL() { root = NULL; }
	
void AVL::insert_node(Hotel ht) {
	root->insert(ht, root);
}


void AVL::display() {
	std::cout << "\n";
	root->print(root, nullptr, false);
	std::cout << "\n";
}

void AVL::find(int &price) {
	Node* p=root->search(price, root);
	if (p != NULL) {
		Hotel hotel = root->get_hotel(p);
		std::cout <<"Found:\n"<< hotel<<"\n";
	}
	else {
		std::cout << "Not found\n";
	}

}


