### catalan

recursive-relation

**h(n)= h(0)\*h(n-1) + h(1)\*h(n-2) + ... + h(n-1)h(0)** 

and its cause a O(n*n)  time-cost



![image-20200718104024191](C:\Users\蒲哥\AppData\Roaming\Typora\typora-user-images\image-20200718104024191.png)

### 通项公式的证明

![image-20200718104400374](C:\Users\蒲哥\AppData\Roaming\Typora\typora-user-images\image-20200718104400374.png)

![image-20200718104426661](C:\Users\蒲哥\AppData\Roaming\Typora\typora-user-images\image-20200718104426661.png)

### 递推公式的证明

![image-20200718104524927](C:\Users\蒲哥\AppData\Roaming\Typora\typora-user-images\image-20200718104524927.png)



### 常用方案 只能往下或者往右走的方案数

(1) dp: 导致O(m*n)的时间复杂度

（2） 组合：总步数为m+n-2,m-1步向下，n-1向右，故有C(m+n-2,n-1)

​	即 (m+n-1)!/[(n-1)! *(m-1)!]



#### N个节点的二叉树情形，不穿越对角线的方案数，进出栈的合法，凸多边形的三角划分

https://blog.csdn.net/Morning_Glory_JR/article/details/102760802