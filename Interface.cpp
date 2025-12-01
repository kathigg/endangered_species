// made by Aastha Desai and Kathleen Higgins
#include "Interface.hpp"
#include "BST.hpp"
#include "TNode.hpp"

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

Interface::Interface(const string name, const bool Xtra) {
    fn = name; 
    tree = new BST(Xtra);
    readFile();
}

void Interface::Menu() {
    char c = 'a';
    while (c != 'q') {

        cout << endl << "****************************************************" << endl;
        cout << "* Choose Option:\n"
             << "*   a\tLook up Species\n"
             << "*   b\tAdd a Species to the Endangered List\n"
             << "*   c\tRemove a species from the Endangered List\n"
             << "*   d\tUpdate the Species Status\n"
             << "*   e\tPrint the Species Tree\n"
             << "*   x\tRun AVL Test (debug)\n"
             << "*   q\tquit" << endl;
        cout << "****************************************************" << endl << endl;

        cin >> c;

        switch (c) {

        case 'a': {
            cout << "What species do you want to look up?" << endl;
            string name;
            cin.ignore();
            getline(cin, name);

            int k = name.length() - 1;
            while (k >= 0 && (name[k] == ' ' || name[k] == '\n' || name[k] == '\t' ||
                              name[k] == '\r' || name[k] == '\v' || name[k] == '\f')) {
                k--;
            }
            name = name.substr(0, k + 1);

            TNode* t = tree->find(name);
            if (t == NULL) {
                cout << "." << name << "." << " not in endangered list." << endl;
            } else {
                t->printNode(true);
            }
            break;
        }

        case 'b': {
            string name, status, info;
            cout << "Enter Species: " << endl;
            cin.ignore();
            getline(cin, name);

            int k = name.length() - 1;
            while (k >= 0 && (name[k] == ' ' || name[k] == '\n' || name[k] == '\t' ||
                              name[k] == '\r' || name[k] == '\v' || name[k] == '\f')) {
                k--;
            }
            name = name.substr(0, k + 1);

            cout << "Enter Status (EX, EW, T1, T2, NT, VU, LC): " << endl;
            cin >> status;

            cout << "Enter species info: ";
            cin.ignore();
            getline(cin, info);

            if (tree->insert(name, status, info)) {
                cout << endl << name << " inserted successfully" << endl;
            } else {
                TNode* t = tree->find(name);
                t->printNode(false);
                cout << "... already in tree" << endl;
            }
            break;
        }

        case 'c': {
            cout << "Enter Species: " << endl;
            string name;
            cin.ignore();
            getline(cin, name);

            int k = name.length() - 1;
            while (k >= 0 && (name[k] == ' ' || name[k] == '\n' || name[k] == '\t' ||
                              name[k] == '\r' || name[k] == '\v' || name[k] == '\f')) {
                k--;
            }
            name = name.substr(0, k + 1);

            TNode* t = tree->remove(name);
            if (t == NULL) {
                cout << endl << name << " not in tree" << endl;
            } else {
                t->printNode(false);
                cout << "... has been removed." << endl;
            }
            break;
        }

        case 'd': {
            cout << "Enter Species: " << endl;
            string name;
            cin.ignore();
            getline(cin, name);

            int k = name.length() - 1;
            while (k >= 0 && (name[k] == ' ' || name[k] == '\n' || name[k] == '\t' ||
                              name[k] == '\r' || name[k] == '\v' || name[k] == '\f')) {
                k--;
            }
            name = name.substr(0, k + 1);

            TNode* tmp = tree->find(name);
            if (!tmp) {
                cout << name << " not found." << endl;
                break;
            }

            cout << "\t" << tmp->animal->name << endl;
            cout << "\t" << tmp->animal->status << endl;
            cout << "\t" << tmp->animal->info << endl << endl;

            cout << "Enter new Status: ";
            string status;
            cin >> status;

            tree->updateStatus(name, status);

            tmp = tree->find(name);
            cout << "\t" << tmp->animal->name << endl;
            cout << "\t" << tmp->animal->status << endl;
            cout << "\t" << tmp->animal->info << endl << endl;
            break;
        }

        case 'e': {
            cout << "Choose a for pre, b for in, or c for post-order: ";
            char k;
            cin >> k;

            cout << endl << "************************************************" << endl;

            if (k == 'a') {
                cout << "*********** Printing Tree Pre Order ************" << endl;
                tree->printTreePre();
            } else if (k == 'b') {
                cout << "*********** Printing Tree In Order *************" << endl;
                tree->printTreeIO();
            } else if (k == 'c') {
                cout << "*********** Printing Tree Post Order ***********" << endl;
                tree->printTreePost();
            }
            break;
        }

        case 'x': {
            cout << "Running isolated AVL test...\n";
            BST test(false); 

            test.insert("A", "T1", "x");
            test.insert("B", "T1", "x");
            test.insert("C", "T1", "x");

            cout << "\nPre-order should be: B A C\nYour output:\n";
            test.printTreePre();
            break;
        }

        case 'q': {
            cout << "Bye now!" << endl << endl;
            break;
        }

        default:
            cout << "Invalid option." << endl;
        }
    }
}

void Interface::strip(string s, string arr[]) {
    const char* EndChar = "|";
    size_t start = 0;
    int len;
    for (int i = 0; i < 3; i++) {
        len = s.length();
        s = s.substr(start, len - start + 1);
        size_t end = s.find_first_of(EndChar);
        if (end > 0) {
            arr[i] = s.substr(0, end);
            s = s.substr(end + 1, len - end);
        }
    }

    int k = arr[0].length() - 1;
    while (k >= 0 && (arr[0][k] == ' ' || arr[0][k] == '\n' || arr[0][k] == '\t' ||arr[0][k] == '\r' || arr[0][k] == '\v' || arr[0][k] == '\f')) {
		k--;
    }
    arr[0] = arr[0].substr(0, k + 1);
}

void Interface::readFile() {
    ifstream file(fn.c_str());
    string arr[3];
    string j;

    getline(file, j);

    while (!file.eof()) {
        if (j.length() > 0) {
            strip(j, arr);
            cout << arr[0] << ", " << arr[1] << ", " << arr[2] << endl;
            tree->insert(arr[0], arr[1], arr[2]);
        }
        getline(file, j);
    }

    tree->printTreeIO();
}
