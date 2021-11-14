cmake_minimum_required(VERSION 3.20)
project(tro_lo_lo_lo C)

set(CMAKE_C_STANDARD 99)

link_directories(Libft source/commands source/parsing)
add_executable(tro_lo_lo_lo main.c minishell.h main.c utils_1.c pars_dollar.c pars_quotes.c
        utils_list_1.c creation_list.c write_array.c pre_parsing.c delete_space.c check_space_divider.c
        divider.c write_error.c check_symbol.c parsing.c init_env.c cmd_cd.c cd_utils.c
        cmd_echo.c cmd_exit.c cmd_export.c export_sort.c cmd_pwd.c cmd_unset.c cmd_utils.c signal.c
        main_job.c get_next_line.c)
target_link_libraries(tro_lo_lo_lo libft.a readline)