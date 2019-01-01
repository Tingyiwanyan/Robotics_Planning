cmake_minimum_required(VERSION 2.8.3)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
project(robot_planning)


## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  genmsg
  grid_map_core
  grid_map_ros
  grid_map_cv
  grid_map_filters
  grid_map_loader
  grid_map_msgs
  grid_map_octomap
  grid_map_rviz_plugin
  grid_map_visualization
)

#catkin_package()

find_package(OpenCV REQUIRED
  COMPONENTS
  opencv_highgui
  CONFIG
)
find_package(octomap REQUIRED)

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS
#  DEPENDS system_lib
)

set(SOURCES src/Hello.cpp src/main.cpp src/rtdp.cpp src/ssp.cpp)
set(SOURCES_VIS src/rtdp.cpp src/ssp.cpp src/Grid_map_vis.cpp)
set(LIBS_ARMA		"armadillo")  #lapack blas
set(LIBS_NETCDF_C++	"netcdf_c++4")
set(LIBS_YAML_CPP	"yaml-cpp")
set(LIBS_SOGP		"sogp")
set(LIBS_OPENGL		"GLU glut GL Xext pthread")
set(LIBS_OPENCV		"opencv_core opencv_highgui opencv_imgproc opencv_video") #-lopencv_imgcodecs
set(LIBS_BOOST_FILESYSTEM  "boost_filesystem")
set(LIBS_BOOST_SYSTEM      "boost_system")
set(LIBS_ALL
  #${LIBS_ARMA}
  #${LIBS_NETCDF_C++} ${LIBS_YAML_CPP} ${LIBS_GP}
  #${LIBS_OPENGL} ${LIBS_OPENCV}
)

set(EXTERNAL_LIBS_PATH
  "/usr/local/lib"
  "/usr/lib"
)

set(SOGP_INCL_PATH
  "/usr/local/include/sogp"
)

set(EIGEN_INCL_PATH
  "/usr/local/include/eigen3"
  "/usr/include/eigen3"
)

set(GRID_MAP_PATH
  "/home/tingyi/Research_Frame_work_ros/src/grid_map/grid_map_core/include/grid_map_core"
)


catkin_package(
  INCLUDE_DIRS include
  LIBRARIES dyna_rtdp
  CATKIN_DEPENDS roscpp rospy std_msgs
  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
  ${OCTOMAP_INCLUDE_DIR}
)


add_executable(rtdp ${SOURCES})
target_link_libraries(rtdp
   ${catkin_LIBRARIES}
   ${OCTOMAP_LIBRARIES}
   ${OpenCV_LIBRARIES}
 )

 add_executable(grid_map_vis ${SOURCES_VIS})
 target_link_libraries(grid_map_vis
    ${catkin_LIBRARIES}
    ${OCTOMAP_LIBRARIES}
    ${OpenCV_LIBRARIES}
  )



target_include_directories(rtdp PRIVATE ${GRID_MAP_PATH} ${PROJECT_SOURCE_DIR}/include
${EXTERNAL_LIBS_PATH} ${EIGEN_INCL_PATH} ${SOGP_INCL_PATH} ${LIBS_BOOST_SYSTEM} ${LIBS_BOOST_FILESYSTEM})

target_include_directories(grid_map_vis PRIVATE ${GRID_MAP_PATH} ${PROJECT_SOURCE_DIR}/include
${EXTERNAL_LIBS_PATH} ${EIGEN_INCL_PATH} ${SOGP_INCL_PATH} ${LIBS_BOOST_SYSTEM} ${LIBS_BOOST_FILESYSTEM})
