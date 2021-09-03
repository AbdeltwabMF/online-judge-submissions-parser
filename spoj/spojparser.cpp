#include <functional>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ios>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

void fast() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}

string submission_id, problem_name, lang, verdict;
vector <vector<string>> submissions(0, vector<string>(4));
vector <vector<string>> unique_subs(0, vector<string>(4));

int main() {
  fast();

  while(cin >> submission_id >> problem_name >> verdict >> lang) {
    if(verdict == "AC" || verdict == "100")
      submissions.push_back({submission_id, problem_name, verdict, lang});
  }

  if(submissions.empty())
    exit(0);

  sort(submissions.begin(), submissions.end(), [&](vector<string> &lhs, vector<string> &rhs) -> bool {
    if(lhs[1] != rhs[1])
      return lhs[1] < rhs[1];
    else
      return lhs[0] > rhs[0];
  });

  unique_subs.emplace_back(submissions[0]);
  for(int i = 1; i < (int)submissions.size(); ++i) {
    if(submissions[i][1] != unique_subs.back()[1]) {
      unique_subs.emplace_back(submissions[i]);
    }
  }

  sort(unique_subs.rbegin(), unique_subs.rend());

  string sol_path = "spoj/solutions/";
  string root_url = "https://www.spoj.com/problems/";
  cout << "| # | Submission ID | Problem Name | Verdict | lang |" << endl;
  cout << "|:-:| :-----------: | :----------: | :-----: | :--: |" << endl;

  for(int i = 0, c = (int)unique_subs.size(); i < (int)unique_subs.size(); ++i) {
    cout << "| " << c--;
    for(int j = 0; j < (int)unique_subs[i].size(); ++j) {
      if(j == 1)
        cout << " | [" << unique_subs[i][j] << "](" << root_url + unique_subs[i][j] << ")";
      else if(j == 0)
        cout << " | [" << unique_subs[i][j] << "](" << sol_path + unique_subs[i][1] << ")";
      else
        cout << " | " << unique_subs[i][j];
    }
    cout << " |" << endl;
  }
}
