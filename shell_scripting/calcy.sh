read num1
read num2
read operation
case "$operation" in
+)
echo "$num1" + "$num2" | bc -l
;;
-)
echo "$num1" - "$num2" | bc -l
;;
x)
echo "$num1 * $num2" | bc -l
;;
/)
echo "$num1" / "$num2" | bc -l
;;
*)
echo "Error"
;;
esac
