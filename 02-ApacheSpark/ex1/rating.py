from pyspark import SparkConf, SparkContext
import collections

conf = SparkConf().setMaster("local").setAppName("RatingsHistogram")
sc = SparkContext(conf = conf)

import os
os.getcwd()

srcdir = '/Users/Shinhoo/Teaching/410-BigdataDisbributedProcessingSystem/code/course410/02-ApacheSpark/ex1/'
# srcdir = '/Users/pepc/Teaching/410-BigdataDistributedProcessingSystem/code/course410-2024/02-ApacheSpark/ex1/'
rdd = sc.textFile((srcdir + "ml-100k/u.data"))

# - - - See the data - - - 
# Bring all the data to the driver and print it.
all_data = rdd.collect() 
for line in all_data:
    print(line)

# foreach apply a function to each element of RDD without collecting the data back to the driver. 
rdd.foreach(lambda line: print(line))

# View first 5 lines of the data
first_5lines = rdd.take(5)
for line in first_5lines:
    print(line)


# - - - extract rating - - - 
# user id | item id | rating | timestamp.
#    0         1         2         3 
# split the line into 4 fields and extract the rating in field 2. 
print(line)
print(line.split()[2] )

ratings = rdd.map(lambda x: x.split()[2]) 
# first_5lines = ratings.take(5)

# count the each unique value
result = ratings.countByValue()

# sort the result based on the key. (Here, key is the unique value.)
sortedResults = collections.OrderedDict(sorted(result.items()))
for key, value in sortedResults.items():
    print("%s %i" % (key, value))
