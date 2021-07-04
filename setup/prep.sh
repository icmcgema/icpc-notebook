# This line MUST BE THE SAME as in test.sh !!
export CXXFLAGS="-std=c++17 -DLOCAL_PC -fsanitize=address,undefined -ggdb3 -Wall -Wextra -Wno-unused-result -Wshadow"

if [ -z "$BITS_PATH" ]; then
	echo "Skipping bits header compilation because env var BITS_PATH is not set"
else
	echo "Pre-compiling bits headers"
	cp $BITS_PATH ./
	(g++ stdc++.h $CXXFLAGS )
fi

if [ $# -eq 0 ]; then
	MAX_PROB=15
else
    MAX_PROB=$(printf '%d' "'$1")
    MAX_PROB=$(( $MAX_PROB - 64 ))
fi


(mkdir "tasks") 2> /dev/null
(mkdir "output") 2> /dev/null

echo "Creating "$MAX_PROB" problems."
for counter in $(seq 1 $MAX_PROB); do
	i=$(( $counter + 64 ));
	c=$(printf \\$(printf '%03o' $i));
	c="tasks/"$c
	(mkdir $c) 2> /dev/null
	if ! [ -z "$BITS_PATH" ]; then
		(mkdir $c"/bits") 2> /dev/null
		(cp "stdc++.h.gch" $c"/bits/")
		(cp "stdc++.h" $c"/bits/")
	fi
	(cp ~/icpc-templates/template.cpp $c"/sol.cpp")
	(cp ~/icpc-templates/test.sh $c"/test.sh")
	(chmod +x $c"/test.sh")
	echo "Created folder "$c
done

rm stdc++.h 2> /dev/null
rm stdc++.h.gch 2> /dev/null
