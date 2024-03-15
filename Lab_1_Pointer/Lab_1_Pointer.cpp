#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

string to_lowercase(string str)
{
    string toLowerStr = "";
    for (int i = 0; i < str.size(); i++) {
        toLowerStr += tolower(str[i]);
    }
    return toLowerStr;
}

string* splite_line(string line) {
    string first, second;
    bool isComma = false;

    for (int i = 0; i < line.size(); i++) {
        if (isComma) {
            if (line[i] != ' ' && line[i] != ',') {
                second += line[i];
            }
        }

        if (line[i] == ',') isComma = true;

        if (!isComma) {
            first += line[i];
        }
    }

    first = to_lowercase(first);
    
    return new string[] { first, second };
}

class Pointer {
public: 
    Pointer() {};
    Pointer(string p_word) {
        word = p_word;
    };
    void setPage(int page) {
        if (pages.size() < 10) 
            pages.insert(page);
    }
    string getWord() {
        return word;
    }
    set<int> getPages() {
        return pages;
    }

private:
    string word;
    set<int> pages;
};

class Component {
public:
    void addPointer(string word, set<int> pages) {
        if (!point.count(word)) {
            Pointer p(word);
            for (int page : pages) {
                p.setPage(page);
            }
            point[word] = p;
        }
        else {
            cout << "This point already exists " << endl;
        }
    }
    void addPointerByFile(string filePath) {
        ifstream file(filePath);


        if (file.is_open()) { 
            string line;

            while (getline(file, line)) { 
                string* splitedLine = splite_line(line);

                string word = splitedLine[0];
                int page = stoi(splitedLine[1]);
       

                if (point.count(word)) {
                    point[word].setPage(page);
                }
                else {
                    Pointer p(word);
                    p.setPage(page);
                    point[word] = p;
                }
            }

            file.close(); 
            cout << "Data from file was successfully added" << endl << endl;
        }
        else {
            cerr << "Unable to open file" << endl << endl;
        }
    }
    Pointer getPointer(string word) {
        if (point.count(word)) {
            return point[word];
        }
        else {
            cout << "This point is not exists" << endl << endl;
        }
    }
    int deletePointer(string word) {
        return point.erase(to_lowercase(word));
    }

private:
    map<string, Pointer> point;
};

int main()
{
    Component comp;

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
            word = to_lowercase(word);

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

            comp.addPointer(word, pages);
            cout << "The pointer was created successfully \n\n";
            break;
        case 2:
            comp.addPointerByFile("C:\\Users\\Alex\\Desktop\\Programming IATU\\Mikeev\\labs\\Lab_1_Pointer\\Lab_1_Pointer\\Pointers.txt");
            break;
        case 3:
        {
            cout << "Please, enter a word\n\n";
            cin >> word;
            word = to_lowercase(word);
            
            Pointer p = comp.getPointer(word);

            cout << "word: " << p.getWord() << endl << endl;
            cout << "pages: " << endl << endl;

            set<int> pages = p.getPages();
            for (int page : pages) cout << page << "; ";
            cout << endl << endl;
        }
            break;
        case 4:
        {
            cout << "Please, enter a word\n\n";
            cin >> word;
            word = to_lowercase(word);

            Pointer p = comp.getPointer(word);

            cout << "Pages: " << endl << endl;
            for (int page : p.getPages()) cout << page << "; " << endl;
        }
            break;
        case 5:
        {
            cout << "Please, enter a word that do you want to delete \n\n";
            cin >> word;

            int deletingResult = comp.deletePointer(word);
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
