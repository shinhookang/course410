import h5py
import numpy as np

# Write a new HDF5 file
ifile = 'ex3.h5'
# f = h5py.File(ifile, 'r')
# f.close()
with h5py.File(ifile, 'r') as f:    

    # List all groups
    print(list(f.keys()))  # Output: ['date', 'products']

    cdate = f['date']
    print(cdate[:]) # b stands for bytes object
    
    # Read the attributes
    for attr_name, attr_value in f.attrs.items():
        print(f"Attribute '{attr_name}': {attr_value}")

    products = f['products']
    print(list(products.keys())) 
    # Output: ['apple', 'dried pepper', 'galic', 'green onion', 'napa cabbage', 'onion', 'pear', 'potato', 'radish']

    # Access the dataset within the group 
    potato = products['potato']
    pepper = products['dried pepper']
    gonion = products['green onion']
    galic = products['galic']
    radish = products['radish']
    pear = products['pear']
    napa = products['napa cabbage']
    apple = products['apple']
    onion = products['onion']

    # Read the attributes
    for attr_name, attr_value in products.attrs.items():
        print(f"Attribute '{attr_name}': {attr_value}")

    print('potato: \n', potato[:])
    print('pepper: \n', pepper[:])
    print('green onion: \n', gonion[:])
    print('galic: \n', galic[:])
    print('radish: \n', radish[:])
    print('pear: \n', pear[:])
    print('napa cabbage: \n', napa[:])
    print('apple: \n', apple[:])
    print('onion: \n', onion[:])
