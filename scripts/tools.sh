# Tool Scripts

# Script fo remove "orchestration_" prefix from all files in directory
# Usage: remove_prefix <directory>
remove_prefix() {
    for file in $1/*; do
        mv $file ${file/orchestration_/}
    done
}

# Script for remove "_1" suffix from all files in directory, maintaining the .c and .h file extensions
# Usage: remove_suffix <directory>
remove_suffix() {
    for file in $1/*; do
        mv $file ${file/_1/}
    done
}