import matplotlib.pyplot as plt
import numpy as np

nthreads = np.array([1, 2, 4, 8, 16])
wtime = np.array([1.7758, 0.8958, 0.5147, 0.3357, 0.2271])
wtime_serial = 1.7758
wtime_ideal = wtime_serial * 1./nthreads
speedup = wtime_serial/wtime
speedup_ideal = wtime_serial/wtime_ideal
efficiency = speedup/speedup_ideal * 100.
efficiency2 = wtime_ideal/wtime * 100.

plt.figure(figsize=(8, 6))
plt.plot(nthreads, wtime, marker='o', linestyle='-', linewidth=2, markersize=8,label='measured')
plt.plot(nthreads, wtime_ideal, marker='x', linestyle=':', linewidth=2, markersize=8,label='ideal')
plt.tick_params(axis='both', which='major', labelsize=14)
plt.xscale('log', base=2)
plt.yscale('log', base=10)

plt.xlabel('Number of Threads', fontsize=16)
plt.ylabel('Execution Time (seconds)', fontsize=16)
# plt.title('Execution Time vs Number of Threads', fontsize=16)

plt.grid(True, which="both", ls="-", alpha=0.2)

plt.xticks(nthreads, labels=nthreads)
plt.ylim(0.05, 5)
plt.xlim(0.5, 26)
plt.legend()

for x, y, r in zip(nthreads, wtime, efficiency):
    plt.annotate(f'{y:.4f}({r:.1f}%)', (x, y), textcoords="offset points", xytext=(0,10), ha='center',fontsize=14)

plt.tight_layout()
#plt.show()
plt.savefig('wtime_vs_nthreads.png', dpi=300, bbox_inches='tight')
