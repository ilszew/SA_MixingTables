cmake_minimum_required(VERSION 3.30)
project(SD_TabliceMieszajace)

set(CMAKE_CXX_STANDARD 20)

add_executable(SD_TabliceMieszajace main.cpp
        hashTableAVL.h
        hashTableChaining.h
        randomGenerator.h
        arrayList.h
        timer.h
        hashTablePerformanceTester.h
)
