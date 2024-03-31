#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <cctype>

#include "Pointer.h"

using namespace std;

string getWordFromConsole() {
    string word = "";

    cout << "Please, enter a word \n";
    cin >> word;
    cout << endl;

    return word;
}

int main()
{
    Pointer point;

    int choice;

    cout << "1. Create a new pointer \n"
        << "2. Add pointers from file \n"
        << "3. Show the pointer \n"
        << "4. Show pages for the word \n"
        << "5. Delete the pointer \n"
        << "6. Quit \n";

    do {
        string word = "";

        cout << "Enter your choice \n\n";
        cin >> choice;

        switch (choice)
        {
        case 1: {
            int countPages = 0;
            int totalPages = 0;
            set<int> pages;

            word = getWordFromConsole();

            do {
                cout << "Please, enter a count of pages(not more 10) \n";
                cin >> countPages;
            } while (countPages > 10 || countPages <= 0);

            map<string, set<int>> pointer = point.getPointer(word);

            if (pointer.size() > 0) {
                totalPages = pointer[Pointer::to_lowercase(word)].size() + countPages;
            }

            if (totalPages > 10) {
                cout << "The pointer " << word << " already has " << pointer[Pointer::to_lowercase(word)].size() << " pages.\n";
                cout << "The number of pages cannot be more than 10 \n";
                break;
            }

            cout << "Please, enter pages \n";
            for (int i = 0; i < countPages; i++) {
                int page;
                cin >> page;
                pages.insert(page);
            }

            cout << "-----RESULT-----\n\n";
            point.setPointer(word, pages);
            cout << "The pointer was created successfully \n\n";
            cout << "-----RESULT----\n\n";
            break;
        }
        case 2:
            point.setPointersByFile("Pointers.txt");
            break;
        case 3:
        {
            word = getWordFromConsole();

            word = Pointer::to_lowercase(word);

            map<string, set<int>> p = point.getPointer(word);

            if (p.size() != 0) {
                auto it = p.find(word);

                cout << "-----RESULT-----\n\n";
                cout << "word: " << it->first << endl;

                cout << "pages: ";

                for (int page : it->second) cout << page << "; ";
                cout << endl << endl;
                cout << "-----RESULT-----\n\n";
            }
            
        }
            break;
        case 4:
        {
            word = getWordFromConsole();

            if (point.getPages(word).size() == 0) {
                cout << "-----RESULT-----\n\n";
                cout << "The pointer dosn't exist\n";
                cout << "-----RESULT-----\n\n";

                break;
            }

            cout << "-----RESULT-----\n\n";
            cout << "Pages: ";
            for (int page : point.getPages(word)) cout << page << "; ";
            cout << endl;
            cout << "-----RESULT-----\n\n";

        }
            break;
        case 5:
        {
            word = getWordFromConsole();

            int deletingResult = point.deletePointer(word);

            cout << "-----RESULT-----\n\n";
            if (deletingResult == 1)
                cout << "The pointer " << word << " was successfully removed \n\n";
            else
                cout << "The pointer " << word << " doesn't exist \n\n";
            cout << "-----RESULT-----\n\n";
        }
            break;
        case 6:
            break;
        default:
            break;
        }
    } while (choice != 6);
}
