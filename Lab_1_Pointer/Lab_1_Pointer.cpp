#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <cctype>

#include "Pointer.h"
#include "MyStr.h"

using namespace std;

int main()
{
    Pointer point;

    int choice;
    string word;
    int countPages;
    set<int> pages;

    cout << "1. Create a new pointer \n"
        << "2. Add pointers from file \n"
        << "3. Show the pointer \n"
        << "4. Show pages for the word \n"
        << "5. Delete the pointer \n"
        << "6. Quit \n";

    do {
        cout << "Enter your choice \n\n";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Please, enter a word \n";
            cin >> word;
            cout << endl;

            do {
                cout << "Please, enter a count of pages(not more 10) \n";
                cin >> countPages;
            } while (countPages > 10);
            
            cout << "Please, enter pages \n";
            for (int i = 0; i < countPages; i++) {
                int page;
                cin >> page;
                pages.insert(page);
            }

            point.setPointer(word, pages);
            cout << "The pointer was created successfully \n\n";
            break;
        case 2:
            point.setPointersByFile("C:\\Users\\Alex\\Desktop\\Programming IATU\\Mikeev\\labs\\Lab_1_Pointer\\Lab_1_Pointer\\Pointers.txt");
            break;
        case 3:
        {
            cout << "Please, enter a word\n\n";
            cin >> word;
            cout << endl;

            word = MyStr::to_lowercase(word);

            map<string, set<int>> p = point.getPointer(word);

            if (p.size() != 0) {
                auto it = p.find(word);

                cout << "word: " << it->first << endl;

                cout << "pages: ";

                for (int page : it->second) cout << page << "; ";
                cout << endl << endl;
            }
            
        }
            break;
        case 4:
        {
            cout << "Please, enter a word\n\n";
            cin >> word;
            cout << endl;

            cout << "Pages: ";
            for (int page : point.getPages(word)) cout << page << "; ";
            cout << endl;
        }
            break;
        case 5:
        {
            cout << "Please, enter a word that do you want to delete \n\n";
            cin >> word;
            cout << endl;

            int deletingResult = point.deletePointer(word);
            if (deletingResult == 1)
                cout << "The pointer " << word << " was successfully removed \n\n";
            else
                cout << "The pointer " << word << " doesn't exist \n\n";
        }
            break;
        case 6:
            break;
        default:
            break;
        }
    } while (choice != 6);
}
