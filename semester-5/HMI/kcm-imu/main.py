import requests
import time
import csv

url = "http://192.168.0.11:8080/get?"

scenarios = [
    (['accZ'], "Scenariusz_1_Podnoszenie_telefonu"),
    (['magX'], "Scenariusz_2_Obracanie_telefonu"),
    (['accX', 'accY', 'gyrZ'], "Scenariusz_3_Kombinacja")
]

current_scenario = 2

sensors, scenario_name = scenarios[current_scenario]

sampling_frequency = 0.02


file_name = f"{scenario_name}.csv"


with open(file_name, 'w', newline='') as csvfile:
    csvwriter = csv.writer(csvfile)

    csvwriter.writerow(['timestamp_ms'] + sensors)

    try:
        while True:

            response = requests.get(url + '&'.join(sensors), timeout=5)
            data = response.json()


            timestamp_ms = int(time.time() * 1000)


            row = [timestamp_ms]
            for sensor in sensors:
                sensor_value = data['buffer'][sensor]['buffer'][0]
                row.append(sensor_value)


            csvwriter.writerow(row)
            print(row)


            time.sleep(sampling_frequency)

    except requests.RequestException as e:
        print(f"HTTP Error: {e}")
    except KeyError as e:
        print(f"Key Error: {e}")
    except KeyboardInterrupt:
        print("\nRecording stopped")

print(f"Finished recording for {scenario_name}")
