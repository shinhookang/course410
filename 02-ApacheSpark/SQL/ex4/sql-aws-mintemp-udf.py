from pyspark.sql import SparkSession
from pyspark.sql import functions as func
from pyspark.sql.types import StructType, StructField, StringType, IntegerType, FloatType


# Create a SparkSession
spark = SparkSession.builder.appName("SparkSQL").getOrCreate()

# Field    
# 0        |   1  |       2        |       3
# Location | Time | Temperature [C]| Precipitation [mm]
schema = StructType([ \
                     StructField("locationID", IntegerType(), True), \
                     StructField("datetime", StringType(), True), \
                     StructField("temperature", FloatType(), True)])

# Read the data as DataFrame 
# srcdir = './SQL/ex4/'
srcdir = './'
df = spark.read.schema(schema).csv(srcdir+"data/OBS_AWS_TIM_20240909161730.csv")
df.printSchema()
df.show()


# Select only locationID and temperature
locationTemps = df.select("locationID", "temperature")


# Aggregate to find minimum temperature for every station
minTempByLocation = locationTemps.groupBy("locationID").min("temperature")
minTempByLocation.show()


# Convert temperature to fahrenheit and sort the dataset
# (0°C × 9/5) + 32 = 32°F

# minTempByLocation_C2F = minTempByLocation.withColumn("temperature",
#                                     func.round(func.col("min(temperature)") * (9.0 / 5.0) + 32.0, 2))

# Define a Python function to categorize age
def celcius_to_fahrenheit(ctemp):
    return ctemp* (9.0 / 5.0) + 32.0

# Register the function as a UDF
celcius_to_fahrenheit_udf = func.udf(celcius_to_fahrenheit, FloatType())

# Add a new column using the UDF
minTempByLocation_C2F = minTempByLocation.withColumn("temp [F]", celcius_to_fahrenheit_udf(func.col("min(temperature)")))
minTempByLocation_C2F.show()
minTempByLocation_C2F_sorted = minTempByLocation_C2F.select("locationID", "temp [F]").sort("temp [F]")
minTempByLocation_C2F_sorted.show()


# Collect, format, and print the results
results = minTempByLocation_C2F_sorted.collect()

for result in results:
    print("ID: {}, Temp[F]: {:.2f}".format(result[0],result[1]))
    
spark.stop()





 