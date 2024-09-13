import xarray as xr

# Open a NetCDF file using Xarray
ifile = 'ex2.nc'
dataset = xr.open_dataset(ifile)

# Explore the dataset
print(dataset)

# Access coordinates
print(dataset['times'])
print(dataset['locations'])

# Access variables in the dataset
temperature = dataset['temperature']
print(temperature)
print(temperature[:].data)

# Access a specific time slice
temp_at_time = temperature.sel(times=1)
print(temp_at_time[:].data)

# Convert to a pandas DataFrame if needed
df = temperature.to_dataframe()
print(df.head())