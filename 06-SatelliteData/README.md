# Google Earth Engine

Date: September 30th, 2025

## Getting Started 

1. Go to https://earthengine.google.com 
2. Click `Get Started`  
3. Click `Create Project`  
4. Go to `Earth Engine / Configuration`
5. Register your Cloud project as `noncommercial`
Earth Engine is free of charge for students, faculty, or staff at an academic institution. 
6. Enable `Earth Engine API`


## Download 

1. Install Earth Engine Python API and `geemap`
   `pip install earthengine-api geemap`
2. Modify the initialization of the API by using your project ID. 
   
``` python
ee.Initialize(project='<project ID>')
```

3. Run ex.py

## Jupyterlab examples

Install and run `JupyterLab`
```
pip install jupyterlab
jupyter lab
```

Install 
```
pip install rasterio localtileserver osmnx 
```
   
## References
* https://github.com/giswqs/geebook/tree/master
* https://github.com/gee-community/geemap/tree/master/examples
* https://github.com/opengeos
* https://pygis.io/docs/a_intro.html




