cmake_minimum_required(VERSION 3.7)
project(rt)
set(CMAKE_CXX_STANDARD 17)

#################### OPENCV
message("------------- OPENCV")

if(WIN32)
    set(CMAKE_MODULE_PATH "C:/users/rmant/CLionProjects/ray_tracer/3rd/opencv")
    message("FindOpenCV.cmake path: " ${CMAKE_MODULE_PATH})
    set(OpenCV_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/3rd/opencv/include")
    set(OpenCV_LIBRARIES "${PROJECT_SOURCE_DIR}/3rd/opencv/lib/libopencv_imgproc470.dll.a;${PROJECT_SOURCE_DIR}/3rd/opencv/lib/libopencv_highgui470.dll.a;${PROJECT_SOURCE_DIR}/3rd/opencv/lib/libopencv_core470.dll.a;${PROJECT_SOURCE_DIR}/3rd/opencv/lib/libopencv_imgcodecs470.dll.a")

    # To automatically generate OpenCV_INCLUDE_DIRS and OpenCV_LIBRARIES uncomment the below lines
#    set(OpenCV_DIR "C:/opencv/mingw-build")
#    find_package(OpenCV REQUIRED)
#    if (OpenCV_FOUND)
#        message("OpenCV found")
#        message("Include directory: " ${OpenCV_INCLUDE_DIRS})
#    endif()
else()
    find_package(OpenCV REQUIRED)
    if (OpenCV_FOUND)
        message("OpenCV found")
        message("Include directory: " ${OpenCV_INCLUDE_DIRS})
    endif()
endif()


############ OUTPUT FOLDERS
message("-------------- OUTPUT DIRECTORIES")
message("Project folder: " ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
message("Runtime folder set to: " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


############ SOURCE FILES
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)


################# RT APP
add_executable(rt ${SOURCE_FILES})

target_include_directories(rt PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(rt PUBLIC ${OpenCV_LIBRARIES})








