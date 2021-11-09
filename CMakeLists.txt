cmake_minimum_required(VERSION 3.20)
project(Minishell C)

set(CMAKE_C_STANDARD 99)

link_directories(Libft)
add_executable(Minishell main.c utils_1.c pars_dollar.c pars_quotes.c utils_list_1.c
        creation_list.c write_array.c pre_parsing.c delete_space.c check_space_divider.c divider.c write_error.c
        check_symbol.c parsing.c)
target_link_libraries(Minishell libft.a readline)