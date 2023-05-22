#include "AVL.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>


void merge(Hotel* arr, int low, int middle, int high) {
    int lw = low, k = low, mid = middle + 1;
    Hotel* new_arr = new Hotel[100];
    while (lw <= middle && mid <= high) {
        if (arr[lw].price < arr[mid].price) {
            new_arr[k++] = arr[lw++];
        }
        else {
            new_arr[k++] = arr[mid++];
        }
    }
    while (lw <= middle) {
        new_arr[k++] = arr[lw++];
    }
    while (mid <= high) {
        new_arr[k++] = arr[mid++];
    }
    for (int i = low; i < k; i++) {
        arr[i] = new_arr[i];
    }
}

void mergeSort(Hotel* arr, int low, int high) {
    if (high <= low) {
        return;
    }
    int mid = (low + high) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}



void readFile(std::vector <Hotel>& hotels, bool theWorst) {
    std::ifstream File;
    std::string text;
    if (theWorst) {
        File.open("practice_example_worst.txt", std::ios::binary);
    }
    else {
        File.open("practice_example.txt", std::ios::binary);
    }
    if (!File.is_open()){
        std::cout << "Can not open\n";
        return;
    }
    char Buf[1024];
    while (!File.eof()) {
        File.getline(Buf, 1024);
        text = std::string(Buf);
        std::stringstream str(text);
        Hotel ht;
        std::string word;
        str >> word;
        ht.name = word;
        str >> word;
        ht.acr = word;
        str >> word;
        ht.numb_of_rooms =stoi(word);
        str >> word;
        ht.numb_of_single_rooms = stoi(word);
        str >> word;
        ht.numb_of_double_rooms = stoi(word);
        str >> word;
        ht.numb_of_triple_rooms = stoi(word);
        str >> word;
        ht.price = stoi(word);
        hotels.push_back(ht);
    }
    File.close();
    std::cout << "\nFile reading completed\n\n";
}

void printHeader() {
    std::cout << "\x1B[34m"; // синий цвет 
    std::cout.width(10);
    std::cout << "Name";
    std::cout.width(6);
    std::cout << "Acr";
    std::cout << " Rooms SingleRooms DoubleRooms TripleRooms  Price\033[0m\n";
}

void menu() {
    static AVL avl;
    static std::vector <Hotel> hotels;
    static char answer;
    static int file;
    std::chrono::system_clock::time_point begin, end;
    if (answer) {
        std::cout << "\nDo you want to change file(y/n)?";
        std::cin >> answer;
        if (answer == 'y') {
            hotels.clear();
            file--;
            readFile(hotels, file);
        }
        else if (answer == 'n');
        else {
            std::cout << "Wrong answer\n";
        }
    }
    else {
        std::cout << "Choose the file: normal(0) / the worst(1)";
        std::cin >> file;
        readFile(hotels, file);
    }
    printHeader();
    for (int i = 0; i < hotels.size(); i++) {
        std::cout << hotels[i];
    }
    std::cout << "\nShould I sort it(y/n)?";
    std::cin >> answer;
    if (answer == 'y') {
        begin = std::chrono::system_clock::now();
        mergeSort(hotels.data(), 0, hotels.size() - 1);
        end = std::chrono::system_clock::now();
        std::cout << "Mergesort: " << (end - begin).count() << " ms\n";
        printHeader();
        for (int i = 0; i < hotels.size(); i++) {
            std::cout << hotels[i];
        }
    }
    else if (answer == 'n');
    else {
        std::cout << "Wrong answer\n";
    }
    for (int i = 0; i < hotels.size(); i++) {
        avl.insert_node(hotels[i]);
    }
    std::cout << "\nDo you want to see AVL(y/n)?";
    std::cin >> answer;
    if (answer == 'y') {
        avl.display();
    }
    else if (answer == 'n');
    else {
        std::cout << "Wrong answer\n";
    }
    int price;
    std::cout << "\nEnter the price you want: ";
    std::cin >> price;
    begin = std::chrono::system_clock::now();
    avl.find(price);
    end = std::chrono::system_clock::now();
    std::cout << "Searching in the tree: " << (end - begin).count() << " ms\n";
    std::cout << "\nDo you want to continue(y/n)?";
    std::cin >> answer;
    if (answer == 'y') {
        menu();
    }
    else if (answer == 'n')
        return;
    else {
        std::cout << "Wrong answer\n";
    }
}


int main() {
    menu();
	return 0;
}