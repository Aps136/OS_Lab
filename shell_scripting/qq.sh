  GNU nano 7.2                                                                                           s2.sh                                                                                                     while true; do
echo "-----MENU------"
echo "1. Count number of files with .sh extension"
echo "2. Count number of files with min 3 characthers"
echo "3. Count number of files starting without vowel"
echo "4. Exit"
echo "Enter your choice"
read choice
if [ "$choice" -eq 4 ]; then
exit 0;
fi
case "$choice" in
1)
count=$(find . -type f -name "*.sh" | wc -l)
echo "The number of files w that extension: $count"
;;
2)
count=$(find . -maxdepth 1 -type f | grep -E '[^/]{3,}' | wc -l)
echo "The number of files w min 3 chs: $count"
;;
3)
count=$(find . -maxdepth 1 -type f | grep -v -i '^[aeiou]' | wc -l)
echo "The number of fliles starting without vowel: $count"
;;
*)
echo "Error"
;;
esac
done
