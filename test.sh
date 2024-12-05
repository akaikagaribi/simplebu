#!/usr/bin/env bash

pass=0
fail=0

filesarr=("test1.txt" "test2.txt" "bytes.txt" "test1.txt test1.txt" "test2.txt test2.txt" "bytes.txt bytes.txt" "test1.txt test2.txt" "test1.txt bytes.txt" "test2.txt test1.txt" "test2.txt bytes.txt" "bytes.txt test1.txt" "bytes.txt test2.txt" "test1.txt test2.txt bytes.txt" "bytes.txt test1.txt test2.txt" "test2.txt bytes.txt test1.txt")

ones=("u" "b" "E" "n" "s" "T" "v")

# 1 ARG
for ((a=0;a<7;a++)); do
    echo "${ones[a]}"
    args="${ones[a]}"
    for files in "${filesarr[@]}"
    do
        # echo "$files"
        mine="$(./s21_cat $files -$args)"
        they="$(cat $files -$args)"
        if diff <(echo "$mine") <(echo "$they") &> /dev/null
        then
            # echo "PASS"
            pass=$(($pass+1))
        else
            echo "FAIL $files -$args"
            fail=$(($fail+1))
        fi
    done
done
# 2 ARGS
for ((a=1;a<7;a++)); do
    for ((b=$a+1;b<7;b++)); do
        echo "${ones[a]}${ones[b]}"
        args="${ones[a]}${ones[b]}"
        for files in "${filesarr[@]}"
        do
            # echo "$files"
            mine="$(./s21_cat $files -$args)"
            they="$(cat $files -$args)"
            if diff <(echo "$mine") <(echo "$they") &> /dev/null
            then
                # echo "PASS"
                pass=$(($pass+1))
            else
                echo "FAIL $files -$args"
                fail=$(($fail+1))
            fi
        done
    done
done
# 3 ARGS
for ((a=1;a<7;a++)); do
    for ((b=$a+1;b<7;b++)); do
        for ((c=$b+1;c<7;c++)); do
            echo "${ones[a]}${ones[b]}${ones[c]}"
            args="${ones[a]}${ones[b]}${ones[c]}"
            for files in "${filesarr[@]}"
            do
                # echo "$files"
                mine="$(./s21_cat $files -$args)"
                they="$(cat $files -$args)"
                if diff <(echo "$mine") <(echo "$they") &> /dev/null
                then
                    # echo "PASS"
                    pass=$(($pass+1))
                else
                    echo "FAIL $files -$args"
                    fail=$(($fail+1))
                fi
            done
        done
    done
done
# 4 ARGS
for ((a=1;a<7;a++)); do
    for ((b=$a+1;b<7;b++)); do
        for ((c=$b+1;c<7;c++)); do
            for ((d=$c+1;d<7;d++)); do
                echo "${ones[a]}${ones[b]}${ones[c]}${ones[d]}"
                args="${ones[a]}${ones[b]}${ones[c]}${ones[d]}"
                for files in "${filesarr[@]}"
                do
                    # echo "$files"
                    mine="$(./s21_cat $files -$args)"
                    they="$(cat $files -$args)"
                    if diff <(echo "$mine") <(echo "$they") &> /dev/null
                    then
                        # echo "PASS"
                        pass=$(($pass+1))
                    else
                        echo "FAIL $files -$args"
                        fail=$(($fail+1))
                    fi
                done
            done
        done
    done
done
# 5 ARGS
for ((a=1;a<7;a++)); do
    for ((b=$a+1;b<7;b++)); do
        for ((c=$b+1;c<7;c++)); do
            for ((d=$c+1;d<7;d++)); do
                for ((e=$d+1;e<7;e++)); do
                    echo "${ones[a]}${ones[b]}${ones[c]}${ones[d]}${ones[e]}"
                    args="${ones[a]}${ones[b]}${ones[c]}${ones[d]}${ones[e]}"
                    for files in "${filesarr[@]}"
                    do
                        # echo "$files"
                        mine="$(./s21_cat $files -$args)"
                        they="$(cat $files -$args)"
                        if diff <(echo "$mine") <(echo "$they") &> /dev/null
                        then
                            # echo "PASS"
                            pass=$(($pass+1))
                        else
                            echo "FAIL $files -$args"
                            fail=$(($fail+1))
                        fi
                    done
                done
            done
        done
    done
done
# 6 ARGS
for ((a=0;a<7;a++)); do
    for ((b=$a+1;b<7;b++)); do
        for ((c=$b+1;c<7;c++)); do
            for ((d=$c+1;d<7;d++)); do
                for ((e=$d+1;e<7;e++)); do
                    for ((f=$e+1;f<7;f++)); do
                        echo "${ones[a]}${ones[b]}${ones[c]}${ones[d]}${ones[e]}${ones[f]}"
                        args="${ones[a]}${ones[b]}${ones[c]}${ones[d]}${ones[e]}${ones[f]}"
                        for files in "${filesarr[@]}"
                        do
                            # echo "$files"
                            mine="$(./s21_cat $files -$args)"
                            they="$(cat $files -$args)"
                            if diff <(echo "$mine") <(echo "$they") &> /dev/null
                            then
                                # echo "PASS"
                                pass=$(($pass+1))
                            else
                                echo "FAIL $files -$args"
                                fail=$(($fail+1))
                            fi
                        done
                    done
                done
            done
        done
    done
done

echo "PASS: $pass; FAIL: $fail"
