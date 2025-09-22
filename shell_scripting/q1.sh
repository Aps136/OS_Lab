 find . -type f -name "*.txt" -regex ".*[0-9].*" | grep -e '^([^aeiouAEIOU].{3,})\.txt'
