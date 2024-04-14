#include <iostream>
#include <vector>

struct BI {
  std::string num;
  BI(std::string str) : num(str) {}
  BI(char ch) : num(std::string() + ch) {}
  BI operator/(int xx) {
    xx += xx;
    BI other = *this;
    other.num.pop_back();
    return other;
  }
  BI operator%(int xx) {
    xx += xx;
    return {num[num.size() - 1]};
  }
  bool operator==(int xx) const {
    if (xx == 1) {
      return num == "1";
    }
    return num == "0";
  }
  BI& operator--() {
    if (*this == 0) {
      return *this;
    }
    int pos = num.size() - 1;
    while (num[pos] != '1') {
      --pos;
    }
    num[pos] = '0';
    ++pos;
    while (pos < int(num.size())) {
      num[pos] = '1';
      ++pos;
    }
    return *this;
  }
};

int mod;
int size;
int prof;

struct Matrix {
  std::vector<std::vector<int>> mat;

  Matrix()
      : mat(std::vector<std::vector<int>>(size, std::vector<int>(size, 0))) {}

  explicit Matrix(int xx) {
    mat = std::vector<std::vector<int>>(size, std::vector<int>(size, 0));
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        if (i == j) {
          mat[i][j] = xx % mod;
        }
      }
    }
  }

  void Assign(int ind, int jnd, int val) { mat[ind][jnd] = val % mod; }

  long long Sum() {
    long long res = 0;
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        res += mat[i][j] % mod;
      }
    }
    return res % mod;
  }

  Matrix operator*(Matrix other) {
    Matrix res;
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        for (int k = 0; k < size; ++k) {
          res.mat[i][j] += (mat[i][k] * other.mat[k][j]) % mod;
        }
        res.mat[i][j] %= mod;
      }
    }
    return res;
  }

  Matrix operator^(int xx) {
    xx += xx;
    return (*this) * (*this);
  }
};

Matrix Pow(Matrix& mat, BI pow) {
  if (pow == 1) {
    return mat;
  }
  if (pow == 0) {
    return Matrix(1);
  }
  return ((Pow(mat, pow / 2)) ^ 2) * (Pow(mat, pow % 2));
}

const int kDec = 10;

std::string operator/(std::string& str, int xx) {
  xx += xx;
  int rem = 0;
  std::string ans;
  for (size_t i = 0; i < str.size(); ++i) {
    int sign = str[i] - '0';
    ans += char((kDec * rem + sign) / 2 + '0');
    rem = (kDec * rem + sign) % 2;
  }
  if (ans[0] == '0' && ans != "0") {
    ans = std::string(ans.begin() + 1, ans.end());
  }
  return ans;
}

std::string Bin(std::string xx) {
  if (xx == "0") {
    return "0";
  }
  std::string str = Bin(xx / 2) + char(xx[xx.size() - 1] % 2 + '0');
  if (str[0] == '0' && str != "0") {
    str = std::string(str.begin() + 1, str.end());
  }
  return str;
}

bool Check(int p1, int p2) {
  for (int i = 0; i < prof - 1; ++i) {
    int sum = (p1 >> i) % 2 + (p2 >> i) % 2 + (p1 >> (i + 1)) % 2 +
              (p2 >> (i + 1)) % 2;
    if (sum < 1 || sum > 3) {
      return false;
    }
  }
  return true;
}

int main() {
  std::string ln;
  std::cin >> ln >> prof >> mod;
  size = (1 << prof);
  Matrix matrix;
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      matrix.Assign(i, j, int(Check(i, j)));
    }
  }
  std::cout << Pow(matrix, --BI(Bin(ln))).Sum();
}