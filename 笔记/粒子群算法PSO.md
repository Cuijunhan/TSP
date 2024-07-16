# 粒子群算法PSO

​	粒子群算法，也称粒子群优化算法或鸟群觅食算法（Particle Swarm Optimization），缩写为 PSO， 是近年来由J. Kennedy和R. C. Eberhart等开发的一种新的进化算法(Evolutionary Algorithm - EA)。

​	通过追随当前搜索到的最优值来寻找全局最优

​	在粒子群算法中，每一个优化问题的解都是搜索空间中的一只鸟、粒子。所有粒子都有一个适应值（fitness value）、速度、距离。

​	初始化为随机值然后迭代收敛到最优解。

### 抽象成数学表达

​	粒子群算法通过设计一种无质量的粒子来模拟鸟群中的鸟，粒子仅具有两个属性：速度和位置，速度代表移动的快慢，位置代表移动的方向。

​	鸟被抽象为没有质量和体积的微粒(点)，并延伸到N维空间，粒子i在N维空间的位置表示为矢量Xi＝(x1，x2，…，xN)，飞行速度表示为矢量Vi＝(v1，v2，…，vN)。每个粒子都有一个由目标函数决定的适应值(fitness value)，并且知道自己到目前为止发现的最好位置(pbest)和现在的位置Xi。这个可以看作是粒子自己的飞行经验。除此之外，每个粒子还知道到目前为止整个群体中所有粒子发现的最好位置(gbest)(gbest是pbest中的最好值)，这个可以看作是粒子同伴的经验。粒子就是通过自己的经验和同伴中最好的经验来决定下一步的运动。

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly91cGxvYWQtaW1hZ2VzLmppYW5zaHUuaW8vdXBsb2FkX2ltYWdlcy8xMDM4Njk0MC0zMWM3NGNhOWRhMTdiNjRiLmpwZw?x-oss-process=image/format,png)