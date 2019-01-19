cmake_minimum_required(VERSION 2.8)

project(SimpleVirtualMachine)

include_directories(./include)


add_subdirectory(./src)
add_subdirectory(./tests)

set(SRC main.c)



link_libraries(SimpleVirtualMachine SimpleVirutalMachineLib)

add_executable(SimpleVirtualMachine ${SRC})
