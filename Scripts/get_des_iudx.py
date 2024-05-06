import requests

url = "https://iudx-rs-onem2m.iiit.ac.in/resource/descriptor/AQ-PH03-00"

payload = {}
headers = {}

response = requests.request("GET", url, headers=headers, data=payload)

print(response.text)