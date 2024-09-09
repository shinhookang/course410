from pyspark import SparkConf, SparkContext

conf = SparkConf().setMaster("local").setAppName("WordCount")
sc = SparkContext(conf = conf)


# Start with two lines.
text_data = ["Korea University Sejong Campus is located in Sejong City.", "Our global residence system presents a new paradigm of undergraduate education."] 
rdd = sc.parallelize(text_data)
all_data = rdd.collect() 
for line in all_data:
    print(line)

# Split sentences into words
rdd_split = rdd.flatMap(lambda x: x.split())
all_data = rdd_split.collect() 
for line in all_data:
    print(line)

# Convert all the words to uppercase letters
rdd_upper = rdd_split.flatMap(lambda x: x.upper())
all_data = rdd_split.collect() 
for line in all_data:
    print(line)
 
