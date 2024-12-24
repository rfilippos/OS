#/bin/bash

#default value (last four digits of my AEM)
DefaultInt=0379

# Check if input was given
if [ $# -gt 0 ]; then
	UniqueInt="$1"
else
	UniqueInt="$DefaultInt"
fi


#convert int to string to hash it later
UniqueString=`echo -n $UniqueInt`

#Generate hash and save it 
hash=`echo -n "$UniqueString" | sha256sum | awk '{print $1}'`
echo "$hash" > hash_output.txt
