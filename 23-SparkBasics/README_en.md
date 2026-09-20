# 03 · Spark I — DataFrame and SQL

We rewrite the `map→shuffle→reduce` distributed aggregation we hand-wrote in Week 2 as
`DataFrame` and `SQL` on a real engine, **Apache Spark** (local mode). This week's
deliverable is a **basic ETL pipeline** that turns the raw observation CSV into a clean
table. 

## What it covers

- **SparkSession**: local mode, and the partition distribution of `range`.
- **Extract**: explicit schema vs `inferSchema` — a comparison on reproducibility and
  performance, plus `to_timestamp` parsing.
- **Transform**: cleaning missing values and duplicates with `filter`,
  `dropDuplicates` and `withColumn` (narrow transformations).
- **Aggregation**: the `groupBy().agg()` result matches the serial pandas computation
  to within $10^{-6}$ (Spark's automatic partial aggregation).
- **Spark SQL**: a temp view plus `spark.sql` gives the same result as the DataFrame
  API (Catalyst), along with `join`, window functions and UDFs.
- **Lazy**: reading partial aggregate → Exchange (shuffle) → final aggregate in
  `explain()`.


## Where this sits in the closed-loop twin pipeline

It implements the **① ingest observations → ② align and aggregate in space-time**
stretch as a Spark ETL. It leads into Week 4's (Spark II) space-time aggregation and the
**M0 baseline** submission in Week 5.

