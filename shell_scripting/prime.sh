echo "enter a number"
read number
if ! [[ "$number" =~ ^[0-9]+$ ]]; then
echo "False"
exit 1
fi
if [ "$number" -le 1 ]; then
echo "False"
exit 0
fi
for (( i=2; i*i <= number; i++ )); do
if (( number % i ==0 )); then
echo "false"
exit 0
fi
done
echo "True"

