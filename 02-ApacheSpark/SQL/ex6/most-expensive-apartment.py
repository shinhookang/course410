from pyspark.sql import SparkSession
from pyspark.sql import functions as func
from pyspark.sql.window import Window 
from pyspark.sql.types import StructType, StructField, IntegerType, StringType

spark = SparkSession.builder.appName("MostExpensiveApartment").getOrCreate()

# Area,Size,Year,Month,Price
schema = StructType([ \
                     StructField("area", StringType(), True), \
                     StructField("size", StringType(), True), \
                     StructField("year", IntegerType(), True), \
                     StructField("month", IntegerType(), True), \
                     StructField("price", IntegerType(), True)])

# srcdir = './ex7/'
srcdir = './'
df = spark.read.schema(schema) \
    .option("sep", ",") \
    .option("header", "true") \
    .csv(srcdir + "data/PrivateApartmentSalesPriceTrends-20240630.csv")
df.show()

# group by area
df_cnt = df.groupBy("area").count()
df_cnt.show()

# sort by price
df_sort = df.sort(func.col("price").desc())
df_sort.show()
df_top = df_sort.sort(func.col("price").desc()).first()
print(df_top[0] + " has the most expensive apartment with " + str(df_top["price"]))

# Apartments in Seoul are expensive
df_Seoul = df.filter(df["area"] == "Seoul")
df_Seoul.show()




