import requests
import json

# URL for the descriptor data
descriptor_url = "http://onem2m.iiit.ac.in:443/~/in-cse/in-name/AE-AQ/AQ-KH00-00/Descriptor/la"

# Headers for the request
headers = {
    'X-M2M-Origin': 'iiith_guest:iiith_guest',
    'Content-Type': 'application/json'
}

# Make the GET request for the descriptor
response_descriptor = requests.get(descriptor_url, headers=headers)

# Check if the request was successful (status code 200)
if response_descriptor.status_code == 200:
    # Parse the JSON response
    descriptor_data = json.loads(response_descriptor.text)

    # Extract the "Data String Parameters"
    data_string_parameters = descriptor_data["m2m:cin"]["con"].split("Data String Parameters")[1].split("\n")[0].strip().strip("\"")

    # Print the "Data String Parameters"
    print("Data String Parameters:", data_string_parameters)
else:
    print("Request failed with status code:", response_descriptor.status_code)
