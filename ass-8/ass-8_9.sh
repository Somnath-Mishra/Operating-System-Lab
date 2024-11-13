:<<'EOF'
Name : Somnath Mishra sec : A1 Roll : 1058
output : 
The content inside the "upperToLower.txt" file is -
hello I am Somnath Mishra
~                                 

HELLO i AM sOMNATH mISHRA

EOF
#!/bin/bash
file=$1
tr '[:lower:][:upper:]' '[:upper:][:lower:]' < "$file"

