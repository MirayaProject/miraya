cmake_minimum_required(VERSION 3.16)

project(miraya VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(COMPANY "MirayaOSU")
set(IDENTIFIER "com.github.mirayaosu")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets WebSockets Network)
qt_standard_project_setup()

add_executable(miraya
	main.cpp
	gosumemoryClient.cpp gosumemoryClient.h
	gosumemorydatawrapper.h gosumemorydatawrapper.cpp
	twitchClient.cpp twitchClient.h
	twitchdatawrapper.h twitchdatawrapper.cpp
	twitchcommandhandler.h twitchcommandhandler.cpp
	osuircclient.h osuircclient.cpp
	mainwindow.h mainwindow.cpp mainwindow.ui
	utils.h utils.cpp
	setupwizard.h setupwizard.cpp setupwizard.ui
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	set_property(TARGET miraya PROPERTY WIN32_EXECUTABLE true)
endif()

target_link_libraries(miraya PRIVATE Qt6::Core)
target_link_libraries(miraya PRIVATE Qt6::Widgets)
target_link_libraries(miraya PRIVATE Qt6::WebSockets)
target_link_libraries(miraya PRIVATE Qt6::Network)
