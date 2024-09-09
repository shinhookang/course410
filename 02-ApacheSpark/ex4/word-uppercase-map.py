from pyspark import SparkConf, SparkContext

conf = SparkConf().setMaster("local").setAppName("WordCount")
sc = SparkContext(conf = conf)


# Start with two lines.
text_data = ["Korea University Sejong Campus is located in Sejong City.", "Our global residence system presents a new paradigm of undergraduate education."] 
rdd = sc.parallelize(text_data)
all_data = rdd.collect() 
for line in all_data:
    print(line)

# Convert all the words to uppercase letters
rdd_upper = rdd.map(lambda x: x.upper())

# End up with two lines.
all_data = rdd_upper.collect() 
for line in all_data:
    print(line)

