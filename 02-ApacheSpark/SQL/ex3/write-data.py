# Import necessary modules
from pyspark.sql import SparkSession

# Create a Spark session
spark = SparkSession.builder.appName("WriteDataExample").getOrCreate()

# Sample data
data = [("John", 34, "Engineering", 75000),
        ("Sara", 29, "Marketing", 60000),
        ("Mike", 41, "Engineering", 90000)]

# Create a DataFrame
df = spark.createDataFrame(data, ["name", "age", "department", "salary"])

# Show the DataFrame
df.show()

# Write the DataFrame to different formats
srcdir = './SQL/ex3/'

# 1. Write to CSV format
# Note that Spark writes data in a distributed manner. 
df.write.csv(srcdir+"data-csv",header=True,mode="overwrite")
# If you want to save the data into a single file, then use 'coalesce'
df.coalesce(1).write.csv(srcdir+"data-csv-single",header=True,mode="overwrite")

# 2. Write to JSON format
df.write.json(srcdir+"data-json", mode="overwrite")
df.coalesce(1).write.json(srcdir+"data-json-single", mode="overwrite")

# 3. Write to Parquet format
# Parquet: columnar storage file format 
# designed for efficient data processing and storage,
# especially in distributed systems like Apache Spark, Hadoop, and Apache Hive. 
df.write.parquet(srcdir+"data-parquet", mode="overwrite")
df.coalesce(1).write.parquet(srcdir+"data-parquet-single", mode="overwrite")


df.rdd()
