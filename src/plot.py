import matplotlib.pyplot as plt
import sys


def draw_plot(filename, tour = -1):
    # 读取数据文件
    data1 = []
    with open("/home/ae/project-tsp/dataset/out_data/"+filename+"-ga-gt.txt", 'r') as file:
        for line in file:
            data1.append(float(line.strip()))

    data2 = []
    with open("/home/ae/project-tsp/dataset/out_data/"+filename+"-ga-gt-greedy.txt", 'r') as file:
        for line in file:
            data2.append(float(line.strip()))

    # 绘制折线图
    plt.figure(figsize=(10, 6))
    plt.plot(data1, marker='.', linestyle='-', color='b', label='GA-GT')
    plt.plot(data2, marker='.', linestyle='-', color='r', label='GA-GT-greedy')
    plt.xlabel('Index')
    plt.ylabel('Value')
    plt.title("filename:"+filename+", tour:"+str(tour)+", GA-GT:"+str(data1[-1])+", GA-GT-greedy:"+str(data2[-1]))
    plt.grid(True)
    plt.legend()
    plt.tight_layout()

    # 显示图形
    plt.show()



if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python3 your_script.py <filename>")
        sys.exit(1)

    filename = sys.argv[1]
    tour = int(sys.argv[2])
    draw_plot(filename,tour)    


