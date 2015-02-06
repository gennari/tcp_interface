cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})
#find_package(Eigen REQUIRED)
#include_directories(${Eigen_INCLUDE_DIRS})
rosbuild_add_library(gnetwork_lib 
  src/gnetwork/binaryclient.cpp 
  src/gnetwork/binarymessage.cpp 
  src/gnetwork/network.cpp 
  src/gnetwork/networkedmodule.cpp 
  src/gnetwork/binaryclient.h
  src/gnetwork/binarymessage.h 
  src/gnetwork/gformatters.h 
  src/gnetwork/networkedmodule.h 
  src/gnetwork/network.h
)

rosbuild_add_executable(tcp_interface src/CmdServer.cpp src/TcpServer.cpp src/TcpClient.cpp src/TcpClientList.cpp src/UDPManager.cpp src/tcpinterface.cpp)

rosbuild_add_compile_flags(tcp_interface -DLINUX)

target_link_libraries(tcp_interface gnetwork_lib)

rosbuild_add_executable(netsuppliertest src/gnetwork/netsuppliertest.cpp)
target_link_libraries(netsuppliertest gnetwork_lib)

rosbuild_add_executable(netclienttest src/gnetwork/netclienttest.cpp)
target_link_libraries(netclienttest gnetwork_lib)
