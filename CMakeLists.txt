cmake_minimum_required(VERSION 3.10)

project(mastermind)

file(GLOB SRC
	"general/*"
	"mastermind/*"
)
add_executable(a.out main.c ${SRC})

target_link_libraries(a.out PRIVATE m SDL3)
