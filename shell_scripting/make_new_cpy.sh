file=$1
if [ ! -f "$file" ]; then
echo "No such file"
fi
cp "$file" newfileyo.txt
echo "done"







