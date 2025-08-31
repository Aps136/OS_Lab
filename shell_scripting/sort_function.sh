sorts() {
if [ "$#" -eq 0 ]; then
echo "No strings to sort"
return
fi
printf "%s\n" "$@" | sort
}
if [ "$#" -eq 0 ]; then
echo "Usage: $0 string1 string2..."
exit 1
fi
sorts "$@"

