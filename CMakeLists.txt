project(電話帳_Phone_Book_App
        LANGUAGES C)

cmake_minimum_required(VERSION 2.6)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER} -rdynamic)

message(STATUS "Include: ${GTK3_INCLUDE_DIRS}\n LIB_DIR: ${GTK3_LIBRARY_DIRS} \n CFLAGS_OTHERS: ${GTK3_CFLAGS_OTHER} \n LIBS: ${GTK3_LIBRARIES}")


add_library( applib STATIC app.c)

add_executable(c_project c_project.c)
add_executable(read_file read_file.c)

add_subdirectory(cgraph)
add_subdirectory(libfdr)
 

target_link_libraries(c_project ${GTK3_LIBRARIES} cgraph fdr applib)
target_link_libraries(read_file ${GTK3_LIBRARIES} cgraph fdr applib)






