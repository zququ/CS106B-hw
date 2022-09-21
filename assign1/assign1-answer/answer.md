### Q1:

执行时间见下图：

![p1](assets/Students-test.png)

执行找到四个完全数，包括6，28，496 和 8128。

### Q2:

`findPerfects` 执行时间为：

| number | time/s |
|--------|--------|
| 15000  | 0.931  |
| 30000  | 3.650  |
| 60000  | 14.282 |
| 120000 | 57.243 |

作图如下：

![p2](assets/predicted-time-for-4th-perfectnumber.png)

### Q3

对于 10 和 1000 计算 `isPerfect` 工作量不一样多，因为对于函数（`divisorSum(n)`）随着数字（`n`）的变大需要更多枚举的数字（`divisor < n, divisor++`）用于计算 `n ?% divisor`。另一方面，更大的数字理论上也会占用更多的内存，但是不是主要影响速度的原因。

对于 1-1000 和 1000-2000 这两个区间，对于计算 `findPerfect()` 函数则工作量相差不大，因为都只执行了相同次数的函数包括 `isPerfect()` 过程。

### Q4

由 Q2 可见时间约为 4396972 秒。

### 深入测试

`total` 的初始值从 0 改为 1，测试错误如下：

```
Incorrect (PROVIDED_TEST, perfect.cpp:94) Confirm divisorSum of small inputs
Line 95: EXPECT_EQUAL failed: divisorSum(1) != 0
divisorSum(1) = 1
```

### Q5

其他测试不能通过，因为改变 `total` 的初始值会造成 `divisorSum()` 的计算错误。






