# Secret Sharing Implementation

This repository contains implementations of Shamir's secret sharing scheme in both C++ and Rust. The secret sharing scheme allows you to divide a secret (e.g., an image) into multiple shares such that the secret can only be reconstructed when a sufficient number of shares are combined.

## Features

- **C++ Version**: The C++ implementation performs secret sharing using an image as the secret.
- **Rust Version**: The Rust implementation handles secret sharing of a single integer.

## Requirements

### C++ Version

- C++11 or later
- CMake
- OpenCV

### Rust Version

- Rust (latest stable version)

## Building and Running

### C++ Version

1. **Navigate to the C++ version directory:**

   ```sh
   cd cpp
   ```

2. **Create a build directory:**

   ```sh
   mkdir build && cd build
   ```

3. **Run CMake to configure the project:**

   ```sh
   cmake ..
   ```

4. **Build the project:**

   ```sh
   make
   ```

5. **Run the executable:**

   ```sh
   ./SecretSharingCPP [path_to_image]
   ```

   If no image path is provided, the program will default to `../../resources/secret_image.jpg`.

### Rust Version

1. **Navigate to the Rust version directory:**

   ```sh
   cd rust
   ```

2. **Build the project using Cargo:**

   ```sh
   cargo build
   ```

3. **Run the executable:**

   ```sh
   cargo run
   ```

## License

This project is licensed under the MIT License.

## Contact

If you have any questions, feel free to reach out via GitHub issues or connect with me on [LinkedIn](https://www.linkedin.com/in/rosemary-koikara/).

![LinkedIn Icon](https://cdn-icons-png.flaticon.com/16/174/174857.png)
