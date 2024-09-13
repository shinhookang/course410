import h5py

# Write a new HDF5 file
ifile = 'ex1.h5'
with h5py.File(ifile, 'w') as f:    
    # Create a new file named 'ifile' and write a list to it.
    data = [1, 2, 3, 4, 5]
    dset = f.create_dataset('my_dataset', data=data)

    