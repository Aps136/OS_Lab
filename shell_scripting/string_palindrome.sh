if [ -z "$1" ]; then
echo "Error"
exit 1
fi
orig="$1"
rev=""
len=${#orig}
for (( i=$len-1; i>=0; i-- )); do
rev="$rev${orig:i:1}"
done
if [ "$orig" = "$rev" ]; then
echo "'$orig' is a palindrome"
else
echo "'$orig' is not a palidrome"
fi
