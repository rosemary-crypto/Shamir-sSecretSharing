#ifndef SECRET_SHARING_H_
#define SECRET_SHARING_H_

#include <vector>
#include <utility>

class SecretSharing {
 public:
  SecretSharing(int n, int k, int prime);
  std::vector<std::pair<int, int>> GenerateShares(const int secret);
  int ReconstructSecret(const std::vector<std::pair<int, int>>& shares);

 private:
  int EvaluatePolynomial(const std::vector<int>& coefficients, int x) const;
  int Interpolate(const std::vector<std::pair<int, int>>& points, int x) const;

  int n_;  // Number of shares
  int k_;  // Threshold number of shares needed to reconstruct the secret
  int prime_;  // Prime number for the finite field
};

// Helper function to compute modular inverse
int ModInverse(int a, int m);

#endif  // SECRET_SHARING_H_
