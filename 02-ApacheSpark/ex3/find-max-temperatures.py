from pyspark import SparkConf, SparkContext

conf = SparkConf().setMaster("local").setAppName("MinTemperatures")
sc = SparkContext(conf = conf)

def parseLine(line):
    fields = line.split(',')
    stationID = fields[0]
    temperature = float(fields[2])
    return (stationID, temperature)

# Adjust srcdir to your local directory. 
srcdir = '/Users/pepc/Teaching/410-BigdataDistributedProcessingSystem/code/course410-2024/02-ApacheSpark/ex3/'
rdd = sc.textFile((srcdir + "data/OBS_AWS_TIM_20240909161730.csv")) # CSV: comma separated values
first_5lines = rdd.take(5)
for line in first_5lines:
    print(line)
# Field    
# 0        |   1  |       2        |       3
# Location | Time | Temperature [C]| Precipitation [mm]

parsed_rdd = rdd.map(parseLine)
first_5lines = parsed_rdd.take(5)
for line in first_5lines:
    print(line)

maxTemps = parsed_rdd.reduceByKey(lambda x, y: max(x,y))
first_5lines = maxTemps.take(5)
for line in first_5lines:
    print(line)

results = maxTemps.collect()

for result in results:
    print(result[0] + "\t{:.2f} [C]".format(result[1]))
