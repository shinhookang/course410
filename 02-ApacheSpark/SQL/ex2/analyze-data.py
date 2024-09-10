# Import necessary modules
from pyspark.sql import SparkSession
from pyspark.sql.functions import avg, max, min, count

# Create a Spark session
spark = SparkSession.builder.appName("DataAnalysisExample").getOrCreate()

# Read data from a CSV file into a DataFrame
srcdir = './SQL/ex2/'
df = spark.read.csv(srcdir+"data/employees.csv", header=True, inferSchema=True) #infers datatype

# Show the first few rows of the DataFrame
df.show()

# Print the schema of the DataFrame
df.printSchema()

# Select specific columns
df.select("name", "age", "salary").show()

# Filter rows where the salary is greater than 60,000
df.filter(df["salary"] > 60000).show()

# Group by the department and calculate the average salary per department
# agg(): Apply one or more aggregate functions on the selected columns.
# groupBy(): Before applying the aggregate functions, 
#           we grouped the data by department to perform the aggregations within each group.
df.groupBy("department").agg(avg("salary").alias("average_salary")).show()

# Find the maximum and minimum salary in the company
df.select(max("salary").alias("max_salary"), min("salary").alias("min_salary")).show()

# Count the number of employees in each department
df.groupBy("department").agg(count("name").alias("employee_count")).show()

# Sort the DataFrame by salary in descending order
df.orderBy(df["salary"].desc()).show()