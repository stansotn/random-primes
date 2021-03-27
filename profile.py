import subprocess
import statistics
import csv

n_samples = 100
n_start = 2048
n_stop = 4096
time_mean = []
time_std = []

with open('metrics.csv', "w") as f:
    writer = csv.writer(f)
    writer.writerow(['n_bits', 'time_mean', 'time_stdev'])
    for n in range(n_start, n_stop+1):

        time_measurements = []

        for _ in range(n_samples):

            proc = subprocess.run(['/usr/bin/time', '-p', './a.out', str(n)], capture_output=True, check=True).stderr.decode()
            time_measurements.append(float(proc.split()[1]))

        mean = statistics.mean(time_measurements)
        stdev = statistics.stdev(time_measurements)

        print('Sampling {} bits.. Mean Time: {}. stdev: {}'.format(n, mean, stdev))

        writer.writerow([n, mean, stdev])