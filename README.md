# 42_get_next_line
get_next_line is a function that reads and returns one line at a time from a file or input stream. It maintains a saved buffer between calls, allowing you to read lines sequentially. This function is commonly used in C programming for line-by-line text processing.

# A. Mandatory Part

# Algorithm


# USAGE

git clone 

to combile

cc -Wall -Werror -Wextra get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=<size>

# B. Bonus Part
The core concept of the bonus part is exactly the same as the mandatory except it should able to read from multiple files. Hence, opened fd should store in the saved[] as indexes so that the read chars will store on it. 
