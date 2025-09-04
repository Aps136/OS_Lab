read choice
if [ "$choice" -eq 4 ]; then
exit
fi
case "$choice" in
1)
echo "enter strings"
read string
sorteds=$(echo "$string" | tr ' ' '\n' | sort)
echo "$sorteds"
;;
2)
echo "enter filename"
read file
sed 's/ex:/example:/g' "$file"
;;
3)
read word
read file
count=$(grep -o -w "$word" "$file" | wc -l)
echo "$count"
;;
*)
echo "enter valid one"
;;
esac
