read num
if [ "$num" -lt 0 ]; then
echo "Factorial is not defined for neg numbers"
exit 1
fi
if [ "$num" -eq 0 ]; then
echo "1"
exit 0
fi
x=1
while [ "$num" -gt 0 ]; do
x=$(( x * num ))
num=$(( num-1 ))
done
echo "$x"
