#! Name : Somnath Mishra : 1058 sec : A1

#! output : [be2258@localhost ~]$ ls
: <<'EOF'
All My Cprogs Files  a.out  arm  assignment4  assignment5  assignment6  ComputerNetwork  dsaLab  GDB  OOP  OOPLab  OOS  os  resultOfStudents.cls  skel  SoftwareEngineeringLab
[be2258@localhost ~]$ cd All\ My\ Cprogs\ Files/
[be2258@localhost All My Cprogs Files]$ ls
allCombinationOf123Digit.c    countDuplicateAndPrintArrayReverseOrder.c  first_100_prime_number.c  patternQ3.c                  reverseOfIntArray.c  sort10Number.c          studentMarksResults.c
allCombinationOfDigit1-2-3.c  factorialsum.c                             is_prime.c                q9_implementCircularQueue.c  reverse_of_number.c  sortingIntArray.c       sum_of_digit.c
armnstrongNumber.c            fibonacciNumber.c                          max_of_three.c            quadraticSolve.c             seriesNSum.c         standardDeviation.c     sumOfnNumber.c
armstrongNumber.c             fibonacciSeries.c                          patternQ1.c               rangeOfArray.c               seriesq1.c           studentMarksResult.c
below9word.c                  first100HappyNumber.c                      patternQ2.c               resultOfStudents.c           sort_10_number.c     studentMarksResults1.c
[be2258@localhost All My Cprogs Files]$ 


EOF

#!/bin/bash
# Check if there are any .c files in the home directory
if ls "$HOME"/*.c 1> /dev/null 2>&1; then
  # Move the .c files from home directory if they exist
  mv "$HOME"/*.c "$HOME/All My Cprogs Files"
  echo "All .c files have been moved from '$HOME' to '$HOME/All My Cprogs Files'."
else
  echo "No .c files found in the home directory."
fi

