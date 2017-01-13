cmake_minimum_required(VERSION 2.6)

project(Tools)

aux_source_directory(./src/dbc SRC_DBC)
aux_source_directory(./src/wdt SRC_WDT)
aux_source_directory(./src/wmo SRC_WMO)

add_executable(Dbc ${SRC_DBC})
add_executable(Wdt ${SRC_WDT})
add_executable(Wmo ${SRC_WMO})