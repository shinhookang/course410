from pyspark.sql import SparkSession

# Create a Spark session
spark = SparkSession.builder.appName("RDDZipExample").getOrCreate()

# Create two RDDs
rdd1 = spark.sparkContext.parallelize([1, 2, 3, 4])
rdd2 = spark.sparkContext.parallelize(["a", "b", "c", "d"])

# Zip the two RDDs together
zipped_rdd = rdd1.zip(rdd2)

# Collect and print the results
result = zipped_rdd.collect()
print(result)

# Stop the Spark session
spark.stop()