EXEC=minishell;
ARGS=;
valgrind --leak-check=full --leak-resolution=high --show-reachable=yes --suppressions=supress_readline_error --log-file=valgrind_log.txt --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$EXEC $ARGS;grep -A1 "valgrind" valgrind_log.txt|grep $EXEC
