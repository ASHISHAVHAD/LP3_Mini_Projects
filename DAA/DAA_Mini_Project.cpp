#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> naiveStringMatching(const string& text, const string& pattern) {
    vector<int> positions;
    int n = text.size();
    int m = pattern.size();

    for (int i = 0; i <= n - m; i++) {
        bool match = true;
        for (int j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            positions.push_back(i);
        }
    }

    return positions;
}

vector<int> rabinKarp(const string& text, const string& pattern, int q = 101) {
    vector<int> positions;
    int n = text.size();
    int m = pattern.size();
    int d = 256;
    int p = 0;
    int t = 0;
    int h = 1;

    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    
    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    
    for (int i = 0; i <= n - m; i++) {
        
        if (p == t) {
            
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match)
                positions.push_back(i);
        }

        
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0)
                t = (t + q);
        }
    }

    return positions;
}

int main() {
    string text, pattern;

    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Enter the pattern: ";
    getline(cin, pattern);

    cout << "Choose algorithm:\n1. Naive String Matching\n2. Rabin-Karp Algorithm\n";
    int choice;
    cin >> choice;
    cin.ignore();

    vector<int> positions;

    switch (choice) {
        case 1:
            positions = naiveStringMatching(text, pattern);
            cout << "Naive String Matching positions: ";
            break;
        case 2:
            positions = rabinKarp(text, pattern);
            cout << "Rabin-Karp String Matching positions: ";
            break;
        default:
            cout << "Invalid choice!" << endl;
            return 1;
    }

    for (int pos : positions) {
        cout << pos << " ";
    }
    cout << endl;

    return 0;
}

/*

Output

C:\Users\ASHISH\Desktop\Sem 7\LP-III\Mini-Projects>DAA_Mini_Project
Enter the text: hello I am a computer student
Enter the pattern: uter
Choose algorithm:
1. Naive String Matching
2. Rabin-Karp Algorithm
1
Naive String Matching positions: 17

C:\Users\ASHISH\Desktop\Sem 7\LP-III\Mini-Projects>DAA_Mini_Project
Enter the text: hello I am a computer student
Enter the pattern: ent
Choose algorithm:
1. Naive String Matching
2. Rabin-Karp Algorithm
2
Rabin-Karp String Matching positions: 26

*/
