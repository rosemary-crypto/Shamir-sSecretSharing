cmake_minimum_required(VERSION 3.10)
project(SecretSharingCPP)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

find_path(GMP_INCLUDE_DIR gmp.h /usr/include /usr/local/include)
find_library(GMP_LIBRARY NAMES gmp gmpxx PATHS /usr/lib /usr/local/lib)

if(NOT GMP_INCLUDE_DIR OR NOT GMP_LIBRARY)
    message(FATAL_ERROR "Could not find GMP library")
endif()

include_directories(${GMP_INCLUDE_DIR})
link_libraries(${GMP_LIBRARY})

# Find other dependencies
find_package(OpenCV REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})

add_executable(SecretSharingCPP main.cpp src/SecretSharing.cpp)
target_link_libraries(SecretSharingCPP ${OpenCV_LIBS} ${GMP_LIBRARIES} OpenSSL::SSL OpenSSL::Crypto)
