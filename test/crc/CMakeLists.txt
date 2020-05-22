cmake_minimum_required(VERSION 3.14)
project(crc CXX)

add_definitions(-D__BYTE_ORDER=4321)

add_library(crc Crc32.cpp Crc32.h)