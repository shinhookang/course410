import xarray as xr
import numpy as np

# Create a new dataset
times = [0, 1, 2]  # Example time values
locations = [10, 20, 30, 40]  # Example location values
temperature = np.random.rand(3, 4)  # Random data for temperature


# Xarray can open NetCDF files and load them into a Dataset, 
# which behaves like a dictionary containing multiple DataArrays (variables).

# Create an Xarray DataArray
xr_temperature = xr.DataArray(temperature, dims=["times", "locations"],
                           coords={"times": times, "locations": locations},
                           attrs={"units": "Celsius"})

# Create an Xarray Dataset to hold multiple DataArrays
dataset = xr.Dataset({"temperature": xr_temperature})

# Save the dataset to a NetCDF file
dataset.to_netcdf('ex2.nc')

# Verify the file was written
print(xr.open_dataset('ex2.nc'))