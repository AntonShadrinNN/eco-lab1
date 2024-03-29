cmake_minimum_required(VERSION 3.20)
project(lab2 C)

set(CMAKE_C_STANDARD 90)

set(CMAKE_C_FLAGS "/TC /Gz")
set(CMAKE_SHARED_LINKER_FLAGS "/DYNAMICBASE")
set(CMAKE_EXE_LINKER_FLAGS "/DYNAMICBASE")

add_definitions(-DECO_WINDOWS)
add_definitions(-D_DEBUG)
add_definitions(-DECO_DLL)
add_definitions(-DUGUID_UTILITY)
add_definitions(-DECO_WIN32)
add_definitions(-DWIN32)
add_definitions(-D_WINDOWS)
add_definitions(-D_CONSOLE)

include_directories(lab1/HeaderFiles)
include_directories(lab1/SharedFiles)
include_directories(components/SharedFiles)

include_directories(
        $ENV{ECO_FRAMEWORK}/Eco.List1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.Core1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.InterfaceBus1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.System1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.MemoryManager1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.FileSystemManagement1/SharedFiles
)


add_library(
        1F5DF16EE1BF43B999A434ED38FE8F3A
        SHARED
        lab1/SourceFiles/CEcoLab1.c
        lab1/SourceFiles/CEcoLab1Factory.c
        lab1/SharedFiles/IdEcoLab1.h
        lab1/SharedFiles/IEcoLab1.h
        lab1/HeaderFiles/CEcoLab1.h
        lab1/HeaderFiles/CEcoLab1Factory.h

        components/SharedFiles/IEcoCalculatorY.h
        components/SharedFiles/IEcoCalculatorX.h
        components/SharedFiles/IdEcoCalculatorD.h
        components/SharedFiles/IdEcoCalculatorE.h
        components/SharedFiles/IdEcoCalculatorA.h
        components/SharedFiles/IdEcoCalculatorB.h
)


add_executable(
        lab2
        UnitTestFiles/SourceFiles/EcoLab2.c
        lab1/SharedFiles/IdEcoLab1.h
        lab1/SharedFiles/IEcoLab1.h

        components/SharedFiles/IEcoCalculatorY.h
        components/SharedFiles/IEcoCalculatorX.h
        components/SharedFiles/IdEcoCalculatorD.h
        components/SharedFiles/IdEcoCalculatorE.h
        components/SharedFiles/IdEcoCalculatorA.h
        components/SharedFiles/IdEcoCalculatorB.h
)

include_directories(lab2/HeaderFiles)
include_directories(lab2/SharedFiles)

add_library(
        1F5DF16EE1BF43B999A434ED38FE8F3B
        SHARED
        lab2/SharedFiles/IEcoLab1.h
        lab2/SharedFiles/IdEcoLab2.h
        lab2/HeaderFiles/CEcoLab2.h
        lab2/HeaderFiles/CEcoLab2Factory.h
        lab2/SourceFiles/CEcoLab2.c
        lab2/SourceFiles/CEcoLab2Factory.c
)

target_link_libraries(lab2 1F5DF16EE1BF43B999A434ED38FE8F3A)
target_link_libraries(
        lab2
        $ENV{ECO_FRAMEWORK}/Eco.InterfaceBus1/BuildFiles/Windows/x86/StaticRelease/00000000000000000000000042757331.lib
        $ENV{ECO_FRAMEWORK}/Eco.MemoryManager1/BuildFiles/Windows/x86/StaticRelease/0000000000000000000000004D656D31.lib
        $ENV{ECO_FRAMEWORK}/Eco.FileSystemManagement1/BuildFiles/Windows/x86/StaticRelease/00000000000000000000000046534D31.lib
        $ENV{ECO_FRAMEWORK}/Eco.System1/BuildFiles/Windows/x86/StaticRelease/00000000000000000000000000000100.lib

        1F5DF16EE1BF43B999A434ED38FE8F3A
        1F5DF16EE1BF43B999A434ED38FE8F3B
)