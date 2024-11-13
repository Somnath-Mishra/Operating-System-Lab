:<<'EOF'
Name : Somnath Mishra Roll : 1058 sec : A1

output : 
[be2258@localhost ass-8]$ sh ass-8_8.sh
Enter first number:
56
Enter second number:
44
The sum is: 100
[be2258@localhost ass-8]$

EOF
#!/bin/bash
echo "Enter first number:"
read num1
echo "Enter second number:"
read num2
sum=$(echo "$num1 + $num2" | bc)
echo "The sum is: $sum"

