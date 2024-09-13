import h5py

# Write a new HDF5 file with metadata
ifile = 'ex3.h5'
# f = h5py.File(ifile, 'r')
with h5py.File(ifile, 'r') as f:    

    # List all groups
    print(list(f.keys()))  # Output: ['my_dataset']

    dset = f['my_dataset']
    # print(dset[:])

    # Read the attributes
    for attr_name, attr_value in dset.attrs.items():
        print(f"Attribute '{attr_name}': {attr_value}")

    