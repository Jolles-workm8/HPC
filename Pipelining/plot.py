import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
import random
import matplotlib.colors as mcolors


def plot_fmul_fmla_latency_src():

    df1 = pd.read_csv("./latency_fmla.csv")
    df2 = pd.read_csv("./latency_fmul.csv")

    df2 = df2.drop(columns=['Cores'])

    df1 = df1.reset_index(drop=True)
    df2 = df2.reset_index(drop=True)

    df = pd.concat([df1, df2], axis=1)

    print(df)

    print(df.iloc[:, 2])

    plt.plot(df.iloc[:, 0], df.iloc[:, 1], color = 'blue', label = 'fmla')
    plt.plot(df.iloc[:, 0], df.iloc[:, 2], color = 'red', label = 'fmul')

    plt.legend()
    plt.xlabel('Cores')
    plt.ylabel('MFLOPS')
    plt.title('Benchmarking Source Pipeline On Neoverse v2')


    #plt.show()

    plt.savefig('fmul_fmla_src.png')

    plt.show()

def plot_fmul_fmla_latency_dst():

    df1 = pd.read_csv("./latency_dst_fmla.csv")
    df2 = pd.read_csv("./latency_dst_fmul.csv")

    df2 = df2.drop(columns=['Cores'])

    df1 = df1.reset_index(drop=True)
    df2 = df2.reset_index(drop=True)

    df = pd.concat([df1, df2], axis=1)

    print(df)

    print(df.iloc[:, 2])

    plt.plot(df.iloc[:, 0], df.iloc[:, 1], color = 'blue', label = 'fmla')
    plt.plot(df.iloc[:, 0], df.iloc[:, 2], color = 'red', label = 'fmul')

    plt.legend()
    plt.xlabel('Cores')
    plt.ylabel('MFLOPS')
    plt.title('Benchmarking Destination Pipeline On Neoverse v2')


    #plt.show()

    plt.savefig('fmul_fmla_dst.png')

if __name__ == "__main__":
    plot_fmul_fmla_latency_src()
    plot_fmul_fmla_latency_dst()
