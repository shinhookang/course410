from pyspark.sql import SparkSession
from pyspark.sql.functions import trim

# Create a Spark session
spark = SparkSession.builder.appName("example").getOrCreate()

# Sample DataFrame with leading and trailing spaces in strings
data = [("  The Matrix  ",), ("  Inception ",), (" Interstellar ",)]
columns = ["movie_title"]
df = spark.createDataFrame(data, columns)
df.show()

# Use trim to remove leading and trailing spaces
df_trimmed = df.withColumn("trimmed_title", trim(df["movie_title"]))

# Show the result
df_trimmed.show()