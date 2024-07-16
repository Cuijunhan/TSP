import random
global n,c1,c2,vmax,x,v,y
n = 2 #粒子个数，这里为了方便演示，我们只取两个，观察其运动方向

c1=2
c2=2
vmax=0.1 #速度最大值
    #适应度计算函数，每个粒子都有它的适应度
def fitnessFunction():
    y = []
    for i in range(0,n):
        y[i]=-1*x[i]*(x[i]-2)
    return y
    
def init():    
    #本来是应该随机产生的，为了方便演示，我这里手动随机落两个点，分别落在最大值两边
    global x,y
    x = [0,2]
    v = [0.01,0.02]
    y = fitnessFunction()
    #初始化当前个体最优位置，并找到群体最优位置
    for i in range(n):
        pbest[i]=y[i]
        if y[i]>gbest:
            gbest=y[i]
    print("算法开始，起始最优解:"+gbest+"\n")

def PSO(max):
    #粒子群算法
    for i in range(max):
        w = 0.4
        for j in range(n):
            #更新位置和速度，下面就是我们之前重点讲解的两条公式。
            v[j]=w*v[j]+c1*random.random()*(pbest[j]-x[j])+c2*random.random()*(gbest-x[j])
            if v[j] > vmax : v[j] = vmax#控制速度不超过最大值
            x[j]+=v[j]
 
            #越界判断，范围限定在[0, 2]
            if(x[j]>2): x[j]=2
            if(x[j]<0) :x[j]=0

            y = fitnessFunction()
        #更新个体极值和群体极值
        for j in range(n):
            pbest[j]=max(y[j],pbest[j])
            if pbest[j]>gbest : gbest=pbest[j]
            print("粒子n"+j+": x = "+x[j]+"  "+"v = "+v[j])
        print("第"+(i+1)+"次迭代，全局最优解 gbest = "+gbest)
        print("\n")    

#运行我们的算法
def  main():
    init()
    PSO(10)


if __name__ == "__main__" :
    main()


