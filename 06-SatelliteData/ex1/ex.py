
import ee, geemap
ee.Initialize()

# MODIS NDVI
col = ee.ImageCollection("MODIS/006/MOD13A2") \
          .filterDate("2020-07-01", "2020-07-31") \
          .select("NDVI")

image = col.first()

roi = ee.Geometry.Rectangle([124.0, 33.0, 132.0, 43.0])

# 시각화 스타일 정의
vis_params = {
    "min": 0,
    "max": 9000,
    "palette": ["white", "green"]
}

vis_image = image.visualize(**vis_params)

ofile = "modis_ndvi.tif"
geemap.ee_export_image(
    vis_image,
    filename=ofile,
    scale=1000,
    region=roi
)

ofile2 = 'modis_ndvi.jpg'
from PIL import Image
im = Image.open(ofile)
im.convert("RGB").save(ofile2, "JPEG")
