cmake_minimum_required(VERSION 3.16)
project(aisd_projects LANGUAGES CXX)

# Cross-platform build of all five assignments. The original Visual Studio
# solutions (.sln/.vcxproj) in each folder still work as before.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release)
endif()
if(MSVC)
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

set(RPN_DIR "Proj_AISD_1_2024/Proj_AISD_1_2024")
add_executable(rpn
  "${RPN_DIR}/Source.cpp" "${RPN_DIR}/RPN.cpp" "${RPN_DIR}/myString.cpp")

set(CSS_DIR "ProjektAIDS2/ProjektAIDS2")
add_executable(css "${CSS_DIR}/ProjektAIDS2.cpp")

set(HEX_DIR "AISD_Proj2_2024 Hex/AISD_Proj2_2024 Hex")
add_executable(hex
  "${HEX_DIR}/Source.cpp" "${HEX_DIR}/game.cpp" "${HEX_DIR}/myString.cpp")

set(JD_DIR "C++_ProjectAIDS_2_JakDojade_Graph_Dijkstra/C++_ProjectAIDS_2_JakDojade_Graph_Dijkstra")
add_executable(jakdojade
  "${JD_DIR}/Source.cpp" "${JD_DIR}/Graph.cpp" "${JD_DIR}/Queue.cpp")

set(GRAPHS_DIR "AISD_Proj3/AISD_Proj3")
add_executable(graphs
  "${GRAPHS_DIR}/Source.cpp" "${GRAPHS_DIR}/GraphList.cpp" "${GRAPHS_DIR}/GraphMatrix.cpp"
  "${GRAPHS_DIR}/tree.cpp" "${GRAPHS_DIR}/utils.cpp")
