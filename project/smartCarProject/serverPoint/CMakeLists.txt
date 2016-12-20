cmake_minimum_required(VERSION 2.8)

SET(COMPILE_DEFINITIONS -Werror)

include_directories(/home/pi/git_server/project/smartCarProject/serverPoint/uart)

link_directories(/home/pi/git_server/project/smartCarProject/serverPoint/uart)

add_executable(smartCarService smartCarService.c)

target_link_libraries(smartCarService BCM2835Uart)

