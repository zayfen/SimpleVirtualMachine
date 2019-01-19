cmake_minimum_required(VERSION 2.8)

project(SimpleVirtualMachine)

include_directories(../include)

set(SRC vm.c)

add_library(SimpleVirutalMachineLib SHARED ${SRC})
