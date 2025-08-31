read filename
read start
read end
sed -n "${start},${end}p" "$filename"







