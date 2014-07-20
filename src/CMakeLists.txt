cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(Boost REQUIRED COMPONENTS system)
find_package(Protobuf REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_subdirectory(msgs)

include (FindPkgConfig)
if (PKG_CONFIG_FOUND)
  pkg_check_modules(GAZEBO gazebo)
endif()
include_directories(../include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/msgs)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})

add_library(UarmController SHARED UarmController.cc)
target_link_libraries(UarmController new_joint_position_msgs new_position_msgs ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES} ${PROTOBUF_LIBRARIES})
add_dependencies(UarmController new_joint_position_msgs new_position_msgs)

add_library(suction_cup SHARED SuctionCup.cc)
target_link_libraries(suction_cup ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES} ${PROTOBUF_LIBRARIES})

add_library(UarmPublisher UarmPublisher.cc)
target_link_libraries(UarmPublisher new_joint_position_msgs new_position_msgs ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES} ${PROTOBUF_LIBRARIES} )
add_dependencies(UarmPublisher new_joint_position_msgs new_position_msgs)

add_executable(UarmPub UarmPub.cc)
target_link_libraries(UarmPub UarmPublisher)
add_dependencies(UarmPub new_joint_position_msgs new_position_msgs)

add_library(uarm_suction_cup_contact SHARED ContactPlugin.cc)
target_link_libraries(uarm_suction_cup_contact suction_cup_contact_msgs ${GAZEBO_libraries} ${Boost_LIBRARIES} ${PROTOBUF_LIBRARIES} )
add_dependencies(uarm_suction_cup_contact suction_cup_contact_msgs)
