import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
import random
import matplotlib.colors as mcolors


def plot_scalar_simd():
    df=pd.read_csv("./SP_Scalar_pinned.csv")



    df.plot(x='Cores', color='green')

    plt.xlabel('Cores')
    plt.ylabel('MFLOPS')
    plt.title('Benchmarking Neoverse N1')


    plt.show()


if __name__ == "__main__":
    plot_scalar_simd()
