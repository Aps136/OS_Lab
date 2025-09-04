while true; do
echo "Menu: "
echo "1. list all files and counts in dir"
echo "2. Replace all .c file extensions with .gcc"
echo "3. exit"
echo "enter yo choice: "
read choice
case "$choice" in
1)
echo "enter dir"
read dirr
if [ ! -d "$dirr" ]; then
echo "error"
else
ls -1 "$dirr"
filec=$(ls -1 "$dirr" | wc -l)
echo "$filec"
fi
;;
2)
echo "enter directory path to modify"
read dirr
if [ ! -d "$dirr" ]; then
echo "directory not found"
else
find "$dirr" -type f -name "*.gcc" | while read -r file; do
mv "$file" "${file%.gcc}.c"
echo "renamed"
done
echo "Replacement complete"
fi
;;
3)
exit 0
;;
*)
echo "invalid"
;;
esac
done
