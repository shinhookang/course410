import h5py

# Write a new HDF5 file with metadata
ifile = 'ex3.h5'
with h5py.File(ifile, 'w') as f:    
    # Create a new file named 'ifile' and write a list to it.
    data = [1, 2, 3, 4, 5]
    dset = f.create_dataset('my_dataset', data=data)

    # Add an attribute to the dataset
    dset.attrs['description'] = 'This is a test dataset.'
    dset.attrs['version'] = 1.0

    