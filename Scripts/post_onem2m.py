import time
import random
import requests

# WiFi Configuration (not required for Python script)
# Define NTP server and other constants
ntp_server = "pool.ntp.org"
CSE_IP = "dev-onem2m.iiit.ac.in"
CSE_PORT = 443
HTTPS = False
OM2M_ORGIN = "wdmon@20:gpod@llk4"
OM2M_MN = "/~/in-cse/in-name/"
OM2M_AE = "AE-WM/WM-WD"
OM2M_DATA_CONT = "WM-WD-PL00-00/Data"

# Function to get current epoch time
def get_epoch_time():
    return int(time.time())

# Function to send data to server
def send_data(temp, rh, i):
    data = f"[{temp}, {rh}]"
    server = "http"
    if HTTPS:
        server += "s"
    server += f"://{CSE_IP}:{CSE_PORT}{OM2M_MN}"

    url = server + OM2M_AE + "/" + OM2M_DATA_CONT
    headers = {
        "X-M2M-Origin": OM2M_ORGIN,
        "Content-Type": "application/json;ty=4",
        "Content-Length": "100",
        "Connection": "close"  # Debugging header
    }

    req_data = {
        "m2m:cin": {
            "con": data,
            "rn": f"cin_{i}",
            "cnf": "text"
        }
    }

    print("Server URL: " + url)
    print("Request Data: " + str(req_data))

    response = requests.post(url, json=req_data, headers=headers)
    print(response.status_code)
    response.close()

# Main loop
i = 0
while True:
    epoch_time = get_epoch_time()
    print("Epoch Time: ", epoch_time)

    temp = random.randint(27, 48)
    rh = random.randint(60, 85)
    time.sleep(1)

    send_data(temp, rh, i)
    i += 1
    time.sleep(1)
