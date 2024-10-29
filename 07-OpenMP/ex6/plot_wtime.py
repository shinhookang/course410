import matplotlib.pyplot as plt

nthreads = [1, 2, 4, 8, 16]
wtime = [8.8482, 4.5263, 2.4352, 1.3924, 0.8091]

plt.figure(figsize=(10, 6))
plt.plot(nthreads, wtime, marker='o', linestyle='-', linewidth=2, markersize=8)
plt.xscale('log', base=2)
plt.yscale('log', base=2)

plt.xlabel('Number of Threads', fontsize=12)
plt.ylabel('Execution Time (seconds)', fontsize=12)
plt.title('Execution Time vs Number of Threads', fontsize=14)

plt.grid(True, which="both", ls="-", alpha=0.2)

plt.xticks(nthreads, labels=nthreads)
plt.ylim(0.1, 2)

for x, y in zip(nthreads, wtime):
    plt.annotate(f'{y:.4f}', (x, y), textcoords="offset points", xytext=(0,10), ha='center')

plt.tight_layout()
#plt.show()
plt.savefig('wtime_vs_nthreads.png', dpi=300, bbox_inches='tight')
