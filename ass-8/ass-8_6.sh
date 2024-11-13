:<<'EOF'
Name : Somnath Mishra  Roll : 1058 sec : A1
description : this command is used to count the numbers of files in home directory
output : 
[be2258@localhost ass-8]$ vi ass-8_6.sh
[be2258@localhost ass-8]$ sh ass-8_6.sh
444
EOF

#!/bin/bash
find "$HOME" -type f | wc -l

