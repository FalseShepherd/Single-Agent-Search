cmake_minimum_required(VERSION 3.5)
project(LandmarksAndDifferentialHeuristics)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    arena.map
    DifferentialHeuristic.h
    Dijkstra.h
    EfficientAstar.h
    EfficientList.h
    GridAction.cpp
    GridEnvironment.cpp
    GridEnvironment.h
    InefficientAStar.h
    InefficientList.h
    main.cpp
    StateWrapper.h)

add_executable(LandmarksAndDifferentialHeuristics ${SOURCE_FILES})