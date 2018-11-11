#!/bin/bash
# echo "testbench started" #comment this out later

simulator=$1
sh test/convert_mips.sh #this is part of the testbench
binary_files=test/mips_binary
assembly_files=test/mips_assembly
log_files=test/output

function extract_info {
    file=$1
    field_to_extract=$2
    IFS=$'\n'
    extracted_info_field="" #nullify variable
    #echo "filename: " $file
    while IFS= read -r line
    do
        if [[ ${line:0:1} == '#' ]];
        then
            without_hashtag=${line#*#}
            field_from_line=${without_hashtag%:*}
            if [ "$field_from_line" == "$field_to_extract" ];
            then
                #echo extracting $field_from_line
                extracted_info_field=${line#*": "}
            fi
        fi
    done < "$file"
}

function convert_8_bit_dec_to_2s_complement {
    NUMBER="$1"
    converted_result=""
    N_POW=$((2 ** 8))
    NM1_POW=$((2 ** 7))
    if [ $NUMBER -lt $NM1_POW ];
    then
        converted_result=$NUMBER
    else
        converted_result=$(($NUMBER - $N_POW))
    fi
}

csv_lines=()
mkdir -p $log_files

if [[ $# -ne 1 ]];
then
    echo "invalid number of command line arguments"
    exit -20
fi

for binary_file in $binary_files/*
do
    sim_stdout=$($simulator $binary_file)
    exit_code=$?
    convert_8_bit_dec_to_2s_complement $exit_code
    exit_code=$converted_result
    sim_stdout=$(printf '%d' "'$sim_stdout")
    text_file=$assembly_files/$(basename -- "${binary_file%.*}").txt
    
    #extract info
    extract_info $text_file author
    author=$extracted_info_field
    if [[ -z $author ]];
    then
        author=$USER #default value 
    fi
    
    
    extract_info $text_file expected_output
    expected_output=$extracted_info_field
    
    extract_info $text_file expected_exit_code
    expected_exit_code=$extracted_info_field
    
    test_id=$(basename -- "${binary_file%.*}")
    instruction=${test_id//[[:digit:]]/}
    
    debug_message=""
    pass_fail_string="Pass"
    if [ -n "${expected_exit_code}" ];
    then
        debug_message="$debug_message expected exit code: $expected_exit_code actual exit code: $exit_code"
        if [[ $expected_exit_code != $exit_code ]]; then
            pass_fail_string="Fail"
        fi
    fi
    
    if [ -n "${expected_output}" ];
    then
        debug_message="$debug_message expected output: $expected_output actual output: $sim_stdout"
        if [[ $expected_output != $sim_stdout ]]; then
            pass_fail_string="Fail"
        fi
    fi
    
    
    csv_line="$test_id, $instruction, $pass_fail_string, $author, $debug_message"
    csv_lines+=($csv_line)
    echo $csv_line > "$log_files/$test_id.csv"
done
printf '%s\n' "${csv_lines[@]}"
# printf '%d\n' "'$sim_stdout" #for printing decimal value of ascii