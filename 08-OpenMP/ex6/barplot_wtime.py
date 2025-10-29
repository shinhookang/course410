import matplotlib.pyplot as plt
import numpy as np

nthreads = [1, 2, 4, 8, 16]
wtime = [8.8482, 4.5263, 2.4352, 1.3924, 0.8091]

plt.figure(figsize=(12, 6))

#plt.plot(nthreads, wtime, marker='o', linestyle='-', linewidth=2, markersize=8)
#plt.xscale('log', base=2)
#plt.yscale('log', base=2)


# Create the bar plot
bars = plt.bar(range(len(nthreads)), wtime, align='center', alpha=0.8, color='skyblue', edgecolor='navy')

plt.xlabel('Number of Threads', fontsize=12)
plt.ylabel('Execution Time (seconds)', fontsize=12)
plt.title('Execution Time vs Number of Threads', fontsize=14)

# Set x-axis ticks to show thread numbers
plt.xticks(range(len(nthreads)), nthreads)

# Add value labels on top of each bar
for bar in bars:
    height = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2., height,
             f'{height:.4f}',
             ha='center', va='bottom')

# Add grid lines for better readability
plt.grid(axis='y', linestyle='--', alpha=0.7)

# Adjust y-axis to start from 0 and have some headroom above the highest bar
plt.ylim(0, max(wtime) * 1.1)

plt.tight_layout()

# Save the figure
plt.savefig('wtime_vs_nthreads_barplot.png', dpi=300, bbox_inches='tight')
