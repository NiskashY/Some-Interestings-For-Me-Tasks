#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/// Not best solve but it works :)


void CreateCalendar(const vector <int>& month, vector <vector<vector<string>>>& cal) {
    int ind = 0, ind_last = 12;
    for(; ind < ind_last; ++ind) {
        cal[ind].assign(month[ind], vector <string> ());
    }
}

int CheckIndex(const int number_of_month) {
    if (number_of_month == 11) {
        return 0;
    }
    return number_of_month + 1;
}

vector <string> GetListFromDays (const vector <vector<string>>& list, int first, int second) {
    vector <string> s = list[first - 1];

    for(int i = first; i < second; ++i) {
        if (!list[i].empty()) {
            for(auto& now : list[i]) {
                s.push_back(now);
            }
        }
    }
    return s;
}

void DeleteUpDays(vector <vector<string>>& list, int first, int second) {
    for(int i = first; i < second; i++) {
        list.pop_back();
    }
}

int GetAmountOfWords (const vector <string> & str) {
    return (int)str.size();
}

void PrintList (vector <string>& ls) {
    for (auto& now : ls) {
        cout << now << ' ';
    }
}


int main() {
    vector <int> month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    vector <vector<vector<string>>> calendar (month.size()) ;
    CreateCalendar(month, calendar);

    int n, index = 0;
    cin >> n;

    while (n--) {
        string s, to_do_list;
        int tmp;
        cin >> s;
        if (s == "ADD"){
            cin >> tmp;
            cin.get();
            getline(cin, to_do_list);

            calendar[index][tmp - 1].push_back(to_do_list);
        }
        else if (s == "DUMP") {
            cin >> tmp;

            cout << GetAmountOfWords(calendar[index][tmp - 1]) << ' ';
            PrintList(calendar[index][tmp - 1]);
            cout << '\n';

        }
        else if (s == "NEXT"){
            int index_prev = index, index_next = CheckIndex(index);

            if (month[index_prev] < month[index_next]) {
                /**
                 * Create temp vector, that contains empty vector. This vector is needed for insert this vector in the end of new
                 **/
                vector <vector <string>> none_vec (month[index_next] - month[index_prev]);
                calendar[index_next] = calendar[index_prev];
                calendar[index_next].insert(end(calendar[index_next]), begin(none_vec), end(none_vec));
            }
            else if (month[index_prev] > month[index_next]) {
                vector <string> todo_list_tmp = GetListFromDays(calendar[index_prev], month[index_next], month[index_prev]);
                calendar[index_next] = calendar[index_prev];
                DeleteUpDays(calendar[index_next], month[index_next], month[index_prev]);
                calendar[index_next].back() = todo_list_tmp;
            }
            else {
                calendar[index_next] = calendar[index_prev];
            }
            index = index_next;
        }
    }
}