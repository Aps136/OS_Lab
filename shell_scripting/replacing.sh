if [ ! -d "$path" ]; then
echo "Directory not found"
exit 1
fi
for file in "$path"/*.txt; do
if [ -f "$file" ]; then
echo "processing file"
sed -i 's/ex:/example:/g' "$file"
echo "done with $file"
fi
done
