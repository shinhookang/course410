import h5py

ifile = 'ex1.h5'
# f = h5py.File(ifile, 'r')
with h5py.File(ifile, 'r') as f:
    # Access the dataset
    dataset = f['my_dataset']
    print(dataset[:])  # Print the entire dataset as a NumPy array