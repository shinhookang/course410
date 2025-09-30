import cudf

# object creation
s = cudf.Series([1, 2, 3, None, 4])

df = cudf.DataFrame(
    {
        "a": list(range(20)),
        "b": list(reversed(range(20))),
        "c": list(range(20)),
    } )
df
df.head(5)
df.tail(10)


import pandas as pd
pdf = pd.DataFrame({"a": [0, 1, 2, 3], "b": [0.1, 0.2, None, 0.3]})
gdf = cudf.DataFrame.from_pandas(pdf)
gdf

gdf.sort_values(by="b")

# select columns
pdf["a"]
gdf["a"]

# Selecting Rows by Label#
gdf.loc[2:5, ["a", "b"]]

# Selecting Rows by Position
gdf.iloc[0]
gdf.iloc[0:3,0:2]

# Boolean Indexing#
gdf[gdf.b > 0.2]
gdf.query("b == 0.3")

# fill missing data
s.fillna(999)

# Multiindex
# group hierarchically
arrays = [["a", "a", "b", "b"], [1, 2, 3, 4]]
zip(*arrays)
tuples = list(zip(*arrays))
idx = cudf.MultiIndex.from_tuples(tuples)
idx

import cupy as cp
gdf1 = cudf.DataFrame(
    {"first": cp.random.rand(4), "second": cp.random.rand(4)}
)
gdf1.index = idx
gdf1


gdf2 = cudf.DataFrame(
    {"first": cp.random.rand(4), "second": cp.random.rand(4)}
).T
gdf2.columns = idx
gdf2

# - - - Apply map - - -
#Applying functions to a Series.
def add_ten(num):
    return num + 10

df["a"].apply(add_ten)

# - - - Histogramming - - -
#Counting the number of occurrences of each unique value of variable.

df.a
df["a"].value_counts()


# - - - String methods - - - 
s = cudf.Series(["A", "B", "C", "Aaba", "Baca", None, "CABA", "dog", "cat"])
s.str.lower()


# - - - Convert to PANDAS - - -
df.head().to_pandas()

# - - - Convert to NUMPY - - - 
df.head().to_numpy()

# - - - SAVE and LOAD CSV- - - 
df.to_csv("foo.csv", index=False)

df = cudf.read_csv("foo.csv")
