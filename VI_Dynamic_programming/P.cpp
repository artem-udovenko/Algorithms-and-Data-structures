#include <iostream>
#include <vector>

const int kMod = 1'000'000'007;
int wd;
int ln;
std::vector<std::string> mat;

bool Match(int prof) {
  for (int i = 0; i < wd; ++i) {
    if (mat[i][0] == '+' && ((prof & (1 << (wd - i - 1))) == 0)) {
      return false;
    }
    if (mat[i][0] == '-' && ((prof & (1 << (wd - i - 1))) != 0)) {
      return false;
    }
  }
  return true;
}

bool Check(char c1, char c2, int mask) {
  return (c1 != '+' || (mask / 2 != 0)) && (c2 != '-' || (mask % 2 != 1)) &&
         (c1 != '-' || (mask / 2 != 1)) && (c2 != '+' || (mask % 2 != 0));
}

void Dynamics(int ind, int jnd, int maskl, int maskr,
              std::vector<std::vector<long long>>& dp) {
  if (ind == 0) {
    for (int ms = 0; ms < (1 << 2); ++ms) {
      if (Check(mat[ind][jnd - 1], mat[ind][jnd], ms)) {
        Dynamics(ind + 1, jnd, ms / 2, ms % 2, dp);
      }
    }
  } else if (ind < wd) {
    for (int ms = 0; ms < (1 << 2); ++ms) {
      if (Check(mat[ind][jnd - 1], mat[ind][jnd], ms) &&
          (maskl % 2 + maskr % 2 + ms / 2 + ms % 2) == 2) {
        Dynamics(ind + 1, jnd, maskl * 2 + ms / 2, maskr * 2 + ms % 2, dp);
      }
    }
  } else {
    dp[jnd][maskr] += dp[jnd - 1][maskl];
    dp[jnd][maskr] %= kMod;
  }
}

int main() {
  std::cin >> wd >> ln;
  mat = std::vector<std::string>(wd);
  std::vector<std::vector<long long>> dp(ln,
                                         std::vector<long long>(1 << wd, 0));
  for (int i = 0; i < wd; ++i) {
    std::cin >> mat[i];
  }
  for (int prof = 0; prof < (1 << wd); ++prof) {
    if (Match(prof)) {
      dp[0][prof] = 1;
    }
  }
  for (int j = 1; j < ln; ++j) {
    Dynamics(0, j, 0, 0, dp);
  }
  long long res = 0;
  for (int prof = 0; prof < (1 << wd); ++prof) {
    res += dp[ln - 1][prof];
    res %= kMod;
  }
  std::cout << res;
}