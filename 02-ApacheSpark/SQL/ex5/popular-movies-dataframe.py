from pyspark.sql import SparkSession
from pyspark.sql import functions as func
from pyspark.sql.types import StructType, StructField, IntegerType, LongType, StringType

spark = SparkSession.builder.appName("PopularMovies").getOrCreate()

# Create schema when reading u.data
# user id | item id | rating | timestamp
schema = StructType([ \
                     StructField("userID", IntegerType(), True), \
                     StructField("itemID", IntegerType(), True), \
                     StructField("rating", IntegerType(), True), \
                     StructField("timestamp", LongType(), True)])

# Load up movie data as dataframe
# Adjust srcdir to your local directory. 
srcdir = './ex6/'
df = spark.read.option("sep", "\t").schema(schema).csv(srcdir + "ml-100k/u.data")

# Count how many people have written reviews each movie.
df_itemID = df.groupBy("itemID").count()
df_itemID.show()

# func.desc() is a method used to define the sorting order for a DataFrame column in descending order.
topviewed_itemIDs = df_itemID.orderBy(func.desc("count"))

# Grab the top 10
topviewed_itemIDs.show(20)


# Repalce itemID with movie name
import codecs
# The codecs module in Python provides a way to encode and decode various types of character data
# line = '1|Toy Story (1995)|01-Jan-1995||http://us.imdb.com/M/title-exact?Toy%20Story%20(1995)|0|0|0|1|1|1|0|0|0|0|0|0|0|0|0|0|0|0|0'
def GetAllMovieTitle():
    movieTitles = {}
    with codecs.open(srcdir + "ml-100k/u.item", "r", encoding='ISO-8859-1', errors='ignore') as f:
        for line in f:
            fields = line.split('|')
            movieTitles[int(fields[0])] = fields[1]
    return movieTitles
movieTitles = GetAllMovieTitle() # dictionary 

def GetMovieTitle(key):
    return movieTitles[key]

# Register the function as a UDF
GetMovieTitle_udf = func.udf(GetMovieTitle, StringType()) #output type

# Add a new column using the UDF
topviewed_movies = topviewed_itemIDs.withColumn('movie title', GetMovieTitle_udf( func.col("itemID")  ) )
topviewed_movies.show()

# Stop the session
spark.stop()
