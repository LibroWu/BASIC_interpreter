cmake_minimum_required(VERSION 3.17)
project(code)

set(CMAKE_CXX_STANDARD 14)

add_executable(windows_for_make Basic/Basic.cpp Basic/exp.h Basic/exp.cpp
                Basic/program.h Basic/program.cpp
                Basic/parser.cpp Basic/parser.h
        StanfordCPPLib/tokenscanner.h StanfordCPPLib/tokenscanner.cpp
        StanfordCPPLib/simpio.h StanfordCPPLib/simpio.cpp
        StanfordCPPLib/strlib.h StanfordCPPLib/strlib.cpp
        StanfordCPPLib/error.h StanfordCPPLib/error.cpp
        Basic/statement.h Basic/statement.cpp
        Basic/evalstate.h Basic/evalstate.cpp)