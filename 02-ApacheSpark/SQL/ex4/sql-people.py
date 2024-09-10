from pyspark.sql import SparkSession
from pyspark.sql import Row

# Create a Spark session
spark = SparkSession.builder.appName("TempViewExample").getOrCreate()

# Create an RDD of Rows
rdd_people = spark.sparkContext.parallelize([
    Row(name="John", age=34, department="Engineering"),
    Row(name="Sara", age=29, department="Marketing"),
    Row(name="Mike", age=41, department="Engineering")
])

# Convert the RDD to a DataFrame
df_people = spark.createDataFrame(rdd_people)
df_people.show()

# Create a temporary view called "people"
df_people.createOrReplaceTempView("people")

# Run SQL queries on the DataFrame via the temporary view
result = spark.sql("SELECT name, age FROM people WHERE age > 30")
result.show()

result = spark.sql("SELECT name, age FROM people WHERE age < 30")
result.show()

# Show the result
