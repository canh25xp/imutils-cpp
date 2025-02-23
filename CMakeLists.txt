cmake_minimum_required(VERSION 3.9)
project(imutils-cpp
    LANGUAGES CXX
    VERSION 1.0.1
    DESCRIPTION "imutils-cpp A series of convenience functions to make basic image processing functions such as translation, rotation, resizing and skeletonization easier with OpenCV "
    )

include(GNUInstallDirs)

find_package(OpenCV REQUIRED)
find_package(CURL REQUIRED)

if (MSVC AND BUILD_SHARED_LIBS)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()

set(CMAKE_DEBUG_POSTFIX d)

add_library(${PROJECT_NAME} src/text.cpp src/paths.cpp src/perspective.cpp src/convenience.cpp)

set(IMUTILS_HEADERS include/imutils/text.hpp include/imutils/paths.hpp include/imutils/perspective.hpp include/imutils/convenience.hpp include/imutils/imutils.hpp)
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER "${IMUTILS_HEADERS}"
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
)
target_link_libraries(${PROJECT_NAME} opencv_core opencv_imgcodecs opencv_imgproc CURL::libcurl)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/permissive-")
endif()
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    )

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/imutils
)

install(EXPORT ${PROJECT_NAME}Targets
    NAMESPACE imutils-cpp::
    DESTINATION lib/cmake
)
