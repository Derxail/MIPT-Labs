import pandas as pd
import matplotlib.pyplot as plt

filenames = ['linear', 'binary', 'fa-linear', 'fa-square',
             'freq-linear-uniform-0', 'freq-linear-uniform-a', 'freq-linear-uniform-b',
             'freq-linear-uniform-c', 'freq-linear-binomial-0', 'freq-linear-binomial-a',
             'freq-linear-binomial-b', 'freq-linear-binomial-c']

for name in filenames[0:4]:
    data = pd.read_csv('./data/' + name + '.csv', sep=',')
    fig, ax = plt.subplots()
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)

    ax.plot(data['n'], data['std'], label='Average')
    ax.plot(data['n'], data['worst'], label='Worst')

    plt.legend()
    fig.savefig('./graphs/' + name + '.png', dpi=300)

for name in filenames[4:]:
    data = pd.read_csv('./data/' + name + '.csv', sep=',')
    fig, ax = plt.subplots()
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)

    ax.plot(data['n'], data['std'], label='Average')

    plt.legend()
    fig.savefig('./graphs/' + name + '.png', dpi=300)

plt.show()
