# Install script for directory: /home/tingyi/Research_Frame_work_ros/src/grid_map/dyna_rtdp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/tingyi/Research_Frame_work_ros/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/tingyi/Research_Frame_work_ros/build/grid_map/dyna_rtdp/catkin_generated/installspace/dyna_rtdp.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/dyna_rtdp/cmake" TYPE FILE FILES
    "/home/tingyi/Research_Frame_work_ros/build/grid_map/dyna_rtdp/catkin_generated/installspace/dyna_rtdpConfig.cmake"
    "/home/tingyi/Research_Frame_work_ros/build/grid_map/dyna_rtdp/catkin_generated/installspace/dyna_rtdpConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/dyna_rtdp" TYPE FILE FILES "/home/tingyi/Research_Frame_work_ros/src/grid_map/dyna_rtdp/package.xml")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/tingyi/Research_Frame_work_ros/build/grid_map/dyna_rtdp/catkin_generated/installspace/dyna_rtdp.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/dyna_rtdp/cmake" TYPE FILE FILES
    "/home/tingyi/Research_Frame_work_ros/build/grid_map/dyna_rtdp/catkin_generated/installspace/dyna_rtdpConfig.cmake"
    "/home/tingyi/Research_Frame_work_ros/build/grid_map/dyna_rtdp/catkin_generated/installspace/dyna_rtdpConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/dyna_rtdp" TYPE FILE FILES "/home/tingyi/Research_Frame_work_ros/src/grid_map/dyna_rtdp/package.xml")
endif()

