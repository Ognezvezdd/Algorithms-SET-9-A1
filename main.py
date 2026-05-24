import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results.txt", sep=";")

types = df["type"].unique()
algorithms = df["algorithm"].unique()

type_names = {
    "random": "случайный массив",
    "reverse": "обратно отсортированный массив",
    "almost": "почти отсортированный массив",
    "prefix": "массив с общим префиксом"
}

algorithm_names = {
    "QUICKSORT": "QUICKSORT",
    "MERGESORT": "MERGESORT",
    "STRING_QUICK_SORT": "STRING QUICK SORT",
    "STRING_MERGE_SORT": "STRING MERGE SORT",
    "MSD_RADIX_SORT": "MSD RADIX SORT",
    "MSD_RADIX_QUICK_SORT": "MSD RADIX + QUICK SORT"
}

for t in types:
    cur = df[df["type"] == t]

    plt.figure(figsize=(10, 6))

    for alg in algorithms:
        part = cur[cur["algorithm"] == alg]
        plt.plot(part["n"], part["time_microseconds"], marker="o", label=algorithm_names.get(alg, alg))

    plt.title(f"Время работы, {type_names.get(t, t)}")
    plt.xlabel("Размер массива")
    plt.ylabel("Время, микросекунды")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"time_{t}.png")
    plt.close()

for t in types:
    cur = df[df["type"] == t]

    plt.figure(figsize=(10, 6))

    for alg in algorithms:
        part = cur[cur["algorithm"] == alg]
        plt.plot(part["n"], part["char_comparisons"], marker="o", label=algorithm_names.get(alg, alg))

    plt.title(f"Посимвольные сравнения, {type_names.get(t, t)}")
    plt.xlabel("Размер массива")
    plt.ylabel("Количество посимвольных сравнений")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"comparisons_{t}.png")
    plt.close()

summary = df.groupby(["type", "algorithm"])[["time_microseconds", "char_comparisons"]].mean()
summary.to_csv("summary.csv", sep=";")

print(summary)