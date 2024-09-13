# https://www.kaggle.com/code/shivamaggarwal513/dl-ai-hand-signs-05-dataset-example
import numpy as np
import matplotlib.pyplot as plt
import os
import h5py

def load_dataset(data_path):
    train_dataset = h5py.File(os.path.join(data_path, 'train.h5'), 'r')
    test_dataset  = h5py.File(os.path.join(data_path, 'test.h5'), 'r')
    
    X_train = train_dataset['train_set_x'][:]
    y_train = train_dataset['train_set_y'][:]
    classes = train_dataset['list_classes'][:]
    
    X_test  = test_dataset['test_set_x'][:]
    y_test  = test_dataset['test_set_y'][:]
    classes = test_dataset['list_classes'][:]
    
    return X_train, y_train, X_test, y_test, classes


data_path  = './ex2/data'
X_train, y_train, X_test, y_test, classes = load_dataset(data_path)

print(f'number of training examples : {X_train.shape[0]}')
print(f'number of test examples     : {X_test.shape[0]}')
print(f'X_train : {type(X_train)} {X_train.shape}')
print(f'y_train : {type(y_train)} {y_train.shape}')
print(f'X_test  : {type(X_test)} {X_test.shape}')
print(f'y_test  : {type(y_test)} {y_test.shape}')
print(f'classes : {classes}')


plt.figure(figsize=(10, 10))

for i in range(25):
    ax = plt.subplot(5, 5, i + 1)
    plt.imshow(X_train[i])
    plt.title(classes[y_train[i]])
    plt.axis("off")

plt.show()