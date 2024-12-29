import pandas as pd
import matplotlib.pyplot as plt

# Load data
data = pd.read_csv('Scenariusz_1_Podnoszenie_telefonu.csv')

data['time_s'] = (data['timestamp_ms'] - data['timestamp_ms'].iloc[0]) / 1000
g = 9.8

stable_threshold = 0.08
floating_threshold = 9.72
going_up_threshold = 9.72
going_down_threshold = 9.88

data['motion'] = 'Stable'

for i in range(1, len(data)):
    current_accZ = data.loc[i, 'accZ']
    previous_motion = data.loc[i - 1, 'motion']

    if previous_motion == 'Stable':
        if current_accZ < going_up_threshold:
            data.loc[i, 'motion'] = 'Going Up'
        else:
            data.loc[i, 'motion'] = 'Stable'

    elif previous_motion == 'Floating':
        if current_accZ > going_down_threshold:
            data.loc[i, 'motion'] = 'Going Down'
        else:
            data.loc[i, 'motion'] = 'Floating'

    elif previous_motion == 'Going Up':
        if current_accZ < floating_threshold:
            data.loc[i, 'motion'] = 'Floating'
        else:
            data.loc[i, 'motion'] = 'Going Up'

    elif previous_motion == 'Going Down':
        if abs(current_accZ - g) <= stable_threshold:
            data.loc[i, 'motion'] = 'Stable'
        else:
            data.loc[i, 'motion'] = 'Going Down'

data['distance'] = 0.0
data['velocity'] = 0.0

for i in range(1, len(data)):
    dt = data.loc[i, 'time_s'] - data.loc[i - 1, 'time_s']
    acc_corrected = data.loc[i, 'accZ'] - g

    if data.loc[i, 'motion'] == 'Going Up':
        data.loc[i, 'velocity'] = data.loc[i - 1, 'velocity'] + acc_corrected * dt
        data.loc[i, 'distance'] = data.loc[i - 1, 'distance'] + data.loc[i, 'velocity'] * dt
    elif data.loc[i, 'motion'] == 'Going Down':
        data.loc[i, 'velocity'] = data.loc[i - 1, 'velocity'] + acc_corrected * dt
        data.loc[i, 'distance'] = data.loc[i - 1, 'distance'] + data.loc[i, 'velocity'] * dt
    else:
        data.loc[i, 'velocity'] = 0.0
        data.loc[i, 'distance'] = data.loc[i - 1, 'distance']

data.to_csv('motion_with_distance.csv', index=False)

plt.figure(figsize=(10, 6))
plt.plot(data['time_s'], data['distance'], color='green')
plt.xlabel('Time [s]')
plt.ylabel('Distance [m]')
plt.title('Position');
plt.grid()

plt.savefig('distance_over_time.png', bbox_inches='tight')
plt.show()
