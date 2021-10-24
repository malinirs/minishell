cmake_minimum_required(VERSION 3.20)
project(Minishell C)

set(CMAKE_C_STANDARD 99)

link_directories(Libft)
add_executable(Minishell main.c utils_1.c pars_dollar.c pars_quotes.c)
target_link_libraries(Minishell libft.a readline)