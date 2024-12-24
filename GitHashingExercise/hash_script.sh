#/bin/bash

UniqueInt=0379

#convert int to string to hash it later
UniqueString=`echo -n UniqueInt`

#Generate hash and save it 
hash=`echo -n "$UniqueString" | sha256sum | awk '{print $1}'`
echo "$hash" > hash_output.txt
