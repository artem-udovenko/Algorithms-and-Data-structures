#include <iostream>
#include <stack>

int Identificate(char ch) {
  const int kLen = 6;
  char dict[kLen] = {'(', ')', '[', ']', '{', '}'};
  for (int i = 0; i < kLen; ++i) {
    if (ch == dict[i]) {
      return i;
    }
  }
  return -1;
}

int main() {
  std::string str;
  std::cin >> str;
  std::stack<char> st;
  bool flag = true;
  for (char ch : str) {
    int id = Identificate(ch);
    if (id % 2 == 0) {
      st.push(ch);
    } else {
      if (st.empty()) {
        flag = false;
      } else if (Identificate(st.top()) == id - 1) {
        st.pop();
      } else {
        flag = false;
        break;
      }
    }
  }
  if (flag && st.empty()) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  return 0;
}