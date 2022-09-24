### Q1 该程序在你的电脑上执行了多久？共有多少个完全数，分别是哪些？

执行时间见下图：

![p1](assets/Students-test.png)

执行找到四个完全数，包括6，28，496 和 8128。

### Q2 在表格中记录findPerfects的执行时间。

`findPerfects` 执行时间为：

| number | time (s) |
|--------|----------|
| 15000  | 0.931    |
| 30000  | 3.650    |
| 60000  | 14.282   |
| 120000 | 57.243   |

作图如下：

![p2](assets/predicted-time-for-4th-perfectnumber.png)

### Q3 对于 10 与 1000，计算 isPerfect是否做了同样多的工作？为什么一样多，或者为什么不一样多？对于搜索范围为 1-1000 的数，findPerfect其工作量是否与 1000-2000 时一致？为什么一样多，或者为什么不一样多？

对于 10 和 1000 计算 `isPerfect` 工作量不一样多，因为对于函数（`divisorSum(n)`）随着数字（`n`）的变大需要更多枚举的数字（`divisor < n, divisor++`）用于计算 `n ?% divisor`。另一方面，更大的数字理论上也会占用更多的内存，但是不是主要影响速度的原因。

对于 1-1000 和 1000-2000 这两个区间，对于计算 `findPerfect()` 函数则工作量相差不大，因为都只执行了相同次数的函数包括 `isPerfect()` 过程。

### Q4 根据你收集到的数据进行推测：找出第五个数 findPerfect 要花费多少时间？

由 Q2 计算 $f(33550336)$ 时间约为 4396972 秒。

#### 深入测试

`total` 的初始值从 0 改为 1，测试错误如下：

```
Incorrect (PROVIDED\_TEST, perfect.cpp:94) Confirm divisorSum of small inputs
Line 95: EXPECT_EQUAL failed: divisorSum(1) != 0
divisorSum(1) = 1
```

### Q5 这个函数测试失败时，其他测试是否还能通过？为什么？

其他测试不能通过，因为改变 `total` 的初始值会造成 `divisorSum()` 的计算错误。

### Q6 描述一下你的测试策略。

测试策略包括以下几个方面：

1. 负数测试
2. 完全数的测试
3. 非完全数的测试
4. 边缘测试，平方数的测试
5. 速度测试

### Q7 在表格中记录findPerfectsSmarter的执行时间。

测试结果见下图：

![p3](assets/smarter-student-test.png) 

时间测试结果如下表格：

| number  | time (s) |
|---------|----------|
| 500000  | 2.667    |
| 1000000 | 7.314    |
| 2000000 | 20.635   |
| 4000000 | 57.368   |

### Q8 推测：findPerfectsSmarter 找到第 5 个完全数需要多久？

将 Q7 中数据做曲线的手动估计拟合，得到函数关系如下图：

![p4](assets/smarter-predicted-time-for-5th.png) 

可以计算出 `findPerfectsSmarter` 找到第五个完全数需要大约 1385 s。


### Q9 阐述下你选择的测试案例的动机，解释下为什么你认为这几个测试可以确定函数 findNthPerfectEuclid 正常工作。

```cpp
// student test for findNthPerfectEuclid()
STUDENT_TEST("Confirm find -1 perfect number is ok."){
    EXPECT(!isPerfect(findNthPerfectEuclid(-1)));
}

// edged test

STUDENT_TEST("Confirm find 0 perfect number is will not make troubles."){
    EXPECT(!isPerfect(findNthPerfectEuclid(0)));
}

STUDENT_TEST("Confirm find 5 perfect number is ok." ){
    EXPECT(isPerfect(findNthPerfectEuclid(5)));
}

// large number calculation test
STUDENT_TEST("Confirm find 6 perfect number is ok." ){
    EXPECT(isPerfect(findNthPerfectEuclid(6)));
}
```

`findNthPerfectEuclid(-1)`  --> 负值检测，虽然一般不会用到，防止出现奇怪问题；

`findNthPerfectEuclid(0)`  --> 同上；

`findNthPerfectEuclid(5)` --> 正常检测；

`findNthPerfectEuclid(6)` --> 机器能力内，较大计算量的压力测试。

### Q10 "Angelou" 的编码是多少呢？

"Angelou" 的编码

0520400 --> A524

### Q11 在写代码之前，自行进行头脑风暴，尝试把这个任务分解成几个小任务。简单描述一下你的分解过程。

1. 去特殊符号、保留首字母并大写；
2. 字母编码为数字；
3. 去掉重复数字、去掉零；
4. 长度小于4，填充0；长度大于等于4截短length-4长度。






