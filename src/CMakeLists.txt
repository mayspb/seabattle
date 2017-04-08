cmake_minimum_required(VERSION 2.8)

project(Sea_battle)

file(GLOB FILES ./*.h | ./*.cc)

add_executable(${PROJECT_NAME} ${FILES})