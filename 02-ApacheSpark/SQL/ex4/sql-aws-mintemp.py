from pyspark.sql import SparkSession
from pyspark.sql import functions as func
from pyspark.sql.types import StructType, StructField, StringType, IntegerType, FloatType

# from pyspark.sql import Row
# Row class, 
#  which allows you to create structured data objects (rows) that resemble records in a DataFrame.
#  A Row is essentially a way to create a data structure similar to a tuple
#  but with named fields, making it easier to work with and refer to specific columns by name.

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
srcdir = './SQL/ex4/'
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

minTempByLocation_C2F = minTempByLocation.withColumn("temperature",
                                    func.round(func.col("min(temperature)") * (9.0 / 5.0) + 32.0, 2))
minTempByLocation_C2F.show()
minTempByLocation_C2F_sorted = minTempByLocation_C2F.select("locationID", "temperature").sort("temperature")
minTempByLocation_C2F_sorted.show()


# Collect, format, and print the results
results = minTempByLocation_C2F_sorted.collect()

for result in results:
    print("ID: {}, Temp[F]: {:.2f}".format(result[0],result[1]))
    
spark.stop()


 