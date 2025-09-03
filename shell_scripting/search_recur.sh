if [ -z "$1" ]; then
echo "Error"
exit 1
fi
search="$1"
grep -r -i -n "$search"

