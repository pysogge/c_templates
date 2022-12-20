
FILE* file = popen( "grep mykeyword", "r" );
fwrite( str_to_grep, 1, strlen( str_to_grep ), file );
pclose( file );