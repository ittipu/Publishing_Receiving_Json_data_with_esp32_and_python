Description:

This project works for receiving json data from mqtt client (we use python "paho") and 
deserialize the data. Also sending json data from esp32 to python client.


How it's work:
	1. We use ArduinoJson library for serialize-deserialize json data.
	2. Use dummy data send to python client and use json.loads() method
	   to use those data.

	3. Python client publish dummy data like timestamp, data to esp32 client.



