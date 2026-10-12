# 06 · Scientific Data Formats — NetCDF · Zarr · Xarray

This week we take the space-and-time data cube from Week 4 and the observations we collected in Week 5. We put them into an Xarray Dataset, which is a multidimensional array with labels. The labels say what the data means, so the data explains itself. Then we save it in standard science file formats. At the end of this week you will have a Dataset with dimensions, coordinates and attrs, saved as NetCDF and Zarr files. This is the "storage" step of our data pipeline.


## What it covers

- **Why labelled arrays**: the fragility of numpy integer indexing (memorising axes and coordinates, silent bugs) versus xarray's `.sel` label selection. Building a synthetic spatiotemporal Dataset (`time × lat × lon`, variables `t2m`, `rh`, `wspd`) — dims/coords/attrs and the Climate and Forecast (CF) conventions.
- **Label-based selection**: `.isel` (integer), `.sel` (label), `.interp` (interpolation), `.where` (masking), and slicing in time and space.
- **Label-aware aggregation**: `groupby("time.hour")` (peak at 15:00), `resample("1D")` (0.4 °C/day), `mean("time")` (latitude −1.8 °C per °N) and deseasonalising (anomalies) — recovering the planted structure numerically.
- **NetCDF = HDF5**: `to_netcdf`/`open_dataset`, CF attrs (units, Conventions). Inspecting the file's insides (datasets and attributes) and the HDF5 magic number directly with `h5py`. Decoding the CF time encoding.
- **Zarr**: chunked storage with `to_zarr` (zarr v3, `consolidated=False`), a NetCDF vs Zarr comparison (chunking, parallelism, cloud), a chunk-layout visualisation and the JSON metadata.
- **Size and integrity**: a bar chart of raw vs NetCDF vs Zarr storage size (plus compression), and round-trip integrity verified with `xr.testing.assert_allclose` and SHA-256 checksums (both formats lossless).

## Where this sits in the closed-loop twin pipeline

The **storage layer** — turning ingested (①) and aligned (②) observations into a storable, shareable, self-describing Dataset. The **chunks** defined here are what Week 7 (Xarray + Dask) consumes as its unit of parallel computation, and the Dataset feeds straight into Week 8's **observation-driven ML** as input features.

 