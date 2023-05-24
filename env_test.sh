#!/bin/bash

#run command and save it in a file
output=$(env)

#Count the number of words in the output using the '/bin/ls' command
word_count=$(echo "$output" | wc -w)

#count the number of chars in the output
char_count=$(echo "$output" | wc -m)

#count the number of bytes in the output
byte_count=$(echo -n "$output" | ec -c)

#Print the counts 
echo "Word count: $word_count"
echo "character count: $char_count"
echo "Byte count: $byte_count"
