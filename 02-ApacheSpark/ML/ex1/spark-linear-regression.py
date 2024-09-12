from __future__ import print_function

from pyspark.ml.regression import LinearRegression
from pyspark.ml.linalg import Vectors
from pyspark.sql import SparkSession
from pyspark.sql import functions as func
from pyspark.sql.window import Window 
from pyspark.sql.types import StructType, StructField, IntegerType, StringType
from pyspark.ml.feature import VectorAssembler

spark = SparkSession.builder.appName("LinearRegression").getOrCreate()

# Create DataFrame for HIV
schema = StructType([ \
                     StructField("year", IntegerType(), True), \
                     StructField("npatients(man)", IntegerType(), True), \
                     StructField("npatients(woman)", IntegerType(), True), \
                     StructField("death(man)", IntegerType(), True), \
                     StructField("death(woman)", IntegerType(), True), \
                     StructField("survivors(man)", IntegerType(), True), \
                     StructField("survivors(woman)", IntegerType(), True)])

# srcdir = './ML/ex1/'
srcdir = './'
df = spark.read.schema(schema) \
    .option("sep", ",") \
    .option("header", "false") \
    .csv(srcdir + "data/HIV_20221231.csv")
df.show()

# extract data from 1996~2014
df_truncated = df[df['year'] < 2015]
df_truncated.show()


# extract year and npatients(man)
df_yearnpatients = df_truncated.select("year","npatients(man)")
df_yearnpatients.show()

# - - - numpy array - - - 
x = df_yearnpatients.select("year").toPandas().to_numpy().squeeze()
y = df_yearnpatients.select("npatients(man)").toPandas().to_numpy().squeeze()
import matplotlib.pyplot as plt
import numpy as np
# plt.plot(x, y, 'o--', color='blue', alpha=0.3)
xnormal = (x - np.mean(x))/10.
ynormal = (y - np.mean(y))/400.
# plt.plot(xnormal, ynormal, 'o--', color='blue', alpha=0.3)
# plt.show()


# - - - Create Panda DataFrame using normalized x and y values - - - 
# x: features
# y: labels
xy = np.array([xnormal,ynormal]).transpose()
import pandas as pd
pandas_df = pd.DataFrame(xy, columns=['features', 'label'])
# pandas_df

# Spark DataFrame
df = spark.createDataFrame(pandas_df)
df.show()

 
# Step 3: Use VectorAssembler to convert the float column into a vector
# assembler = VectorAssembler(inputCols=["label"], outputCol="label-vector")
assembler = VectorAssembler(inputCols=["features"], outputCol="features-vector")

# Step 4: Transform the DataFrame to add the vector column
df_with_vector = assembler.transform(df)
df_with_vector.show()

# extract features and label-vector
df_data = df_with_vector.select("features-vector","label")
df_data.show()


# Let's split our data into training data and testing data
training_data, test_data = df_data.randomSplit([0.8, 0.2])



# Now create our linear regression model
# https://spark.apache.org/docs/latest/api/python/reference/api/pyspark.ml.regression.LinearRegression.html
# The objective of the ElasticNet is to minimize the following loss function:
# \text{min} \left( ||y - X \beta||_2^2 + \lambda_1 ||\beta||_1 + \lambda_2 ||\beta||_2^2 \right)
# elasticNetParam = 0: Pure L2 regularization (Ridge).
# elasticNetParam = 1: Pure L1 regularization (Lasso).
#
# regParam=0.1: This specifies the strength of the regularization.
# A lower value like 0.1 applies relatively weak regularization, meaning it penalizes large coefficients slightly.
lrclass = LinearRegression(featuresCol="features-vector", labelCol="label", maxIter=100, regParam=0.1, elasticNetParam=0.1)
# lrclass = LinearRegression(featuresCol="features", labelCol="label-vector", maxIter=200, loss='squaredError')




# Train the model using our training data
# Failed to load implementation from:dev.ludovic.netlib.blas.JNIBLAS
#  If native libraries are not properly configured in the system,
#  the Java implementation (javaBLAS) will be used as fallback option
model = lrclass.fit(training_data)

# print("Coefficients: %s" % str(model.coefficients))
# print("Intercept: %s" % str(model.intercept))
# model.summary.residuals.show()

# Now see if we can predict values in our test data.
# Generate predictions using our linear regression model for all features in our
# test dataframe:
fullPredictions = model.transform(test_data).cache()
fullPredictions.show()

fullPredictions = model.transform(df_data).cache()
fullPredictions.show()

# extract prediction, yhat
yhatnormal = fullPredictions.select("prediction").toPandas().to_numpy().squeeze()

# recover y from normalization
# ynormal = (y - np.mean(y))/400.
yhat = 400*yhatnormal + np.mean(y)
plt.plot(x, y, 'o--', color='blue', alpha=0.3)
plt.plot(x, yhat, 'x-.', color='red', alpha=0.3)
plt.show()


 
# Stop the session
spark.stop()
