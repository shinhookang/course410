# Import necessary modules
from pyspark.sql import SparkSession

# Create a Spark session
spark = SparkSession.builder.appName("ReadJSONExample").getOrCreate()

# Read data from a JSON file into a DataFrame
srcdir = './SQL/ex1/'
df = spark.read.option("multiline", "true").json(srcdir+"data/file.json")

# Show the first few rows of the DataFrame
df.show()

# Print the schema of the DataFrame to understand the structure
df.printSchema()

# Select specific columns from the DataFrame
df.select("age", "city").show()

# Filter rows where age is greater than 25
df.filter(df["age"] > 25).show()