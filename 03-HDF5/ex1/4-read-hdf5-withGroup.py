import h5py
import numpy as np

# Write a new HDF5 file
ifile = 'ex2.h5'
# f = h5py.File(ifile, 'r')
with h5py.File(ifile, 'r') as f:    

    # List all groups
    print(list(f.keys()))  # Output: ['number', 'text']

    grp_text = f['text']
    grp_number = f['number']
    print(list(grp_text.keys()))  # Output: ['dataset1', 'dataset2']
    print(list(grp_number.keys()))  # Output: ['dataset3', 'dataset4']

    # Access the dataset within the group 
    # dataset1 = grp_text['dataset1'] # same 
    dataset1 = f['text/dataset1']    
    dataset2 = f['text/dataset2']
    dataset3 = f['number/dataset3']
    dataset4 = f['number/dataset4']

    print(dataset1[:]) # b stands for bytes object
    print(dataset2[:])
    print(dataset3[:])
    print(dataset4[:])
