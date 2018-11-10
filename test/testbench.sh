#!/bin/bash
# echo "testbench started" #comment this out later
simulator=$1
binary_files=test/mips_binary
assembly_files=test/mips_assembly
log_files=test/output

function extract_info {
    file=$1
    field_to_extract=$2
    IFS=$'\n'
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

csv_lines=()
mkdir -p $log_files
for binary_file in $binary_files/*
do
    sim_stdout=$($simulator $binary_file)
    exit_code=$?
    text_file=$assembly_files/$(basename -- "${binary_file%.*}").txt

    extract_info $text_file author
    author=$extracted_info_field

    extract_info $text_file expected_value
    expected_value=$extracted_info_field

    test_id=$(basename -- "${binary_file%.*}")
    instruction=${test_id//[[:digit:]]/}

    csv_line="$test_id, $instruction, pass/fail, $author, expected value: $expected_value actual value: TEMP_ACTUAL_VALUE expected exit code: TEMP_EXIT_CODE actual exit code: $exit_code"
    csv_lines+=($csv_line)
    > "$log_files/$test_id.csv" cat <<< $csv_line
done
printf '%s\n' "${csv_lines[@]}"
# printf '%d\n' "'$sim_stdout" #for printing decimal value of ascii

