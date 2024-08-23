#include "SecretSharing.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

SecretSharing::SecretSharing(int n, int k, int prime)
    : n_(n), k_(k), prime_(prime) {
  std::srand(std::time(0));  // Seed for random number generation
}

int SecretSharing::EvaluatePolynomial(const std::vector<int>& coefficients, int x) const {
  int y = 0;
  int x_power = 1;  // This will be x^i for each term

  for (int coeff : coefficients) {
    y += coeff * x_power;
    y %= prime_;  // Keep it within the field
    x_power = x_power * x;
  }

  return y;
}

std::vector<std::pair<int, int>> SecretSharing::GenerateShares(const int secret ) {
  std::vector<std::pair<int, int>> shares;
  std::vector<int> coefficients(k_);  // Coefficients for the polynomial

  // Randomly generate coefficients (excluding the secret, which is the constant term)
  coefficients[0] = secret;
  for (int i = 1; i < k_; ++i) {
    coefficients[i] = rand() % prime_;  // Random coefficient less than prime
  }

  // Generate shares
  for (int x = 1; x <= n_; ++x) {
    int y = EvaluatePolynomial(coefficients, x);
    shares.push_back({x, y});
  }
  return shares;
}

// Interpolate a polynomial from given points
int SecretSharing::Interpolate(const std::vector<std::pair<int, int>>& points, int x) const {
  int result = 0;

  for (size_t i = 0; i < points.size(); ++i) {
    int xi = points[i].first;
    int yi = points[i].second;

    int li = 1;  // Lagrange basis polynomial

    for (size_t j = 0; j < points.size(); ++j) {
      if (i != j) {
        int xj = points[j].first;
        int numerator = (x - xj + prime_) % prime_;
        int denominator = (xi - xj + prime_) % prime_;

        // Calculate the modular inverse of the denominator
        int denominator_inv = ModInverse(denominator, prime_);
        if (denominator_inv == -1) {
          std::cerr << "Modular inverse calculation failed!" << std::endl;
          return -1;
        }

        // Multiply and take modulo prime
        li = (li * numerator) % prime_;
        li = (li * denominator_inv) % prime_;
      }
    }

    // Add the contribution of this term to the result
    result = (result + (yi * li) % prime_) % prime_;
  }

  // Ensure the result is non-negative
  if (result < 0) {
    result += prime_;
  }

  return result;
}



int SecretSharing::ReconstructSecret(const std::vector<std::pair<int, int>>& shares) {
  return Interpolate(shares, 0);  // Interpolate at x=0 to find the secret
}

// Helper function to compute modular inverse
int ModInverse(int a, int m) {
  int m0 = m, t, q;
  int x0 = 0, x1 = 1;

  if (m == 1) return 0;

  while (a > 1) {
    // q is quotient
    q = a / m;
    t = m;

    // m is remainder now, process same as Euclid's algo
    m = a % m, a = t;
    t = x0;

    x0 = x1 - q * x0;
    x1 = t;
  }

  if (x1 < 0) x1 += m0;

  return x1;
}
