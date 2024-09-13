import h5py
import numpy as np

# Write a new HDF5 file
ifile = 'ex2.h5'
with h5py.File(ifile, 'w') as f:    

    # Create Groups
    grp_text = f.create_group('text')
    grp_number = f.create_group('number')
    
    # Create datasets within the groups
    grp_text.create_dataset('dataset1', data=['hdf5', 'is', 'great'])
    grp_text.create_dataset('dataset2', data=['a', 'b', 'c'])
    grp_number.create_dataset('dataset3', data=[4, 5, 6])
    grp_number.create_dataset('dataset4', data=np.array([[1,2,3],[4,5,6]]))
    
    