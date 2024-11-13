:<<'EOF'
Name : Somnath Mishra  Roll : 1058 sec : A1
output : 
[be2258@localhost ass-8]$ sh ass-8_10.sh
Enter the number of rows:
7
1
1 2
1 2 3
1 2 3 4
1 2 3 4 5
1 2 3 4 5 6
1 2 3 4 5 6 7
[be2258@localhost ass-8]$
EOF

#!/bin/bash
echo "Enter the number of rows:"
read n
for (( i=1; i<=n; i++ ))
do
  for (( j=1; j<=i; j++ ))
  do
    echo -n "$j "
  done
  echo
done

