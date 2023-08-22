inputF=$1 # crash or hand folder
outputF=$2 # Experiment results folder

# Check if the input directory exists
if [ ! -d "$inputF" ]; then
    echo "Input directory '$inputF' does not exist."
    exit 1
fi

gem5="/home/ubuntu/gem5-ssbse-challenge-2023/build/X86/gem5.opt"
gem5_script="/home/ubuntu/gem5-ssbse-challenge-2023/ssbse-challenge-examples/hello-custom-binary-Ex.py"
index=0

# Iterate over all .txt files in the input directory
for txt_file in "$input_dir"/*; do
    if [ -f "$txt_file" ]; then
        # Process each .txt file here
        echo "Processing file: $txt_file"
        # You can add your custom logic here to process the file
        (ulimit -St 500 $gem5 $gem5_script --isa X86 --input $txt_file) > gem5.log 2>&1
        if [ $? -ne 0 ]; then
 	   mkdir $outputF"/BUG-"$index
           mv gem5.log $outputF"/BUG-"$index
           cp $txt_file $outputF"/BUG-"$index
           binFile=`head -n 1 $txt_file"
           cp $binFile $outputF"/BUG-"$index
           ((index++))
        fi
    fi
done
