# CSCI411_Project
For my CSCI 411 Project I did the Huffman Algorithm.

# In order to run the testcases, do the following : 

 1. Get runTests
   a. Create a file in your terminal thats called "runTests" and has the below bash information

#!/bin/bash

#./runTests <executable> <directory with test files>

passed=0
failed=0
for f in "$2"/*.in
do
  basefile=$(basename -- "$f")
  #extension="${basefile##*.}"
  testfile="${basefile%.*}.test"
  outfile="$2${basefile%.*}.out"
  difffile="$2${basefile%.*}.diff"
  echo -n "Running test $f..."
  ./"$1" < "$f" > $testfile
  if cmp -s "$testfile" "$outfile"
  then
    echo "passed"
    passed=$((passed+1))
    rm -f "$difffile"
  else
    echo "failed, see $difffile"
    diff "$testfile" "$outfile" > "$difffile"
    failed=$((failed+1))
  fi
  rm $testfile
done

echo $passed" PASSED out of "$(($failed+$passed))" ("$failed" failed)"


 2. Download tests cases called "messages"

 3. Run code
   a. Put the following line in your terminal "g++ Huffman.cpp"

 4. Run test cases
   a. Put the following line in your terminal " ./runTests a.out messages" 
