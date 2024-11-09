import matplotlib.pyplot as plt
import pandas as pd

names = ["3d6", "adv", "d100", "disadv", "double"]

for name in names:
    data = pd.read_csv(f"data/dstr_{name}.csv", sep=", ")
    fig, ax = plt.subplots()
    ax.stairs(data["frequency"], fill=True)
    fig.savefig(f"graphs/dstr_{name}.png")
