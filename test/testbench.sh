#!/bin/bash
# echo "testbench started" #comment this out later

simulator=$1

#convert mips
rm -rf test/mips_binary #refresh the binaries and remove the old ones
mkdir -p test/mips_binary
for assembly_file in test/mips_assembly/*
do
    test/mips-parser/bin/parser $assembly_file test/mips_binary/# >/dev/null
done

binary_files=test/mips_binary
assembly_files=test/mips_assembly
log_files=test/output
temp_files=test/temp
test_input_file=test/wibble.txt

function extract_info {
    file=$1
    field_to_extract=$2
    IFS=$'\n'
    extracted_info_field="" #nullify variable
    #echo "filename: " $file
    while IFS= read -r line
    do
        if [[ $line == '#'* ]];
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

function convert_ascii_string_to_decimal {
    ascii=$1
    converted_result=""
    
    while IFS='' read -r -d '' -n 1 char; do
        decimal=$(printf '%d' "'$char")
        converted_result="$converted_result $decimal"
    done < <(printf %s "$ascii")
    converted_result=$(echo $converted_result | xargs) #strip leading and trailing whitespace
    
    
}

csv_lines=()
mkdir -p $log_files
mkdir -p $temp_files

if [[ $# -ne 1 ]];
then
    echo "invalid number of command line arguments"
    exit -20
fi

for binary_file in $binary_files/*
do
    temp_stderr_file="$temp_files/tmp_err.txt"
    temp_stdout_file="$temp_files/tmp_out.txt"
    sim_stdout=$(cat $test_input_file | $simulator $binary_file 2>$temp_stderr_file 1>$temp_stdout_file)
    exit_code=$?
    convert_8_bit_dec_to_2s_complement $exit_code
    exit_code=$converted_result
    sim_stderr=$(< $temp_stderr_file) #this line needs to be places below exit code for exit code to be correct for some reason
    sim_stdout=$(< $temp_stdout_file)
    # echo $sim_stdout
    convert_ascii_string_to_decimal $sim_stdout
    sim_stdout=$converted_result
    assembly_file=$assembly_files/$(basename -- "${binary_file%.*}").s
    
    #extract info
    extract_info $assembly_file author
    author=$extracted_info_field
    if [[ -z $author ]];
    then
        author=$USER #default value
    fi
    
    
    extract_info $assembly_file expected_output
    expected_output=$extracted_info_field
    
    extract_info $assembly_file expected_exit_code
    expected_exit_code=$extracted_info_field
    
    extract_info $assembly_file extra_info
    extra_info=$extracted_info_field
    
    test_id=$(basename -- "${binary_file%.*}")
    instruction=${test_id//[[:digit:]]/}
    
    debug_message=""
    pass_fail_string="Pass"
    if [ -n "${expected_exit_code}" ];
    then
        debug_message="$debug_message | expected exit code: $expected_exit_code actual exit code: $exit_code"
        if [[ $expected_exit_code != $exit_code ]]; then
            pass_fail_string="Fail"
        fi
    fi
    
    if [ -n "${expected_output}" ];
    then
        debug_message="$debug_message | expected output: $expected_output actual output: $sim_stdout"
        if [[ $expected_output != $sim_stdout ]]; then
            pass_fail_string="Fail"
        fi
    fi
    
    if [ -n "${extra_info}" ];
    then
        debug_message="$debug_message | extra info: $extra_info"
    fi
    
    #multiple input chars give multiple output that needs to all be checked sequentially
    #need to while true and break if extract info doesn't retur nanything for that number
    
    # while IFS= read -r -n1 char
    # do
    #     # display one character at a time
    #     echo  "$char"
    #     # extract_info $assembly_file expected_output // DO THIS NEXT
    #     # expected_output=$extracted_info_field
    # done < "$temp_stdout_file"
    
    csv_line="$test_id, $instruction, $pass_fail_string, $author,${debug_message//,} |"
    csv_lines+=($csv_line)
    
    # echo $csv_line > "$log_files/$test_id.txt"
    this_test_log_file="$log_files/$test_id.txt"
    cp -f $temp_stderr_file $this_test_log_file
    echo $csv_line >> $this_test_log_file
done
printf '%s\n' "${csv_lines[@]}"
# rm -rf $temp_files
# printf '%d\n' "'$sim_stdout" #for printing decimal value of ascii