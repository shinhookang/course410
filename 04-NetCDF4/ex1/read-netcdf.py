import netCDF4 as nc

# Open the NetCDF file
ifile = 'ex1.nc'
dataset = nc.Dataset(ifile, 'r')

# Explore the dataset
print(dataset)

# Explore the dimensions in the dataset
print(dataset.dimensions)

# Explore the variables in the dataset
print(dataset.variables)

# Access a specific variable
temperature = dataset.variables['temperature']
print(temperature[:])  # Print all temperature data

# Access a specific time slice
print(temperature[0, :, :])  # Access data for the first time index

# Close the dataset
dataset.close()