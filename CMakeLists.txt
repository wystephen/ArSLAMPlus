cmake_minimum_required(VERSION 3.5)
project(ArSLAM_)

set(CMAKE_CXX_STANDARD 11)


#Project parameters
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3   -lopencv_aruco -lpthread ")




##Add Libraries
find_package(Eigen3 REQUIRED)
find_package(OpenCV 3.1 REQUIRED)
find_package(PCL 1.8  REQUIRED)
add_definitions(${PCL_DEFINITIONS})
FIND_PACKAGE( OpenMP REQUIRED)
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
# 添加g2o的依赖
# 因为g2o不是常用库，要添加它的findg2o.cmake文件
LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

SET( G2O_ROOT /usr/local/include/g2o )
FIND_PACKAGE( G2O )
# CSparse
FIND_PACKAGE( CSparse )
INCLUDE_DIRECTORIES( ${G2O_INCLUDE_DIR} ${CSPARSE_INCLUDE_DIR} )

include_directories(
        ${EIGEN3_INCLUDE_DIR}
        ${OpenCV_INCLUDE_DIRS}
        ${PCL_INCLUDE_DIRS}
        ./include
        /usr/local/cuda/include
        /usr/include
        /usr/local/include
        ${CSPARSE_INCLUDE_DIR}
        #     ${PROJECT_SOURCE_DIR}/thirdparty/g2o
#        ${PROJECT_SOURCE_DIR}/thirdparty/g2o
#         /usr/include/suitesparse
        ${G2O_INCLUDE_DIR}
        ${CSPARSE_INCLUDE_DIR}
)


link_directories(
        /usr/local/lib
        /usr/lib
        ${PCL_LIBRARY_DIRS}
        #        ~/Code/g2o/libCMakeLists.txt:60
#        ${PROJECT_SOURCE_DIR}/thirdparty/g2o/lib
)
SET(G2O_LIBS g2o_cli g2o_ext_freeglut_minimal g2o_simulator
        g2o_solver_slam2d_linear g2o_types_icp g2o_types_slam2d
        g2o_core g2o_interface g2o_solver_csparse g2o_solver_structure_only
        g2o_types_sba g2o_types_slam3d g2o_csparse_extension g2o_opengl_helper
        g2o_solver_dense g2o_stuff g2o_types_sclam2d g2o_parser g2o_solver_pcg
        g2o_types_data g2o_types_sim3 cxsparse )



##EXECUTABLE(Target)



# test executable application.
add_executable(g2oTEST test/g2o_test.cpp )
target_link_libraries(g2oTEST ${G2O_LIBS} ${CSPARSE_LIBRARY})


add_executable(capTEST test/cap_test.cpp)
target_link_libraries(capTEST ${OpenCV_LIBS})

