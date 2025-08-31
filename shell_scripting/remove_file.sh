for file in "$@"; do
if [ -f "$file" ]; then
rm -i "$file"
fi
done
echo "done"










