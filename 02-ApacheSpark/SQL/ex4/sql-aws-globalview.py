from pyspark.sql import SparkSession
from pyspark.sql import Row
# Row class, 
#  which allows you to create structured data objects (rows) that resemble records in a DataFrame.
#  A Row is essentially a way to create a data structure similar to a tuple
#  but with named fields, making it easier to work with and refer to specific columns by name.

# Create a SparkSession
spark = SparkSession.builder.appName("SparkSQL").getOrCreate()

# Field    
# 0        |   1  |       2        |       3
# Location | Time | Temperature [C]| Precipitation [mm]
def mapper(line):
    fields = line.split(',')
    return Row(locationID=int(fields[0]),
               datetime=str(fields[1]), \
               temperature=float(fields[2])) 

# srcdir = './SQL/ex4/'
srcdir = './'
rdd = spark.sparkContext.textFile(srcdir+"data/OBS_AWS_TIM_20240909161730.csv")
first_5lines = rdd.take(5)
for line in first_5lines:
    print(line)

# rdd.foreach(lambda line: print(line))

rdd_aws = rdd.map(mapper)
first_5lines = rdd_aws.take(357)
for line in first_5lines:
    print(line)
#rdd_aws.foreach(lambda line: print(line))


# Infer the schema, and register the DataFrame as a table.
schemaAws = spark.createDataFrame(rdd_aws)
schemaAws.show()
#schemaAws.show(schemaAws.count())

schemaAws.select("temperature").show()

# Register DataFrame as as a table.
# schemaAws.createOrReplaceTempView("aws")
# Global temporary views are stored in a system-defined database called global_temp,
#  so you must prefix the view name with this database name when querying it
schemaAws.createOrReplaceGlobalTempView("aws")

# SQL can be run over DataFrames that have been registered as a table.
temperature_warm = spark.sql("SELECT * FROM global_temp.aws WHERE temperature >= 25 AND temperature <= 27")
temperature_warm.show()

temperature_chill = spark.sql("SELECT * FROM global_temp.aws WHERE temperature < 20 ")
temperature_chill.show()


# # We can also use functions instead of SQL queries:
temperature_chill.groupBy("locationID").count().show()


# Create a new session and query the same global temporary view
new_session = spark.newSession()
new_result = new_session.sql("SELECT * FROM global_temp.aws")
new_result.show()


spark.stop()

