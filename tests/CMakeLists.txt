# Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
#
# Author:     zhangteng <zhangteng@uniontech.com>
#
# Maintainer: zhangteng <zhangteng@uniontech.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.7)

if (NOT DEFINED VERSION)
    set(VERSION 1.2.2)
endif ()

set(APP_QRC "../assets/images.qrc")

ADD_COMPILE_OPTIONS(-fno-access-control)

# 设置添加gocv相关信息的输出
set(CMAKE_CXX_FLAGS "-g -fprofile-arcs -ftest-coverage")

find_package(Qt5Test REQUIRED)
find_package(GTest REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5Xml REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(src)

set(PROJECT_NAME_TEST
    ${PROJECT_NAME}_test)

# 定义 source 文件
#FILE (GLOB allTestSource
#    "./src/*.cpp"  "./src/*.c"
#    "./src/*.h"
#    )

#Include all app own subdirectorys

file(GLOB_RECURSE VNOTE_SRC_TEST ${CMAKE_CURRENT_LIST_DIR}/../src/*.cpp)
file(GLOB_RECURSE VNOTE_SRC_TEST1 ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

list(REMOVE_ITEM VNOTE_SRC_TEST "${CMAKE_CURRENT_LIST_DIR}/../src/main.cpp")
list(REMOVE_ITEM VNOTE_SRC_TEST "${CMAKE_CURRENT_LIST_DIR}/../src/common/vnoteaudiodevicewatcher.cpp")
list(REMOVE_ITEM VNOTE_SRC_TEST "${CMAKE_CURRENT_LIST_DIR}/../src/common/vnoteaudiomanager.cpp")


# 生成测试可执行程序
add_executable(${PROJECT_NAME_TEST}
    ${VNOTE_SRC_TEST}
    ${VNOTE_SRC_TEST1}

    ${APP_QRC}
    )

# 生成测试可执行程序的依赖库
target_link_libraries(${PROJECT_NAME_TEST} gtest gtest_main -pthread)

target_include_directories(${PROJECT_NAME_TEST} PUBLIC ${DtkWidget_INCLUDE_DIRS}
                                                       ${DtkCore_INCLUDE_DIRS}
                                                        ${DtkGui_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME_TEST}
    ${DtkWidget_LIBRARIES}
    ${DtkCore_LIBRARIES}
    ${DFrameworkdbus_LIBRARIES}
    ${GSTREAMER_LIBRARIES}
    ${LIBVLC_LIBRARIES}
    ${GTEST_LIBRARYS}
    ${GTEST_MAIN_LIBRARYS}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::DBus
    Qt5::Sql
    Qt5::Multimedia
    Qt5::Test
    ${Qt5Svg_LIBRARIES}
    ${Qt5Xml_LIBRARIES}
)

##------------------------------ 创建'make test'指令---------------------------------------
add_custom_target(test
    COMMAND echo " =================== TEST BEGIN ==================== "
    COMMAND ${CMAKE_BINARY_DIR}/tests/${PROJECT_NAME_TEST}
    COMMAND echo " =================== TEST END ==================== "
)

##'make test'命令依赖与我们的测试程序
add_dependencies(test ${PROJECT_NAME_TEST})
