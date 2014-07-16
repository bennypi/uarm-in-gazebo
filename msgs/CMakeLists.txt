find_package(Protobuf REQUIRED)

set(PROTOBUF_IMPORT_DIRS)
foreach(ITR ${GAZEBO_INCLUDE_DIRS})
  if(ITR MATCHES ".*gazebo-[0-9.]+$")
    set(PROTOBUF_IMPORT_DIRS "${ITR}/gazebo/msgs/proto")
  endif()
endforeach()

set (msgs
  new_joint_position.proto
)

set (msgs
  new_position.proto
  new_joint_position.proto
)

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${msgs})

add_library(new_joint_position_msgs SHARED ${PROTO_SRCS})
target_link_libraries(new_joint_position_msgs ${PROTOBUF_LIBRARY})

add_library(new_position_msgs SHARED ${PROTO_SRCS})
target_link_libraries(new_position_msgs ${PROTOBUF_LIBRARY})
