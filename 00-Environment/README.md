# Windows system 

## Install WSL2 

1. Install Windows Terminal from Microsoft Store.

2. WSL2 
Run Termnial in administrator mode.
(Windows + S, search Terminal, Right-click to run in administrator mode.)
Type the following commands:
```
$ wsl —install 
$ wsl --set-default-version 2
```

3. Install Ubuntu Linux from Microsoft Store
ID: kus2024, PASSWD: kus2024

4. Check the WSL version 
```
$ wsl -l -v 
```
If version is 1, then try 
```
$ wsl --set-version Ubuntu 2
$ wsl -l -v 
```

## Install Python3

1. Update Ubuntu distribution
```
sudo apt update
sudo apt upgrade
```

2. Upgrade Python
```
sudo apt upgrade python3
```

3. Install `pip` and `venv`
```
sudo apt install python3-pip
sudo apt install python3-venv
python3 -m pip install --upgrade pip
```

## Install Open JDK 11
```bash 
sudo apt install openjdk-11-jdk
```

Check the `java` version 
```bash 
java --version
```

Find `JAVA_HOME location`
```bash 
dirname $(dirname $(readlink -f $(which java)))
```

# Mac system

## Install Homebrew 
```bash 
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

## Install Open JDK 11
```bash 
brew install openjdk@11
```
Check the `java` version 
```bash 
java --version
```

# Create a virtual environment
Create a virtual environment. `python -m venv .venv`

Activate the virtual environment. `source .venv/bin/activate`

Deactivate the virtual environment. `deactivate`




<!-- ## Reference 

[Setting up a Single Node Cluster](https://hadoop.apache.org/docs/stable/hadoop-project-dist/hadoop-common/SingleCluster.html#Standalone_Operation) -->
