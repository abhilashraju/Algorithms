cmake_minimum_required(VERSION 3.14)

project(algorithms LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(algorithms
  coinsplit.cpp
  gridtraveller.cpp
  targetstring.cpp
  matrices.cpp
  SpiralSumVector.cpp
  SortedMedian.cpp
  longestpalindrome.cpp
  longestplaindromiterative.cpp
  zigzagstring.cpp
  smallestpositive.cpp
  Trapping_Rain_Water.cpp
  Reverse_Nodes_in_k_Group.cpp
  Merge_k_Sorted_Lists.cpp
  Substring_with_Concatenation_of_All_Words.cpp
  Longest_Valid_Parentheses.cpp

)




