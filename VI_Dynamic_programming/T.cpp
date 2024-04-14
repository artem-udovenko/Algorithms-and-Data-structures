#include <iostream>
#include <vector>

int size;
const int kMod = 1'000'000'007;

struct Matrix {
  std::vector<std::vector<long long>> mat;

  Matrix()
      : mat(std::vector<std::vector<long long>>(
      size, std::vector<long long>(size, 0))) {
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        if (abs(i - j) < 2) {
          mat.at(i).at(j) = 1;
        }
      }
    }
  }

  explicit Matrix(int xx) {
    mat = std::vector<std::vector<long long>>(size,
                                              std::vector<long long>(size, 0));
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        if (i == j) {
          mat.at(i).at(j) = xx % kMod;
        }
      }
    }
  }

  Matrix operator*(Matrix other) {
    Matrix res(0);
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        for (int k = 0; k < size; ++k) {
          res.mat.at(i).at(j) +=
              (mat.at(i).at(k) * other.mat.at(k).at(j)) % kMod;
        }
        res.mat.at(i).at(j) %= kMod;
      }
    }
    return res;
  }

  Matrix operator^(int xx) {
    xx += xx;
    return (*this) * (*this);
  }

  long long Get(int ind, int jnd) { return mat.at(ind).at(jnd); }
};

Matrix Pow(Matrix& mat, long long pow) {
  if (pow == 1) {
    return mat;
  }
  if (pow == 0) {
    return Matrix(1);
  }
  return ((Pow(mat, pow / 2)) ^ 2) * (Pow(mat, pow % 2));
}

std::vector<long long> operator*(Matrix& matrix, std::vector<long long>& vec) {
  std::vector<long long> res(size);
  for (int i = 0; i < size; ++i) {
    long long ans = 0;
    for (int j = 0; j < size; ++j) {
      ans += (matrix.Get(i, j) * vec.at(j)) % kMod;
    }
    res.at(i) = ans % kMod;
  }
  return res;
}

int main() {
  int& size1 = size;
  int quantity;
  long long final;
  std::cin >> quantity >> final;
  std::vector<std::vector<long long>> src(quantity, std::vector<long long>(3));
  for (int i = 0; i < quantity; ++i) {
    std::cin >> src.at(i).at(0) >> src.at(i).at(1) >> src.at(i).at(2);
  }
  src.at(quantity - 1).at(1) = final;
  size1 = src.at(0).at(2) + 1;
  std::vector<long long> vec(size1, 0);
  vec.at(0) = 1;
  Matrix matrix;
  matrix = Pow(matrix, src.at(0).at(1) - src.at(0).at(0));
  vec = matrix * vec;
  for (int i = 1; i < quantity; ++i) {
    size1 = src.at(i).at(2) + 1;
    if (size1 < int(vec.size())) {
      vec = std::vector<long long>(vec.begin(), vec.begin() + size1);
    } else {
      const int kSize = vec.size();
      for (int k = 0; k < size1 - kSize; ++k) {
        vec.push_back(0);
      }
    }
    Matrix matr;
    matr = Pow(matr, src.at(i).at(1) - src.at(i).at(0));
    vec = matr * vec;
  }
  std::cout << vec.at(0) % kMod;
}