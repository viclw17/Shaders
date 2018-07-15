# Chapter 3: Rays, a simple camera, and background
原理分析：
光线起点（也就是eye或者camera）固定的情况下，光线的方向向量的变动范围形成光线束。光线束即是eye或者camera看到画面。也就意味着：方向向量的变动范围决定着所能看到画面的范围。另外，光线中每个光子的频率（颜色）决定这画面的内容。

所以，如果我们要通过光线追踪来画图的话，只需要做两件事情：
- 第一步，确定光线的方向向量的变动范围函数t，从而确定画面的范围、大小（一条光线对应这画面上的一个像素点）。
- 第二步，对每一条光线（像素点）设置颜色，（高质量图的每个像素点上可能对应多个采样）从而确定画面上的内容。

如下图，光线的起点为（0，0，0），要求在黑框内作图（即光线和黑框平面的交点落在黑框内）
![](smallpt/RaytracingInOneWeekend/figure-1.png)
Followed the [right-handed coordinate system](https://en.wikipedia.org/wiki/Right-hand_rule), z is pointing out of screen. So pointing into the screen is the negative z-axis.


Tranverse the screen from lower_left_corner and use 2 offset vectors along the screen sides to move the ray endpoint across the screen

所以，交点坐标可以表示为向量：```lower_left_corner + u*horizontal + v*vertical```. 光线的方向向量 = 交点的向量 - 起点向量，由于起点为原点，所以方向向量=交点向量。每个交点的u，v的值即为该像素点在整个画面中的位置。
