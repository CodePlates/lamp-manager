cmake_minimum_required(VERSION 2.8)
project(lampman)

include_directories(include)
set(CMAKE_INCLUDE_CURRENT_DIR YES)

set(CMAKE_CXX_STANDARD 11)

# Needed for installation of the required helpers at KDE directories
find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)

set(HELPER "src/helpers.cpp")

set(SOURCES 
		"main.cpp"  
		"src/utilities.cpp"  
		"src/server.cpp"  
		"src/lampman.cpp"  
		"src/page_cpanel.cpp"  
		"src/page_php.cpp"  
		"src/page_vhosts.cpp" 
		"src/apache2/apache_config.cpp"  
		"src/apache2/vhost.cpp" 
		"src/apache2/vhost_dialog.cpp" 
		"src/apache2/parser/conf_node_base.cpp" 
		"src/apache2/parser/conf_node.cpp" 
		"src/apache2/parser/conf_tree.cpp" 
		"src/apache2/parser/scanner.cpp"  
		"src/apache2/parser/parser.cpp"  
		"src/php/php_config.cpp" 
	)


# Find necessary Qt and Kf5Ath libraries.
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(KF5Auth)

 
add_executable(lampman ${SOURCES})
target_link_libraries(lampman Qt5::Widgets Qt5::Core Qt5::Gui KF5::Auth)
install(TARGETS lampman DESTINATION bin)

add_executable(lampman_helper ${HELPER})
target_include_directories(lampman_helper PUBLIC include)
target_link_Libraries(lampman_helper Qt5::Core KF5::Auth)
set_target_properties(lampman_helper PROPERTIES AUTOMOC TRUE)

# KAUTH_HELPER_INSTALL_DIR defined ion the KDEInstallDirs
install(TARGETS lampman_helper DESTINATION ${KAUTH_HELPER_INSTALL_DIR})

# CMake macros defined in KF5Auth
kauth_install_helper_files(lampman_helper com.codeplates.lampman root)
kauth_install_actions(com.codeplates.lampman com.codeplates.lampman.actions)

