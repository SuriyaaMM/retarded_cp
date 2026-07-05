import matplotlib.pyplot as plt 
import seaborn as sns
import numpy as np

def main():
    a = np.array([6, 6, 6, 6, 7, 7, 7])
    n = a.shape[0]
    k = 13

    table = np.zeros(shape=(n, n), dtype=a.dtype)

    seen = {}

    for i in range(0, n):
        for j in range(i + 1, n):
            for kk in range(i, j):
                prefix_min = min(a[i : kk + 1])
                suffix_max = max(a[kk + 1 : j + 1])

                if prefix_min + suffix_max == k:
                    if seen.get((i, j), 0) == 0:
                        table[i][j] += 1
                        seen[(i, j)] = 1

    plt.figure()

    sns.heatmap(table, annot=True)
    plt.xlabel("i")
    plt.ylabel("j")

    plt.show()

if __name__ == "__main__":
    main()