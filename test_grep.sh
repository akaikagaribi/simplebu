#!/usr/bin/env bash

pass=0
fail=0

filesarr=("test1.txt" "test2.txt" "lspci.txt" "test1.txt test1.txt" "test2.txt test2.txt" "lspci.txt lspci.txt" "test1.txt test2.txt" "test1.txt lspci.txt" "test2.txt test1.txt" "test2.txt lspci.txt" "lspci.txt test1.txt" "lspci.txt test2.txt" "test1.txt test2.txt lspci.txt" "lspci.txt test1.txt test2.txt" "test2.txt lspci.txt test1.txt")

ones=("-i" "-v" "-c" "-l" "-n" "-h" "-s" "-o")
regs=("-e e" "-eo" "-e llo" "-f reg1.txt" "-freg2.txt")

# 1 ARG
for ((a=0;a<8;a++)); do
    args="${ones[a]}"
    temps=""
    for ((i=0;i<5;i++)); do
        temps="${temps} ${regs[i]}"
        for files in "${filesarr[@]}"; do
            echo $args $temps $files
            mine="$(./s21_grep $args $temps $files)"
            they="$(grep $args $temps $files)"
            if diff <(echo "$mine") <(echo "$they") &> /dev/null
            then
                # echo "PASS"
                pass=$(($pass+1))
            else
                echo "FAIL $args $temps $files"
                fail=$(($fail+1))
            fi
        done
    done
done
# 2 ARGS
for ((a=1;a<8;a++)); do
    for ((b=$a+1;b<8;b++)); do
        echo "${ones[a]} ${ones[b]}"
        args="${ones[a]} ${ones[b]}"
        temps=""
        for ((i=0;i<5;i++)); do
            temps="${temps} ${regs[i]}"
            for files in "${filesarr[@]}"; do
                echo $args $temps $files
                mine="$(./s21_grep $args $temps $files)"
                they="$(grep $args $temps $files)"
                if diff <(echo "$mine") <(echo "$they") &> /dev/null
                then
                    # echo "PASS"
                    pass=$(($pass+1))
                else
                    echo "FAIL $args $temps $files"
                    fail=$(($fail+1))
                fi
            done
        done
    done
done
# 3 ARGS
for ((a=1;a<8;a++)); do
    for ((b=$a+1;b<8;b++)); do
        for ((c=$b+1;c<8;c++)); do
            echo "${ones[a]} ${ones[b]} ${ones[c]}"
            args="${ones[a]} ${ones[b]} ${ones[c]}"
            temps=""
            for ((i=0;i<5;i++)); do
                temps="${temps} ${regs[i]}"
                for files in "${filesarr[@]}"; do
                    echo $args $temps $files
                    mine="$(./s21_grep $args $temps $files)"
                    they="$(grep $args $temps $files)"
                    if diff <(echo "$mine") <(echo "$they") &> /dev/null
                    then
                        # echo "PASS"
                        pass=$(($pass+1))
                    else
                        echo "FAIL $args $temps $files"
                        fail=$(($fail+1))
                    fi
                done
            done
        done
    done
done
# 4 ARGS
for ((a=1;a<8;a++)); do
    for ((b=$a+1;b<8;b++)); do
        for ((c=$b+1;c<8;c++)); do
            for ((d=$c+1;d<8;d++)); do
                echo "${ones[a]} ${ones[b]} ${ones[c]} ${ones[d]}"
                args="${ones[a]} ${ones[b]} ${ones[c]} ${ones[d]}"
                temps=""
                for ((i=0;i<5;i++)); do
                    temps="${temps} ${regs[i]}"
                    for files in "${filesarr[@]}"; do
                        echo $args $temps $files
                        mine="$(./s21_grep $args $temps $files)"
                        they="$(grep $args $temps $files)"
                        if diff <(echo "$mine") <(echo "$they") &> /dev/null
                        then
                            # echo "PASS"
                            pass=$(($pass+1))
                        else
                            echo "FAIL $args $temps $files"
                            fail=$(($fail+1))
                        fi
                    done
                done
            done
        done
    done
done

echo "PASS: $pass; FAIL: $fail"
