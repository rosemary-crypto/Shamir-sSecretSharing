#include "SecretSharing.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  //Default image filename
  std::string image_filename = "../../resources/secret_image.jpg";

  if (argc > 1) {
    image_filename = argv[1];
  }

  cv::Mat secret_image = cv::imread(image_filename, cv::IMREAD_GRAYSCALE);
  if (secret_image.empty()) {
    std::cerr << "Error loading image from: " << image_filename << std::endl;
    return -1;
  }

  // Parameters for secret sharing
  const int kNumShares = 5;  // Number of shares to generate
  const int kThreshold = 3;  // Minimum number of shares needed to reconstruct the secret
  const int kPrime = 257;    // A prime number larger than 255 (since pixel values range from 0 to 255)
  SecretSharing ss(kNumShares, kThreshold, kPrime);
  
  // Generate shares for each pixel
  std::vector<std::vector<std::vector<int>>> shares(
      kNumShares, std::vector<std::vector<int>>(secret_image.rows, std::vector<int>(secret_image.cols)));
  for (int i = 0; i < secret_image.rows; ++i) {
    for (int j = 0; j < secret_image.cols; ++j) {
        int pixel_value = secret_image.at<uchar>(i, j);
        std::vector<std::pair<int, int>> pixel_shares = ss.GenerateShares(pixel_value);
        for (int x = 0; x < kNumShares; ++x) {
        shares[x][i][j] = pixel_shares[x].second;
        }
    }
  }
  
  // Save share images
  for (int x = 0; x < kNumShares; ++x) {
    cv::Mat share_image(secret_image.size(), CV_8U);
    for (int i = 0; i < share_image.rows; ++i) {
      for (int j = 0; j < share_image.cols; ++j) {
        share_image.at<uchar>(i, j) = shares[x][i][j];
      }
    }
    std::string share_filename = "share_" + std::to_string(x + 1) + ".jpg";
    cv::imwrite(share_filename, share_image);
    std::cout << "Share saved to: " << share_filename << std::endl;
  }

  // Reconstruct the image using k shares
  cv::Mat reconstructed_image(secret_image.size(), CV_8U);
  for (int i = 0; i < reconstructed_image.rows; ++i) {
    for (int j = 0; j < reconstructed_image.cols; ++j) {
      std::vector<std::pair<int, int>> pixel_shares;
      for (int x = 0; x < kThreshold; ++x) {
        pixel_shares.push_back({x + 1, shares[x][i][j]});
      }
      int pixel_value = ss.ReconstructSecret(pixel_shares);
      reconstructed_image.at<uchar>(i, j) = pixel_value;
    }
  }

  std::string reconstructed_filename = "reconstructed_image.jpg";
  cv::imwrite(reconstructed_filename, reconstructed_image);
  std::cout << "Reconstructed image saved to: " << reconstructed_filename << std::endl;

  return 0;
}