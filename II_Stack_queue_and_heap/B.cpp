#include <iostream>
#include <stack>
#include <vector>

int main() {
  long long number;
  std::cin >> number;
  std::vector<long long> arr(number);
  for (long long i = 0; i < number; ++i) {
    std::cin >> arr[i];
  }
  std::vector<std::pair<long long, long long>> bord_arr(number);
  std::stack<std::pair<long long, long long>> st;
  st.push(std::pair<long long, long long>(-1, -1));
  for (long long i = 0; i < number; ++i) {
    while (st.top().first >= arr[i]) {
      st.pop();
    }
    bord_arr[i].first = st.top().second;
    st.push(std::pair<long long, long long>(arr[i], i));
  }
  st = std::stack<std::pair<long long, long long>>();
  st.push(std::pair<long long, long long>(-1, number));
  for (long long i = number - 1; i > -1; --i) {
    while (st.top().first >= arr[i]) {
      st.pop();
    }
    bord_arr[i].second = st.top().second;
    st.push(std::pair<long long, long long>(arr[i], i));
  }
  long long max = 0;
  for (long long i = 0; i < number; ++i) {
    long long pl = arr[i] * (bord_arr[i].second - bord_arr[i].first - 1);
    if (pl > max) {
      max = pl;
    }
  }
  std::cout << max;
  return 0;
}