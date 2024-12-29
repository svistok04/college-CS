import subprocess

# Read the libraries in requirements.txt
with open('requirements.txt', 'r') as req_file:
    required_libs = {line.split('==')[0].strip() for line in req_file if line.strip()}

# Read currently installed libraries
installed_libs_output = subprocess.check_output(['pip', 'freeze'], text=True)
installed_libs = {line.split('==')[0].strip() for line in installed_libs_output.splitlines() if line.strip()}

# Find libraries to uninstall
extra_libs = installed_libs - required_libs

if extra_libs:
    print("Libraries to uninstall:", extra_libs)
    for lib in extra_libs:
        subprocess.run(['pip', 'uninstall', '-y', lib])
    print("Uninstallation complete.")
else:
    print("No extra libraries to uninstall.")
