 #!/bin/sh

fileName=$1
numberOfCopies=$2


if [ ! -r $fileName ]; then 
   echo "$fileName doesn't exist."
   exit 1
fi

while [ "$numberOfCopies" != 0 ]; do

  if [ -r $fileName.$numberOfCopies ]; then 
	echo $numberOfCopies
	cp $fileName.$numberOfCopies $fileName.$(( $numberOfCopies + 1 ))
  fi
  
  numberOfCopies=$(( $numberOfCopies - 1 ))
done

cp $fileName $fileName.1
  
 

 echo "END"
