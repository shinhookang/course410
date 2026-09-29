# 04 · Spark II — Space-Time Aggregation of Observations

We **fold** Week 3's cleaned observations (ETL) **into a grid along the time and space
axes**, aligning scattered observations into a regular **(grid cell × time window)
spatiotemporal cube**. This week's deliverable is the **time and space aggregation results
plus a persistence baseline**.  

## What it covers

- **Time aggregation**: `date_trunc` (resampling by day and hour) and the
  `F.window("ts", "3 hours")` tumbling window — verified to match a manual integer bin to
  within $10^{-6}$.
- **Spatial aggregation**: floor gridding (`gi, gj, grid_id` at 0.5° resolution), with the
  latitude gradient confirmed on the grid map through a regression slope.
- **The spatiotemporal cube**: the result of `groupBy("grid_id", "tbin")` matches the serial
  pandas computation; spatial snapshots show the latitude gradient plus the day/night
  structure.
- **Window functions**: a **persistence** baseline from a time-ordered `lag`, with its RMSE
  improvement over climatology confirmed numerically. Plus a three-point moving average.
- **A complete grid**: cross/left join + `coalesce` to expose and fill the holes, leaving
  zero missing values.
 

## Where this sits in the closed-loop twin pipeline

It completes the **② align and aggregate in space-time** stretch — turning scattered
observations (①) into the regular grid that forecasting and scoring use. It leads into Week
5's **OpenAPI ingestion (①) and M0 baseline submission**, and the cube stays on as the shared
input and scoring grid for ML (M1), the physical simulator (M2) and the hybrid twin (M3).

 