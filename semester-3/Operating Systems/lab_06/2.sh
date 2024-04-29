read numbers
result=0

for number in $numbers
do
    result=$((result + number))
done

echo "$result"
