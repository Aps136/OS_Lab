ispali(){
number=$1
reversed=0
orig=$number
while [ $number -gt 0 ]; do
lastdig=$(( number % 10 ))
reversed=$(( reversed * 10 + lastdig ))
number=$((number / 10 ))
done
if [ "$orig" -eq "$reversed" ]; then
echo "yes palindrome"
else
echo "No, not palindrome"
fi
}
ispali 200
