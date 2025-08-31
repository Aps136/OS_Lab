  GNU nano 7.2                                   s1.sh *                                          myfunc(){
param1=("${!1}")
param2=("${!2}")
for i in ${param1[@]}; do
for j in ${param2[@]}; do
if [ "${i}" == "${j}" ]; then
echo ${i}
echo ${j}
fi
done
done
}
a=(yoyo)
b=(yoyo)
myfunc a[@] b[@]


