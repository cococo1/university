#!/bin/bash
for file in "$@"
 do
#extracting the file name without extension
        outFile="${file%.*}"
        if [[ $file == *.c ]]
        then
        {
#       echo "c"
                sudo gcc $file -o $outFile  &&
                 echo "$file compiled successfully. Running:" &&
                ./$outFile
        }
        elif [[ $file == *.cpp ]]
        then
        {
#       echo "cpp"
                sudo g++ -o $outFile $file &&
                echo  "$file compiled successfully. Running:" &&
                ./$outFile
        }
        elif [[ $file == *.java ]]
        then
{
#       echo "java"
                sudo javac $file &&
                echo "$file compiled successfully. Running:" &&
                cd java
                java HelloWorld
                cd ..
        }
        elif [[ $file == *.rb ]]
        then
        {
                echo "Running $file" && ruby $file
        }
        elif [[ $file == *.py ]]
        then
        {
                 echo "Running $file" && python $file
        }
        else
        {
                echo "Unsupported format."
        }
        fi
done;
