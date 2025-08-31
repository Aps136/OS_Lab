echo "No filename provided"
exit 1
fi
input="$1"
evenf="evenfile.txt"
oddf="oddfile.txt"
if [ ! -f "$input" ]; then
echo "Error"
exit 1
fi
sed -n '2~2p' "$input" > "$evenf"
sed -n '1~2p' "$input" > "$oddf"
echo "Processing complete"
echo "Done"


