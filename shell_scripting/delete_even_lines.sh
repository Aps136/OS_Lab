if [ -f "$filename" ]; then
sed -i '2~2d' "$filename"
else
echo "Error: file not found"
fi

