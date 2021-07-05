# If you want to use pre-compiled headers, this line must be the same as in prep.sh !!
export CXXFLAGS="-std=c++17 -DLOCAL_PC -fsanitize=address,undefined -ggdb3 -Wall -Wextra -Wno-unused-result -Wshadow"

C_RED="\e[1;31m";
C_GREEN="\e[1;32m";
C_BLUE="\e[1;34m";
C_BOLD="\e[1;39m";
C_RESET="\e[0m";

if [ $# -eq 0 ]; then
    EXEC_FILE="sol"
else
    EXEC_FILE="$1"
fi

if ! [ -e ${EXEC_FILE}.cpp ]; then
    echo "Please, give a valid source file as an argument."
    exit 1
fi

make "${EXEC_FILE}"
if ! [ $? -eq 0 ]; then
    echo "Compilation error."
    exit 1
fi

echo -e "Compiled...\n";

ACCEPTED=0
WRONG=0
UNKNOWN=0

for filename in *.in; do
    echo -en "Running testcase $(basename "$filename" .in): ";
    x=$( { \time -f "%es %MkB" ./sol < $(basename "$filename" .in).in > OUTPUT_RESULT; } 2>&1 );

    if [ -e $(basename "$filename" .in).out ]; then
        (diff -w $(basename "$filename" .in).out <(./"${EXEC_FILE}" < $(basename "$filename" .in).in)) > /dev/null;
        status=$?
    else
        status="-1"
    fi

    if [ "$status" -eq "0" ]; then
        echo -e "${C_GREEN}AC on ${x}${C_RESET}";
        echo " Your output: ";
        echo "$(cat OUTPUT_RESULT)";
        echo -e " ----------------";
        ACCEPTED=$(( $ACCEPTED + 1 ));
    elif [ "$status" -eq "-1" ]; then
        echo -e "${C_BLUE}? on ${x}${C_RESET}";
        echo " Your output: ";
        echo "$(cat OUTPUT_RESULT)";
        echo -e " ----------------";
        UNKNOWN=$(( $UNKNOWN + 1 ));
    else
        echo -e "${C_RED}WA on ${x}${C_RESET}";
        echo " Expected output:"
        echo "$(cat $(basename "$filename" .in).out)";
        echo -e " ----------------";
        echo " Your output: ";
        echo "$(cat OUTPUT_RESULT)";
        echo -e " ----------------";
        WRONG=$(( $WRONG + 1 ));
    fi

    echo ""

    if [ -e OUTPUT_RESULT ]; then
        rm OUTPUT_RESULT;
    fi
    done

echo -e "${C_BOLD}Test count: ${C_GREEN}${ACCEPTED} AC${C_BOLD} vs ${C_RED}${WRONG} WA${C_BOLD} vs${C_BLUE} ${UNKNOWN} untested${C_RESET}"
cp "${EXEC_FILE}".cpp "../../output/sol.cpp"