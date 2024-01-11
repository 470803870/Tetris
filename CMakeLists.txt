cmake_minimum_required(VERSION 3.20)

project(Tetris)

aux_source_directory(. src)

add_executable(Tetris ${src})