def read_price():
    # Import necessary modules
    from pyspark.sql import SparkSession

    # Create a Spark session
    spark = SparkSession.builder.appName("DataAnalysisExample").getOrCreate()

    # Read data from a CSV file into a DataFrame
    srcdir = './'
    df = spark.read.csv(srcdir+"data/salesprice.csv", header=True, inferSchema=True) #infers datatype

    # Show the first few rows of the DataFrame
    df.show(df.count())

    # Print the schema of the DataFrame
    df.printSchema()

    # convert to numpy array 
    pd = df.toPandas()
    cdate = pd['date'].astype(str).to_numpy()
    potato = pd['potato'].to_numpy()
    pepper = pd['dried pepper'].to_numpy()
    gonion = pd['green onion'].to_numpy()
    galic = pd['galic'].to_numpy()
    radish = pd['radish'].to_numpy()
    pear = pd['pear'].to_numpy()
    napa = pd['napa cabbage'].to_numpy()
    apple = pd['apple'].to_numpy()
    onion = pd['onion'].to_numpy()

    return (cdate,potato,pepper,gonion,galic,radish,pear,napa,apple,onion)


cdate,potato,pepper,gonion,galic,radish,pear,napa,apple,onion = read_price()


# - - - - - Write a new HDF5 file - - - - - 
import h5py
import numpy as np
ifile = 'ex3.h5'
