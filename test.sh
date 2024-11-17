pass=0
fail=0

argsarr=('' ' --number' ' --number-nonblank')

for args in "${argsarr[@]}"
do
    echo "Test$args"
    echo "test1.txt"
    mine="$(./a.out test1.txt$args)"
    they="$(cat test1.txt$args)"
    if diff <(echo "$mine") <(echo "$they") &> /dev/null
    then
        echo "PASS"
        pass=$(($pass+1))
    else
        echo "FAIL"
        fail=$(($fail+1))
    fi
    echo "test2.txt"
    mine="$(./a.out test2.txt$args)"
    they="$(cat test2.txt$args)"
    if diff <(echo "$mine") <(echo "$they") &> /dev/null
    then
        echo "PASS"
        pass=$(($pass+1))
    else
        echo "FAIL"
        fail=$(($fail+1))
    fi
    echo "test1.txt test2.txt"
    mine="$(./a.out test1.txt test2.txt$args)"
    they="$(cat test1.txt test2.txt$args)"
    if diff <(echo "$mine") <(echo "$they") &> /dev/null
    then
        echo "PASS"
        pass=$(($pass+1))
    else
        echo "FAIL"
        fail=$(($fail+1))
    fi
    echo "test2.txt test1.txt"
    mine="$(./a.out test2.txt test1.txt$args)"
    they="$(cat test2.txt test1.txt$args)"
    if diff <(echo "$mine") <(echo "$they") &> /dev/null
    then
        echo "PASS"
        pass=$(($pass+1))
    else
        echo "FAIL"
        fail=$(($fail+1))
    fi
    echo "test1.txt test1.txt"
    mine="$(./a.out test1.txt test1.txt$args)"
    they="$(cat test1.txt test1.txt$args)"
    if diff <(echo "$mine") <(echo "$they") &> /dev/null
    then
        echo "PASS"
        pass=$(($pass+1))
    else
        echo "FAIL"
        fail=$(($fail+1))
    fi
    echo "test2.txt test2.txt"
    mine="$(./a.out test2.txt test2.txt$args)"
    they="$(cat test2.txt test2.txt$args)"
    if diff <(echo "$mine") <(echo "$they") &> /dev/null
    then
        echo "PASS"
        pass=$(($pass+1))
    else
        echo "FAIL"
        fail=$(($fail+1))
    fi
    echo "test1.txt test2.txt test1.txt"
    mine="$(./a.out test1.txt test2.txt test1.txt$args)"
    they="$(cat test1.txt test2.txt test1.txt$args)"
    if diff <(echo "$mine") <(echo "$they") &> /dev/null
    then
        echo "PASS"
        pass=$(($pass+1))
    else
        echo "FAIL"
        fail=$(($fail+1))
    fi
    echo "test2.txt test1.txt test2.txt"
    mine="$(./a.out test2.txt test1.txt test2.txt$args)"
    they="$(cat test2.txt test1.txt test2.txt$args)"
    if diff <(echo "$mine") <(echo "$they") &> /dev/null
    then
        echo "PASS"
        pass=$(($pass+1))
    else
        echo "FAIL"
        fail=$(($fail+1))
    fi
done

echo "PASS: $pass; FAIL: $fail"