option="$1"
file="$2"
if [ ! -f "$file" ]; then
echo "Error"
exit 1
fi
case "$option" in
"linec")
count=$(wc -l < "$file")
echo "Line count: $count"
;;
"wordc")
count=$(wc -w < "$file")
echo "word count: $count"
;;
"charc")
count=$(wc -m < "$file")
echo "ch: $count"
;;
*)
echo "Invalid option"
exit 1
;;
esac
