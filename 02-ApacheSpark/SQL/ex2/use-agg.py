from pyspark.sql import SparkSession
from pyspark.sql.functions import sum, avg

# Create a Spark session
spark = SparkSession.builder.appName("AggExample").getOrCreate()

# Sample data
data = [("John", 34, 75000), ("Sara", 29, 60000), ("Mike", 41, 90000)]
df = spark.createDataFrame(data, ["name", "age", "salary"])

# Perform aggregation to find the total salary and average age
# agg: apply aggregate functions on the selected columns
df.agg(sum("salary").alias("total_salary"), avg("age").alias("average_age")).show()

