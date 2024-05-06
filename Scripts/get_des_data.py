import requests
import json

# URL for data and descriptor
data_url = "http://onem2m.iiit.ac.in:443/~/in-cse/in-name/AE-SR/SR-AQ/SR-AQ-KH95-00/Data/la"
descriptor_url = "http://onem2m.iiit.ac.in:443/~/in-cse/in-name/AE-SR/SR-AQ/SR-AQ-KH95-00/Descriptor/la"

# Headers for the requests
headers = {
    'X-M2M-Origin': 'iiith_guest:iiith_guest',
    'Content-Type': 'application/json'
}

# Make the GET request for data
response_data = requests.get(data_url, headers=headers)

# Make the GET request for descriptor
response_descriptor = requests.get(descriptor_url, headers=headers)

# Check if both requests were successful (status code 200)
if response_data.status_code == 200 and response_descriptor.status_code == 200:
    # Parse the JSON response for data
    data = json.loads(response_data.text)
    
    # Parse the JSON response for descriptor
    descriptor_data = json.loads(response_descriptor.text)

    # Extract the "con" value from data
    con_value = data.get("m2m:cin", {}).get("con", "Value not found")

    # Extract the "Data String Parameters" from the descriptor
    descriptor_con = descriptor_data.get("m2m:cin", {}).get("con", "")
    data_string_parameters = descriptor_con.split("Data String Parameters")[1].split("\n")[0].strip().strip("\"")
    data_string_parameters = data_string_parameters[6:-3]

    des = eval(data_string_parameters)
    dat = eval(con_value)
    # print(dat)
    # print(des)
    dic = {}
    for key,value in zip(des,dat):
        dic[key]= value
    for i in dic:
        print(f"{i} : {dic[i]}")
    # print(dic)
    temp=dic['Temperature']
    # print(temp)
else:
    print("One or both requests failed with status codes: Data -", response_data.status_code, "Descriptor -", response_descriptor.status_code)
