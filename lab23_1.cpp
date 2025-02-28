#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source(filename);
    string textline;
    while(getline(source, textline)){
        char format[] = "%[^:]: %d %d %d";
        char name[100];
        int a, b, c;
        sscanf(textline.c_str(), format, name, &a, &b, &c);
        names.push_back(name);
        scores.push_back(a + b + c);
        grades.push_back(score2grade(a + b + c));
    }
    source.close();
}


void getCommand(string &command, string &key){
    cout << "Please input your command:\n";
    getline(cin, command); 
    while (command != "EXIT") { 
        string x = command;
        size_t start = 0;
        size_t end = x.find_first_of(" ");

        if (end != string::npos) { 
            command = x.substr(start, end - start);
            key = x.substr(end + 1); 
        } else {
            command = x;
            key = "";
        }
        break;
    }
}

void searchName(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, const string &key){
    cout << "---------------------------------\n";
    bool found = false;
    for(unsigned i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            found = true;
        }
    }
    if(!found) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, const string &key){
    cout << "---------------------------------\n";
    bool found = false;
    for(unsigned i = 0; i < grades.size(); i++){
        if(grades[i] == key[0]){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if(!found) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
