#include <iostream>
#include <vector>

const long long kMod = 1'000'000'009;

struct Matrix {
  long long a1;
  long long a2;
  long long a3;
  long long a4;
  Matrix() : a1(1), a2(1), a3(1), a4(0) {}
  Matrix(long long a1, long long a2, long long a3, long long a4)
      : a1((a1 % kMod + kMod) % kMod),
        a2((a2 % kMod + kMod) % kMod),
        a3((a3 % kMod + kMod) % kMod),
        a4((a4 % kMod + kMod) % kMod) {}
  explicit Matrix(long long num) : a1(num), a2(0), a3(0), a4(num) {}
  Matrix operator*(Matrix other) const {
    return {((a1 * other.a1 + a2 * other.a3) % kMod + kMod) % kMod,
            ((a1 * other.a2 + a2 * other.a4) % kMod + kMod) % kMod,
            ((a3 * other.a1 + a4 * other.a3) % kMod + kMod) % kMod,
            ((a3 * other.a2 + a4 * other.a4) % kMod + kMod) % kMod};
  }
};

Matrix Fib(long long pow) {
  if (pow <= 0) {
    return Matrix(1);
  }
  if (pow == 1) {
    return {};
  }
  if (pow % 2 == 1) {
    return Matrix() * Fib(pow - 1);
  }
  Matrix matrix = Fib(pow / 2);
  return matrix * matrix;
}

long long Fibonacci(long long pow) {
  if (pow < 0) {
    return 0;
  }
  return ((Fib(pow).a3 + Fib(pow).a4) % kMod + kMod) % kMod;
}

int main() {
  long long quantity;
  long long diag;
  std::cin >> quantity >> diag;
  std::vector<std::vector<long long>> port(quantity, std::vector<long long>(3));
  std::vector<long long> lin(diag);
  for (long long i = 0; i < quantity; ++i) {
    std::cin >> port[i][0] >> port[i][1] >> port[i][2];
  }
  for (long long i = 0; i < diag; ++i) {
    std::cin >> lin[i];
  }
  for (long long j = 0; j < diag; ++j) {
    long long res = 0;
    for (long long i = 0; i < quantity; ++i) {
      res += (port[i][2] % kMod) *
             (Fibonacci(port[i][1] - port[i][0] - lin[j]) % kMod);
      res = (res % kMod + kMod) % kMod;
    }
    std::cout << res << '\n';
  }
  return 0;
}