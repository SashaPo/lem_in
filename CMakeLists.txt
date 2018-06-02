cmake_minimum_required(VERSION 3.9)

aux_source_directory(libft LIBFT_SRC)
aux_source_directory(. LEM_SRC)
aux_source_directory(libft/ft_printf PRINT_SRC)

add_library(ft STATIC ${LIBFT_SRC} ${PRINT_SRC})

add_executable(lem_in ${LEM_SRC})
target_link_libraries(lem_in PUBLIC ft)
target_include_directories(lem_in PUBLIC libft)
include_directories(libft)