#!/bin/bash
:<<'EOF'
Name : Somnath Mishra  Roll : 1058 sec : A1
description : this command shows all the c files in the file "c_files_list.txt"
output : sh ass-8_7.sh
ass-8_1.sh  ass-8_3.sh  ass-8_5.sh  ass-8_7.sh        temp.c
ass-8_2.sh  ass-8_4.sh  ass-8_6.sh  c_files_list.txt

Inside The c_files_txt 
temp.c
~                                                                           ~         
EOF

# Check if there are any .c files in the current directory
if ls *.c 1> /dev/null 2>&1; then
  # List the .c files and save the output to c_files_list.txt
  ls *.c > c_files_list.txt
  echo "List of .c files has been saved to c_files_list.txt."
else
  echo "No .c files found in the current directory."
fi

 

