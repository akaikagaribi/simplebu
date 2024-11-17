pass=0
fail=0

echo "Test no args"
echo "test1.txt"
mine="$(./a.out test1.txt)"
they="$(cat test1.txt)"
if diff <(echo "$mine") <(echo "$they") &> /dev/null
then
    echo "PASS"
    pass=$(($pass+1))
else
    echo "FAIL"
    fail=$(($fail+1))
fi
mine="$(./a.out test2.txt)"
they="$(cat test2.txt)"
echo "test2.txt"
if diff <(echo "$mine") <(echo "$they") &> /dev/null
then
    echo "PASS"
    pass=$(($pass+1))
else
    echo "FAIL"
    fail=$(($fail+1))
fi

echo "Test --number"
echo "test1.txt"
mine="$(./a.out test1.txt --number)"
they="$(cat test1.txt --number)"
if diff <(echo "$mine") <(echo "$they") &> /dev/null
then
    echo "PASS"
    pass=$(($pass+1))
else
    echo "FAIL"
    fail=$(($fail+1))
fi
echo "test2.txt"
mine="$(./a.out test2.txt --number)"
they="$(cat test2.txt --number)"
if diff <(echo "$mine") <(echo "$they") &> /dev/null
then
    echo "PASS"
    pass=$(($pass+1))
else
    echo "FAIL"
    fail=$(($fail+1))
fi

echo "Test --number-nonblank"
echo "test1.txt"
mine="$(./a.out test1.txt --number-nonblank)"
they="$(cat test1.txt --number-nonblank)"
if diff <(echo "$mine") <(echo "$they") &> /dev/null
then
    echo "PASS"
    pass=$(($pass+1))
else
    echo "FAIL"
    fail=$(($fail+1))
fi
echo "test2.txt"
mine="$(./a.out test2.txt --number-nonblank)"
they="$(cat test2.txt --number-nonblank)"
if diff <(echo "$mine") <(echo "$they") &> /dev/null
then
    echo "PASS"
    pass=$(($pass+1))
else
    echo "FAIL"
    fail=$(($fail+1))
fi

echo "PASS: $pass; FAIL: $fail"