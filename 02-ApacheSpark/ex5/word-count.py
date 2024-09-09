from pyspark import SparkConf, SparkContext

conf = SparkConf().setMaster("local").setAppName("WordCount")
sc = SparkContext(conf = conf)

# import os 
# os.getcwd()
# Adjust srcdir to your local directory. 
# srcdir = '/Users/pepc/Teaching/410-BigdataDistributedProcessingSystem/code/course410-2024/02-ApacheSpark/ex3/'
srcdir = './ex5/'
rdd = sc.textFile((srcdir + "data/AIfuture.txt")) 
first_5lines = rdd.take(5)
for line in first_5lines:
    print(line)

# - - - clean sentences - - - 
import re
# # Example sentence
# sentence = "Hello, world. This is an example sentence."
# # Regular expression to match commas and periods
# cleaned_sentence = re.sub(r'[.,]', '', sentence)
# print(cleaned_sentence)

# clean sentences 
rdd_clean = rdd.map(lambda x: re.sub(r'[.,]', '', x) )
first_5lines = rdd_clean.take(5)
for line in first_5lines:
    print(line)

# split sentences into words
words = rdd_clean.flatMap(lambda x: x.split())
first_5lines = words.take(5)
for line in first_5lines:
    print(line)

# count words by value
wordCounts = words.countByValue()
for key, value in wordCounts.items():
    print("%s %i" % (key, value))

# convert every word to a key-value pair with a value 1
wordCounts = words.map(lambda x: (x, 1)).reduceByKey(lambda x, y: x + y)
first_5lines = wordCounts.take(5)
for line in first_5lines:
    print(line)

# change the order of the tuple and sort by key
wordCounts_sort = wordCounts.map(lambda x: (x[1], x[0])).sortByKey()
results = wordCounts_sort.collect()

for key, value in results:
    print("%i %s" % (key, value))

