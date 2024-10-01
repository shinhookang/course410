import requests
LAWD_CD = '11110'
DEAL_YMD= '202407'
# Read service key content from a file
# Modify 'mykey.txt' for your API key
with open('mykey.txt', 'r') as file:
    service_key = file.read()

url = \
'https://apis.data.go.kr/1613000/RTMSDataSvcAptRent/getRTMSDataSvcAptRent?serviceKey='+service_key \
    +'&LAWD_CD='+LAWD_CD \
    +'&DEAL_YMD='+DEAL_YMD
response = requests.get(url)

# Automatically decodes the content using the character encoding specified by the server (like utf-8)
print(response.text)
xml_data = response.text

# This returns the raw content of the response as bytes. 
# No decoding or conversion is done. 
# It’s useful when dealing with non-text responses, like images, files, or other binary data.
print(response.content)

# For text, decode the content using 'utf-8'
print(response.content.decode("utf-8"))


# Save the response content as a text file
with open('example.xml', 'w', encoding='utf-8') as file:
    file.write(xml_data) 

# Read XML content from a file
with open('example.xml', 'r') as file:
    xml_data = file.read()
 

# extract information from XML data, where you can find head and body tags
import xmltodict
all_data = xmltodict.parse(xml_data)

# Extract the body data
body_data = all_data.get('response', {}).get('body', {}).get('items', {})

i = 0
for item in body_data['item']:
    i = i+1
    print(i,item)

items = body_data['item']

# convert it to Pandas DataFrame
import pandas as pd
df = pd.DataFrame.from_dict(items) 
print(df)

print(df.columns)

print(df[['aptNm','buildYear','deposit']])

  