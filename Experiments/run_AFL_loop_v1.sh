# Single custom mutator as in SSBSE 2023. 

# USE FULL PATHS
cm_path=$1   # E.G. "/home/ubuntu/ASEGem5/src/custom_mutators/"
afl=$2       # E.G. /home/ubuntu/AFLplusplus/afl-fuzz
input=$3     # E.G. /home/ubuntu/TinyLlama-test/input
output=$4    # E.G. /home/ubuntu/TinyLlama-test/output
resume=$5    # 0 - new run, 1 - resume

# Check if an argument is provided
if [ $# -le 4 ]; then
    echo "Please provide custom mutator path, afl path, input and output folders, and a value (0 or 1) as a command-line argument."
    exit 1
fi

if [ "$resume" -eq 1 ]; then
    # Resume a new fuzzig
    AFL_NO_AFFINITY=1 AFL_SHUFFLE_QUEUE=1 AFL_CUSTOM_MUTATOR_ONLY=1 AFL_DUMB_FORKSRV=1 AFL_FAST_CAL=1 AFL_IGNORE_PROBLEMS=1 AFL_AUTORESUME=1 AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1 \
AFL_MAP_SIZE=1200000 AFL_CUSTOM_MUTATOR_LIBRARY="$cm_path/cm-gem5.so" \
$afl -m 50000 -t 99000 -i $input -o $output -- /home/ubuntu/gem5-ssbse-challenge-2023/build/X86/gem5.opt \
/home/ubuntu/ASEGem5/hello-custom-binary-Ex.py --isa X86 --input @@
else
    # Starts a new fuzzing
    AFL_NO_AFFINITY=1 AFL_SHUFFLE_QUEUE=1 AFL_CUSTOM_MUTATOR_ONLY=1 AFL_DUMB_FORKSRV=1 AFL_FAST_CAL=1 AFL_IGNORE_PROBLEMS=1 AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1 \
AFL_MAP_SIZE=1200000 AFL_CUSTOM_MUTATOR_LIBRARY="$cm_path/cm-gem5.so" \
$afl -m 50000 -t 99000 -i $input -o $output -- /home/ubuntu/gem5-ssbse-challenge-2023/build/X86/gem5.opt \
/home/ubuntu/ASEGem5/hello-custom-binary-Ex.py --isa X86 --input @@
fi
echo "==End Fuzzing round, script 1=="
date
echo "cm_path=$1; afl=$2; input=$3; output=$4; resume=$5;"
