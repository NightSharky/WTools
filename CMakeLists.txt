cmake_minimum_required(VERSION 2.6)

project(Tools)

aux_source_directory(./src/dbc SRC_DBC)

add_executable(Dbc ${SRC_DBC})

#target_link_libraries(AdtRead -lm)