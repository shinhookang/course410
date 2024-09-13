import netCDF4 as nc
import numpy as np

# Create a new NetCDF file
ofile = 'ex1.nc'
dataset = nc.Dataset(ofile, 'w', format='NETCDF4')

# Define dimensions
time_dim = dataset.createDimension('time', 3)  # 3 time steps
location_dim = dataset.createDimension('location', 4)  # 4 locations

# Define variables in a netCDF
# Details can be found https://unidata.github.io/netcdf4-python/ 
times = dataset.createVariable('time', 'f4', ('time',)) #  (32-bit floating point)
locations = dataset.createVariable('location', 'f4', ('location',))
temperature = dataset.createVariable('temperature', 'f4', ('time', 'location'))

# Write data to variables
times[:] = [0, 1, 2]  # Example time values
locations[:] = [10, 20, 30, 40]  # Example location values
temperature[:, :] = np.random.rand(3, 4)  # Random data for temperature

# Add metadata
temperature.units = 'Celsius'

# Close the file
dataset.close()

# Verify the file was written
ifile = ofile
ds = nc.Dataset(ifile, 'r')
print(ds)
ds.close()