cmake_minimum_required(VERSION 2.8)
##########################################################################
#           Project Name; Don't forget to Name It!!!                     #
##########################################################################


#set( CMAKE_C_COMPILER /usr/local/linaro-aarch64-2017.08-gcc7.1/bin/aarch64-linux-gnu-gcc)
#set( CMAKE_CXX_COMPILER /usr/local/linaro-aarch64-2017.08-gcc7.1/bin/aarch64-linux-gnu-g++)


project(linux_app_test)

##########################################################################
#                  Include buildCentral common rules                     #
##########################################################################



##########################################################################
#                     Include sysroot of ZXQ project                     #
##########################################################################


##########################################################################
#               Head file search path for system library                 #
##########################################################################


##########################################################################
#                  Head file search path for the module                  #
##########################################################################

##########################################################################
#                Build rules for executable and library                  #
# To build executable using:                                             #
#   add_executable(executable_name, source_file, source_file, ...)       #
# To build static library using:                                         # 
#   add_library(library_name STATIC source_file, source_file, ...)       #
# To build shared library using:                                         # 
#   add_library(library_name SHARED source_file, source_file, ...)       #  
##########################################################################


message(STATUS "CMAKE_C_COMPILER1 = ${CMAKE_C_COMPILER}")






add_executable(slecet_client 	main.c)

