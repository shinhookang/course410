from pyspark import SparkConf, SparkContext

conf = SparkConf().setMaster("local").setAppName("FriendsByAge")
sc = SparkContext(conf = conf)

def parseLine(line):
    fields = line.split(',')
    ages = fields[4]
    numPatients = int(fields[6])
    return (ages, numPatients)

# Adjust srcdir to your local directory. 
srcdir = '/Users/pepc/Teaching/410-BigdataDistributedProcessingSystem/code/course410-2024/02-ApacheSpark/ex2/'
rdd = sc.textFile((srcdir + "data/InfectiousDisease.csv")) # CSV: comma separated values
first_5lines = rdd.take(5)
for line in first_5lines:
    print(line)
#       0    |   1     |  2   |   3    |   4  |     5       |    6
#  Area code | Disease | Date | Season | Ages | male/female | # of patients
# 4812100000,C������,2018-01,�ܿ�,60 ~,��,2

# Extract Ages and # of patients
# This gives key-value pairs 
parseLine(line)
rdd_age_npatients = rdd.map(parseLine)
first_5lines = rdd_age_npatients.take(5)
for line in first_5lines:
    print(line)

# mapValues: only affect values; apply a function only to the values of the key-value pairs.
rdd_age_npatients_1 = rdd_age_npatients.mapValues(lambda x: (x, 1)) # change the value x to (x,1)
first_5lines = rdd_age_npatients_1.take(5)
for line in first_5lines:
    print(line)

# line[0]: age
# line[1]: (npatients,1) 
totalsByAge = rdd_age_npatients_1.reduceByKey(lambda x, y: (x[0] + y[0], x[1] + y[1]))
first_5lines = totalsByAge.take(5)
for line in first_5lines:
    print(line)

# average # of patients per ages
averagesByAge = totalsByAge.mapValues(lambda x: x[0] / x[1])
results = averagesByAge.collect()
for result in results:
    print(result)
