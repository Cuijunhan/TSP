
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")


add_executable(GaTSP ${SOURCES})

# 添加可执行文件
# add_executable(GaTSP main.cpp )
# add_executable(csdn-GaTSP CSDN-GA.cpp)


# 如果需要使用其他库，可以在这里添加相关的链接和包含路径
# 例如，如果使用了Matplotlib for C++，可以添加如下的链接
# target_link_libraries(GaTSP matplotlibcpp)
# set(CMAKE_PREFIX_PATH /usr/lib/x86_64-linux-gnu)
# link_directories("/usr/lib/x86_64-linux-gnu/libsfml-graphics.so;/usr/lib/x86_64-linux-gnu/libsfml-window.so;/usr/lib/x86_64-linux-gnu/libsfml-system.so")
find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)


# add_executable(TSPVisualization ./src/GA.cpp)
# add_executable(draw_tsp ./src/draw.cpp)
# target_link_libraries(draw_tsp sfml-graphics sfml-window sfml-system)

# add_executable(GaTSP ./src/draw.cpp)
target_link_libraries(GaTSP sfml-graphics sfml-window sfml-system)



