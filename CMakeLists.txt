cmake_minimum_required(VERSION 3.10.0)
project(projects VERSION 0.1.0 LANGUAGES C CXX)


add_executable(project
        src/main.cpp
        

)
target_include_directories(project PUBLIC include)

