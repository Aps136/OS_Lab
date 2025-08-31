while true; do
echo "......MENU......"
echo "1. Search patterns in given input file"
echo "2. Delete all occurances of pattern in given input file"
echo "3. Exit from shell script"
echo "Enter filename: "
echo "Enter choice: "
read choice
if [ "$choice" -eq 3 ]; then
echo "Exiting..."
exit 0
fi
echo "Enter file: "
read file
if [ ! -f "$file" ]; then
echo "Error, no such file"
continue
fi
case "$choice" in
1)
echo "Enter pattern: "
read pattern
grep "$pattern" "$file"
;;
2)
echo "Enter pattern to delete: "
read pattern
sed -i "s/$pattern//g" "$file"
;;
*)
echo "Enter a valid choice pls"
;;
esac
echo " "
done
