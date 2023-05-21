#!/bin/bash

#run command and save it in a file
output=$(ls)

#Count the number of words in the output using the 'wc' command
word_count=$(echo "$output" | wc -w)

#Count the number of chars in the output
char_count=$(echo "$output" | wc -m)

#Count the number of bytes in the output
byte_count=$(echo -n "$output" | wc -c)


#Print the word count and char count and byte count
echo "Word count: $word_count"
echo "Character count: $char_count"
echo "Byte count: $byte_count"
