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
include_directories(UnitTestFiles/HeaderFiles)

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

        lab1/HeaderFiles/CEcoLab1ConnectionPoint.h
        lab1/HeaderFiles/CEcoLab1EnumConnectionPoints.h
        lab1/HeaderFiles/CEcoLab1EnumConnections.h

        lab1/SharedFiles/IEcoConnectionPoint.h
        lab1/SharedFiles/IEcoConnectionPointContainer.h
        lab1/SharedFiles/IEcoEnumConnectionPoints.h
        lab1/SharedFiles/IEcoEnumConnections.h
        lab1/SharedFiles/IEcoLab1Events.h

        lab1/SourceFiles/CEcoLab1ConnectionPoint.c
        lab1/SourceFiles/CEcoLab1EnumConnectionPoints.c
        lab1/SourceFiles/CEcoLab1EnumConnections.c
)


add_executable(
        lab3
        UnitTestFiles/SourceFiles/EcoLab3.c
        lab1/SharedFiles/IdEcoLab1.h
        lab1/SharedFiles/IEcoLab1.h

        components/SharedFiles/IEcoCalculatorY.h
        components/SharedFiles/IEcoCalculatorX.h
        components/SharedFiles/IdEcoCalculatorD.h
        components/SharedFiles/IdEcoCalculatorE.h
        components/SharedFiles/IdEcoCalculatorA.h
        components/SharedFiles/IdEcoCalculatorB.h

        UnitTestFiles/HeaderFiles/CEcoLab1Sink.h
        UnitTestFiles/SourceFiles/CEcoLab1Sink.c
)

target_link_libraries(
        lab3
        $ENV{ECO_FRAMEWORK}/Eco.InterfaceBus1/BuildFiles/Windows/x86/StaticRelease/00000000000000000000000042757331.lib
        $ENV{ECO_FRAMEWORK}/Eco.MemoryManager1/BuildFiles/Windows/x86/StaticRelease/0000000000000000000000004D656D31.lib
        $ENV{ECO_FRAMEWORK}/Eco.FileSystemManagement1/BuildFiles/Windows/x86/StaticRelease/00000000000000000000000046534D31.lib
        $ENV{ECO_FRAMEWORK}/Eco.System1/BuildFiles/Windows/x86/StaticRelease/00000000000000000000000000000100.lib
        $ENV{ECO_FRAMEWORK}/Eco.List1/BuildFiles/Windows/x86/StaticRelease/53884AFC93C448ECAA929C8D3A562281.lib
        1F5DF16EE1BF43B999A434ED38FE8F3A
)